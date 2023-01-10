# Minimalistic walking skeleton for AVR build and program ATmega328P

No Arduino-IDE required. 

LED_BUILTIN blinks with DELAY_MS

## Install dependencies

``` sh
apt install gcc-avr avrdude avr-libc gcc-doc 
```

## VScode setup

.vscode/c_cpp_properties.json
``` json
{
    "configurations": [
        {
            "name": "Linux AVR Atmega328P",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/lib/avr/include"
            ],
            "defines": [
                "F_CPU=16000000L"
            ],
            "compilerPath": "/usr/bin/avr-gcc",
            "cStandard": "gnu11",
            "cppStandard": "gnu++11",
            "intelliSenseMode": "gcc-x86"
        }
    ],
    "version": 4
}
```

## Build and Upload with make

``` sh
make clean
make all
```

## Build and Upload "low level"

``` sh

# Cleanup
rm a.out blink.hex 

# Build executable binary a.out
avr-gcc -mmcu=atmega328p -Ofast blink.c
# Alternatively, use VScode "Run -> Run Build Task..." to build into the file "blink"
# The "Build Task" is configured in .vscode/tasks.json

# What has been build?
file a.out
# => a.out: ELF 32-bit LSB executable, Atmel AVR 8-bit, version 1 (SYSV), statically linked, with debug_info, not stripped

# Create hex from a.out (smaller size)
avr-objcopy -O ihex a.out blink.hex   

# Compare sizes
avr-size a.out blink.hex 
# =>   text    data     bss     dec     hex filename
# =>    162       0       0     162      a2 a.out
# =>      0     162       0     162      a2 blink.hex

stat -c "%s Bytes" a.out 
# => 6456 Bytes
stat -c "%s Bytes" blink.hex 
# => 480 Bytes

# Upload with the programmer
# Also working: -c stk500v1 
avrdude -v -c arduino -P /dev/ttyUSB0 -p atmega328p -b 57600 -U flash:w:blink.hex:i
# Alternatively, upload the a.out instead of hex
avrdude -v -c arduino -P /dev/ttyUSB0 -p atmega328p -b 57600 -U flash:w:a.out:e
```
