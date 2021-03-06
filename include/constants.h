// Define the RS485 network configuration
#define VNET_SUBNET			0xCE00	//USART Range
#define VNET_SUBNET_MASK	0xFF00

#define USARTBAUDRATE_INSKETCH
#define USART_BAUD19k2			1

#define RS485_GATEWAY_ADDR			VNET_SUBNET | 0x0001
#define RS485_BUTTONS_PANEL_1_ADDR	VNET_SUBNET | 0x0002
#define RS485_RELAYS_1_ADDR			VNET_SUBNET | 0x0003

#define BUTTONS_PANEL_MCAS_ADDR		0xFA00
#define	BUTTON_PUSHED_EVENT			0xC001,0x01

// Buttons Panel Slots
#define BUTTONS_PANEL_BUTTON_1_SLOT			0
#define BUTTONS_PANEL_BUTTON_2_SLOT			1
#define BUTTONS_PANEL_BUTTON_3_SLOT			2
#define BUTTONS_PANEL_BUTTON_4_SLOT			3
#define BUTTONS_PANEL_BUTTON_5_SLOT			4
#define BUTTONS_PANEL_BUTTON_6_SLOT			5
#define BUTTONS_PANEL_BUTTON_7_SLOT			6
#define BUTTONS_PANEL_BUTTON_8_SLOT			7
#define BUTTONS_PANEL_LED_1_SLOT			8
#define BUTTONS_PANEL_LED_2_SLOT			9
#define BUTTONS_PANEL_LED_3_SLOT			10
#define BUTTONS_PANEL_LED_4_SLOT			11
#define BUTTONS_PANEL_LED_5_SLOT			12
#define BUTTONS_PANEL_LED_6_SLOT			13
#define BUTTONS_PANEL_LED_7_SLOT			14
#define BUTTONS_PANEL_LED_8_SLOT			15

// Relays module Slots
#define RELAYS_MODULE_RELAY_1_SLOT			0
#define RELAYS_MODULE_RELAY_2_SLOT			1
#define RELAYS_MODULE_RELAY_3_SLOT			2
#define RELAYS_MODULE_RELAY_4_SLOT			3
#define RELAYS_MODULE_RELAY_5_SLOT			4
#define RELAYS_MODULE_RELAY_6_SLOT			5
#define RELAYS_MODULE_RELAY_7_SLOT			6
#define RELAYS_MODULE_RELAY_8_SLOT			7

#define GATEWAY_LIGHT_1_SLOT					0
#define GATEWAY_LIGHT_2_SLOT					1
#define GATEWAY_BUTTONS_PANEL_1_BUTTON_1_SLOT	2
#define GATEWAY_BUTTONS_PANEL_1_BUTTON_2_SLOT	3
