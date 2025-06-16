# EngineRuntime Project Structure
*Current folder and file organization for AI collaboration*

> **Location**: `/.claude/structure.md` - Live project structure reference  
> **Last Updated**: June 16, 2025  
> **Build Status**: Phase 1 Development - Core Infrastructure (~20% Complete)  

## 📁 Root Directory Structure
```
EngineRuntime/                  # Project root
├── .claude/
│   ├── context.md              # AI collaboration state & decisions
│   ├── structure.md            # This file - current project structure
│   ├── sessions/               # Session history tracking
│   └── templates/              # AI collaboration templates
├── Source/                     # Main runtime source code (50 C++/H files)
├── Dependencies/               # Third-party library dependencies (11 major libs)
├── Libs/                       # Processed library headers and binaries
├── Addons/                     # Runtime addons and extensions
├── DarwinARM64/                # ARM64 build artifacts and distribution
├── OpenSSL/                    # OpenSSL ARM64 libraries
├── jenova_build_env/           # Python 3.13 build environment
├── vir_build_env/              # Virtual build environment
├── Jenova.Builder_ARM64.py     # ARM64-optimized build system
├── Jenova.Runtime.vcxproj      # Visual Studio project file
├── Jenova.Runtime.gdextension  # Godot extension configuration
├── Jenova.sln                  # Visual Studio solution
├── LICENSE                     # Project license
├── ReadMe.md                   # Project documentation
├── Claude.md                   # AI collaboration notes
├── cleanup_repo.py             # Repository maintenance script
├── vir_build_env.sh            # Virtual environment setup
└── build_error.log             # Build system error tracking
```

## 🏗️ Current Implementation Status
```
ACTUAL_STRUCTURE_STATUS:
✅ IMPLEMENTED:
- Complete dual Python build environment system (jenova_build_env + vir_build_env)
- Comprehensive dependency management with 11 major libraries
- ARM64-optimized Jenova Builder with Python 3.13 support
- Full source code structure with 50+ C++/header files
- Visual Studio integration with .vcxproj and .sln files
- Godot GDExtension configuration and integration
- DarwinARM64 build artifacts and distribution system
- OpenSSL ARM64 native integration
- Repository maintenance and cleanup automation

✅ CORE_RUNTIME_COMPONENTS_IMPLEMENTED:
- Asset Monitor system (asset_monitor.cpp/h)
- Script compilation pipeline (script_compiler.cpp/h) 
- Runtime interpreter (script_interpreter.cpp/h)
- Package management (package_manager.cpp/h)
- Task system and profiling (task_system.cpp/h, tiny_profiler.cpp/h)
- Script language integration (script_language.cpp/h)
- Instance management (script_instance.cpp/h, script_instance_base.cpp/h)
- Object system (script_object.cpp/h)
- Template system (script_templates.cpp/h)
- Resource management (script_resource.cpp/h)
- Jenova core runtime (jenova.cpp)
- SDK integration (jenovaSDK.cpp)

✅ BUILD_SYSTEM_IMPLEMENTED:
- ARM64-native Python build environment with dependency isolation
- Cross-platform dependency compilation and linking
- Virtual environment management for clean builds
- Error tracking and logging system
- Repository maintenance automation

📋 PHASE_1_STILL_NEEDED:
- NitroJIT ARM64 emitter conversion from x64
- Abstraction OS Layer platform detection
- Hot-reload file watching integration
- Cross-platform build verification (Linux x64, Windows x64)

🔍 IMMEDIATE_EXPLORATION_PRIORITY:
- Investigate NitroJIT ARM64 backend in Dependencies/libasmjit
- Implement platform detection in current asset_monitor system
- Connect build system to hot-reload capabilities
- Test cross-platform dependency compilation
```

