# GPIOrca

Listens on a UDP port and repeats what is receives out of a serial port. Serial Baud fixed at 19200 at the moment but i intend to add the option to set it at some point. Its not har to change anyway, just set the desired baud in *serial.c*! Originaly made to interface serial hardware with orca projects.

## Build

```
make
```

## Options
-p set the port number  
-s set the serial port

## Example 
```
gpiorca -p 12345 -s /dev/ttyUSB0
