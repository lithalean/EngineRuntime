# Claude.ai Development Context
*AI Collaboration State for Jenova Runtime*

> **Location**: `/.claude/context.md` - Main AI collaboration context file

## 🎯 Project DNA
**Type**: Darwin ARM64 Runtime Porting Effort  
**Architecture**: Dual-Layer (SwiftUI Native + Godot Core)  
**Platforms**: macOS ARM64 (primary), Linux x64, Windows x64  
**Design Language**: High-performance native runtime  
**Current Phase**: Phase 1 - Core Infrastructure  
**Build Status**: IN DEVELOPMENT (~20% Complete)  

## 🧠 Core Architecture Decisions Made
```
DECISION_LOG:
[Initial] - Dual-layer architecture: SwiftUI native + Godot core separation
[Initial] - ARM64 primary target with cross-platform compatibility
[Initial] - NitroJIT for runtime compilation and optimization
[Initial] - CMake + Ninja build system with Python automation
[Initial] - Hot-reload development workflow with state preservation
[Initial] - GDExtension interface for module system
[Initial] - C++17+ standards with modern compiler support
```

## 🏗️ Technical Stack State
```cpp
// Current Architecture Pattern
Dual-Layer Runtime:
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

// Runtime Components
Core/
├── NitroJIT/          # ARM64 JIT compilation
├── Meteora/           # Component system (WORKING)
├── AssetMonitor/      # File watching (TODO)
└── ModuleSystem/      # Dynamic loading (TODO)
```

## 🎨 Design System Implemented
- **Performance-First**: ARM64 optimization with native Darwin APIs
- **Modular Architecture**: Hot-swappable components with clean interfaces
- **Cross-Platform**: Unified codebase with platform-specific optimizations
- **Developer Experience**: Live reload, hot-swap, efficient build pipeline
- **Modern C++**: C++17+ standards with advanced compiler features
- **Build Automation**: Python-based Jenova Builder with dependency management

## 📊 Current Implementation Matrix
```
FEATURE_STATUS_MATRIX:
✅ COMPLETE     🚧 IN_PROGRESS     📋 PLANNED     ❌ BLOCKED

Foundation (Phase 0):
✅ Basic Runtime Building    ✅ NitroJIT ARM64 Emitter   ✅ Meteora Component
✅ Build System             ✅ Dependency Management     ✅ Core Architecture

Core Infrastructure (Phase 1):
🚧 Abstraction OS Layer     📋 Metadata Parser          📋 Asset Monitor
📋 Platform Integration     📋 Hot-Reload System        📋 File Watching

Compilation Pipeline (Phase 2):
📋 Compiler Interface       📋 Module Wrapper           📋 Dynamic Compilation
📋 Symbol Management        📋 GDExtension Integration  📋 Build Pipeline

Runtime & Development (Phase 3):
📋 Interpreter Engine       📋 Module Loader            📋 Development Tools
📋 Performance Optimization 📋 Debug Support            📋 Error Handling
```

## 🔧 Known Technical Debt
```
HIGH_PRIORITY:
- NitroJIT ARM64 Emitter: Currently only emits x64 assembly, needs ARM64 native output
- Asset Monitor: Complete file watching implementation needed for hot-reload
- Abstraction OS Layer: Platform detection and native API wrapping incomplete

MEDIUM_PRIORITY:
- Build System: Jenova Builder needs error handling and cross-platform improvements
- Dependency Management: Some libraries need ARM64 optimization verification
- Documentation: Code documentation and architecture guides needed

PERFORMANCE_OPTIMIZATION:
- Memory management optimization for large game assets
- JIT compilation performance tuning for runtime code generation
- Cross-platform performance parity between ARM64 and x64
```

## 🎯 Next Development Priorities
```
IMMEDIATE (This Week):
1. Abstraction OS Layer - Platform detection implementation - [COMPLEXITY: HIGH]
2. Asset Monitor File Watching - Basic file system monitoring - [COMPLEXITY: MEDIUM]
3. NitroJIT ARM64 - Investigate x64->ARM64 emitter conversion - [COMPLEXITY: HIGH]

SHORT_TERM (This Month):
1. Metadata Parser - C++ AST analysis for reflection data
2. Hot-Reload Pipeline - Script change detection with state preservation
3. Platform Integration - macOS ARM64 native API optimization

ARCHITECTURAL_DECISIONS_NEEDED:
- Asset Monitor Implementation: inotify vs kqueue vs polling for file watching
- Bridge Communication: Message passing vs shared memory for SwiftUI<->Godot
- Module Loading: dlopen vs custom loader for hot-swappable components
```

