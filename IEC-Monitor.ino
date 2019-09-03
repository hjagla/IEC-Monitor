/*
 * Commodore Serial IEC Monitor
 * Copyright (C) 2019 Jim Agla <hjagla@gmail.com>
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

#define IEC_ATN 4
#define IEC_CLK 5
#define IEC_DAT 6

bool IN_ATN = false;
bool IN_CLK = false;

int BITS = 0;
String BITSTR = "";
int BITVAL = 0;

void setup() {
  pinMode(IEC_ATN, INPUT);
  pinMode(IEC_CLK, INPUT);
  pinMode(IEC_DAT, INPUT);

  Serial.begin(115200);
  Serial.print("Ready\r\n");
}

void loop() {
  if (!ReadIEC(IEC_ATN) && !IN_ATN) {
    IN_ATN = true;
    IN_CLK = false;
    BITS = 0;
    BITSTR = "";
    BITVAL = 0;
    Serial.print("\r\n(");
  }
  if (ReadIEC(IEC_ATN) && IN_ATN) {
    IN_ATN = false;
    IN_CLK = false;
    Serial.print(") ");
  }
  if (!ReadIEC(IEC_CLK) && !IN_CLK) {IN_CLK = true;}
  if (ReadIEC(IEC_CLK) && IN_CLK) {
    IN_CLK = false;
      if (ReadIEC(IEC_DAT)) {
        BITSTR += "1";
        BITVAL |= (1 << BITS - 1);
      } else {
        BITSTR += "0";
        BITVAL |= (0 << BITS - 1);
      }
    BITS ++;
    if (BITS > 8) {
      if (IN_ATN) {
        Serial.print(HEXED(BITVAL) + " ");
      } else {
        Serial.print(HEXED(BITVAL) + " ");
      }
      BITS = 0;
      BITSTR = "";
      BITVAL = 0;
    }
  }
}

String HEXED(int VALUE) {
  String temp = "";
  if (VALUE < 16) {temp += "0";}
  temp += String(VALUE, HEX);
  temp.toUpperCase();
  return temp;
}

bool ReadIEC(int PIN) {
  if (digitalRead(PIN) == true) {
    return true;
  } else {
    return false;
  }
}
