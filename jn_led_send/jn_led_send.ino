/*
 * JeeNode Wireless Blinking LED - Sender.
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

#include <RF12.h>

int led_status = 0;


void setup () {
    // initialize the serial port and the RF12 driver
    Serial.begin(9600);
    rf12_config();
    rf12_easyInit(0);
}


void loop() {
  // keep the easy transmission mode going
  rf12_easyPoll();
  // send the data
  rf12_easySend(&led_status, sizeof led_status);
  // change the status
  led_status = !led_status;
  delay(1000);
}

