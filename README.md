# Electric Water Heater
### Quick Hints
> This is an AVR ATMEGA32 based project.
>
> Documentation of the project is a Doxygen which is inside `Application_Code\docs\doxygen`.
>
> The doxygen html file is here `Application_Code\docs\doxygen\html\index.html`.
>


### Role of the project
___
The project idea in simple points:

-  Control water temperature using heater and cooler.
- Getting water temperature value using LM35 sensor.
- Depend on the last 10 readings, cooler or heater is turned ON/OFF.
- Also current temperature is displayed using 7 Segments 2 digits display.
- There are two push buttons to control temperature set point and a push button to turn system ON or OFF.
- An EEPROM is used to store the last temperature set point which set by the user so that when system is turned on after off the last temperature set point is still in the system operation.
- A LED is used to dedicate the state of cooler or heater. When it is turned on, that means the heater is on. When it blinks, that means the cooler is on.


> This project depend on AVR timer for operation and external interrupt for push buttons. 


### Specifications for each hardware module:
___
#### 1. Temperature Setting:
- The **UP** or **DOWN** buttons are used to change the required water temperature (set temperature).
- The first **UP** or **DOWN** button press, enters the temperature setting mode.
- After entering temperature setting mode, a single **UP** button press increase the set temperature by 5 degrees.
- After entering temperature setting mode, a single **DOWN** button press decrease the set temperature by 5 degrees.
- The minimum possible set temperature is 35 degrees.
- The maximum possible set temperature is 75 degrees.
- The **External EEPROM** should save the set temperature once set.
- If the electric water heater is turned OFF then ON, the stored set temperature should be retrieved from the **External EEPROM**.
- The initial temperature is 60 degrees.

#### 2. ON/OFF Behavior:
- If power is connected to the heater,the electric water heater is in OFF state.
- If the **ON/OFF** button is released and the electric water heater is in OFF state, the electric water heater goes to ON state.
- If the **ON/OFF** button is released and the electric water heater is in ON state, the electric water heater goes to OFF state.
- In the OFF state, all display should be turned OFF
	
#### 3. Temperature Sensing
- The temperature sensor measures the water temperature.
- The water temperature should increase, if the **Heating Element** is ON.
- The water temperature should decrease, if the **Cooling Element** is ON.
- Temperature should be sensed once every 100 ms.
- The decision to turn ON or OFF either the **Heating Element** or the **Cooling Element** based on the average of the last 10 temperature readings.

#### 4. Heating/Cooling Elements
- The **Heating Element** should be turned ON, if the current water temperature is less than the set temperature by 5 degrees.
- The **Cooling Element** should be turned OFF, if the current water temperature is less than the set temperature by 5 degrees.
- The **Heating Element** should be turned OFF, if the current water temperature is greater than the set temperature by 5 degrees.
- The **Cooling Element** should be turned ON, if the current water temperature is greater than the set temperature by 5 degrees.

#### 5. Seven Segments
- Seven segment by default show the current water temperature or the set temperature.
- By default, the 2 seven segment display are show the current water temperature.
- If the electric water heater is in the temperature setting mode, the 2 seven segment displays should blink every 1 second and show the set temperature.
- In the temperature setting mode, every change in the set temperature should be reflected on the 2 seven segment displays.
- The 2 seven segment display should exit the temperature setting mode, if the
- **UP** and **DOWN** buttons are not pressed for 5 seconds

#### 6. Heating Element Led
- If the **Heating Element** is ON, the **Heating Element Led** should blink every 1 second.
- If the **Cooling Element** is ON, the **Heating Element Led** should be ON.
