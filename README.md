# Open Geiger Müller Counter

This repository should provide all the needed parts for the construction of low-cost entry-level Geiger Müller (GM) counter system. This counter was build by request from the students of 151-0163-00L  Nuclear Energy Conversion at ETH Zürich. 

The repository itself is subdivided into two two main parts. The hardware parts contains all the relevant EDA files created in KiCAD v9. The software directory contains all the different code written and tested for and on the hardware.

![Both GM-counters completed with J321 GM-tube as well as SBM-20 tube](https://github.com/schwallsunk/Open-Geiger-Mueller/blob/main/resources/Both_versions_GM.png)


## The Geiger Müller chamber :radioactive:
The detector is based on either the chinese J321 GM-tube or the soviet SBM-20 GM-tube (can be varied by soldering the negative receptacle either into the spot closer or further away from the HV terminal). The J321 can be easily bought through Aliexpress or ebay whereas for the SBM-20 tube you need to revert to ebay only. 
Due to the overall bigger detection volume of the SBM-20 tube compared with the J321 tube, the sensitivity of the soviet tube will be much higher at the cost of roughly double the price of the J321 tube.


## Microcontroller
The microcontroller of choice here is the Rasperry Pico 2W (rp2350 + wifi chipset), allowing for programming in a multitude of languages (Micropython, Arduino, C++, C), lowering the overall barrier to entry into microcontroller (uC) programming. But the PCB itself also supports the Pico W or any other uC with a fitting pin out. 
The W version of the uC also offers a wireless chip set which supports WiFi as well as Bluetooth connectivity, for which a micropython example is available. This example sends the activity according to the Bluetooth LE standard wirelessly to a receiving device. 
But in case of budgetary concerns, a Rasperry Pico can also be used as a drop-in replacement. The RISC-V-based implementation in this repository might then not work, though.

### Without IDE install
For an easier starting point, there is a precompiled firmware already available in this repository under [FW-file](https://github.com/schwallsunk/Open-Geiger-Mueller/blob/main/software/cpp/Counter_cpp_RISC-V.uf2). This file can be easily flashed by holding down the only button on the Raspberry Pico and plugging it into the USB port of the PC. 
The Pico will then appear as a mass storage device (The button on the Pico can be released at this point ) onto which the given firmware .uf2 file can be dragged and dropped onto it. The microcontroller will reboot by itself as soon as the new firmware file is fully transferred.
From there on, the clicking noise of the background radiation should be heard.


### IDE firmware development
If the goal is to do micropython code development, the following documentation [chapter 4](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-python-sdk.pdf) might be useful. All the given Micropython examples can be copied and pasted into the IDE and directly deployed. 
For the C/C++ code part, there is either a way to do full code development with the [C/C++ IDE](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline), where the given code example can be copied and pasted into the given editor and then, at a later stag,e converted into a binary.  


## Electronics

### Parts sourcing
The sourcing of the components for this project was done entirely through the [LCSC](https://www.lcsc.com/) except for the GM-tube as well as the Raspberry Pico 2W. The GM-tube was bought off [EBAY SBM-20 search](https://www.ebay.com/sch/i.html?_nkw=sbm20&_sacat=0&_from=R40&_trksid=p4624852.m570.l1313) and the Pico 2W can be bought from your local electronics reseller.

### PCB manufacturing
The custom printed circuit board (PCB) itself was produced by sending the relevant gerber files to [JLCPCB](https://www.jlcpcb.com/) and choosing a black finish apart from that there is nothing special to consider when ordering them. The relevant gerber files are all merged into a single zip. This zip can be found in the hardware part of this repository.


### BOM 
| LCSC part number | Part description                                          | Amount | Price per piece (USD/piece) | Label of Part on PCB                    |
|------------------|-----------------------------------------------------------|--------|-----------------------------|----------------------------------------|
| C252915          | 2.048kHz 3.3V Electromagnetic Through Hole Buzzer         | 1      | 0.1854                      | BZ1                                    |
| C49234238        | Through Hole Pushbutton Switches RoHS                     | 4      | 0.0809                      | SW1, SW2, SW3, SW4                     |
| C2894588         | Carbon Film Resistor 300Ω                                 | 1      | 0.0043                      | R2                                     |
| C122827          | Metal Film Resistor 22Ω 3W                                | 1      | 0.0392                      | R1                                     |
| C2686215         | 10nF -40°C~+110°C ±5% 1kV)                                | 1      | 0.0969                      | C1                                     |
| C714352          | Carbon Film Resistor 10kΩ 500mW                           | 6      | 0.0081                      | R6,R8,R10,R11,R12,R13                  |
| C142864          | Cylindrical Clip Through Hole,P=7.6mm Fuseholders RoHS    | 2      | 0.1619                      | HV POS (+) and either J321 or SBM-20   |
| C20613339        | 20mA 5 mm flat-head LED                                   | 1      | 0.1041                      | D5                                     |
| C433559          | Metal Film Resistor 22kΩ 3W                               | 1      | 0.0549                      | R4                                     |
| C5156722         | 40V 625mW 200mA NPN TO-92 Single Bipolar Transistors RoHS | 1      | 0.0391                      | Q2                                     |
| C30190409        | Glass Glaze Resistor 4.7MΩ                                | 1      | 0.0553                      | R3                                     |
| C2924242         | 100mA 10mH ±10% Drum-core inductor                        | 1      | 0.173                       | L1                                     |
| C152300          | 30A 175ns 600V 1V@1A 1A DO-41 Single Diodes RoHS          | 1      | 0.0655                      | D1 => look at polarity when installing |
| C256388          | 400V 2.1W 1.5A NPN TO-92 Single Bipolar Transistors RoHS  | 1      | 0.1451                      | Q1                                     |
| C122214          | 100kΩ 1W ±250ppm/°C                                       | 1      | 0.0923                      | R5                                     |
| C7499336         | Pin header 2.54mm 20P                                     | 2      | 0.1601                      | A1 both rows                           |
| C434407          | 220pF capacitor                                           | 1      | 0.2914                      | C2                                     |

