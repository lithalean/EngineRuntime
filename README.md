# Projekt J.E.N.O.V.A :: Jenova Runtime (Core)

This repository contains source code of **Jenova Runtime** for Godot 4+ but is not part of **[Projekt J.E.N.O.V.A](https://github.com/Jenova-Framework/J.E.N.O.V.A)**

![image](https://github.com/user-attachments/assets/013eed25-7047-407d-aef8-b964203e73b0)

## Overview

**Projekt J.E.N.O.V.A** is a comprehensive series of extension libraries for the Godot 4+ Game Engine that brings fully-featured C++ scripting directly into the Godot Editor. It allows the use of modern C++20 standards within the Godot Engine similar to GDScript. 

By using Jenova Framework you can easily program your entire game or application in C/C++ without any issues. You can also integrate OpenCV, CUDA, Vulkan, OpenMP and any other modern C++ features seamlessly, All supported by the powerful backend.

Jenova Framework comes with a fully-featured scripting backend offering almost all the features of GDScript that are not available in any other third-party language at the moment. It’s not just an automated GDExtension; It’s a complete scripting backend with many features.

### Structure of Projekt J.E.N.O.V.A

- **Jenova Framework**: The framework contains Jenova Runtime, Jenova Utilities and Jenova SDK.
- **Jenova Runtime (Core)**: The heart of the framework, It includes the Jenova Interpreter, Jenova Compiler Interface, Jenova Packer etc.
- **Jenova Package Manager:** A utility included in Jenova Runtime for installing, removing and managing Jenova packages.
- **Jenova SDK**: An optional component of Jenova Runtime, providing helpers and APIs for Hot-Reloading, Global Allocation/Access etc.

Full feature list can be found [here](https://github.com/Jenova-Framework/J.E.N.O.V.A#%EF%B8%8F-current-features).

## Issue/Bug Reports and Questions
- If you want to report an issue or bug create a new thread at [Issues](https://github.com/Jenova-Framework/Jenova-Runtime/issues).
- If you have any questions you can create a new thread at [Discussions](https://github.com/Jenova-Framework/J.E.N.O.V.A/discussions).
- More details on the build process can be found at [Documentation](https://jenova-framework.github.io/docs/pages/Advanced/Build-Guide/).

## Dependencies

Jenova Core has following dependencies :

- [AsmJIT](https://github.com/asmjit/asmjit)
- [LibArchive](https://github.com/libarchive/libarchive)
- [LibLZMA](https://github.com/ShiftMediaProject/liblzma)
- [LibCurl](https://github.com/curl/curl)
- [LibFastZLib](https://github.com/gildor2/fast_zlib)
- [LibTinyCC](http://download.savannah.gnu.org/releases/tinycc/)
- [LibPThread](https://github.com/GerHobbelt/pthread-win32)
- [JSON++](https://github.com/nlohmann/json)
- [FileWatch](https://github.com/ThomasMonkman/filewatch)
- [ArgParse++](https://github.com/p-ranav/argparse)
- [Base64++](https://github.com/zaphoyd/websocketpp/blob/master/websocketpp/base64/base64.hpp)

> [!IMPORTANT]
> - Edit **base64.hpp** namespace to `base64`
> - Only header file `libtcc.h` is required from TinyCC beside static library
> - In **FileWatch.hpp** change `_callback(file.first, file.second);` to `_callback(_path + "/" + file.first, file.second);`
> - **By using Jenova Builder, All the dependencies are downloaded, manipulated and compiled automatically.**

## Build Systems
### macOS ARM64

Building Jenova Runtime for macOS ARM64 can be done using **Jenova Builder**. To build using Jenova Builder, Install Python 3 and then use the following commands from Terminal:

```bash
# Create a virtual environment
python3 -m venv jenova_build_env
source jenova_build_env/bin/activate
pip install requests py7zr colored

# Then run the build script
python3 Jenova.Builder_ARM64.py
```

Jenova Runtime source code is fully compatible with both Clang++ (18+) and G++ (13+).

### Builder Prerequisites

Before using **Jenova Builder** you need to install following prerequisites with homebrew
- Python (3.10+)
- CMake (3.20+)
- Ninja (1.11+)

## Open Source vs Proprietary
While the public source code of Jenova is ~90% identical to the proprietary version, a few specific features have been removed or disabled.

### macOS ARM64 Only

Jenova Proprietary version includes only Microsoft Visual C++ (MSVC) and Microsoft LLVM Clang (Clang-cl) compilers and is compatible only with Windows. Open-Source version, however, is currently being ported to macOS ARM64

----
Developed By **Hamid.Memar (MemarDesign™ LLC.)**
Ported By **Tyler.Allen (NomadAtelers™ LLC.)**