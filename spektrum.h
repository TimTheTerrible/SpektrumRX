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

#ifndef __spektrum_h__
#define __spektrum_h__

#define DEBUG_PARSE       0x0100
#define DEBUG_SERIAL      0x0200

#define MAX_MSG_LEN       16

#define SRX_VAL_MASK_LEN  11
#define SRX_VAL_MASK      0x07FF

#define CHAN_THROTTLE     16
#define CHAN_AILERON      1
#define CHAN_ELEVATOR     2
#define CHAN_RUDDER       3
#define CHAN_GEAR         4
#define CHAN_AUX1         5
#define CHAN_AUX2         6
#define CHAN_AUX3         7
#define CHAN_AUX4         8
#define CHAN_AUX5         9
#define CHAN_AUX6         10
#define CHAN_AUX7         11
#define CHAN_AUX8         12

typedef struct SpektrumChannels {
  uint16_t throttle = 1024;
  uint16_t aileron = 1024;
  uint16_t elevator = 1024;
  uint16_t rudder = 1024;
  uint16_t gear = 1024;
  uint16_t aux1 = 1024;
  uint16_t aux2 = 1024;
  uint16_t aux3 = 1024;
  uint16_t aux4 = 1024;
  uint16_t aux5 = 1024;
  uint16_t aux6 = 1024;
  uint16_t aux7 = 1024;
  uint16_t aux8 = 1024;
} SpektrumChannels;

class SpektrumRx
{
  public:
    bool begin();
    void parse( uint8_t * );
    SpektrumChannels getChannels();
    uint8_t switchPos( uint8_t, uint8_t );

  private:
    SpektrumChannels m_channels;
};

extern SpektrumRx rx;

#endif
