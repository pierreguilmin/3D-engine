# 3D-engine

![basic_scene.gif](demo.gif)

### Work with this repository

To clone this repository on your local computer please run:
```bash
$ git clone https://github.com/PierreGuilmin/3D-engine.git
```

This project was written under C++ (C++11). It uses the open-source library [SFML](https://www.sfml-dev.org/index.php) (SFML 2.5.0) which is a cross-platform library written in C++ to open window, draw 2d lines/images, handle the keyboard and the mouse... The easiest way to install it on a mac is by using the (famous) [🍺 Homebrew](https://brew.sh) package manager:
```bash
$ brew install sfml
```
Otherwise the library can be compiled from source on the SFML website under the [Download](https://www.sfml-dev.org/download/sfml/2.5.0/index.php) section.

The default compilater used in the makefile is `clang++`. Running the following command in the project folder will compile the sources and create an executable called **3D-engine**:
```bash
$ make
```

To clean the project `.o` and `.d` located in `/obj` and remove the executable you can run in the project folder:
```bash
$ make clean
```

If you don't have `clang++` you can compile the project with any another compiler (`g++` for example), by modifying the two first lines of the `makefile` to match your compiler:
```bash
# current makefile first lines
CXX      = clang++ # compiler name
CXXFLAGS = -Weverything -Wno-c++11-extensions -Wno-padded -Wno-c++98-compat -Wno-float-conversion -Wno-conversion -std=c++11 # compiler flags

# change for something like
CXX      = g++
CXXFLAGS = -Wall -Wno-c++11-extensions
```

### What is the project about

This is a project I did on my own during my free time because I was curious about 3D rendering and wanted to practice C++. The goal was to render 3D objects on my computer screen without using any 3D libraries like OpenGL.

:warning: Because I just created this repository the project is still not well commented.

See under a view of the basic scene proposed in `main.cpp` (the application is on the right, the left pannel is a terminal instance):
![basic_scene.png](basic_scene.png)
