# Installation instructions

## Required libraries

Instructions below make use of package managers for each platform, but these are the libraries used by this project:

* cpprestsdk: https://github.com/microsoft/cpprestsdk
* SDL 2: https://www.libsdl.org/download-2.0.php
* spdlog: https://github.com/gabime/spdlog

## macOS

Install the required libraries using `brew`:

```
$ brew install cpprestsdk
$ brew install sdl2
$ brew install sdl2_image
$ brew install sdl2_gfx
$ brew install sdl2_ttf
$ brew install spdlog
```

Configure and build:

```
$ cd path/to/repo
$ mkdir build
$ cd build
$ cmake .. -G Xcode
$ cmake --build .
```

The project can be built from commandline using `cmake --build .` or with the generated Xcode project.


### Troubleshooting

* `No rule to make target '/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/CoreFoundation.framework'`, or similar
    - This issue may occur when configuring and building using CMake after updating Xcode and macOS. Run `xcode-select --install` to ensure the command line tools are installed, then run `brew update` and `brew upgrade` to have `brew` perform any necessary updates.

## Windows

Install the required libraries using `vcpkg`:

```
> cd path\to\vcpkg
> .\vcpkg install cpprestsdk cpprestsdk:x64-windows
> .\vcpkg install sdl2 sdl2:x64-windows
> .\vcpkg install sdl2-image[libjpeg-turbo] sdl2-image[libjpeg-turbo]:x64-windows
> .\vcpkg install sdl2-gfx sdl2-gfx:x64-windows
> .\vcpkg install sdl2-ttf sdl2-ttf:x64-windows
> .\vcpkg install spdlog spdlog:x64-windows
```

Configure and build:

```
> cd path\to\repo
> mkdir build
> cd build
> cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/full/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
> cmake --build .
```

`CMAKE_TOOLCHAIN_FILE` should be the full path to where `vcpkg` is cloned on your machine.

The project can be built from commandline using `cmake --build .` or with the generated Visual Studio project.

## Ubuntu

Install the required libraries using `apt`:

```
$ sudo apt install libcpprest-dev
$ sudo apt install libsdl2-dev
$ sudo apt install libsdl2-image-dev
$ sudo apt install libsdl2-gfx-dev
$ sudo apt install libsdl2-ttf-dev
$ sudo apt install libspdlog-dev
```

Configure and build:

```
$ cd path/to/repo
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```
