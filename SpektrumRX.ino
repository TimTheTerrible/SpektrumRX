/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Wire.h>

#include "debugprint.h"
#include "spektrum.h"

#define LEDPIN 13

uint32_t debugInterval = 0;

void setup () {
  // Enable debug output
  // Debug = DEBUG_TRACK;

  // Set up the status LED and turn it on
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);

  // Start the serial console port
  Serial.begin(115200);

  // Wait for the it to wake up
  while(!Serial);
  
  debugprint(DEBUG_TRACE, "SpektrumRX Test");
  
  // Set up the receiver
  rx.begin();

  debugprint(DEBUG_TRACE, "Setup is complete!");
  
  // Shut off the status LED
  digitalWrite(LEDPIN, LOW);  
}

void showChannels ( SpektrumChannels channels) {
  debugprint(DEBUG_TRACE, "\nAIL  ELE  THR  RUD  GEAR AUX1 AUX2 AUX3 AUX4 AUX5 AUX6 AUX7 AUX8");
  debugprint(DEBUG_TRACE, "%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d",
    channels.aileron, channels.elevator, channels.throttle, channels.rudder,
    channels.gear, channels.aux1, channels.aux2, channels.aux3, channels.aux4,
    channels.aux5, channels.aux6, channels.aux7, channels.aux8
  );
}
  
void loop () {
  SpektrumChannels channels = rx.getChannels();

  if ( millis() > debugInterval ) {
    showChannels(channels);
    
    // Reset the delay to 1s
    debugInterval = millis() + 1000;
  }
}