## 🐛 Bug Tracking & Issues
```
CRITICAL:
- NitroJIT ARM64 emitter outputs x64 assembly instead of ARM64 | Investigate AsmJIT ARM64 backend | Blocks native performance

HIGH:
- Build system dependency resolution on clean environments | Test virtual environment setup | Affects new developer onboarding

MEDIUM:
- Cross-platform compilation warnings on GCC vs Clang | Standardize compiler flags | Code quality issue

ENHANCEMENT_REQUESTS:
- Live debugging interface for hot-reloaded components | Developer productivity
- Visual build progress indication in Jenova Builder | User experience improvement
```

## 🧪 Testing Strategy State
```
UNIT_TESTS:
- Core components: 15% coverage
- NitroJIT system: 10% coverage
- Build system: 0% coverage (TODO)

INTEGRATION_TESTS:
- Cross-platform builds: Manual testing only
- Hot-reload workflow: Not implemented
- Performance benchmarks: Not implemented

PLATFORM_TESTS:
- macOS ARM64: Primary development target
- Linux x64: Basic compatibility testing needed
- Windows x64: Not yet tested
```

## 🚀 Release Planning Context
```
CURRENT_VERSION: 0.1.0-alpha
TARGET_VERSION: 0.2.0-alpha (Core Infrastructure Complete)
RELEASE_TIMELINE: Q3 2025

PHASE_1_COMPLETE_CHECKLIST:
□ Abstraction OS Layer implemented
□ Metadata Parser functional
□ Asset Monitor with file watching
□ Hot-reload basic functionality
□ Cross-platform build verification

KNOWN_RISKS:
- NitroJIT ARM64 conversion complexity: May require AsmJIT backend changes
- Cross-platform compatibility: Windows/Linux testing infrastructure needed
- Performance targets: ARM64 optimization validation required
```

## 📚 Key Patterns & Conventions Established
```cpp
// File Organization Pattern
JenovaRuntime/
├── Core/             // Core runtime components
├── Bridge/           // SwiftUI<->Godot communication
├── Runtime/          // Execution and compilation
├── Platform/         // OS-specific implementations
└── Build/            // Build system and automation

// Naming Conventions
- Components: [Feature]Component.cpp
- Interfaces: I[Feature].h
- Platform: Platform[OS].cpp
- Tests: Test[Feature].cpp

// Architecture Patterns
- Component-based design with clean interfaces
- Platform abstraction with OS-specific implementations
- Hot-reload friendly with state preservation
- Performance-critical sections in C++ with ARM64 optimization
```

## 🔄 AI Collaboration History
```
LAST_SESSION_FOCUS: Initial project setup and README standardization
DECISIONS_MADE: Adopted Darwin ARM64 README template for runtime project
CODE_GENERATED: Converted project documentation to standard format
NEXT_SESSION_PREP: Begin implementation of Abstraction OS Layer

RECURRING_AI_ASSISTANCE_AREAS:
- Architecture decisions for dual-layer runtime design
- Cross-platform porting strategies and compatibility
- Performance optimization for ARM64 Darwin systems
- JIT compilation and runtime code generation
- Hot-reload and development workflow optimization
```

## 🎨 Design Philosophy & Constraints
```
DESIGN_PRINCIPLES:
- Performance over convenience for runtime-critical code
- Native platform integration over cross-platform compromise
- Hot-reload development workflow over traditional compilation
- Modular architecture over monolithic design
- ARM64 optimization over generic compatibility

TECHNICAL_CONSTRAINTS:
- C++17+ minimum for modern language features
- ARM64 primary target with x64 compatibility
- Godot engine integration requirements
- SwiftUI native layer on Darwin platforms
- Hot-reload capability preservation

PERFORMANCE_PRIORITIES:
1. Runtime execution speed (JIT compilation)
2. Memory efficiency (large game asset handling)
3. Development iteration speed (hot-reload)
4. Cross-platform performance parity
5. Build time optimization
```

## 🏗️ Component Implementation Status
```
PHASE_1_COMPONENTS:
Asset Monitor:
  - File watching system: 0% complete
  - Hot-reload functionality: 0% complete
  - Change detection: 0% complete

Abstraction OS Layer:
  - Platform detection: 0% complete
  - macOS ARM64 support: 0% complete
  - Native API wrapping: 0% complete

Metadata Parser:
  - C++ AST analysis: 0% complete
  - Reflection data generation: 0% complete
  - Godot integration: 0% complete

BUILD_SYSTEM_STATUS:
- Jenova Builder ARM64: Functional
- Dependency management: Complete
- Cross-platform builds: Partial (macOS only)
- Virtual environment: Working
```

---
*Last Updated: June 15, 2025 | Claude.ai Session: Initial Setup*