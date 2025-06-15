# Jenova Runtime
*An Open Source, modern Darwin ARM64 Runtime Porting Effort following native performance principles*

![Platform Support](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-blue)
![C++ Version](https://img.shields.io/badge/C++-17+-orange)
![Build System](https://img.shields.io/badge/build-CMake%20%7C%20Ninja-green)
![License](https://img.shields.io/badge/license-MIT-blue)

## ✨ Current Status: **IN DEVELOPMENT (~20% Complete)**

## 🎯 Project Vision

Building a **high-performance, cross-platform runtime** that bridges SwiftUI native experiences with Godot's powerful game engine core. This hybrid architecture enables native iOS/macOS UI while maintaining Godot's performance-critical C++ gameplay systems.

The runtime features a unique dual-layer architecture with SwiftUI handling platform integration and Godot + Jenova Core managing gameplay systems! 🎉

### 🚀 **What's Working Right Now:**
- ✅ **Basic Runtime Building** - Core infrastructure compiles and runs
- ✅ **NitroJIT ARM64 Emitter** - JIT compilation system (currently x64 assembly output)
- ✅ **Meteora Component** - Working by default with runtime integration
- ✅ **Cross-Platform Foundation** - macOS ARM64 primary target with multi-platform support
- ✅ **Build System** - Jenova Builder with Python automation
- ✅ **Dependency Management** - Complete C++ library integration

## Features

### 🏗️ **Hybrid Architecture**
- **SwiftUI Native Layer** - Platform-native UI for splash, menus, settings, social, IAP, and profiles
- **Godot + Jenova Core** - Pure gameplay experience with physics, rendering, audio, and effects
- **Bridge System** - Seamless communication between native UI and game engine
- **Performance-Critical C++** - Optimized for ARM64 with Darwin-specific enhancements

### 🧠 **Darwin ARM64 Developer-Focused Design**
- **Native Performance** - ARM64 optimized compilation and runtime execution
- **Hot-Reload Development** - Live script changes with state preservation
- **Cross-Platform Compatibility** - Primary macOS ARM64 with Windows/Linux support
- **Modern C++ Standards** - C++17+ with Clang 18+ and GCC 13+ support
- **Professional Build System** - CMake + Ninja with automated dependency management

### 🔧 **Runtime Components**
- **Asset Monitor** - File watching with hot-reload functionality
- **Abstraction OS Layer** - Platform detection and native API wrapping
- **Interpreter Engine** - C++ AST walking with runtime execution
- **Compiler Interface** - Clang/GCC/MSVC integration with dynamic compilation
- **Metadata Parser** - C++ code analysis with reflection data generation
- **Module System** - GDExtension interface with dynamic loading

### 🎮 **Game Engine Integration**
- **Godot Core** - Full Godot engine integration with custom enhancements
- **GDExtension Support** - Method binding, property exposure, signal handling
- **Dynamic Libraries** - Hot-swappable modules with safe unloading
- **Performance Optimization** - ARM64-specific optimizations and memory management

### 📱 **Platform-Specific Features**
- **macOS ARM64** - Primary development target with native API integration
- **Cross-Platform** - Windows x64 and Linux x64 compatibility
- **Native UI Integration** - SwiftUI integration for iOS/macOS experiences
- **Build Automation** - Jenova Builder with Python virtual environment support

## Current Implementation Status

### ✅ **Phase 0: Foundation - COMPLETE**
- [x] Basic runtime building infrastructure
- [x] NitroJIT ARM64 emitter (x64 assembly output)
- [x] Meteora component integration
- [x] Build system with Jenova Builder
- [x] Cross-platform dependency management
- [x] Core architecture design

### 🚧 **Phase 1: Core Infrastructure - IN PROGRESS**
- [ ] **Abstraction OS Layer**: Platform detection and native API wrapping
- [ ] **Metadata Parser**: C++ code analysis and reflection data generation
- [ ] **Asset Monitor**: File watching system with hot-reload functionality
- [ ] **Platform Integration**: macOS ARM64 optimization and native API integration

### 📋 **Phase 2: Compilation Pipeline - PLANNED**
- [ ] **Compiler Interface**: Clang/GCC/MSVC integration with build pipeline
- [ ] **Module Wrapper**: GDExtension interface and Godot integration
- [ ] **Dynamic Compilation**: Source to object file with optimization settings
- [ ] **Symbol Management**: Export management and type registration

### 🔮 **Phase 3: Runtime & Development - PLANNED**
- [ ] **Interpreter Engine**: AST walking with runtime execution
- [ ] **Module Loader**: Dynamic library management with hot-reload
- [ ] **Development Tools**: Debugging support and error handling
- [ ] **Performance Optimization**: ARM64-specific optimizations

## Installation & Setup

### Prerequisites
- **Xcode Command Line Tools** or **Full Xcode**
- **Python 3.10+** for Jenova Builder
- **CMake 3.20+** for build system
- **Ninja 1.11+** for fast compilation
- **Homebrew** for dependency management

### Quick Start
```bash
# Clone the repository
git clone https://github.com/[USERNAME]/jenova-runtime.git
cd jenova-runtime

# Create Python virtual environment
python3 -m venv jenova_build_env
source jenova_build_env/bin/activate
pip install requests py7zr colored

# Build for macOS ARM64
python3 Jenova.Builder_ARM64.py
```

**Supported Compilers**:
- **Clang++ 18+** (Recommended for macOS)
- **GCC 13+** (Linux/Windows)
- **MSVC** (Windows only)

## Usage

### 🎯 **Getting Started**
1. **Set up development environment** - Install prerequisites via Homebrew
2. **Create virtual environment** - Use Python venv for isolated dependencies
3. **Run Jenova Builder** - Execute the ARM64 build script for your platform

### ⌨️ **Build Commands**
- **Full Build**: `python3 Jenova.Builder_ARM64.py`
- **Clean Build**: Add `--clean` flag to builder script
- **Debug Build**: Use `--debug` configuration
- **Development Mode**: Enable hot-reload with `--dev` flag

### 🖥️ **Platform-Specific Features**
- **macOS ARM64**: Native performance with Metal rendering support
- **Cross-Platform**: Unified codebase with platform-specific optimizations
- **Development**: Hot-reload workflow with live script updates

### 💾 **Runtime Architecture**
- **Dual-Layer Design**: SwiftUI native + Godot core separation
- **Bridge Communication**: Efficient data exchange between layers
- **Module System**: Dynamic loading with GDExtension compatibility
- **Asset Pipeline**: Live reloading with change detection

## Technical Architecture

### Hybrid Runtime Stack
- **SwiftUI Layer** - Native platform UI and system integration
- **Bridge System** - Communication layer between native and game code
- **Godot Core** - Game engine with custom Jenova enhancements
- **JIT Compilation** - NitroJIT ARM64 emitter for runtime optimization
- **Module System** - Dynamic loading with hot-reload capabilities

### Key Components
```
JenovaRuntime/
├── Core/
│   ├── NitroJIT/          # ARM64 JIT compilation system
│   ├── Meteora/           # Core component system
│   ├── AssetMonitor/      # File watching and hot-reload
│   └── ModuleSystem/      # Dynamic library management
├── Bridge/
│   ├── SwiftUIBridge/     # Native UI integration
│   ├── GodotBridge/       # Game engine interface
│   └── Communication/     # Inter-layer messaging
├── Runtime/
│   ├── Interpreter/       # C++ script execution
│   ├── Compiler/          # Dynamic compilation interface
│   └── Loader/            # Module loading system
└── Platform/
    ├── Darwin/            # macOS ARM64 optimizations
    ├── Linux/             # Linux x64 support
    └── Windows/           # Windows x64 support
```

### Design Patterns
- **Dual-Layer Architecture** - Native UI with game engine separation
- **Component System** - Modular runtime with hot-swappable components
- **Cross-Platform Abstraction** - Unified API with platform optimizations
- **JIT Compilation** - Runtime optimization for performance-critical code

## Development Roadmap

### 🔜 **Next Up (Phase 1)**
1. **Abstraction OS Layer**: Complete platform detection and native API wrapping
2. **Metadata Parser**: Implement C++ code analysis and reflection generation
3. **Asset Monitor**: File watching system with intelligent change detection
4. **Hot-Reload Pipeline**: Live script updates with state preservation
5. **Performance**: ARM64-specific optimizations and memory management

### 🎯 **Medium Term (Phase 2)**
1. **Compiler Integration**: Clang/GCC/MSVC with dynamic compilation
2. **Module Wrapper**: Complete GDExtension interface implementation
3. **Build Pipeline**: Automated compilation with optimization settings
4. **Development Tools**: Debugging support and error handling systems
5. **Cross-Platform**: Windows and Linux platform completion

### 🚀 **Long Term (Phase 3+)**
1. **Advanced JIT**: Complete ARM64 native code generation
2. **Editor Integration**: Visual development tools and debugging interface
3. **Performance Profiling**: Runtime analysis and optimization tools
4. **Community Ecosystem**: Plugin architecture and third-party extensions
5. **Commercial Features**: Enterprise deployment and support tools

## 🤖 Claude.ai Integration

> **For AI Collaboration**: This project uses Claude.ai assistance for architecture decisions, platform porting challenges, and C++ optimization strategies. The `.claude/` directory contains detailed context files for AI collaboration continuity.

**Quick Context**: Cross-platform runtime porting effort combining SwiftUI native experiences with Godot engine performance, featuring dual-layer architecture and ARM64 optimization focus.

**Key AI Collaboration Areas**:
- 🏗️ **Architecture**: Dual-layer design patterns, bridge communication systems
- 🔧 **Porting**: Darwin ARM64 optimization, cross-platform compatibility
- ⚡ **Performance**: JIT compilation, memory management, runtime optimization
- 📋 **Planning**: Component implementation priorities, technical debt tracking

**AI Context Files**: See `.claude/context.md` for detailed project state, architecture decisions, and ongoing development context.

## Dependencies

### Core Runtime Dependencies
- **[AsmJIT](https://github.com/asmjit/asmjit)** - JIT compilation and code generation
- **[LibArchive](https://github.com/libarchive/libarchive)** - Archive format support
- **[LibLZMA](https://github.com/ShiftMediaProject/liblzma)** - LZMA compression
- **[LibCurl](https://github.com/curl/curl)** - HTTP/network operations
- **[LibFastZLib](https://github.com/gildor2/fast_zlib)** - High-performance compression
- **[LibTinyCC](http://download.savannah.gnu.org/releases/tinycc/)** - Lightweight C compiler
- **[LibPThread](https://github.com/GerHobbelt/pthread-win32)** - Threading support
- **[JSON++](https://github.com/nlohmann/json)** - JSON parsing and generation
- **[FileWatch](https://github.com/ThomasMonkman/filewatch)** - File system monitoring
- **[ArgParse++](https://github.com/p-ranav/argparse)** - Command-line parsing
- **[Base64++](https://github.com/zaphoyd/websocketpp/blob/master/websocketpp/base64/base64.hpp)** - Base64 encoding/decoding

## License

Jenova Runtime is released under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments

- **Godot Engine Team** for the robust game engine foundation
- **Apple Silicon Engineering** for ARM64 architecture and Metal performance
- **Clang/LLVM Team** for advanced compilation infrastructure
- **Darwin ARM64 Community** for porting insights and optimization techniques
- **Hamid.Memar (MemarDesign™ LLC.)** for original development
- **Tyler.Allen (NomadAtelers™ LLC.)** for Darwin ARM64 porting efforts
- **Claude.ai** for architectural guidance and porting assistance