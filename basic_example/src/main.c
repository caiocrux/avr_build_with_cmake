/*
 * main.c
 *
 * Copyright 2022 Caio Felipe Soares da Cruz <caio.crux@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * Example of CMake usage with AVR. Shows how to add lib directories and include
 * in main program
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>
#include "socket.h"
#include "MQTTClient.h"
#include "gpio.h"
#include "led.h"
#include "mqtt_interface.h"
#include "powerled.h"
#include "usart.h"
#include "wizchip_conf.h"
#include "wiznet_ll.h"
#include "timer.h"

static void messageArrived(MessageData *md);
static void onTimer1ms(void);

// User-defined callback function
void onTimer1ms(void) {
  // Code to run every 1 ms
  MilliTimer_Handler();
}

void messageArrived(MessageData *md) {
  char topicName[md->topicName->lenstring.len + 1];
  char payload[md->message->payloadlen + 1];

  // Copy the topic name and payload to local buffers
  memcpy(topicName, md->topicName->lenstring.data, md->topicName->lenstring.len);
  memcpy(payload, md->message->payload, md->message->payloadlen);

  // Null-terminate the strings
  topicName[md->topicName->lenstring.len] = '\0';
  payload[md->message->payloadlen] = '\0';

  USART0_SendString("Message received in topic : ");
  USART0_SendString(topicName);
  USART0_SendString("\r\n");

  unsigned char testbuffer[100] = {0};

  memcpy(testbuffer, (char *)md->message->payload,(int)md->message->payloadlen);

  USART0_SendString("Payload : ");
  USART0_SendString(testbuffer);
  USART0_SendString("\r\n");

  if (testbuffer[0] == '1') {
    USART0_SendString("Led goes to 1!\r\n");
  } else if (testbuffer[0] == '0') {
    USART0_SendString("Led goes to 0\r\n");
  }
}

int main(void) {

  uint8_t txsize[4] = {2, 2, 2, 2}; // Transmit buffer sizes for 4 sockets
  uint8_t rxsize[4] = {2, 2, 2, 2}; // Receive buffer sizes for 4 sockets
  uint8_t retVal = 0;

  USART0_Init(E_BAUD_1000000);
  initWiznetSPI();
  Timer1ms_Init();
  Timer1ms_SetCallback(onTimer1ms);

  USART0_SendString("MQTT test !!\r\n");

  wiz_NetInfo netInfo = {
      .mac = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}, // Mac address
      .ip = {192, 168, 0, 159},                    // IP address
      .sn = {255, 255, 255, 0},                    // Subnet mask
      .gw = {192, 168, 1, 1}};                     // Gateway address

  reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
  reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
  wizchip_init(txsize, rxsize);
  wizchip_setnetinfo(&netInfo);
  // memset(&netInfo, 0, sizeof(netInfo));
  // wizchip_getnetinfo(&netInfo);

  MQTTClient client;
  Network network;
  // Buffers for sending and receiving MQTT messages
  unsigned char sendbuf[100];
  unsigned char readbuf[100];

  char MessageToSend[100];
  sprintf(MessageToSend, "Hello World!  QoS 0 message from Encora Board");
  char *clientid = "Encora Board";
  NewNetwork(&network, 1);
  unsigned char targetIP[4] = {192, 168, 0, 205};
  if (ConnectNetwork(&network, targetIP, 1883) != SOCK_OK) {
    USART0_SendString("Could  Not open the socket!!\r\n");
  }
  // Initialize the MQTT client with a 1-second command timeout
  MQTTClientInit(&client, &network, 1000, sendbuf, sizeof(sendbuf), readbuf,
                 sizeof(readbuf));
  // Packet ot send for broker
  MQTTMessage MessageToBroker;
  MessageToBroker.qos = QOS0;
  MessageToBroker.retained = false; // set to true for retained
  MessageToBroker.dup = false;
  MessageToBroker.payload = (void *)MessageToSend;
  MessageToBroker.payloadlen = strlen(MessageToSend);

  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  data.willFlag = 0;
  data.MQTTVersion = 3;
  data.clientID.cstring = clientid;
  data.keepAliveInterval = 10;
  data.cleansession = 1;
  retVal = MQTTConnect(&client, &data);
  if (retVal != SUCCESSS) {
    USART0_SendString("Error to MQTT COnnect\r\n");
  }
  retVal = MQTTSubscribe(&client, "boardLED2", QOS0, messageArrived);
  if (retVal != SUCCESSS) {
    USART0_SendString("Error to MQTT mqtt subscribe\r\n");
  }
  while (1) {
    MQTTYield(&client, 1000);
    MQTTPublish(&client, "boardLED", &MessageToBroker);
    _delay_ms(1000);
    USART0_SendString("While 1 \r\n");
  }
}