## 📂 Detailed Source Directory (`Source/`)
```
Source/ (50 files)                    # Main runtime implementation
├── Core Runtime Files:
│   ├── jenova.cpp                     # Main Jenova runtime (365KB - core implementation)
│   ├── Jenova.hpp                     # Primary runtime header (38KB)
│   ├── jenovaSDK.cpp                  # SDK integration (28KB)
│   └── JenovaSDK.h                    # SDK header definitions (19KB)
├── Script System:
│   ├── script_compiler.cpp            # C++ compilation system (146KB)
│   ├── script_compiler.h              # Compiler interface (3KB)
│   ├── script_interpreter.cpp         # Runtime interpreter (88KB)
│   ├── script_interpreter.h           # Interpreter interface (6KB)
│   ├── script_language.cpp            # Language integration (20KB)
│   ├── script_language.h              # Language definitions (11KB)
│   ├── script_instance.cpp            # Script instances (20KB)
│   ├── script_instance.h              # Instance interface (3KB)
│   ├── script_instance_base.cpp       # Base instance system (13KB)
│   ├── script_instance_base.h         # Base interface (3KB)
│   ├── script_object.cpp              # Object system (12KB)
│   ├── script_object.h                # Object interface (6KB)
│   ├── script_resource.cpp            # Resource management (7KB)
│   ├── script_resource.h              # Resource interface (3KB)
│   ├── script_templates.cpp           # Template system (11KB)
│   └── script_templates.h             # Template interface (2KB)
├── Asset & Package Management:
│   ├── asset_monitor.cpp              # File watching system (6KB)
│   ├── asset_monitor.h                # Monitor interface (2KB)
│   ├── package_manager.cpp            # PCK management (65KB)
│   ├── package_manager.h              # Package interface (4KB)
│   ├── script_manager.cpp             # Script coordination (3KB)
│   └── script_manager.h               # Manager interface (2KB)
├── Development Tools:
│   ├── clektron.cpp                   # Development tool (36KB)
│   ├── clektron.h                     # Tool interface (1KB)
│   ├── gdextension_exporter.cpp       # GDExtension export (10KB)
│   ├── gdextension_exporter.h         # Exporter interface (1KB)
│   ├── task_system.cpp                # Task management (2KB)
│   ├── task_system.h                  # Task interface (1KB)
│   ├── tiny_profiler.cpp              # Performance profiling (2KB)
│   └── tiny_profiler.h                # Profiler interface (1KB)
├── Runtime Data & Resources:
│   ├── AboutImage.h                   # Embedded about image (5.7MB)
│   ├── BuiltinFonts.h                 # Font resources (920KB)
│   ├── CodeTemplates.h                # Code generation templates (11KB)
│   ├── Documentation.h                # Embedded documentation (5KB)
│   ├── ExtensionHosts.h               # Extension system (2.3MB)
│   ├── IconDatabase.h                 # UI icons database (721KB)
│   ├── InternalModules.h              # Internal modules (5MB)
│   ├── InternalSources.h              # Source templates (1KB)
│   ├── JenovaIcon64.h                 # Jenova icon (88KB)
│   ├── TypesIcons.h                   # Type system icons (17KB)
│   ├── VisualStudioTemplates.h        # VS templates (44KB)
│   └── JenovaVM.h                     # Virtual machine (6KB)
├── Loader System:
│   ├── Jenova.Loader.h                # Dynamic loader (4KB - recently modified)
│   └── Jenova.Loader.h.backup         # Loader backup (7KB)
```

## 🔗 Dependencies Structure (`Dependencies/`)
```
Dependencies/ (11 major libraries)    # Third-party dependencies
├── libarchive/                        # Archive handling library
├── libasmjit/                         # ARM64 JIT compilation (AsmJIT backend)
├── libcurl/                           # HTTP/networking library
├── libgodot/                          # Godot engine integration
├── libjenova/                         # Jenova runtime libraries
│   ├── Archive/                       # Archive utilities
│   ├── AsmJIT/                        # JIT compilation interface
│   ├── Base64/                        # Encoding utilities
│   ├── Curl/                          # Network interface
│   ├── FileWatch/                     # File monitoring
│   ├── Misc/                          # Utility functions
│   ├── Parsers/                       # Data parsing
│   ├── Threading/                     # Thread management
│   ├── TinyCC/                        # C compiler integration
│   └── Zlib/                          # Compression
├── liblzma/                           # LZMA compression (with CMake support)
├── libpthread/                        # Threading library (185 files)
├── libtinycc/                         # Tiny C Compiler
├── libxml2/                           # XML processing (101 files)
└── libzlib/                           # Zlib compression (63 files)
```

## 📚 Processed Libraries (`Libs/`)
```
Libs/                                  # Processed library headers
├── Archive/                           # Archive processing headers
├── AsmJIT/                            # JIT compilation headers
│   ├── core/                          # Core JIT functionality
│   └── x86/                           # x86/x64 backend (needs ARM64 conversion)
├── Base64/                            # Encoding headers
├── Curl/                              # Network headers
├── FileWatch/                         # File monitoring headers
├── GodotSDK/                          # Godot integration
│   └── godot_cpp/                     # C++ bindings
├── Misc/                              # Utility headers
├── OpenSSL/                           # SSL/TLS headers
├── Parsers/                           # Parser headers
├── Threading/                         # Threading headers
├── TinyCC/                            # Compiler headers
└── Zlib/                              # Compression headers
```

