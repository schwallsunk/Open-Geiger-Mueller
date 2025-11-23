# Open Geiger Müller Counter

This repository should provide all the needed parts for the construction of low-cost entry-level Geiger Müller (GM) counter system. This counter was build by request from the students of 151-0163-00L  Nuclear Energy Conversion at ETH Zürich. 


## The Geiger Müller chamber
The detector is based on either the chinese J321 GM-tube or the soviet SBM-20 GM-tube (can be varied by soldering the negative receptacle either into the spot closer or further away from the HV terminal). The J321 can be easily bought through Aliexpress or ebay whereas for the SBM-20 tube you need to revert to ebay only. 
Due to the overall bigger detection volume of the SBM-20 tube compared with the J321 tube, the sensitivity of the soviet tube will be much higher at the cost of roughly double the price of the J321 tube.


## Microcontroller requirements
The microcontroller of choice here is the Rasperry Pico 2W, allowing for programming in a multitude of languages (Micropython, Arduino, C++, C), lowering the overall barrier to entry into microcontroller (uC) programming. But the PCB itself also supports the Pico W or any other uC with a fitting pin out. 
The W version of the uC also offers a wireless chip set which supports WiFi as well as Bluetooth connectivity, for which a micropython example is available. This example sends the activity according to the Bluetooth LE standard wirelessly to a receiving device.   
