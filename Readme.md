#MSXTPLibrary

An open-source Turbo Pascal 3.01 library for MSX computers.

Bringing modern Pascal development to the MSX platform.

MSXTPLibrary is a collection of procedures, functions and system definitions that provide a convenient interface between Borland Turbo Pascal 3 and the MSX BIOS.

The project was originally created as a programming exercise and gradually evolved into a more ambitious goal: providing a complete and easy-to-use development library for MSX programmers who wish to develop software in Turbo Pascal.

Current release: Beta 1.0

#Features

#Graphics
Screen mode management
Pixel plotting
Lines and rectangles
Color handling
MSX2 palette support

#VRAM
VRAM read/write routines
RAM ↔ VRAM transfer functions
VRAM addressing utilities
High-speed VDP command support

#Sprites
Pattern definition
Attribute management
MSX1 and MSX2 sprite support
Hardware and software collision detection
Sprite movement routines

#Input Devices
Keyboard handling
Joystick support
Mouse support
Cursor and trigger management

#Utilities
Hexadecimal conversion
Sound generation (Beep)
BASIC command execution
General-purpose helper routines

#Library Modules
Module	Description
MSX.inc	Core definitions, BIOS entries, VDP registers, system variables
VDP.inc	Graphics and screen management
VRAM.inc	Video memory manipulation
Sprites.inc	Sprite management
Games.inc	User input management
Generic.inc	Utility functions

#Requirements
MSX-DOS
Turbo Pascal 3.01 for CP/M
MSX2 or newer recommended

The library has been primarily tested using OpenMSX configured as an MSX2 machine.

#Project Status

⚠️ This project is currently in Beta status.

The API may change as development continues and new modules are added.

Planned future additions include:

PSG sound library
Music support
Additional VDP helpers
Expanded game-development functions

#Documentation

Complete documentation can be found in the /docs directory.

Available documentation:

Introduction_EN.md
Introduction_IT.md
Modules.md
Reference Manual

#Compatibility
System	Status
MSX1	Partial
MSX2	Supported
MSX2+	Supported
MSX turbo R	Supported

#Acknowledgements

Special thanks to:

MSX Italia
Kazuhiko Nishi
Kari Lammassaari
Edison Moraes
Ian Sinclair
C. I. Barkinshaw
R. Goodley
Jacopo Castelfranchi Editore
Contributors of MSX Pascal Project Template

For complete acknowledgements see:

ACKNOWLEDGEMENTS.md

#License

Released under the MIT License.

See the LICENSE file for details.

About This Project

This library was created by an MSX enthusiast who simply wanted to explore how far Turbo Pascal could be pushed on a platform that continues to inspire creativity more than forty years after its introduction.

If you also believe that retro-computing is about exploration, learning and fun, then this project is for you.
