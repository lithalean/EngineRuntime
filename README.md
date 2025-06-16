# Jenova Runtime
*An Open Source, Darwin ARM64 Runtime Porting Effort following native performance principles*

![Platform Support](https://img.shields.io/badge/platform-macOS%20ARM64%20ONLY-blue)
![C++ Version](https://img.shields.io/badge/C++-17+-orange)
![Build System](https://img.shields.io/badge/build-Python%20ARM64-green)
![License](https://img.shields.io/badge/license-MIT-blue)

## ✨ Current Status: **DARWIN ARM64 PORTING (~20% Complete)**

## 🎯 Project Vision

Building a **high-performance, Darwin ARM64 EXCLUSIVE runtime** that bridges SwiftUI native experiences with Godot's powerful game engine core. This hybrid architecture enables native macOS UI while maintaining Godot's performance-critical C++ gameplay systems.

**IMPORTANT**: This is a **Darwin ARM64 ONLY** project. No Linux or Windows support is planned. The runtime is designed specifically for Apple Silicon with native Foundation framework integration.

The runtime features a unique dual-layer architecture with SwiftUI handling platform integration and Godot + Jenova Core managing gameplay systems! 🍎

### 🚀 **What's Being Ported:**
- 🔧 **Source Code Analysis** - Complete 50+ file C++ runtime codebase identified
- 🎯 **Darwin ARM64 Target** - Porting existing cross-platform code to Darwin-native
- 🏗️ **SwiftUI Integration** - Implementing native dual-layer architecture
- ⚡ **Foundation APIs** - Replacing portable abstractions with Darwin-native calls
- 🔥 **Metal + Core Audio** - Darwin-specific performance optimizations
- 🧠 **NitroJIT ARM64** - Porting x86 JIT backend to native ARM64 Darwin

## Features

### 🏗️ **Darwin-Native Dual Architecture**
- **SwiftUI Native Layer** - Pure Darwin UI for splash, menus, settings, social, IAP, and profiles
- **Godot + Jenova Core** - Game engine with Darwin ARM64 optimizations
- **Foundation Bridge** - Native Darwin communication between UI and engine layers
- **ARM64 Performance** - Darwin-specific optimizations with Metal and Core Audio

### 🧠 **Darwin ARM64 Exclusive Design**
- **Foundation Framework** - Native Darwin APIs replacing cross-platform abstractions
- **Metal Graphics** - Darwin GPU acceleration instead of OpenGL/Vulkan
- **Core Audio** - Native Darwin audio processing
- **FSEvents/kqueue** - Darwin file system monitoring for hot-reload
- **Xcode Integration** - Native Darwin development workflow
- **Instruments Profiling** - Darwin-native performance analysis

### 🔧 **Porting Components**
- **NitroJIT ARM64** - Converting x86 JIT backend to native ARM64 Darwin
- **Asset Monitor Darwin** - Porting file watching to FSEvents/kqueue
- **Foundation Integration** - Replacing portable code with Darwin-native APIs
- **SwiftUI Bridge** - Implementing dual-layer communication system
- **Memory Management** - Darwin-specific allocators and optimization
- **Godot ARM64** - Optimizing engine for Darwin ARM64 performance

### 🎮 **Game Engine Integration**
- **Godot Darwin ARM64** - Engine optimized specifically for Apple Silicon
- **GDExtension Darwin** - Native Darwin integration for method binding
- **Metal Rendering** - Darwin GPU acceleration for game graphics
- **Core Audio Integration** - Native Darwin audio for game sound
- **Foundation APIs** - Darwin-native system integration

### 📱 **Darwin-Specific Features**
- **macOS ARM64 ONLY** - Exclusive focus on Apple Silicon
- **SwiftUI Integration** - Native Darwin UI framework
- **Foundation APIs** - Core Darwin system integration
- **Metal Performance** - Darwin GPU optimization
- **Core Audio** - Native Darwin audio processing
- **Xcode Workflow** - Native Darwin development environment

## Current Porting Status

### 📋 **Phase 0: Source Analysis - COMPLETE**
- [x] Identified 50+ C++ source files to be ported
- [x] Analyzed existing cross-platform architecture
- [x] Evaluated dependencies for Darwin compatibility
- [x] Established Darwin ARM64 build environment
- [x] Created porting strategy and priorities

### 🚧 **Phase 1: Darwin Native Porting - IN PROGRESS (20%)**
- [ ] **NitroJIT ARM64 Backend**: Port x86 JIT to native ARM64 Darwin
- [ ] **Foundation API Integration**: Replace portable abstractions with Darwin APIs
- [ ] **SwiftUI Bridge Layer**: Implement dual-layer communication
- [ ] **FSEvents File Monitoring**: Port asset monitoring to Darwin-native APIs
- [ ] **Metal Integration**: Implement Darwin GPU acceleration
- [ ] **Core Audio Integration**: Native Darwin audio processing

### 📋 **Phase 2: Darwin Optimization - PLANNED**
- [ ] **Memory Management**: Darwin-specific allocators and optimization
- [ ] **Godot ARM64 Darwin**: Engine optimization for Apple Silicon
- [ ] **Xcode Integration**: Native development workflow
- [ ] **Instruments Profiling**: Darwin performance analysis tools
- [ ] **Build System Darwin**: Optimize for Darwin-only compilation

### 🔮 **Phase 3: Production Darwin - PLANNED**
- [ ] **App Store Compatibility**: Darwin distribution optimization
- [ ] **Notarization Support**: Apple security requirements
- [ ] **Sandboxing**: Darwin security model integration
- [ ] **Performance Validation**: Darwin-specific benchmarking
- [ ] **Release Pipeline**: Darwin deployment automation

## Installation & Setup

### Prerequisites (Darwin ARM64 ONLY)
- **macOS 12.0+** with Apple Silicon (M1/M2/M3/M4)
- **Xcode 14.0+** or Command Line Tools
- **Python 3.10+** for Jenova Builder ARM64
- **Homebrew** for Darwin dependency management

### Quick Start (Darwin ARM64)
```bash
# Clone the repository (Darwin ARM64 only)
git clone https://github.com/[USERNAME]/jenova-runtime.git
cd jenova-runtime

# Create Darwin Python environment
python3 -m venv jenova_build_env
source jenova_build_env/bin/activate
pip install requests py7zr colored psutil

# Build for Darwin ARM64 ONLY
python3 Jenova.Builder_ARM64.py
```

**Supported Compiler (Darwin ONLY)**:
- **Clang++ 18+** (Darwin ARM64 exclusive)

⚠️ **NO SUPPORT**: Linux, Windows, or Intel Macs are not supported and will not be ported.

## Usage

### 🎯 **Darwin ARM64 Development**
1. **Darwin Setup** - Install Xcode and Homebrew on Apple Silicon Mac
2. **ARM64 Environment** - Use Python venv for Darwin-specific dependencies
3. **Darwin Build** - Execute ARM64-only build script
4. **SwiftUI Integration** - Develop with native Darwin UI framework

### ⌨️ **Darwin Build Commands**
- **Darwin Build**: `python3 Jenova.Builder_ARM64.py` (macOS ARM64 only)
- **Clean Build**: Darwin-specific cache clearing
- **Debug Build**: Darwin development configuration
- **Release Build**: Darwin App Store optimization

### 🖥️ **Darwin-Specific Features**
- **Apple Silicon**: Native ARM64 performance optimization
- **Metal Rendering**: Darwin GPU acceleration
- **Core Audio**: Native Darwin audio processing
- **SwiftUI**: Native Darwin UI framework
- **Foundation**: Darwin system API integration

### 💾 **Darwin Runtime Architecture**
- **SwiftUI Native**: Darwin UI layer with Foundation APIs
- **Bridge System**: Darwin-native communication layer
- **Godot ARM64**: Game engine optimized for Apple Silicon
- **Darwin APIs**: Foundation, Metal, Core Audio integration

## Technical Architecture

### Darwin ARM64 Runtime Stack
- **SwiftUI Layer** - Native Darwin UI with Foundation framework
- **Foundation Bridge** - Darwin-native communication system
- **Godot Darwin** - Game engine with ARM64 Apple Silicon optimization
- **NitroJIT ARM64** - Native Darwin ARM64 code generation
- **Darwin APIs** - Metal, Core Audio, FSEvents integration

### Darwin Components
```
JenovaRuntime/ (Darwin ARM64 EXCLUSIVE)
├── Source/ (50+ files to be ported)
│   ├── jenova.cpp (365KB)         # Core runtime → Darwin ARM64
│   ├── script_compiler.cpp        # Compilation → Darwin native
│   ├── script_interpreter.cpp     # Interpreter → ARM64 optimization
│   ├── package_manager.cpp        # Package system → Foundation APIs
│   ├── asset_monitor.cpp          # File watching → FSEvents/kqueue
│   └── [45+ more files]           # Full porting scope
├── Dependencies/ (Darwin compatibility)
│   ├── libasmjit/                 # JIT → ARM64 Darwin backend
│   ├── libgodot/                  # Engine → ARM64 optimization
│   └── [9 more libraries]         # Darwin compatibility validation
├── Darwin Integration/
│   ├── SwiftUI Bridge/            # Native UI integration
│   ├── Foundation APIs/           # Darwin system integration
│   ├── Metal Graphics/            # Darwin GPU acceleration
│   └── Core Audio/                # Darwin audio processing
└── Build System/
    ├── Jenova.Builder_ARM64.py    # Darwin-only build system
    ├── jenova_build_env/          # Darwin Python environment
    └── Darwin Dependencies/       # Apple Silicon optimization
```

### Darwin Design Patterns
- **Foundation Framework** - Native Darwin APIs over portable abstractions
- **SwiftUI Integration** - Darwin UI framework for dual-layer architecture
- **Metal Graphics** - Darwin GPU acceleration over OpenGL/Vulkan
- **Core Audio** - Darwin audio processing over portable audio libraries
- **ARM64 Optimization** - Apple Silicon-specific performance tuning

## Development Roadmap

### 🔜 **Phase 1: Darwin Native Porting (Current)**
1. **NitroJIT ARM64**: Port x86 JIT backend to native ARM64 Darwin
2. **Foundation Integration**: Replace cross-platform code with Darwin APIs
3. **SwiftUI Bridge**: Implement dual-layer Darwin architecture
4. **FSEvents Monitoring**: Port file watching to Darwin-native APIs
5. **Metal Integration**: Implement Darwin GPU acceleration

### 🎯 **Phase 2: Darwin Optimization**
1. **Memory Management**: Darwin-specific allocators and optimization
2. **Godot ARM64**: Engine optimization for Apple Silicon
3. **Core Audio**: Native Darwin audio processing
4. **Xcode Integration**: Darwin development workflow
5. **Instruments Profiling**: Darwin performance analysis

### 🚀 **Phase 3: Darwin Production**
1. **App Store Ready**: Darwin distribution optimization
2. **Notarization**: Apple security requirements
3. **Sandboxing**: Darwin security model
4. **Performance Validation**: Darwin benchmarking
5. **Release Pipeline**: Darwin deployment automation

## 🤖 Claude.ai Integration

> **For AI Collaboration**: This project uses Claude.ai assistance for Darwin ARM64 porting challenges, Foundation API integration, and SwiftUI architecture decisions.

**Darwin Porting Context**: Exclusive Darwin ARM64 runtime porting effort combining SwiftUI native experiences with Godot engine performance, featuring Foundation framework integration and Apple Silicon optimization.

**Key AI Collaboration Areas**:
- 🍎 **Darwin Porting**: ARM64 optimization, Foundation API integration
- 🏗️ **SwiftUI Architecture**: Dual-layer design, native Darwin UI
- ⚡ **Apple Silicon**: ARM64 JIT compilation, Metal graphics, Core Audio
- 🔧 **Foundation APIs**: Replacing portable code with Darwin-native calls

**AI Context Files**: See `.claude/context.md` for Darwin ARM64 porting state, architecture decisions, and Foundation integration progress.

## Dependencies (Darwin Compatibility)

### Darwin ARM64 Runtime Dependencies
- **[AsmJIT](https://github.com/asmjit/asmjit)** - JIT compilation → ARM64 Darwin backend
- **[LibArchive](https://github.com/libarchive/libarchive)** - Archive support → Darwin compatibility
- **[LibLZMA](https://github.com/ShiftMediaProject/liblzma)** - LZMA compression → ARM64 optimization
- **[LibCurl](https://github.com/curl/curl)** - Network operations → Darwin integration
- **[LibGodot](https://github.com/godotengine/godot-cpp)** - Engine integration → ARM64 Darwin
- **[LibJenova](./Dependencies/libjenova/)** - Runtime utilities → Darwin APIs
- **[LibTinyCC](http://download.savannah.gnu.org/releases/tinycc/)** - C compiler → ARM64 Darwin
- **[LibPThread](https://github.com/GerHobbelt/pthread-win32)** - Threading → Darwin native
- **[LibZlib](https://github.com/madler/zlib)** - Compression → Darwin optimization
- **[LibXML2](http://xmlsoft.org/)** - XML processing → Darwin compatibility

### Darwin-Specific Integration
- **Foundation Framework** - Core Darwin APIs
- **SwiftUI** - Native Darwin UI framework
- **Metal** - Darwin GPU acceleration
- **Core Audio** - Darwin audio processing
- **FSEvents** - Darwin file system monitoring
- **Xcode Tools** - Darwin development environment

## License

Jenova Runtime is released under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments

- **Apple Silicon Team** for ARM64 architecture and Metal performance
- **Apple Foundation Team** for Darwin API framework
- **Godot Engine Team** for the robust game engine foundation
- **Darwin ARM64 Community** for porting insights and optimization techniques
- **Hamid.Memar (MemarDesign™ LLC.)** for original cross-platform development
- **Tyler.Allen (NomadAtelers™ LLC.)** for Darwin ARM64 EXCLUSIVE porting effort
- **Claude.ai** for Darwin porting guidance and Foundation API integration assistance