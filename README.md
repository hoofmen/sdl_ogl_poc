# SDL OpenGL POC

Simple 3D POC using SDL and OpenGL

### Required Tools
* C/C++
* [SDL 1.2](https://www.libsdl.org/download-1.2.php) for events, texture loading and window management. 
* OpenGL the 3d library

### How to Build
Go to the root directory where main.cpp file is located and run:
 --  On MAC (`must have Xcode and the SDL.framework installed`)
```sh
$ g++ -framework SDL -framework OpenGL main.cpp -o sdl_ogl_poc
```
-- On GNU/Linux (`must have c++/g++, SDL 1.2 and OpenGL installed`)
```sh
$ g++ `sdl-config --cflags --libs` -lGL -lGLU main.cpp -o sdl_ogl_poc 
``` 

