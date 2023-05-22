# MMC_PS_CAN_monitor
CANBUS Engine &amp; AT temperature monitor <br>
Required: 
- Arduino Uno
- MCP2515 CanBus Shield
- Oled Display 0,91" SSD1306 128x32 or similar
- DC-DC step down converter (or you can use USB power supply)
- OBD II Connector 
- Capacitive button module such as TTP223


Required libs:
 - Arduino MCP2515 by autowp https://github.com/autowp/arduino-mcp2515/archive/master.zip
 - Adafruit GFX https://github.com/adafruit/Adafruit-GFX-Library
 - Adafruit SSD1306 https://github.com/adafruit/Adafruit_SSD1306

Wire it up:

Arduino  +  MCP2515  +  TTP223 + OLED <br>

<b>OLED Display</b><br>
5V	-> VCC <br>
GND ->	GND <br>
A5 ->	SCL <br>
A4 ->	SDA <br>

<b>MCP2515</b><br>
Vin	-> 5V <br>
GND ->	GND <br>
D2 ->	INT <br>
D10 ->	CS <br>
D11 ->	SI <br>
D12 ->	SO <br>
D13 ->	SCK <br>

<b>TTP223</b><br>
5V	-> VCC <br>
GND ->	GND <br>
A3 ->	I/O <br>


<b>OBD + MCP2515</b><br>
Can H	-> OBD pin 6 <br>
Can L ->	OBD pin 14 <br>
Termination resistor not req. if connecting thru OBD connector.


 <br>
Incuded can-USB sniffer in serial monitor <br>
You can connect to USB and catch all canbus traffic from 500kBps line (if connected to diagnostic port (ETACS ECU)) <br>
Data will be shown in following format: ID  DLC   DATA <br>

You can decode more parameters and add more pages to display. Switching pages avail. by touching button. 
Added temperature from ECU and instrument clustere (slow) and temp. readings from AT ECU. 
<br>
All will work out of the box on MMCNA Galant IX DM1A 2.4L  


Example of installing OLED display in seatbelt indicator lamp cap:


Enjoy) 
