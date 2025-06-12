
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

# Runtime Roadmap

## Progress Overview
- [x] Basic runtime building (~20% complete)
- [x] NitroJIT ARM64 emitter (currently emits x64 assembly)
- [x] Meteora component (working by default)

## Remaining Components (~80% of work)

### 1. Asset Monitor
- [ ] **File watching system**
  - [ ] Implement file system monitoring
  - [ ] Change detection algorithms
  - [ ] Asset reloading pipeline
- [ ] **Hot-reload functionality**
  - [ ] Script change detection
  - [ ] Module recompilation triggers
  - [ ] State preservation during reload
- [ ] **Files to implement**: `*asset*`, `*monitor*`, `*watch*`

### 2. Abstraction OS Layer
- [ ] **Platform detection**
  - [ ] macOS ARM64 support
  - [ ] macOS x64 support
  - [ ] Windows x64 support
  - [ ] Linux x64 support
- [ ] **OS-specific APIs**
  - [ ] File system operations
  - [ ] Threading primitives
  - [ ] Memory management
  - [ ] Process management
- [ ] **Native API wrapping**
  - [ ] System calls abstraction
  - [ ] Platform-specific optimizations

### 3. Interpreter
- [ ] **Core interpreter engine**
  - [ ] AST walking implementation
  - [ ] Runtime execution engine
  - [ ] Variable management system
- [ ] **C++ language support**
  - [ ] Expression evaluation
  - [ ] Function call handling
  - [ ] Object lifecycle management
- [ ] **Integration with runtime**
  - [ ] Godot API binding
  - [ ] Memory safety guarantees
  - [ ] Error handling and debugging

### 4. Compiler Interface
- [ ] **Compiler integration**
  - [ ] Clang integration
  - [ ] GCC integration
  - [ ] MSVC integration (Windows)
- [ ] **Compilation pipeline**
  - [ ] Compiler invocation system
  - [ ] Build flag management
  - [ ] Optimization settings
- [ ] **C++ script compilation**
  - [ ] Source to object file
  - [ ] Dynamic library generation
  - [ ] Symbol export management

### 5. Metadata Parser
- [ ] **C++ code analysis**
  - [ ] AST parsing implementation
  - [ ] Class structure extraction
  - [ ] Method signature parsing
  - [ ] Property detection
- [ ] **Reflection data generation**
  - [ ] Type information generation
  - [ ] Method binding metadata
  - [ ] Property binding metadata
- [ ] **Godot integration**
  - [ ] Editor support data
  - [ ] Runtime type information
  - [ ] Documentation extraction

### 6. Module Wrapper
- [ ] **GDExtension interface**
  - [ ] Method binding system
  - [ ] Property exposure
  - [ ] Signal handling
- [ ] **Godot integration**
  - [ ] Node class wrapping
  - [ ] Resource class wrapping
  - [ ] Custom type registration
- [ ] **Runtime binding**
  - [ ] Dynamic method resolution
  - [ ] Type conversion system
  - [ ] Error propagation

### 7. Module Loader
- [ ] **Dynamic library management**
  - [ ] Library loading system
  - [ ] Symbol resolution
  - [ ] Dependency management
- [ ] **Hot-reload support**
  - [ ] Safe module unloading
  - [ ] State migration
  - [ ] Reference updating
- [ ] **Runtime management**
  - [ ] Module lifecycle
  - [ ] Memory cleanup
  - [ ] Error recovery

## Implementation Priority

### Phase 1: Core Infrastructure (Weeks 1-4)
- [ ] Abstraction OS Layer
- [ ] Metadata Parser

### Phase 2: Compilation Pipeline (Weeks 5-8)
- [ ] Compiler Interface
- [ ] Module Wrapper

### Phase 3: Runtime & Development (Weeks 9-12)
- [ ] Interpreter
- [ ] Module Loader
- [ ] Asset Monitor

## Notes
- **NitroJIT**: ARM64 emitter implemented but currently only emits x64 assembly
- **Meteora**: Should work fine by default
- **Current completion**: ~20% of total port roadmap


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


----
Developed By **Hamid.Memar (MemarDesign™ LLC.)**
Ported By **Tyler.Allen (NomadAtelers™ LLC.)**