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

#include <HardwareSerial.h>

#include "debugprint.h"
#include "spektrum.h"

SpektrumRx rx;

/*
 * Serial Port Handler
 */

uint8_t msgIndex = 0;
uint8_t inputBuffer[MAX_MSG_LEN];

void serialEvent1() {
  debugprint(DEBUG_SERIAL, "serialEvent()!");

  // Read the incoming data
  while (Serial1.available()) {

    // get the new byte:
    uint8_t inByte = (uint8_t)Serial1.read();

    // add it to the input buffer
    inputBuffer[msgIndex++] = inByte;
  }

  if ( msgIndex == MAX_MSG_LEN ) {
    rx.parse(inputBuffer);
    msgIndex = 0;
  }
}

/*
 * SpektrumRx Class Methods
 */

bool SpektrumRx::begin () {
  // Set up the serial port
  Serial1.begin(115200);

  debugprint(DEBUG_TRACE, "Receiver intialized!");
  return true;
}

SpektrumChannels SpektrumRx::getChannels () {
  const SpektrumChannels theChannels = m_channels;

  return theChannels;
}

/*
 * Spektrum Sattelite Receiver Message Format
 * 
 * NOTE: This applies only to the specific situation
 * I was facing: a Spektrum sattelite receiver bound 
 * to a DX9 transmitter. Your mileage may vary if
 * you're using a different combination of receiver 
 * and transmitter.
 * 
 * The receiver sends 16-byte frames. Each frame
 * contains two header bytes and six channel byte
 * pairs. The ordering of channles is arbitrary.
 * For transmitters with more than six channels,
 * multiple frames are sent, six channels at a time. 
 * All channels are eventually sent.
 * 
 * Channel numbers start at 0 and go to 12, with oddball
 * THROTTLE at 16 for no apparent reason.
 * The channel values go from 0 to 2048.
 * 
 * FEDCBA0987654321
 * 1111100000000000 Channel Number
 * 0000011111111111 Channle Value
 * 
 * TODO: what's the value/meaning of the header bytes?
 * TODO: unused channels seem to always be 1024. try other radios and see what happens.
 * TODO: channel 24 seems to be a tenth channel, or maybe RSSI
 * 
 */
 
void SpektrumRx::parse( uint8_t * input) {
  char bMSB[9];
  char bLSB[9];
  char bWord[17];
  uint16_t msgWord;
  uint8_t channelNum;
  uint16_t channelVal;

  debugprint(DEBUG_PARSE, "\nParsing new message...");
  
  debugprint(DEBUG_PARSE, "HDR: %2.2hx:%2.2hx", input[0], input[1]);

  for ( uint8_t i = 2; i < MAX_MSG_LEN; i += 2) {
    
    // What are the two bytes?
    strncpy(bMSB, byte_to_binary(input[i]), 9);
    strncpy(bLSB, byte_to_binary(input[i+1]), 9);
    debugprint(DEBUG_PARSE, "MSB: %2.2hx %s LSB: %2.2hx %s", input[i], bMSB, input[i+1], bLSB);
    
    // Assemble the bytes into a word
    msgWord = input[i] << 8; msgWord = msgWord | input[i+1];
    strncpy(bWord, word_to_binary(msgWord), 17);
    debugprint(DEBUG_PARSE, "msgWord: %4.4hx %s", msgWord, bWord);

    // Calculate the channel number and value
    channelNum = msgWord >> SRX_VAL_MASK_LEN;
    channelVal = msgWord & SRX_VAL_MASK;
    debugprint(DEBUG_PARSE, "CHAN: %4d VAL: %4d", channelNum, channelVal);

    // TODO: clean up the value of channelVal

    // Store the value in a channel
    switch ( channelNum ) {
      case CHAN_THROTTLE:
        m_channels.throttle = channelVal;
        break;
      case CHAN_AILERON:
        m_channels.aileron = channelVal;
        break;
      case CHAN_ELEVATOR:
        m_channels.elevator = channelVal;
        break;
      case CHAN_RUDDER:
        m_channels.rudder = channelVal;
        break;
      case CHAN_GEAR:
        m_channels.gear = channelVal;
        break;
      case CHAN_AUX1:
        m_channels.aux1 = channelVal;
        break;
      case CHAN_AUX2:
        m_channels.aux2 = channelVal;
        break;
      case CHAN_AUX3:
        m_channels.aux3 = channelVal;
        break;
      case CHAN_AUX4:
        m_channels.aux4 = channelVal;
        break;
      case CHAN_AUX5:
        m_channels.aux5 = channelVal;
        break;
      case CHAN_AUX6:
        m_channels.aux6 = channelVal;
        break;
      case CHAN_AUX7:
        m_channels.aux7 = channelVal;
        break;
      case CHAN_AUX8:
        m_channels.aux8 = channelVal;
        break;
      default:
        debugprint(DEBUG_ERROR, "Invalid channel number: %d", channelNum);
        break;
    }
  }
}

uint8_t SpektrumRx::switchPos ( uint8_t channel, uint8_t poles ) {

  uint16_t channelVal;
  switch ( channel ) {
    case CHAN_THROTTLE:
      channelVal = m_channels.throttle;
      break;
    case CHAN_AILERON:
      channelVal = m_channels.aileron;
      break;
    case CHAN_ELEVATOR:
      channelVal = m_channels.elevator;
      break;
    case CHAN_RUDDER:
      channelVal = m_channels.rudder;
      break;
    case CHAN_GEAR:
      channelVal = m_channels.gear;
      break;
    case CHAN_AUX1:
      channelVal = m_channels.aux1;
      break;
    case CHAN_AUX2:
      channelVal = m_channels.aux2;
      break;
    case CHAN_AUX3:
      channelVal = m_channels.aux3;
      break;
    case CHAN_AUX4:
      channelVal = m_channels.aux4;
      break;
    case CHAN_AUX5:
      channelVal = m_channels.aux5;
      break;
    case CHAN_AUX6:
      channelVal = m_channels.aux6;
      break;
    case CHAN_AUX7:
      channelVal = m_channels.aux7;
      break;
    case CHAN_AUX8:
      channelVal = m_channels.aux8;
      break;
    default:
      debugprint(DEBUG_ERROR, "Invalid switch channel: %d", channel);
      return 0;
      break;
  }

  switch ( poles ) {
    case 2:
      return channelVal > 1024 ? 1 : 0;
      break;
    case 3:
      if ( channelVal < 512 )
        return 0;
      else if ( channelVal < 1500 ) 
        return 1;
      else
        return 2;
      break;
    default:
      debugprint(DEBUG_ERROR, "Invalid  number of poles: %d", poles);    
      break;
  }
  
  return 0;
}

