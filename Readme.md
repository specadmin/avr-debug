
# Understand
This is a C++ library for sending any debug information from your **AVR** device to your host machine. It uses an UART interface, that could be assigned to **any** port pin of your controller. So it helps to debug the firmware in AVR devices that have no JTAG and Debugwire interfaces.


### Limits
* The library supports only 16 MHz CPU frequency.
* UART baudrate could be set to 115200 or 1152000 only.
* The library assumes that you are using GNU AVR compiller in your project.


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
#define DEBUG_PORT         PORTD       // debug port register address
#define DEBUG_DDR          DDRD        // debug port direction register address
#define DEBUG_BIT          2           // bit number in debug port
#define DEBUG_BAUD_RATE    1152000     // 115200 or 1152000 only
```

### Optional parameters
```
#define DEBUG_BUF_SIZE     64          // memory buffer size (default: 96 bytes)
#define DEBUG_EXTENDED_DUMP            // appends ASCII dump to the HEX dump
```

### Special parameters
Use it wih care. You should exactly know what you're doing.
```
#define DEBUG_SECTION      .text       // code section for bootloader (if needed)
```
# Include
Add the following line in the firmware modules, where debug is needed
```
#include "lib/debug.h"
```
Also, please ensure that you have a -DF_CPU parameter set in your command line compiller's options.


# Enable
Add -DDEBUG parameter to your compiller command line options. If this parameter is not set, all debug calls will be ommited by the compiller. So, you don't need to remove all of them in release builds.


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

## DREG()

DREG() prints register name and it's value in hexadecimal  format.

### Code
```
DREG(PORTD);
```

### Output
```
PORTD=0x16
```

## DHEX()

DHEX() prints an integer variable value in hexadecimal format

### Code
```
char a=0x1A;
DHEX(a);
int b=0x1A2B;
DHEX(b);
long int c=0x1A2B3C4D;
DHEX(c);
```

### Output
```
1A
1A2B
1A2B3C4D
```

## DHEX8()

DHEX8() prints several byte values in hexadecimal format one by one in the line

### Code
```
char a=0x1A;
char b=0x2B;
unsigned char c=0x3C;
DHEX8(3, a, b, c);
```

### Output
```
1A 2B 3C
```

## DUMP_MEM()

DUMP_MEM() prints RAM dump from the specified location

### Code
```
char a[]="Some large text";
DUMP_MEM(a, sizeof(a));
```

### Output
If DEBUG_EXTENDED_DUMP is defined
```

```

If DEBUG_EXTENDED_DUMP is **not** defined
```

```
