# MAX31855_RT

Arduino library for MAX31855 chip for K type thermocouple

## Description

The MAX38155 is a chip to convert the reading of a K-type thermocouple to a temperature.
The working of thermocouples (TC) is based upon Seebeck effect.
Different TC's have a different Seebeck Coefficient (SC) expressed in µV/°C.
See http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html

For every type of TC there exist an MAX31855 variant, this library is primary
developed for the K-type sensor. However it has experimental support for all
other types of TC's. See details below.

To make a temperature reading call **tc.read()**.
It returns the status of the read which is a value between 0..7

Status from **read()**

| value | Description | Action |
|:----:|:----|:----|
| 0 | OK | - |
| 1 | Thermocouple open circuit | check wiring |
| 2 | Thermocouple short to GND | check wiring |
| 4 | Thermocouple short to VCC | check wiring |
| 7 | Generic error | |
| 128 | No read done yet | check wiring |
| 129 | No communication | check wiring |

The function **getStatus()** returns the same status value. There are three functions
to check individual error conditions.

After a **tc.read()** you can get the temperature with **tc.getTemperature()** 
and **tc.getInternal()** for the temperature of the chip / board itself.

Repeated calls to **getTemperature()** will give the same value until a new **tc.read()**.
The latter fetches a new value from the sensor, and does the most work.

The library supports a fixed offset to callibrate the thermocouple.
For this the functions **getOffset()** and **setOffset(offset)** are available.
This offset is included in the **getTemperature()** function.

As the **tc** object holds its last known temperature it is easy to determine the delta 
with the last known temperature, e.g. for trend analysis.
```cpp
float last = tc.getTemperature();
int state  = tc.read();
float new  = tc.getTemperature();
float delta = new - last;
```

The **tc** object keeps track of the last time **read()** is called in the function **lastRead()**.
The time is tracked in **millis()**. This makes it easy to read the sensor at certain intervals.

```cpp
if (millis() - lastRead() >= interval)
{
  tc.read();
  float new = tc.getTemperature();
  // process read value.
}
```

## Operation

See examples

## Experimental part (to be tested)

The MAX31855 is designed for K type sensors. It essentially measures a 
voltage difference and converts this voltage using the Seebeck Coefficient (SC) 
to the temperature. As the SC is lineair in its nature it is possible
to replace the K-type TC with one of the other types of TC.

Datasheet Table 1, page 8

| Sensor type | Seebeck Coefficient (µV/°C) | Temp Range (°C) | Material |
|:----|:----|:----|:----|
| E_TC | 76.373 | -270 to +1000 | Constantan Chromel |
| J_TC | 57.953 | -210 to +1200 | Constantan Iron |
| K_TC | 41.276 | -270 to +1372 | Alumel Chromel |
| N_TC | 36.256 | -270 to +1300 | Nisil Nicrosil |
| R_TC | 10.506 | -50 to +1768 | Platinum Platinum/Rhodium |
| S_TC | 9.587  | +50 to +1768 | Platinum Platinum/Rhodium |
| T_TC | 52.18  | -270 to +400 | Constantan Copper |

The core formula to calculate the temperature is  (Datasheet page 8)
```
Vout = (41.276µV/°C) x (Temp_R - Temp_internal)
```
As we know the internal temperature and the returned temperature from the sensor
the library can calculate the Vout measured(as the chip assumes that a K-type 
thermocouple is connected. 
Having that Vout we can redo the math for the actual thermocouple type and
calculate the real temperature. 
The library has two functions **setSeebeckCoefficient(factor)** and 
**getSeebeckCoefficient()**
to get/set the Seebeck Coefficient (== thermocouple) to be used. 
One can adjust the values to improve the accuracy of the temperature read. 

The **getTemperature()** has implemented this algorithm, however as long
as one does not set the SC it will use the K_TC as default.

**NOTE:** 
The support for other thermocouples is experimental **use at your own risk**.

