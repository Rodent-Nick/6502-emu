# 6502-emu
A C++ Emulator of the famous 6502 microprocessor.
Dedicated to a winter vacation of idling and doing nothing.

**An ongoing project from a dabbling hobbyist. Any suggestion welcomed :)**

## Dependencies
- `Catch2` for unit testing.

## Usage
1. Extract the `emu.exe` in the release ZIP file to a directory.
1. Click on it and enter commands. Enter `help` to view a list of availabe
commands.

### To Run a Program
1. Compile your program into binary file.
1. Boot the emulator, and load this file by entering the relative/absolute
address to the binary file `<file-addr>` and the memory offset of the program.
For example, you want your program `a.bin` to be loaded at $0800, enter command:
`load a.bin 0800`.
1. Point the Program Counter `p` to the start of the program. In the previous
example, enter command `setr p 0800`.
1. Enter `run` to run the program until the emulator hit `BRK` or an illegal
operation.
1. As of commit `0feed06`, the emulator lacks peripherals of any kind. So you
must peek memory manually to see the result of a program. After program stops,
enter `showm` with the starting address and size (all in hexidecimal) to view
a segment of the memory. For instance, you can check 16 bytes of memory between
$0200 and $020F by entering `showm 0200 10`.

## Reference
For those who want to build their own emulator, the following material is a very
good place to start IMHO:
1. Andrew Jacobs' Website
[(Archive on 6502.org)](http://6502.org/users/obelisk/)
1. Mag. Norbert Landsteiner's 6502 Instruction Set
[(link)](https://www.masswerk.at/6502/6502_instruction_set.html)
