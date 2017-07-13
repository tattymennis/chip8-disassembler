#CHIP-8 Disassembler in C++

##Written by Matthew Tennis
##matthewtennisypr@gmail.com

This is my first real program written in C++ and reflects a multi-front learning curve. 

[+] The following program is a disassembler for CHIP-8 ROMs and binaries.
[+] The following sources were used and referenced for specifications:
  [++] http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
  [++] https://en.wikipedia.org/wiki/CHIP-8
  [++] https://github.com/badlogic/chip8/tree/master/roms (for ROM input)
[+] Target operating system: Ubuntu 16.04.2 LTS xenial (little endian system)
[+] This program is written in C++ and compiled on g++ 5.4.0
[+] This program must be compiled with g++ w/ --std=c++0x switch on a Debian machine

[+] Compilation
  [++] Either run the Bash script provided: ./compile.sh
  [++] Or manually enter: g++ -Wall -Wextra -Werror --std=c++0x -o NAME main.cpp where NAME is the desired executable name.
  [+++] Variance on compiler arguments have not been tested, and omitting the --std=c++0x switch will result in failure to compile.

[+] Execution
  [++] ROMs have been provided for testing in roms/
  [++] Program requires one argument that is a CHIP-8 binary
  [++] Syntax: ./disassembler name.rom
  [++] Future versions will implement multi-file handling
  
