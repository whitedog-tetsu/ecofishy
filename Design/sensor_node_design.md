

<div style="text-align: center;">

# Ecofishy design

</div>

- [Ecofishy design](#ecofishy-design)
  - [Class](#class)
  - [Calculate temperature](#calculate-temperature)
  - [Arduino UNO pin assign](#arduino-uno-pin-assign)
  - [Arduino Micro pin assign](#arduino-micro-pin-assign)


## Class
![class](../out/Design/sensor_node_class/sensor_node_class.png)   


## Calculate temperature
![class](../out/Design/calculate_temperature/calculate_temperature.png)   

sensor variance is 
To less output variance of discrete, average analog data as low-pass filter.


## Arduino UNO pin assign 

| No. |Pin on Board |IO  |H/L |P.U./P.D./IN.P.U. |Dst. Pin |Use       |Description |
|-----|-------------|----|----|------------------|---------|----------|------------|
|    1| MOSI        | -  |    |                  |         | Reserved | SPI        |
|    2| SS          | -  |    |                  |         | Reserved | SPI        |
|    3| D1/TX       |    |    |                  | RX      | BP35A  1 | MUST need level shifter |
|    4| D0/RX       |    |    |                  | TX      | BP35A1   | MUST need level shifter |
|    5| RESET       |    |    |                  |         | Unused   |            |
|    6| GND         |    |    |                  |         | Unused   |            |
|    7| D2/SDA      | -  |    |                  |         | Reserved |            |
|    8| D3/SCL      | -  |    |                  |         | Reserved |            |
|    9| D4          | -  |    |                  | WKUP    | BP35A1   |MUST need level shifter |
|   10| D5          | -  |    |                  | RESET   | BP35A1   |MUST need level shifter |
|   11| D6          | -  |    |                  |         | Unused   |            |
|   12| D7          | -  |    |                  |         | Unused   |            |
|   13| IO8         | -  |    |                  |         | Unused   |            |
|   14| IO9         | -  |    |                  |         | Unused   |            |
|   15| IO10        | -  |    |                  |         | Unused   |            |
|   16| IO11        | -  |    |                  |         | Reserved |            |
|   17| IO12        | -  |    |                  |         | Reserved |            |
|   18| IO13        | -  |    |                  |         | Reserved |            |
|   19| 3.3V        | -  |    |                  |         | Unused   |            |
|   20| AREF        | -  |    |                  |         | Unused   |            |
|   21| A0          | I  |    |                  |         | AT103-11 |            |
|   22| A1          |    |    |                  |         | AT103-11 |            |
|   23| A2          |    |    |                  |         | AT103-11 |            |
|   24| A3          |    |    |                  |         | AT103-11 |            |
|   25| A4          |I/O |    |                  |         | Reserved | for I2C    |
|   26| A5          |    |    |                  |         | Reserved | for I2C    |
|   27| N.C.        |    |    |                  |         | Unused   |            |
|   28| N.C.        |    |    |                  |         | Unused   |            |
|   29| +5V         |    |    |                  |         | Unused   |            |
|   30| RESET       |    |    |                  |         | Unused   |            |
|   31| GND         |    |    |                  |         | Unused   |            |
|   32| VIN         |    |    |                  |         | Unused   |            |
|   33| MISO        | -  |    |                  |         | Reserved | SPI        |
|   34| SCK         | -  |    |                  |         | Reserved | SPI        |


note: unused pin is set to output low.


## Arduino Micro pin assign 

|Pin on Board |IO  |H/L |Pull-Up/Pull-Down  |Dst. Pin |Use       |Description |
|-------------|----|----|------------------|---------|----------|------------|
| A0          | I  |    |                  |         | AT103-11 |            |
| A1          | I  | -  | Pull-Up          |         | Unused   |            |
| A3          | I  | -  | Pull-Up          |         | Unused   |            |
| A4          | I  | -  | Pull-Up          |         | Unused   |            |
| A5          | I  | -  | Pull-Up          |         | Unused   |            |
| D0          | I  |    |                  | RX      | BP35A1   | MUST need level shifter |
| D1          | O  |    |                  | TX      | BP35A1   | MUST need level shifter |
| D2          | I/O |    |                | SDA     | SDA      |  I2C master   |
| D3          | O  |    |                  | SCL     | SCL      |  I2C master   |
| D4          | O  | L  |                  | WKUP    | BP35A1   |MUST need level shifter |
| D5          | O  | L  |                  | RESET   | BP35A1   |MUST need level shifter |
| D6          | I  | -  | Pull-Up          |         | Unused   |            |****
| D7          | I  | -  | Pull-Up          |         | Unused   | INT6       |
| D8          | -  |    |                  | Arduino Micro RESET   | Arduino Micro Reset | If not software reset    |
| D9          | O  | L  |                  |         | LED  R   | PWM         |
| D10         | O  | L  |                  |         | LED  G   | PWM         |
| D11         | O  | L  |                  |         | LED  B   | PWM         |
| D12         | I  | -  | Pull-Up          |         | Unused   |             |
| D13         | I  | -  | Pull-Up          |         | Unused   |             |
| D14         | O  | L  |                  |         | MISO     | SPI         |
| D15         | O  | L  |                  |         | SCLK     | SPI         |
| D16         | O  | L  |                  |         | MOSI     | SPI         |
| D17         | O  | L  |                  |         | SS       | SPI         |
| AREF        | O  |    |                  |         | Unused   |             |
| RESET       | I  |    |                  |         | Unused   |             |
| IOREF       | O  |    |                  |         | Unused   |             |


note: unused pins are set to input pull-up.


