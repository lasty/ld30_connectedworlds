
#Ludum Dare 30 Warmup weekend

by Lasty

##Prerequisites

Build Tools:
* CMake 3.0 or above  (2.8 won't work) 
* GCC 4.8 or above  (uses C++11 features)

Required Libraries:
* SDL2 (2.0.0 or above)
* FreeType (Preferably 2.5.3 or above)
* GLM (0.9.5.4 or above)

If these libraries are not installed in standard locations,
install them to ../libs  or ./libs, or edit the CMakelists.txt
to add additional search paths.


##Building

For Windows, requires MinGW MSYS shell:
```
mkdir Debug
cd Debug
cmake -G"MSYS Makefiles" ..
make
make install    # Installs the .dll files
```

For Linux/MacOSX: (Not yet tested)
(Assumes libraries are installed and accessible in the system PATH)
```
mkdir Debug
cd Debug
cmake ..
make
```


