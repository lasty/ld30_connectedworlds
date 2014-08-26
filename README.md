
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


## Platform Notes

####Windows 64bit
(I used Windows 8.1, should work on Vista/7 too)

If Windows 8 is giving you a "Windows Protected Your PC" message,
click "More info" then "Run Anyway".


####MacOSX 64bit Mavericks
(Probably wont run on earlier versions.  The upgrade to Mavericks is free now, so..)

If MacOSX gives you an "Untrusted Developer" warning, Control-RightClick the app, and
choose Open, then click Open.


####Linux 64bit
(I am using Ubuntu 14.04)

If it complains about missing libraries, just run this, it will install
all the required libraries.  (This is for Ubuntu 14.04)

`$ sudo apt-get install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libfreetype6`

## Release History
#### LD30_Patch1

Small patch fixing some bugs:

* Coins now respawn on the underworld when picked up
* Adjusted value of Potato Salad (was too expensive per food than the others)
* Food gives you health (equal to its food value).  Can't believe I missed that.

And fixing some minor issues:

* Adjusted starting hunger values (More time to get used to the game)
* Changed text on shop/portal to make it more obvious what to do
* Added pickup text (Shows name of the item when picked up)
* Increased font size for Health/Hunger


#### LD30_Submit

* Initial version released to Ludum Dare competition just before the deadline.


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


For Linux/Ubuntu, use this to get the developer versions of the libraries:

`$ sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev libfreetype6-dev libglm-dev`

But unfortunately you will need to get CMake 3.0 manually..


##Licence

Released under BSD licence.


