# MSXTPLibrary 1.0 Beta

There are projects born out of necessity, others out of curiosity, and others still out of love.

This MSX library for Turbo Pascal 3.01 was born from all three.

It was born from the need for modern tools to program a system that is anything but modern. It was born from the curiosity of discovering how far a language such as Pascal can be pushed on a machine like the MSX. And it was born from a deep affection for a platform that defined an era and continues to live thanks to those who study it, expand it and reinvent it.

MSXTPLibrary originally began as a programming exercise and only later evolved into an attempt, still very much a work in progress, to provide a complete interface between the Turbo Pascal language and the MSX system.

MSX-DOS, available on all computers from the original MSX1 to the MSX turbo R equipped with a floppy disk drive, is compatible with CP/M-80. As a result, Borland Turbo Pascal 3, as well as other commercial software of the era such as dBase II, MS COBOL and WordStar, runs perfectly on MSX machines. Naturally, it provides no direct support for exploiting the graphic capabilities of the MSX hardware. Hence the need for a library of procedures and functions capable of building a bridge between Turbo Pascal and the MSX BIOS.

At the time of writing, the library is still in beta status, but it already includes a growing number of functions that allow the creation of practical MSX applications in Turbo Pascal. Because the generated code is compiled rather than interpreted, programs can achieve significantly higher execution speeds than traditional MSX BASIC software.

The compiler generates a bootable .DSK image containing MSXDOS.SYS, COMMAND.COM, the compiled executable and any additional files required by the application. Development can be performed comfortably through modern tools such as the msx-pascal-project-template environment for Visual Studio Code.

# Why Turbo Pascal?

Why create a library for MSX programming using Turbo Pascal?

The first answer is simple: gratitude.

Pascal was the programming language I studied in high school and therefore forms part of my earliest memories as a programmer. When I attended the Feltrinelli Technical Institute in Milan, I was already quite familiar with MSX BASIC, while Pascal represented a more modern and structured approach to software development.

At the time object-oriented programming was only beginning to gain attention, and Turbo Pascal was one of the most widely used educational programming languages. It offered strict typing, a clear syntax, a disciplined structure and, thanks to Borland's outstanding compiler technology, fast and efficient executables.

Even today Turbo Pascal remains an elegant language. Its simplicity encourages good programming practices while remaining remarkably productive.

# Why an MSX Library in 2026?

The MSX belongs to another era.

Yet anyone familiar with the platform knows that it has never truly grown old.

Its modular architecture, open philosophy and passionate community have transformed it into a timeless system.

Turbo Pascal 3.0 for CP/M is equally timeless. It is one of the most elegant programming environments ever created. Its syntax is clear, its structure encourages precision and its logic remains easy to follow.

Bringing together MSX and Pascal means uniting two worlds: the essential and almost poetic hardware of the 1980s with the clarity and discipline of Pascal.

This library exists to make those worlds communicate naturally.

Programming the MSX in Pascal presents very specific challenges. The BIOS was not designed with Pascal in mind. The VDP requires indirect access. VRAM cannot be addressed directly. Sprites rely on complex data structures. The MSX2 mouse uses dedicated communication protocols. Advanced VDP commands are powerful but often difficult to use.

This library attempts to hide much of that complexity.

What began as a programming exercise gradually became a way to simplify, abstract and organize access to MSX hardware while taking advantage of the speed and efficiency of Borland's compiler.

Pascal code interacting with MSX hardware should feel natural, not like a continuous struggle against the machine.

# Library Modules

- MSX.inc
- VDP.inc	
- VRAM.inc	
- Sprites.inc	
- Games.inc	
- Generic.inc	

# Module Overview
MSX.inc — The Foundation

This module contains the constants required by the library, system variables, simulated Z80 registers, VDP register definitions, BIOS entry points and several data types used by different functions and procedures.

It must always be included first.

Without it, the rest of the library cannot exist.

