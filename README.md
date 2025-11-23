This repository should provide all the needed parts for the construction of low-cost entry level Geiger Müller (GM) counter system. This counter was build by request from the students of 151-0163-00L  Nuclear Energy Conversion at ETH Zürich. 

The detector is based on either the chinese J321 GM-tube or the soviet SBM-20 GM-tube (can be varied by soldering the negative receptacle either into the spot closer or further away from the HV terminal). The J321 can be easily bought through Aliexpress or ebay whereas for the SBM-20 tube you need to revert to ebay only. 
Due to the overall bigger detection volume of the SBM-20 tube compared with the J321 tube, the sensitivity of the soviet tube will be much higher at the cost of roughly double the price of the J321 tube.

The microcontroller of choice here is the Rasperry Pico 2W, allowing for programming in a multitude of languages (Micropython, Arduino, C++, C), lowering the overall barrier to entry into microcontroller (uC) programming. 
The uC also offers a wireless chip set which supports WiFi as well as Bluetooth connectivity.  
