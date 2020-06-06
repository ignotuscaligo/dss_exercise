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

## SDL 2

Source code: https://www.libsdl.org/download-2.0.php

### macOS

Install with brew
```
$ brew install sdl2
```

### Windows

Install with vcpkg
```
PS> vcpkg install sdl2 sdl2:x64-windows
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

# Troubleshooting

* `No rule to make target `/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/CoreFoundation.framework'`, or similar
    * This issue may occur when configuring and building using CMake after updating Xcode and macOS. Run `xcode-select --install` to ensure the command line tools are installed, then run `brew update` and `brew upgrade` to have `brew` perform any necessary updates.
