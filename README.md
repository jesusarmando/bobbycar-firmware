# bobbycar-firmware
Development happens inside QtCreator, no other shitty IDEs.

To compile software for the two hoverboard controllers:
```
git clone --recursive git@github.com:0xFEEDC0DE64/bobbycar-firmware.git
mkdir -v build_bobbycar-firmware
cd build_bobbycar-firmware
cmake ../bobbycar-firmware
make unlock0 # needed only once
make flash
```

To compile the software for the ESP32 board computer with display:
```
git clone --recursive git@github.com:0xFEEDC0DE64/bobbycar-firmware.git
cd build_bobbycar-firmware/boardcomputer
platformio init --ide qtcreator
platformio run --target upload
```

TODO: connection diagrams between boardcomputer, displays, potis and motor controllers.

## with Field Oriented Control (FOC)

This repository implements Field Oriented Control (FOC) for stock hoverboards. Compared to the commutation method, this new FOC control method offers superior performance featuring:
 - reduced noise and vibrations
 - smooth torque output and improved motor efficiency. Thus, lower energy consumption
 - field weakening to increase maximum speed range

 This new firmware offers 3 control modes:
  - **VOLTAGE MODE**: in this mode the controller applies a constant Voltage to the motors
  - **SPEED MODE**: in this mode a closed-loop controller realizes the input target speed by rejecting any of the disturbance (resistive load) applied to the motor
  - **TORQUE MODE**: in this mode the target torque set by the user is realized. This mode enables motor "freewheeling" when the torque target is "0".

  **NOTE**: In all the modes, the controller features maximum motor speed and maximum motor current protection. This brings great advantages to fulfil the needs of many robotic applications while maintaining safe operation.

### Firmware architecture

The main firmware architecture includes:
- **Estimations**: estimates the rotor position, angle and motor speed based on Hall sensors signal
- **Diagnostics**: implements error detection such as unconnected Hall sensor, motor blocked, MOSFET defective
- **Control Manager**: manages the transitions between control modes (Voltage, Speed, Torque)
- **FOC Algorithm**: implements the FOC strategy
- **Control Type Manager**: Manages the transition between Commutation, Sinusoidal, and FOC control type

![Firmware architecture](/docs/pictures/FW_architecture.png)

The FOC algorithm architecture is illustrated in the figure below:

![FOC algorithm](/docs/pictures/FOC_algorithm.png)

In this firmware 3 control types are available:
- Commutation
- SIN (Sinusoidal)
- FOC (Field Oriented Control)
![Schematic representation of the available control methods](/01_Matlab/02_Figures/control_methods.png)