VDP.inc — Graphics

This is where pixels live.

Alongside them live lines, rectangles, graphical text, colors and MSX2 palettes.

It is the module that turns Pascal into a paintbrush.

VRAM.inc — Video Memory

VRAM management is one of the most challenging aspects of MSX programming.

This module simplifies it by providing functions and procedures for reading and writing bytes, transferring data between RAM and VRAM, managing VRAM addresses and using high-speed VDP commands.

Sprites.inc — Movement

Sprites are one of the enduring magical features of the MSX architecture.

This module manages pattern definitions, sprite attributes, MSX2 color assignments, software and hardware collision detection, sprite visibility and movement.

Games.inc — Input

This module contains the procedures and functions required to handle common input devices such as the keyboard, joystick and mouse.

In other words, it gives programs the ability to listen to the user.

Generic.inc — Utility Tools

This module contains a variety of utility functions and procedures.

It is expected to grow as new development needs emerge.

Current contents include hexadecimal conversion routines, sound generation, BASIC command execution and helper functions designed to simplify everyday development tasks.

Small tools, perhaps.

Essential ones, certainly.

# Notes

All procedures and functions have been tested primarily using OpenMSX configured as an MSX2 machine.

Although they also work under MSX2+ and MSX turbo R systems, no hardware-specific optimizations have yet been implemented for those machines.

The routines are intended to be compatible with both MSX1 and MSX2 environments. However, due to memory limitations inherent to standard MSX1 systems, the complete library is not intended to run on original MSX1 hardware. Instead, it allows MSX1-compatible software development on MSX2 and later systems.

Development continues.

At the moment experimentation is underway with the PSG sound chip, and a dedicated PSG.INC module is expected in a future release to provide music and sound support.

# Acknowledgements

This work is dedicated:

to those who love the MSX
to those who love Pascal
to those who love programming
to those who believe that technology can also be poetry

Special thanks, in no particular order, to:

# MSX Italia

A wonderful group of friends through whom I rediscovered the MSX and everything surrounding its world. Although we live in different parts of Italy, genuine friendships have grown from this shared passion.

# Kazuhiko Nishi

For creating the MSX standard and for his enthusiastic participation in the Pisa DevCon organized by MSX Italia.

# Arnaud de Klerk

For his extraordinary work collecting, preserving and sharing an immense amount of MSX documentation, software and historical material with the entire community.

# Kari Lammassaari

Whose libraries inspired many of the ideas behind this project, and from whose work I occasionally learned useful techniques and implementation details.

# decocq-stuff/msx-pascal-project-template

For providing a modern Turbo Pascal development workflow integrated with Visual Studio Code.

# Edison Moraes

For the excellent book MSX Top Secret III, an endless source of information and inspiration.

# C. I. Barkinshaw and R. Goodley

For the book MSX Machine Language, one of the few Italian-language references available during the early years of the MSX.

# Ian Sinclair

For the book MSX Machine Language and Assembly Language Programming, an excellent introduction to Z80 assembly language programming.

# Jacopo Castelfranchi Editore

One of the few Italian publishers that actively supported the MSX ecosystem during its golden years.

# Scuola 2F

Which, perhaps unknowingly, introduced many students to what may have been the only truly Italian MSX computer: the Frael Bruc 100.

# Microsoft Copilot

For occasionally helping me investigate undocumented BIOS functions, discuss implementation strategies and solve technical problems encountered during the development of this library.

# The Global MSX Community

To all the developers, enthusiasts, document authors, hardware designers, archivists and preservationists who have kept the MSX alive through the decades.

# Final Thoughts

MSXTPLibrary is not an attempt to modernize the MSX.

The MSX needs no modernization.

Rather, it is an attempt to make programming for this remarkable machine a little easier, a little cleaner and, hopefully, a little more enjoyable.

If this library helps someone write their first Pascal program on an MSX, then it will already have achieved its goal.
