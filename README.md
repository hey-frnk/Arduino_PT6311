# Arduino PT6311
A simple driver for PT6311 VFD display controller in Arduino using SPI

- pt6311.h/pt6311.cpp: PT6311 driver using SPI interface. Not all functions according to datasheet are implemented; the functions are not inside an object to ensure compatibility to upper level code, which is written in platform independent C language. Includes setup, brightness, on/off, display data and input reading from input SW
-  vfd_8d14s.h/vfd_8d14s.c: Abstraction for a Chinese AOTOM 20070-1A04 8 digit, 14 segment VFD display built upon PT6311 driver. Can be used to display a single character, or a C-String and includes a hand crafted ASCII map

### Changelog
09-18-2020:
- Initial commit