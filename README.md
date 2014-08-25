
# Starving Symbiosis

(For Ludum Dare 30: Connected Worlds)

by Lasty   @tristan_lasty

https://github.com/lasty/ld30_connectedworlds

##TL;DR

* Get Coins from UnderWorld
* Buy Food in OverWorld
* Use Portal to transfer
* Press TAB to change worlds


# Intro

You and a friend have found yourself in a predicament.

You are both hungry, and need to buy food.

However, one person has all the shops, and one person has all the coins.

You must share items using the portal to survive.



## Instructions

In game help is available onscreen.

* Use WSAD/Arrows to move, mouse pointer to aim.
* Left click to eat,  Right click to throw.
* TAB to change worlds
* 1-5 to change your current inventory slot.
* ESC to quit
* N for new game.


## Regrets

Yeah, I ran out of time.

I was planning to have weapons, and some sort of zombie wave / tower defence on the overworld,
using metal ores mined in the underworld.

But yeah... No time :(  There's always next Ludum Dare.



##Build Prerequisites

Should Build in Windows (MSYS/Mingw), Macosx (Clang/Xcode) or Linux (Clang or GCC).

###Build Tools:
* CMake 3.0 or above  (2.8 won't work) 
* GCC 4.8 or above  (uses C++11 features)

###Required Libraries:
* SDL2 (2.0.0 or above)
* SDL_Image (2.0.0 or above)
* SDL_Mixer (2.0.0 or above)
* FreeType (Preferably 2.5.3 or above, should work with any 2.x)
* GLM (0.9.5.1 or above)

If these libraries are not installed in standard locations,
install them to `../libs`  or `./libs`, or edit the CMakelists.txt
to add additional search paths.


## Library URLs

+ SDL2  (Currently 2.0.3)

	http://www.libsdl.org/download-2.0.php

+ SDL2_Image  (2.0.0)  (Get the devel versions)

	https://www.libsdl.org/projects/SDL_image/

+ SDL2_Mixer  (2.0.0)  (Get the devel versions)

	https://www.libsdl.org/projects/SDL_mixer/

+ Freetype

	http://www.freetype.org/download.html
	(Windows users get both the dev and runtime files from the GTK link)

+ GLM (OpenGL mathematics Library)

	http://glm.g-truc.net/


##Building

Uses CMake out-of-source building.  Easist way is to create a
subdirectory and point to the parent .. directory.

For Windows, requires MinGW MSYS shell:
```
mkdir Debug
cd Debug
cmake -G"MSYS Makefiles" ..
make
make install    # Installs the .dll files
```

For Linux/MacOSX:
```
mkdir Debug
cd Debug
cmake ..
make
```

##Licence

Released under BSD licence.


