/*
  AirQuality library v1.0
  2010 Copyright (c) Seeed Technology Inc.  All right reserved.

  Original Author: Bruce.Qin

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef __AIR_QUALITY_H__
#define __AIR_QUALITY_H__

#include"Arduino.h"
class AirQuality
{
public:
    int i ;
    long val_standard;
    //int init_voltage;
    int init_sensorValue = 0;
    int first_val;
    int last_val;
    long temp;
    int counter;
    boolean timer_index;
    boolean error;
    void init(int pin);
    int slope(void);
private:
    int _pin;
    void avgVoltage(void);
};
#endif
