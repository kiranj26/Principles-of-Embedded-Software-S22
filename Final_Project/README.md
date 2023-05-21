[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-8d59dc4de5201274e310e4c54b9627a8934c3b88527886e3b421487c677d23eb.svg)](https://classroom.github.com/a/o8qShciV)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10723708&assignment_repo_type=AssignmentRepo)
# PES : Final Project
# “Home-Care” 
The "Home-Care" project is a temperature and humidity monitoring system that utilizes the SHT21 sensor to enable users to track the temperature and humidity levels in their homes. The project offers multiple modes of operation, including a watch dog timer mode to conserve safety of hardware and home. The system is built to incorporate error checking and reporting to ensure the accuracy and reliability of data. Additionally, a slider has been integrated into the system to allow users to set threshold values of the sensor according to their preferences.

**Note** : As indicated by professor, commitments missed in final delivarable compared to initial proposal is mentioned in detail here [Click Here to see Missed Commitments](#missed-commit)

**Note** : To directly see the demo video click here. [Click Here to See Demo](#demo)

# Features
* SHT21 temperature and humidity sensor
* KL25Z board
* Circular buffers for data storage
* State machines for multi-mode control
* I2C protocol for sensor communication
* UART for user interface and command processing
* Watchdog Dmer for system reliability
* DAC for LED breathing pattern control
* GPIO for LED and slider control
* Interrupts for sensor data aquisition
* Detailed configuraDon of the system clock using sys cloks
* Pulse width modulation for LED intensity control
* Watchdog Timer Mode for sensor health monitoring

# Objectives

* A system that monitors temperature and humidity levels in a smart home
using the SHT21 sensor
* Multiple modes of operaDon to allow users to customize their monitoring
preferences
* Watchdog timer mode to monitor the sensor health
* Error checking and reporting to ensure data accuracy and reliability
* User interface using UART and RGB LED's for easy interacDon with the system
* LED feedback with different breathing patterns to indicate different modes of
operation
* Slider to set the threshold values of the sensor to trigger alert mode

# Hardware
The system's hardware overview is clearly illustrated in the following image. The SHT21 sensor is utilized in the system, and it communicates with the KL25Z microcontroller via the I2C communication protocol, which is implemented using I2C1 on Port E (PTE0 and PT1). The threshold values can be adjusted using a slider, and the user can observe the different states of the system using LEDs.

<p align="center"><img src="https://user-images.githubusercontent.com/111842372/236433613-25bef2a5-1403-4e2c-8c50-9770246accdf.png" alt="BigPicture"></p>

Below picture shows the detailed view of SHT21 sensor pinout. SDA and SCK is connected to respective SDA and SCK pin for I2C1 on port E mainly PTE0 and PTE1 respectively on KL25Z Freedom Board

<p align="center"><img src="https://user-images.githubusercontent.com/111842372/236433880-ba01dcbb-bd7a-49d1-aa87-fa4b99145245.png" alt="Screenshot 2023-05-05 at 4 22 52 AM"></p> 

# Working And UART Ouput
Detailed code working of the project with varying humidity values is as follows. 

**Note**: To check the output with temperature values click here [Demo Video](#demo)

### System Boot Up
Upon booting up, the code initiates the watchdog timer as the first step. Then, it proceeds to conduct a series of tests on both the software and hardware components of the system. 
The software testing includes verifying the functionality of the PWM LED, which entails creating various color patterns for the RGB LEDs. As part of the hardware testing, 
the system tests the FIFO circular buffer with different test cases to ensure that it is working correctly. Lastly, the system performs ten readings of the 
temperature and humidity sensor to verify its accuracy and consistency. This process involves reading the sensor values ten times to establish the reliability of the sensor.

Through details of how the hardware and software has been tested is explained in detail here. [Click here to see testing section](#testing)

Typical output on UART after system bootup looks like below 

```
+---------------------------------------+
|         Enabling Watchdog Timer       |
+---------------------------------------+

+---------------------------------------+
|       Hardware & Software Testing     |
+---------------------------------------+
Testing PWM with different values : 
PWM Tested Successfully! 

Testing CBFIFO with different values : 
CBFIFO Tested Successfully! 

Testing SHT21 to read value 10 times : 
Temperature: 26.58 C
Humidity: 35.50 %
Temperature: 26.58 C
Humidity: 35.50 %
Temperature: 26.58 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
Temperature: 27.27 C
Humidity: 35.50 %
SHT21 Sensor Tested Successfully! 
```

### User UI
Once testing and bootup is finished, code provides UI for user options which is as follows

```

+---------------------------------------+
|       Welcome to Home-Safe System     |
+---------------------------------------+
|                                       |
|  Please select an option:             |
|                                       |
|  +---------------------------------+  |
|  | 'temp'   : Temperature Reading  |  |
|  | 'hum'    : Humidity Reading     |  |
|  | 'start'  : Start State Machine  |  |
|  | 'test'   : Test Hardware        |  |
|  | 'help'   : List Options         |  |
|  | 'author' : Print author        |  |
|  +---------------------------------+  |
|                                       |
+---------------------------------------+

```
Below is the result of all the user commands options provided

```
? temp
Temperature is: 27.271 
? hum
Humidity is: 37.449 
? author
Kiran Narendra Jojare 
? help
+-----------------------------------------------------------------+
|                          COMMAND LIST                           |
+-----------------------------------------------------------------+
+------------+---------------------------------------------------+
| temp       | Prints Surrounding Temperature                    |
| hum        | Prints Surrounding Humidity                       |
| start      | Starts State Machine                                 |
| test       | Starts hardware and software testing              |
| help       | Shows possible user options                       |
| author     | Author Name                                       |
+------------+---------------------------------------------------+
? start
+---------------------------------------+

|         State Machine Enabled         |

+---------------------------------------+
```

### State Machine Modes & Results
The UART output once the state machine starts is explained in detaile in the demo video. Outputs for each state is shown here along with the LED output in diagram attached.

#### SLEEP Mode
Initially systsem is in `SLEEP MODE`. In sleep mode systems showcases the latest value of temperature and humidity sensor and LED blinks blue in breathing pattern achived using PWM and GPIO.
Output of system in `SLEEP MODE` looks like this. 

Output on UART in `SLEEP Mode`
```
+---------------------------------------+
|         State Machine Enabled         |
+---------------------------------------+
|             Sleep Mode                |
Temperature is: 27.271 
Humidity is: 39.403 
|             Sleep Mode                |
Temperature is: 27.271 
Humidity is: 42.332 
|             Sleep Mode                |
Temperature is: 27.271 
Humidity is: 39.891 
|             Sleep Mode                |
Temperature is: 27.271 
Humidity is: 57.957 
```
LED Color in `SLEEP Mode`

https://user-images.githubusercontent.com/111842372/236423012-9c12197e-74a1-45a1-9d1a-4d5a5a06325c.mp4


#### ALERT Mode
System goes into `ALERT Mode` when the teperature or humidity value goes above maximum allowed range. Example, system going into ALERT mode as som as humidity reaches above th maximum threshold level.
Output on UART in `SLEEP Mode`

Uart output showing that system moves from `SLEEP Mode` to `ALERT Mode` as soon as humidity values goes above 100 % 
```
|             Sleep Mode                |
Temperature is: 27.271 
Humidity is: 57.957 
|             Sleep Mode                |
Temperature is: 27.958 
Humidity is: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 53
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 83
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 112
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 141
Humidity is High: 118.992 
```

LED COlour in `ALERT Mode`
Red colour will blink in breathing pattern indicating current mode as `ALERT Mode`

https://user-images.githubusercontent.com/111842372/236425140-49aed3ca-cf26-4f75-b7d2-53a5a8f97f85.mp4

### Slider Mode
Slider Mode is a feature that enables the system to transition from SLEEP mode to ALERT mode based on predetermined threshold values for temperature and humidity sensors. The exciting part is that users can adjust these threshold values while the system is running, by utilizing the slider touch sensor. By sliding the sensor to the left, new threshold values of 50 for both temperature and humidity sensors will be selected. On the other hand, sliding the sensor to the right will result in a new threshold value of 150 for each sensor reading. This functionality provides users with greater flexibility and control over the system's behavior.

UART Output indicating use of slider to change temperature and humidity threshold values
```
|             Sleep Mode                |
Temperature is: 26.585 
Humidity is: 50.633 
|              Slider Mode                |
|          Sensor Thresholds Changed      |
| Temperature Threshold - 50.0000 |
| Humidity Threshold    - 50.0000 |
|              Slider Mode                |
|          Sensor Thresholds Changed      |
| Temperature Threshold - 50.0000 |
| Humidity Threshold    - 50.0000 |
|              Slider Mode                |
|          Sensor Thresholds Changed      |
| Temperature Threshold - 50.0000 |
| Humidity Threshold    - 50.0000 |
|             Sleep Mode                |
Temperature is: 26.585 
Humidity is: 48.680 
|             Sleep Mode                |
Temperature is: 26.585 
|              Slider Mode                |
|          Sensor Thresholds Changed      |
| Temperature Threshold - 150.0000 |
| Humidity Threshold    - 150.0000 |
```

LED Colour during `SLIDER Mode`
Video shows LED Color changing from Blue to White once slider is touched and updated values can be see on UART

https://user-images.githubusercontent.com/111842372/236426747-c08c4634-63ab-4a28-bc14-cd1b935e573c.mp4

### Watchdog Mode
The state machine continuesly monitors the alert mode. During alert mode if the system stays in alert mode for the longer duration of time system will reset the state machine and control will start from mode `SLEEP Mode` again.
Acting as a watch dog feature.

UART Output when system goes into the Watchdog reset state. Below output shows that system transitions from ALERT Mode to WATCHDOG Mode resetting everything in software and starting from SLEEP Mode again.
As soon as time in ALERT Mode reached 1000 i.e 10 Sec, system starts the watch dog mode which resets all software elements and forces state machine to go to SLEEP Mode again.
```
|     Alert Mode (Humidity)             |
Time in alert Mode = 847
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 876
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 906
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 935
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 964
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 994
Humidity is High: 118.992 
|     Alert Mode (Humidity)             |
Time in alert Mode = 1023
Humidity is High: 118.992 
|              Watch Dog Mode             |
|               !! ALERT !!               |
|          SENSOR READING HIGH            |
|          Resetting the system           |
|             Sleep Mode                |
Temperature is: 33.449 
Humidity is: 118.992 
```

**Note :  Apart from this software based watch dog timer simulation in alert mode. Actual watch dog timer in KL25Z has been also used in the code. 
Please refer wdt.c and wdt.h files to see how its used and monitored in system. **

# Demo Presentation<a name="demo"></a>

The video demonstration exhibits the functioning of the system with respect to two sensors - humidity and temperature. To test the humidity sensor, a wet finger  and damp cloth is used, while a hair dryer is used to test the temperature sensor.
Detailed demo presentation is available at the below link.

https://drive.google.com/file/d/1azBYBSV1QXr9xztD1GsxEpQ6gj4JpFpW/view?usp=sharing

**Note** : please download the file after clicking on the google drive link if the preview is not available

# Code Organisation

Code organisation is as follows. The entry function is defined in file `main.c`

| File             | Description                                                                   |
|------------------|-------------------------------------------------------------------------------|
| `accumulate_line.c` | Contains the implementation of the `accumulate_line` function.                  |
| `accumulate_line.h` | Contains the declaration of the `accumulate_line` function.                     |
| `cfifo.c`        | Contains the implementation of the circular FIFO buffer.                      |
| `cbfifo.h`       | Contains the declaration of the circular FIFO buffer.                         |
| `i2c.c`          | Contains the implementation of the I2C interface.                             |
| `i2c.h`          | Contains the declaration of the I2C interface.                                |
| `main.c`         | Contains the main function and program entry point.                           |
| `process_command.c` | Contains the implementation of the `process_command` function.                  |
| `process_command.h` | Contains the declaration of the `process_command` function.                     |
| `pwm.c`          | Contains the implementation of the Pulse Width Modulation interface.          |
| `pwm.h`          | Contains the declaration of the Pulse Width Modulation interface.             |
| `rgb_led.c`      | Contains the implementation of the RGB LED control functions.                 |
| `rgb_led.h`      | Contains the declaration of the RGB LED control functions.                    |
| `sht21.c`        | Contains the implementation of the SHT21 temperature and humidity sensor.     |
| `sht21.h`        | Contains the declaration of the SHT21 temperature and humidity sensor.        |
| `state_machine.c` | Contains the implementation of the system state machine.                       |
| `statemachine.h` | Contains the declaration of the system state machine.                          |
| `sysclock.c`     | Contains the implementation of the system clock interface.                   |
| `sysclock.h`     | Contains the declaration of the system clock interface.                      |
| `test_cbfifo.c`  | Contains unit tests for the circular FIFO buffer.                            |
| `test_cbfifo.h`  | Contains declarations for the unit tests for the circular FIFO buffer.        |
| `test_sht21.c`   | Contains unit tests for the SHT21 temperature and humidity sensor.            |
| `test_sht21.h`   | Contains declarations for the unit tests for the SHT21 temperature and humidity sensor. |
| `timer.c`        | Contains the implementation of the system timer interface.                   |
| `timer.h`        | Contains the declaration of the system timer interface.                      |
| `TSI.c`          | Contains the implementation of the Touch-Sensing Interface.                  |
| `TSI.h`          | Contains the declaration of the Touch-Sensing Interface.                     |
| `wdt.c`          | Contains the implementation of the Watchdog Timer interface.                 |
| `wdt.h`          | Contains the declaration of the Watchdog Timer interface.                    |

# UART Configuration 
See the screenshot below for UART configurations used and configured using bare metal code in project. 

![Screenshot 2023-05-05 at 4 12 15 AM](https://user-images.githubusercontent.com/111842372/236431700-637999ab-18fe-4000-bb66-823d8dce4c2f.png)

# Calibration Data
### UART
The following #define can be changed in uart.c file to change teh baud rate start bit stop bit settings of UART
```
#define BAUD_RATE 		(38400)          // Set baud rate to 38400
#define UART_OVERSAMPLE_RATE 	(16)
#define SYS_CLOCK 				(24e6)
#define STOP_BIT 				(1)
#define PARITY 					(0)
#define BIT 					(0)
```
### SHT21 Thresholds
Following #defines can be changed in sht21.c and sht21.h file to configure teh default threshold and addresses for temp and hum values readings.
```
static float TEMP_THRESHOLD = 100.00; // temperature threshold
static float HUMD_THRESHOLD = 100.00; // humidity threshold

#define SHT21_ADDRESS 	(0x40)   	// Assign device address for SHT21 as 0x40
#define TEMPERATURE 	(0xE3)     	// Assign master register address for temperature as 0xE3
#define HUMIDITY 		(0xE5)    	// Assign master register address for humidity as 0xE5
```
### Hardware Watchdog Timer
Follwoing #defines can be changed defined in wdt.c and wdt,h file to implement watchdog timer settings

`main.c`
```
#define WDT_TIMEOUT 	COP_CYCLES_03    // Define watchdog timer timeout value
										 // (COP timeout after 2^8 LPO cycles or 2^16 bus clock cycles)
#define WDT_CLK_SRC 	BUS_CLOCK        // Set watchdog timer clock source to bus clock
#define WDT_WIN_MODE 	NORMAL_MODE      // Set watchdog timer window mode to normal mode
```
`wdt.h`
```
// COP Watchdog Timeout
// These write-once bits select the timeout period of the COP.
// The COPT field along with the COPCLKS bit define the COP timeout period.
#define COP_DISABLED    0   //00 COP disabled
#define COP_CYCLES_01   1   //01 COP timeout after 2^5 LPO cycles or 2^13 bus clock cycles
#define COP_CYCLES_02   2   //10 COP timeout after 2^8 LPO cycles or 2^16 bus clock cycles
#define COP_CYCLES_03   3   //11 COP timeout after 2^10 LPO cycles or 2^18 bus clock cycles

//COP Clock Select
//This write-once bit selects the clock source of the COP watchdog.
#define INTERNAL_1KHz   0   //00 Internal 1 kHz clock is source to COP
#define BUS_CLOCK       1   //01 Bus clock is source to COP

// Windowed mode is only supported when COP is running from the bus clock.
// The COP window is opened three quarters through the timeout period.
#define NORMAL_MODE     0   //00 Normal mode
#define WINDOWED_MODE   1   //01 Windowed mode
```
# Missed Commitments<a name="missed-commit"></a>
* Use of Actuators like LCD or Buzzer to indicate different states was not implemented due to time limitation but on the other side very unique LED blinking pattern for each state in statemachine has been implemented called as 'breathing pattern of LED's'
* Use of mode in state machine called `HISTORY Mode` which used to dump value of temperature and humidty from past 1 hours is not implemented due to limitations of HEAP Space.

# Testing<a name="testing"></a>
System has been throughly tested by testing software as well as hardware section.	
* `test_pwm`    : Tests the RGB LED's throughly by blinking each of them for allc olour spectrum ranges with a breathing pattern sequense.
* `test_cbfifo` : Test circular buffer implementation throughly using different corner case.
* `test_sht21`  : Test the SHT21 fingerprint sensor readings by making sure that the sensor readings after the conversion is matching the data sheet requirement and the ranges.

Along with through testing using software sensor was initially tested and verified with different hardware like Arduino Uno and Rasberry PI using different freely available libraray functions for SHT21 sensor.


# Author

Kiran Jojare.   
University of Colorado, Boulder. 
MS- Electrical & Computer Engineering.   

# Extent Bugs

The code meets the basic requirements without issues. However, the only bug discovered is the slow performance of UART when the state machine is running in parallel. I couldn't come up with a solution to make it run faster as both operations rely heavily on interrupts. Aside from the interrupt-based approach, I couldn't find any other way to improve the system's performance.
