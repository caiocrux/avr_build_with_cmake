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

#include <gpio.h>
#include <led.h>
#include <powerled.h>
#include <stdbool.h>
#include <string.h>
#include <usart.h>
#include <wizchip_conf.h>
#include <wiznet_ll.h>
#include "socket.h"
#include <MQTTClient.h>
#include <mqtt_interface.h>
void messageArrived(MessageData *md);

void messageArrived(MessageData *md) {
  MQTTMessage *message = md->message;
  unsigned char testbuffer[100];
  memset(testbuffer, 0, 100);

  memcpy(testbuffer, (char *)message->payload, (int)message->payloadlen);
  //*(testbuffer + (int)message->payloadlen + 1) = "\n";
  printf("%s\r\n", testbuffer);
  if (testbuffer[0] == '1') {
    USART0_SendString("Led goes to 1!");
  } else if (testbuffer[0] == '0') {
    USART0_SendString("Led goes to 0");
  }
}

int main(void) {
  USART0_Init(E_BAUD_1000000);
  initWiznetSPI();
  uint8_t bufSize[] = {2, 2, 2, 2};
  uint8_t retVal = 0;
  USART0_SendString("MQTT test !!\r\n");
  wiz_NetInfo netInfo = {
      .mac = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}, // Mac address
      .ip = {192, 168, 0, 159},                   // IP address
      .sn = {255, 255, 255, 0},                    // Subnet mask
      .gw = {192, 168, 1, 1}};                    // Gateway address

  reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
  reg_wizchip_spi_cbfunc(spi_rb, spi_wb);

  wizchip_init(bufSize, bufSize);

  wizchip_setnetinfo(&netInfo);
  memset(&netInfo, 0, sizeof(netInfo));

  wizchip_getnetinfo(&netInfo);

  USART0_SendString("MQTT test2 !!\r\n");
  MQTTClient c;
  Network n;
  unsigned char buf[100];
  unsigned char readbuf[100];
  char MessageToSend[100];
  sprintf(MessageToSend, "Hello World!  QoS 0 message from UatuBoard");
  char *clientid = "UatuBoard";
  NewNetwork(&n, 1);
  USART0_SendString("MQTT test3 !!\r\n");
  ConnectNetwork(&n, "broker.hivemq.com", 1883);
  USART0_SendString("MQTT test4 !!\r\n");
  MQTTClientInit(&c, &n, 1000, buf, 100, readbuf, 100);
  USART0_SendString("MQTT test5 !!\r\n");
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
  USART0_SendString("MQTT test6 !!\r\n");
  retVal = MQTTConnect(&c, &data);
  USART0_SendString("MQTT test7 !!\r\n");
  if(retVal != SOCK_OK ){
	USART0_SendString("Error to MQTT COnnect");
  }
  retVal = MQTTSubscribe(&c, "boardLED2", QOS0, messageArrived);
  if( retVal != 1) {
	  USART0_SendString("Error to MQTT mqtt subscribe");
  }
  while (1) {
    MQTTYield(&c, 1000);
    MQTTPublish(&c, "boardLED", &MessageToBroker);
    _delay_ms(1000);
    USART0_SendString("While 1 ");
  }
}
