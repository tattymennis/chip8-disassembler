# CHIP-8 Disassembler in C++ </br>

## Written by Matthew Tennis </br>
## matthewtennisypr@gmail.com </br>

This is my first real program written in C++ and reflects a multi-front learning curve. 

[+] The following program is a disassembler for CHIP-8 ROMs and binaries. </br>
[+] The following sources were used and referenced for specifications:</br>
  [++] http://devernay.free.fr/hacks/chip8/C8TECH10.HTM</br>
  [++] https://en.wikipedia.org/wiki/CHIP-8</br>
  [++] https://github.com/badlogic/chip8/tree/master/roms (for ROM input)</br>
[+] Target operating system: Ubuntu 16.04.2 LTS xenial (little endian system)</br>
[+] This program is written in C++ and compiled on g++ 5.4.0</br>
[+] This program must be compiled with g++ w/ --std=c++0x switch on a Debian machine</br>

[+] Compilation</br>
  [++] Either run the Bash script provided: ./compile.sh</br>
  [++] Or manually enter: g++ -Wall -Wextra -Werror --std=c++0x -o NAME main.cpp where NAME is the desired executable name.</br>
  [+++] Variance on compiler arguments have not been tested, and omitting the --std=c++0x switch will result in failure to compile.</br>

[+] Execution</br>
  [++] ROMs have been provided for testing in roms/</br>
  [++] Program requires one argument that is a CHIP-8 binary</br>
  [++] Syntax: ./disassembler name.rom</br>
  [++] Future versions will implement multi-file handling</br>
  
