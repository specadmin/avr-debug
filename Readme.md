# Understand
This is a C++ library for sending any debug information from your **AVR** device to your host machine. It uses an UART interface, that could be assigned to **any** pin of your controller. So it helps to debug the firmware in AVR devices that have no JTAG and Debugwire interfaces.

The library assumes that you are using GNU AVR compiller in your project.


# Connect
Use USB UART adapter or RS232 adapter to connect your controller to the host machine. Connect adapter's RX pin to the assigned pin (see Configure) and don't forget about GND.

# Add to your project
```
git submodule add https://github.com/specadmin/avr-debug lib/avr-debug
```

# Configure

Add or edit config.sh in your include directory

### Required parameters
```
#define DEBUG_PORT         PORTD    // debug port register address
#define DEBUG_DDR          DDRD     // debug port direction register address
#define DEBUG_BIT          2        // bit number in debug port
#define DEBUG_BAUD_RATE    1152000  // 115200 or 1152000 only
```

### Optional parameters
```
#define DEBUG_BUF_SIZE     64       // memory buffer size (default: 96 bytes)
#define DEBUG_EXTENDED_DUMP         // appends ASCII dump to the HEX dump
```

### Special parameters
Use it wih care. You should know what you're doing.
```
#define DEBUG_SECTION      .text    // code section for bootloader (if needed)
```
# Include
Add the following line in the firmware modules, where debug is needed
```
#include "lib/debug.h"
```

# Use

## DSTR()

DSTR() prints constant string with carrier return (\n). The string is printed from FLASH memory directly, saving your RAM.

### Code
```
DSTR("Hello world!");
DSTR("It works!");
```

### Output
```
Hello world!
It works!
```


## DSTRN()

DSTRN() prints constant string without carrier return. The string is printed from FLASH memory directly, saving your RAM.

### Code
```
DSTRN("Hello world!");
DSTRN("It works!");
```

### Output
```
Hello world!It works!
```

## DVAR()

DVAR() prints an integer variable name and its value in decimal view.

### Code
```
char a=10;
DVAR(a);
unsigned char b=200;
DVAR(b);
int c=45000;
DVAR(c);
long int d=1000000;
DVAR(d);
DVAR(a+b);
```

### Output
```
a=10
b=200
c=45000
d=1000000
a+b=210
```
