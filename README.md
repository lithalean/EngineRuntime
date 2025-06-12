
```
┌─────────────────────────────────────────┐
│           SwiftUI Native Layer          │
│  ┌─────────┐ ┌─────────┐ ┌─────────┐    │
│  │ Splash  │ │  Menu   │ │Settings │    │
│  └─────────┘ └─────────┘ └─────────┘    │
│  ┌─────────┐ ┌─────────┐ ┌─────────┐    │
│  │ Social  │ │   IAP   │ │Profile  │    │
│  └─────────┘ └─────────┘ └─────────┘    │
└─────────────────────────────────────────┘
					↕ Bridge
┌─────────────────────────────────────────┐
│        Godot + Jenova Core              │
│   ┌─────────────────────────────────┐   │
│   │    Pure Gameplay Experience     │   │
│   │  • Game mechanics               │   │
│   │  • Physics & rendering          │   │
│   │  • Audio & effects              │   │
│   │  • Performance-critical C++     │   │
│   └─────────────────────────────────┘   │
└─────────────────────────────────────────┘
```


## Dependencies

Core has following dependencies :

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


### macOS ARM64 Only

----
Developed By **Hamid.Memar (MemarDesign™ LLC.)**
Ported By **Tyler.Allen (NomadAtelers™ LLC.)**