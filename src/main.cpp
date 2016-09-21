// Controller/Gateway

// Let the IDE point to the Souliss framework
#include "SoulissFramework.h"

// Configure the framework
#include "bconf/StandardArduino.h"				// Use a standard Arduino
#include "conf/usart.h"							// USART RS485

/*************/
// Use the following if you are using an RS485 transceiver with
// transmission enable pin, otherwise delete this section.
//
#define USARTDRIVER_INSKETCH
#define USART_TXENABLE			1
#define USART_TXENPIN			3
#define USARTDRIVER				Serial
/*************/

// Include framework code and libraries
#include <SPI.h>
#include <Souliss.h>

#include "../../ControllerGateway/include/constants.h"
#include "../../ControllerGateway/include/types.h"

void setup()
{
	Initialize();

	// Set network parameters
	SetAddress(RS485_GATEWAY_ADDR, VNET_SUBNET_MASK, RS485_GATEWAY_ADDR);

	vNet_SetMulticastGroup(BUTTONS_PANEL_MCAS_ADDR, 0);

	Set_T11(GATEWAY_LIGHT_1_SLOT);
	Set_T11(GATEWAY_LIGHT_2_SLOT);

	pinMode(13, OUTPUT); // Debug

}

void loop()
{
	// Here we start to play
	EXECUTEFAST() {
		UPDATEFAST();

		// Execute every 510ms the logic, the command to open and close the garage door
		// cames directly from SoulissApp or the push-button located on the other node
		FAST_50ms() {

			boolean button_pressed = false;
			button_address button;
			uint8_t len;
			if (subscribedata(BUTTON_PUSHED_EVENT, (uint8_t*)&button, &len)) {
				if (button.button_panel_addr == RS485_BUTTONS_PANEL_1_ADDR && button.button == 1) {
					mInput(GATEWAY_LIGHT_1_SLOT) = Souliss_T1n_ToggleCmd;
					button_pressed = true;
				}
				if (button.button_panel_addr == RS485_BUTTONS_PANEL_1_ADDR && button.button == 2) {
					mInput(GATEWAY_LIGHT_2_SLOT) = Souliss_T1n_ToggleCmd;
					button_pressed = true;
				}
			}

			Logic_T11(GATEWAY_LIGHT_1_SLOT);
			Logic_T11(GATEWAY_LIGHT_2_SLOT);

			if (button_pressed && button.button_panel_addr == RS485_BUTTONS_PANEL_1_ADDR && button.button == 1) {
				uint8_t cmd;
	            if(mOutput(GATEWAY_LIGHT_1_SLOT))
	                cmd = Souliss_T1n_OnCmd;
	            else
	                cmd = Souliss_T1n_OffCmd;
				Send(RS485_RELAYS_1_ADDR, RELAYS_MODULE_RELAY_1_SLOT, cmd);
				Send(RS485_BUTTONS_PANEL_1_ADDR, BUTTONS_PANEL_LED_1_SLOT, cmd);
				//digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
			}
			if (button_pressed && button.button_panel_addr == RS485_BUTTONS_PANEL_1_ADDR && button.button == 2) {
				uint8_t cmd;
	            if(mOutput(GATEWAY_LIGHT_2_SLOT))
	                cmd = Souliss_T1n_OnCmd;
	            else
	                cmd = Souliss_T1n_OffCmd;
				Send(RS485_BUTTONS_PANEL_1_ADDR, BUTTONS_PANEL_LED_2_SLOT, cmd);
				Send(RS485_RELAYS_1_ADDR, RELAYS_MODULE_RELAY_2_SLOT, cmd);
				//digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
			}

			// Check GATEWAY_LIGHT_1_SLOT status
			DigOut(13, Souliss_T1n_Coil, GATEWAY_LIGHT_1_SLOT);
		}

		// Process the communication, this include the command that are coming from SoulissApp
		// or from the push-button located on the other node
		FAST_PeerComms();

	}

	EXECUTESLOW() {
		UPDATESLOW();
	}

}