---
## General Notes
 - The C code for the controller was auto-code generated using [Matlab/Simulink](https://nl.mathworks.com/solutions/embedded-code-generation.html) from a model which I developed from scratch specifically for hoverboard control. For more details regarding the working principle of the controller please consult the [Matlab/Simulink model](/01_Matlab).
 - A [webview](/01_Matlab/BLDC_controller_ert_rtw/html/webview) was created, so Matlab/Simulink installation is not needed, unless you want to regenerate the code. The webview is an html page that can be opened with browsers like: Microsoft Internet Explorer or Microsoft Edge.

### Field Weakening / Phase Advance

 - By default the Field weakening is enabled. You can disable it in config.h file by setting the FIELD_WEAK_ENA = 0
 - The Field Weakening is a linear interpolation from 0 to FIELD_WEAK_MAX or PHASE_ADV_MAX (depeding if FOC or SIN is selected, respectively)
 - The Field Weakening starts engaging at FIELD_WEAK_LO and reaches the maximum value at FIELD_WEAK_HI
 - The figure below shows different possible calibrations for Field Weakening / Phase Advance
 ![Field Weakening](/docs/pictures/FieldWeakening.png)
 - If you re-calibrate the Field Weakening please take all the safety measures! The motors can spin very fast!


### Parameters
 - All the calibratable motor parameters can be found in the 'BLDC_controller_data.c'. I provided you with an already calibrated controller, but if you feel like fine tuning it feel free to do so
 - The parameters are represented in Fixed-point data type for a more efficient code execution
 - For calibrating the fixed-point parameters use the [Fixed-Point Viewer](https://github.com/EmanuelFeru/FixedPointViewer) tool
 - The parameters data Fixed-point types are given in the following table:

![Parameters table](/docs/pictures/paramTable.png)


### Diagnostics
Each motor is constantly monitored for errors. These errors are:
- **Error 001**: Hall sensor not connected
- **Error 002**: Hall sensor short circuit
- **Error 004**: Motor NOT able to spin (Possible causes: motor phase disconnected, MOSFET defective, operational Amplifier defective, motor blocked)

The error codes above are reported for each motor in the variables **errCode_Left** and **errCode_Right** for Left motor (long wired motor) and Right motor (short wired motor), respectively. In case of error, the motor power is reduced to 0, while an audible (fast beep) can be heard to notify the user.

---

## Hardware
![otter](https://raw.githubusercontent.com/EmanuelFeru/hoverboard-firmware-hack/master/pinout.png)

[►Video: HOVERCAR demo](https://drive.google.com/open?id=18IvRJVdQSsjTg1I0Wedlg19e0FuDjfdS)


---


Demo videos:

[►Video: Commutation vs Advanced control (constant speed)](https://drive.google.com/open?id=1vC_kEkp2LE2lAaMCJcmK4z2m3jrPUoBD)

[►Video: Commutation vs Advanced control (variable speed)](https://drive.google.com/open?id=1rrQ4k5VLhhAWXQzDSCar_SmEdsbM-hq2)

[►Video: Reliable Serial Communication demo](https://drive.google.com/open?id=1mUM-p7SE6gmyTH7zhDHy5DUyczXvmy5d)

[►Video: HOVERCAR demo](https://drive.google.com/open?id=18IvRJVdQSsjTg1I0Wedlg19e0FuDjfdS)

![Hoverboard wheel](/docs/pictures/hoverboard_wheel.JPG)


---

## Flashing
To build the firmware, just type "make flash". Right to the STM32, there is a debugging header with GND, 3V3, SWDIO and SWCLK. Connect GND, SWDIO and SWCLK to your SWD programmer, like the ST-Link found on many STM devboards.

Right to the STM32, there is a debugging header with GND, 3V3, SWDIO and SWCLK. Connect GND, SWDIO and SWCLK to your SWD programmer, like the ST-Link found on many STM devboards.

If you have never flashed your sideboard before, the MCU is probably locked. To unlock the flash, check-out the wiki page [How to Unlock MCU flash](https://github.com/EmanuelFeru/hoverboard-firmware-hack-FOC/wiki/How-to-Unlock-MCU-flash).

Do not power the mainboard from the 3.3V of your programmer! This has already killed multiple mainboards.

Make sure you hold the powerbutton or connect a jumper to the power button pins while flashing the firmware, as the STM might release the power latch and switches itself off during flashing. Battery > 36V have to be connected while flashing.

To build and flash choose one of the following methods:

If you never flashed your mainboard before, the STM is probably locked. To unlock the flash, use the following OpenOCD command:
```
make unlock0
```

- open the folder in the IDE of choice (vscode or Atom)
- press the 'PlatformIO:Build' or the 'PlatformIO:Upload' button (bottom left in vscode).

### Method 2: Using Keil uVision

- in [Keil uVision](https://www.keil.com/download/product/), open the [mainboard-hack.uvproj](/MDK-ARM/)
- if you are asked to install missing packages, click Yes
- click Build Target (or press F7) to build the firmware
- click Load Code (or press F8) to flash the firmware.

### Method 3: Using Ubuntu

- prerequisites: install [ST-Flash utility](https://github.com/texane/stlink).
- open a terminal in the repo check-out folder and type:
```
make unlock1
```
- flash the firmware by typing:
```
make unlock2
```

---
## Troubleshooting
First, check that power is connected and voltage is >36V while flashing.
If the board draws more than 100mA in idle, it's probably broken.

If the motors do something, but don't rotate smooth and quietly, try to use an alternative phase mapping. Usually, color-correct mapping (blue to blue, green to green, yellow to yellow) works fine. However, some hoverboards have a different layout then others, and this might be the reason your motor isn't spinning.

---
## Acknowledgements

Last but not least, I would like to acknowledge and thank the following people:
- Original firmware: [@NiklasFauth](https://github.com/NiklasFauth)
- Github: [@TomTinkering](https://github.com/TomTinkering), [@ced2c](https://github.com/ced2c), [@btsimonh](https://github.com/btsimonh), [@lalalandrus](https://github.com/lalalandrus), [@p-h-a-i-l](https://github.com/p-h-a-i-l) , [@AntumArk](https://github.com/AntumArk), [@juodumas](https://github.com/juodumas)
- Github: all the people that contributed via Pull Requests
- ST Employee: [cedric H](https://community.st.com/s/question/0D50X0000B28qTDSQY/custom-foc-control-current-measurement-dma-timer-interrupt-needs-review)


---
## Contributions

Every contribution to this repository is highly appreciated! Feel free to create pull requests to improve this firmware as ultimately you are going to help everyone. 

If you want to donate to keep this firmware updated, please use the link below:

[![paypal](https://www.paypalobjects.com/en_US/NL/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=CU2SWN2XV9SCY&currency_code=EUR&source=url)

---

