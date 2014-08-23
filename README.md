
#Ludum Dare 30: Connected Worlds

by Lasty


TODO: Intro


##Build Prerequisites

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

Please feel free to use as a base for your own projects.