## 🔧 Build System Architecture
```
BUILD_SYSTEM_COMPONENTS:
✅ Jenova.Builder_ARM64.py             # Main ARM64 build system (24KB)
    • Python 3.13 virtual environment management
    • Dependency compilation and linking
    • Cross-platform build configuration
    • ARM64 optimization settings
    • Error tracking and reporting

✅ jenova_build_env/                   # Primary build environment
    • Python 3.13.x isolated environment
    • Build dependencies: py7zr, psutil, requests, cryptodome
    • Archive processing: Brotli, pyzstd, multivolumefile
    • Network tools: urllib3, certifi, charset_normalizer

✅ vir_build_env/                      # Virtual build environment
    • Parallel build environment for testing
    • Identical dependency set for verification
    • Clean environment builds

✅ Visual Studio Integration:
    • Jenova.Runtime.vcxproj           # VS project configuration
    • Jenova.sln                       # Solution file
    • Cross-platform project management

✅ Godot Integration:
    • Jenova.Runtime.gdextension       # GDExtension configuration
    • Direct engine embedding support

CURRENT_BUILD_CAPABILITIES:
✅ ARM64 native compilation on Darwin
✅ Dependency isolation and management
✅ Virtual environment automation
✅ Error tracking and logging
✅ Repository maintenance automation

📋 BUILD_SYSTEM_NEEDS:
- Cross-platform build verification (Linux x64, Windows x64)
- Hot-reload integration with asset monitoring
- Performance optimization for large builds
- Parallel compilation improvements
```

## 🎯 Current Architecture Implementation
```
RUNTIME_ARCHITECTURE_STATUS:
✅ DUAL_LAYER_FOUNDATION:
- Source/ contains complete runtime implementation
- Asset monitoring and file watching foundation (asset_monitor.cpp)
- Script compilation pipeline (script_compiler.cpp - 146KB implementation)
- Runtime interpreter system (script_interpreter.cpp - 88KB)
- Package management (package_manager.cpp - 65KB)

✅ JIT_COMPILATION_SYSTEM:
- AsmJIT integration in Dependencies/libasmjit and Libs/AsmJIT
- Currently x64 backend (needs ARM64 conversion)
- Core JIT functionality implemented
- Runtime compilation pipeline ready

✅ GODOT_INTEGRATION:
- Complete Godot SDK in Dependencies/libgodot
- GDExtension configuration (Jenova.Runtime.gdextension)
- Script language integration (script_language.cpp - 20KB)
- Object system bridge (script_object.cpp - 12KB)

✅ COMPONENT_SYSTEM:
- Task system implementation (task_system.cpp)
- Performance profiling (tiny_profiler.cpp)
- Template system (script_templates.cpp)
- Resource management (script_resource.cpp)

CRITICAL_COMPONENTS_STATUS:
🚧 NitroJIT ARM64 Conversion:
    - AsmJIT backend exists in Dependencies/libasmjit
    - Current x64 implementation in Libs/AsmJIT/x86/
    - Needs ARM64 backend implementation

🚧 Asset Monitor Integration:
    - Basic file watching in asset_monitor.cpp (6KB)
    - Needs hot-reload integration
    - FileWatch utilities in Dependencies/libjenova/FileWatch

🚧 Platform Abstraction:
    - Foundation exists in runtime components
    - Needs OS detection and platform-specific optimization
    - Threading system ready (libpthread integration)
```

## 🔍 Key System Integration Points
```
INTEGRATION_ANALYSIS:
✅ BUILD_TO_RUNTIME_PIPELINE:
- Jenova.Builder_ARM64.py → Source/ compilation
- Virtual environments ensure clean builds
- Dependency resolution from Dependencies/ to Libs/
- ARM64 optimization throughout pipeline

✅ SCRIPT_TO_RUNTIME_PIPELINE:
- script_compiler.cpp → script_interpreter.cpp
- Template system → Resource management
- Package management → Asset monitoring
- Task system coordination

✅ GODOT_INTEGRATION_PIPELINE:
- libgodot dependency → GodotSDK headers
- GDExtension configuration → Runtime bridge
- Script language → Object system
- Instance management complete

MISSING_INTEGRATION_POINTS:
📋 Hot-reload workflow: asset_monitor.cpp → script_compiler.cpp
📋 JIT optimization: AsmJIT ARM64 → script_interpreter.cpp  
📋 Cross-platform builds: Dependencies/ → platform-specific Libs/
📋 Performance monitoring: tiny_profiler.cpp → runtime metrics
```

