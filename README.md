# Installation instructions

## cpprestsdk

Source code: https://github.com/microsoft/cpprestsdk

### macOS

Install with brew
```
$ brew install cpprestsdk
```

### Windows

Install with vcpkg
```
PS> vcpkg install cpprestsdk cpprestsdk:x64-windows
```

### Ubuntu

Install with apt
```
$ sudo apt install libcpprest-dev
```

## SDL 2

Source code: https://www.libsdl.org/download-2.0.php

### macOS

Install with brew
```
$ brew install sdl2
$ brew install sdl2_image
$ brew install sdl2_gfx
$ brew install sdl2_ttf
```

### Windows

Install with vcpkg
```
PS> vcpkg install sdl2 sdl2:x64-windows
PS> vcpkg install sdl2-image[libjpeg-turbo] sdl2-image[libjpeg-turbo]:x64-windows
PS> vcpkg install sdl2-gfx sdl2-gfx:x64-windows
PS> vcpkg install sdl2-ttf sdl2-ttf:x64-windows
```

### Ubuntu

Install with apt
```
$ sudo apt install libsdl2-dev
$ sudo apt install libsdl2-image-dev
$ sudo apt install libsdl2-gfx-dev
$ sudo apt install libsdl2-ttf-dev
```

## spdlog

Source code: https://github.com/gabime/spdlog

### macOS

Install with brew
```
$ brew install spdlog
```

### Windows

Install with vcpkg
```
PS> vcpkg install spdlog spdlog:x64-windows
```

### Ubuntu

Install with apt
```
$ sudo apt install libspdlog-dev
```

# Building

## Windows

Run the `vcpkg` integration before each session

```
PS> .\vcpkg integrate install
```

When configuring the CMake project on Windows, and additional flag needs to be provided for the `vcpkg` libraries to be found correctly:

```
PS> cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/full/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Windows builds a Visual Studio project, the executable can be built from either the command line or with the project.

### macOS

macOS builds an Xcode project, the executable can be built from either the command line or with the project.

## Shared

```
> cd path/to/repo
> mkdir build
> cd build
> cmake ..
> cmake --build .
```

# Troubleshooting

* `No rule to make target `/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/CoreFoundation.framework'`, or similar
    * This issue may occur when configuring and building using CMake after updating Xcode and macOS. Run `xcode-select --install` to ensure the command line tools are installed, then run `brew update` and `brew upgrade` to have `brew` perform any necessary updates.
