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

void setup()
{
	Initialize();

	// Set network parameters
	SetAddress(RS485_GATEWAY_ADDR, VNET_SUBNET_MASK, RS485_GATEWAY_ADDR);

	Set_T11(GATEWAY_LIGHT_1_SLOT);
	Set_T11(GATEWAY_LIGHT_2_SLOT);

	Set_T11(GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT);
	Set_T11(GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT);

}

void loop()
{
	// Here we start to play
	EXECUTEFAST() {
		UPDATEFAST();

		// Execute every 510ms the logic, the command to open and close the garage door
		// cames directly from SoulissApp or the push-button located on the other node
		FAST_50ms() {

			// Copy input from BUTTONS to LIGHTS
			mInput(GATEWAY_LIGHT_1_SLOT) = mInput(GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT);
			//
			Logic_T11(GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT);
			Logic_T11(GATEWAY_BUTTONS_PANEL_1_BUTTON_2_SLOT);

			//
			//void Souliss_LinkOI(U8 *memory_map, U8 input_slot, U8 output_slot)
			//{
			//	if(memory_map[MaCaco_OUT_s + output_slot] != 0x00)
			//		memory_map[MaCaco_IN_s + input_slot] = memory_map[MaCaco_OUT_s + output_slot];	// Link IO
			//}
			//Souliss_LinkOI(memory_map, GATEWAY_LIGHT_1_SLOT, GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT);
			//sSouliss_LinkOI(memory_map, GATEWAY_LIGHT_2_SLOT, GATEWAY_BUTTONS_PANEL_1_BUTTON_2_SLOT);
			// Link GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT To GATEWAY_LIGHT_1_SLOT
			// Link GATEWAY_BUTTONS_PANEL_1_BUTTON_2_SLOT To GATEWAY_LIGHT_2_SLOT
			//

			if (Logic_T11(GATEWAY_LIGHT_1_SLOT)) {
				Send(RS485_BUTTONS_PANEL_1_ADDR, BUTTONS_PANEL_1_LED_1_SLOT, mOutput(GATEWAY_LIGHT_1_SLOT));
				Send(RS485_RELAYS_1_ADDR, RELAYS_1_RELAY_1_SLOT, mOutput(GATEWAY_LIGHT_1_SLOT));
			}
			if (Logic_T11(GATEWAY_LIGHT_2_SLOT)) {
				Send(RS485_BUTTONS_PANEL_1_ADDR, BUTTONS_PANEL_1_LED_2_SLOT, mOutput(GATEWAY_LIGHT_2_SLOT));
				Send(RS485_RELAYS_1_ADDR, RELAYS_1_RELAY_2_SLOT, mOutput(GATEWAY_LIGHT_2_SLOT));
			}

			//DigOut(LED_1_PIN, Souliss_T1n_Coil, GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT);

		}

		// Process the communication, this include the command that are coming from SoulissApp
		// or from the push-button located on the other node
		FAST_PeerComms();

	}

	EXECUTESLOW() {
		UPDATESLOW();
	}

}
