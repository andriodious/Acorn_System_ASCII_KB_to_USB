# SystemASCIItoUSB
Acorn System ASCII keyboard to USB keyboard

This board powers an Acorn System ASCII keyboard and reads in and translates each key output when triggered by NSTROBE 

It requires a Teensy++2.0, for more details on setting up this device please see:

https://www.pjrc.com/teensy/teensyduino.html

A diode on the PCB is to prevent the teensy board being powered when a System computer is powering the keyboard in native mode.