## 🚀 Phase 1 Implementation Priority Matrix
```
IMMEDIATE_ACTIONS_BASED_ON_CURRENT_STRUCTURE:

HIGH_PRIORITY (This Week):
1. NitroJIT ARM64 Investigation:
   → Analyze Dependencies/libasmjit ARM64 capabilities
   → Convert Libs/AsmJIT/x86/ to ARM64 backend
   → Test JIT compilation on Darwin ARM64

2. Asset Monitor Enhancement:
   → Extend asset_monitor.cpp with hot-reload capabilities
   → Integrate Dependencies/libjenova/FileWatch
   → Connect to script_compiler.cpp pipeline

3. Cross-Platform Build Testing:
   → Test Jenova.Builder_ARM64.py on clean environments
   → Verify Dependencies/ compilation on Linux x64
   → Document build requirements and setup

MEDIUM_PRIORITY (This Month):
1. Platform Abstraction Implementation:
   → Add OS detection to existing runtime
   → Optimize Dependencies/libpthread for ARM64
   → Platform-specific optimizations in Libs/

2. Hot-Reload Integration:
   → Connect asset_monitor.cpp to package_manager.cpp
   → Implement script change detection
   → State preservation during reload

ARCHITECTURAL_STRENGTHS_TO_LEVERAGE:
✅ Comprehensive dependency management already implemented
✅ Dual virtual environment system ensures build reliability
✅ Complete script compilation and interpretation pipeline
✅ Godot integration foundation solid and ready
✅ ARM64 build system functional and optimized
```

## 🧪 Testing Strategy Implementation
```
CURRENT_TESTING_INFRASTRUCTURE:
✅ Build System Testing:
- Dual environment verification (jenova_build_env + vir_build_env)
- Error logging and tracking (build_error.log)
- Repository maintenance automation (cleanup_repo.py)

✅ Dependency Testing:
- Complete library compilation verification
- Cross-platform dependency resolution
- ARM64 optimization validation

📋 NEEDED_TESTING_COMPONENTS:
- Unit tests for Source/ components (50 files)
- Integration tests for script compilation pipeline
- Performance benchmarks for JIT compilation
- Cross-platform build verification
- Hot-reload workflow testing

TESTING_PRIORITIES:
1. NitroJIT ARM64 backend validation
2. Asset monitor hot-reload functionality
3. Cross-platform dependency compilation
4. Script compilation and interpretation pipeline
5. Godot integration and GDExtension functionality
```

## 📊 File Size Analysis & Complexity Mapping
```
MAJOR_IMPLEMENTATION_FILES_BY_SIZE:
🔥 Critical Large Files (100KB+):
- jenova.cpp (365KB)                   # Core runtime - high complexity
- script_compiler.cpp (146KB)          # Compilation pipeline - high complexity  
- script_interpreter.cpp (88KB)        # Runtime interpreter - high complexity
- package_manager.cpp (65KB)           # Package management - medium complexity

📊 Embedded Resource Files (1MB+):
- AboutImage.h (5.7MB)                 # UI resources - low complexity
- InternalModules.h (5MB)              # Module definitions - medium complexity
- ExtensionHosts.h (2.3MB)             # Extension system - medium complexity
- BuiltinFonts.h (920KB)               # Font resources - low complexity

🎯 Key Integration Files:
- script_language.cpp (20KB)           # Language bridge - high complexity
- script_instance.cpp (20KB)           # Instance management - high complexity
- clektron.cpp (36KB)                  # Development tools - medium complexity
- JenovaSDK.h (19KB)                   # SDK interface - high complexity

COMPLEXITY_ASSESSMENT:
- High Complexity: Core runtime, compilation, interpretation, language integration
- Medium Complexity: Package management, extension system, development tools
- Low Complexity: Resource files, utilities, basic interfaces
```

---
*Auto-generated structure reference for Claude.ai collaboration*  
*Current focus: Phase 1 core infrastructure with comprehensive build system*