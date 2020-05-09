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
#include"Arduino.h"
#include"Air_Quality.h"

//Get the avg voltage in 5 minutes.

void AirQuality::avgVoltage()
{
    if(i == 150)//sum 5 minutes
    {
        val_standard = temp/150;
        temp = 0;
        Serial.print("Val_standard in 5 minutes:");
        Serial.println(val_standard);
        i=0;
    }
    else
    {
        temp += first_val;
        i++;
    }
}
void AirQuality::init(int pin)
{
    _pin=pin;
    
    pinMode(_pin,INPUT);
    unsigned char i = 0;
    Serial.println("sys_starting...");
    delay(20000);//200000
    init_sensorValue = analogRead(_pin);
    Serial.println("The init_sensorValue is ...");
    Serial.println(init_sensorValue);
    while(init_sensorValue)
    {
        if(init_sensorValue < 798 && init_sensorValue > 10)    // the init voltage is ok
        {
            first_val = analogRead(_pin);     //initialize first value
            last_val = first_val;
            val_standard = last_val;
            Serial.println("Sensor ready.");
            error=false;;
            break;
        }
        else if(init_sensorValue > 798 || init_sensorValue <= 10)
        {
            i++;
            delay(60000);//60000
            Serial.println("waitting sensor init..");
            init_sensorValue = analogRead(_pin);
            if(i == 5)
            {
                i = 0;
                error=true;
                Serial.println("Sensor Error!");
            }
          }
        else
        break;
    }
    //init the timer
  //  TCCR2A=0;//normal model
   // TCCR2B=0x07;//set clock as 1024*(1/16M)
   // TIMSK2=0x01;//enable overflow interrupt
    Serial.println("Test begin...");
 //   sei();
}
int AirQuality::slope(void)
{
    while(timer_index)
    {
        if(first_val - last_val > 400 || first_val > 700)
        {
            Serial.println("High pollution! Force signal active.");
            timer_index = 0;
            avgVoltage();
            return 0;
        }
        else if((first_val - last_val > 400 && first_val < 700) || first_val - val_standard > 150)
        {
            Serial.print("sensor_value: ");
            Serial.print(first_val);
            Serial.println("\t High pollution!");
            timer_index = 0;
            avgVoltage();
            return 1;

        }
        else if((first_val - last_val > 200 && first_val < 700) || first_val - val_standard > 50)
        {
            //Serial.println(first_vol-last_vol);
            Serial.print("sensor_value: ");
            Serial.print(first_val);
            Serial.println("\t Low pollution!");
            timer_index = 0;
            avgVoltage();
            return 2;
        }
        else
        {
            avgVoltage();
            Serial.print("sensor_value: ");
            Serial.print(first_val);
            Serial.println("\t Air fresh");
            timer_index = 0;
            return 3;
        }
    }
    return -1;
}
