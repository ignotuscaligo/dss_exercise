# Installation instructions

## cpprestsdk

Source code: https://github.com/microsoft/cpprestsdk

Taken from their directions:

With [vcpkg](https://github.com/Microsoft/vcpkg) on Windows
```
PS> vcpkg install cpprestsdk cpprestsdk:x64-windows
```

With [brew](https://github.com/Homebrew/homebrew-core/blob/master/Formula/cpprestsdk.rb) on OSX
```
$ brew install cpprestsdk
```

## SDL 2

Source code: https://www.libsdl.org/download-2.0.php

### macOS

Install with brew
```
$ brew install sdl2
```

# Troubleshooting

* `No rule to make target `/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/CoreFoundation.framework'`, or similar
    * This issue may occur when configuring and building using CMake after updating Xcode and macOS. Run `xcode-select --install` to ensure the command line tools are installed, then run `brew update` and `brew upgrade` to have `brew` perform any necessary updates.
