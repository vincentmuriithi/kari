# Board dev names

### avr boards:
uno - uno
arduino mega - atmega2560
arduino nano - uses uno static lib so no need to compile for it-have same microprocessor atmega328p
#I't is important to note that for all staic libraries with avr keyword in them 
can work interchangeably and the last name just for showing the board they 
present in the folder they are placed but that doesn't make them incompatible.

### espressif32 boards:
esp32 - lolin32
esp32c3 - esp32-c3-devkitm-1
esp32s3 - uses esp32 i.e lolin32
others - use esp32 name

### espressif8266 boards:
esp8266 - esp12e
AdaFruit Feather HUZZAH 8266 - esp12e
NodeMCU 1.0 - esp21e
ESPectro Core - esp12e
LOLIN(WEMOS) D1 mini Pro
SparkFun Bylnk Board
Generic ESP8285 Module
4D Systems gen4 loD Range

and many more...

**The esp12e board architecture is used for espressif8266 since it is compatible**
**with most of the espressif8266 projects**
#### **Note:exclamation:** precompiled kari is currently not available for Arduino Gemma board