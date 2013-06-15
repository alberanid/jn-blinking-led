/*
 * JeeNode Wireless Blinking LED - Receiver.
 *
 * A very basic example of how to set an LED status (turning it
 * on and off) based on the value received from another JeeNode.
 *
 * Copyright (c) 2013 Davide Alberani <da@erlug.linux.it>
 *
 * It's assumed that you've already set the nodes IDs following
 * the guide in http://jeelabs.net/projects/cafe/wiki/POF_03_-_Wireless_light_sensor
 * This example is absolutely NOT optimized, and will consume a lot
 * of power unnecessarily; in the same page, you can find many improvements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <JeeLib.h>

Port led (1);

int led_status = 0;


void setup () {
    // initialize the serial port and the RF12 driver
    Serial.begin(9600);
    rf12_config();
    // set up easy transmissions
    rf12_easyInit(5);
    // set LED port to output
    led.mode(OUTPUT);
}


void loop() {
  // check if something has been received and if it's correct.
  if (!rf12_recvDone()) {
    return;
  }
  if (rf12_crc) {
    Serial.println("CRC ERROR");
    return;
  }
  if (rf12_len != sizeof led_status) {
    Serial.println("WRONG DATA SIZE");
    return;
  }
  // copy the data in another memory location
  memcpy(&led_status, (int*) rf12_data, sizeof led_status);
  // turn on or off the LED, accordingly to the received value
  led.digiWrite(led_status);
}

