# Source-sdk

**Source-sdk** is meant to be a powerful, easy to use toolkit to understand the inner core of the Source Game Engine. 
In easier words, our project stands as a base to help people improve upon their game hacking skills.

# Branching

This base has been designed to be able to use in almost all the existing source games.  
By default, we have decided to make three branches for the specified games:
- Counter-Strike: Source
- Team Fortress 2
- Left 4 Dead 2

There is also the main branch which just follows the base Source Game Engine and is very bare bones.  
  
**You are currently on the Counter-Strike: Source branch**
**NOTE: This branch has been developed on the Counter-Strike: Source STEAM v93 version!**

# Features

## Project
- Organized in easy to understand directories
- Uses C++20 features
- Well commented source code
- Use of PascalCase for objects and camelCase for variables

## Functionality
- Debug utilities (LOG macro)
- Input library (WndProc)
- Memory library (Pattern scanning, module caching)
- Crash handler (Exceptions)
- Easy to use interface manager (Fetch interfaces from the interface list / by signatures)
- Easy to use netvar manager (Including dumping netvars and clientclass ids to text files)
- Easy to use rendering library based on source engine drawing wrapper (ISurface)
- Easy to use event listener
- Math utilities (WorldToScreen, vector/matrix math functions)
- Simple VMT Hooking library
- Few hooks like CreateMove, PaintTraverse etc. in order to exemplify functionality
- Base entity classes and datatypes
- Features like entity bounding boxes, bunny hop
- ... Many other miscellaneous entries!

Although the sdk isn't empty at all, we still consider it not quite complete.  
There are still many features to add / improve upon such as:  
- Making your own menu using the renderer
- Adding proper engine prediction
- ... Whatever comes through your mind!

# Licensing

This project runs under the GNU GENERAL PUBLIC LICENSE (Version 3, 29 June 2007).  
Read the LICENSE file for more information.
