#!/usr/bin/env python3
# Jenova Runtime Build System - macOS ARM64
# Streamlined version for Darwin ARM64 builds
# Usage: python3 ./jenova_builder_macos.py [--skip-deps] [--skip-cache] [--skip-packaging] [--clean]

import os
import sys
import json
import time
import shutil
import hashlib
import subprocess
import argparse
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

# Try to import optional dependencies
try:
    import requests
except ImportError:
    print("ERROR: 'requests' module not found. Install with: pip3 install requests")
    sys.exit(1)

try:
    import py7zr
except ImportError:
    print("ERROR: 'py7zr' module not found. Install with: pip3 install py7zr")
    sys.exit(1)

# Configuration
DEPS_VERSION = "4.3"
OUTPUT_DIR = "DarwinARM64"
OUTPUT_NAME = "Jenova.Runtime.DarwinARM64.dylib"
MAP_FILE = "Jenova.Runtime.DarwinARM64.map"

# Build flags
BUILD_FLAGS = [
    "NDEBUG",
    "JENOVA_RUNTIME", 
    "JENOVA_SDK_BUILD",
    "TYPED_METHOD_BIND"
]

# Include directories
INCLUDE_DIRS = [
    "Libs",
    "Libs/GodotSDK", 
    "Libs/GodotSDK/godot_cpp",
    "Libs/OpenSSL/include",
    "Source"
]

# Source files to compile
SOURCE_FILES = [
    "Source/jenova.cpp",
    "Source/jenovaSDK.cpp", 
    "Source/script_instance_base.cpp",
    "Source/script_object.cpp",
    "Source/script_instance.cpp",
    "Source/script_resource.cpp",
    "Source/script_interpreter.cpp",
    "Source/script_templates.cpp",
    "Source/script_language.cpp",
    "Source/script_compiler.cpp",
    "Source/script_manager.cpp",
    "Source/clektron.cpp",
    "Source/tiny_profiler.cpp",
    "Source/task_system.cpp",
    "Source/package_manager.cpp",
    "Source/asset_monitor.cpp",
    "Source/gdextension_exporter.cpp"
]

# Static libraries
STATIC_LIBS = [
    "Libs/libzlib-static-arm64.a",
    "Libs/libtcc-static-arm64.a", 
    "Libs/libgodotcpp-static-arm64.a",
    "Libs/libcurl-static-arm64.a",
    "Libs/libasmjit-static-arm64.a",
    "Libs/libarchive-static-arm64.a",
    "Libs/liblzma-static-arm64.a",
    "Libs/libxml2-static-arm64.a", 
    "Libs/OpenSSL/libssl-arm64.a", 
    "Libs/OpenSSL/libcrypto-arm64.a"
]

class Colors:
    GREEN = '\033[92m'
    BLUE = '\033[94m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    END = '\033[0m'
    BOLD = '\033[1m'

def print_colored(color, message, end='\n'):
    print(f"{color}{message}{Colors.END}", end=end)

def print_banner():
    banner = f"""{Colors.GREEN}
===========================================================================
       _________   ______ _    _____       ____        _ __    __
      / / ____/ | / / __ \\ |  / /   |     / __ )__  __(_) /___/ /__  _____
 __  / / __/ /  |/ / / / / | / / /| |    / __  / / / / / / __  / _ \\/ ___/
/ /_/ / /___/ /|  / /_/ /| |/ / ___ |   / /_/ / /_/ / / / /_/ /  __/ /
\\____/_____/_/ |_/\\____/ |___/_/  |_|  /_____/\\__,_/_/_/\\__,_/\\___/_/

===========================================================================
                    Developed by Hamid.Memar
===========================================================================
{Colors.END}
"""
    print(banner)

def check_prerequisites():
    """Check if required tools are available"""
    print_colored(Colors.BLUE, "[ ✓ ] Checking prerequisites...")
    
    required_tools = ['clang++', 'cmake', 'ninja']
    for tool in required_tools:
        if not shutil.which(tool):
            print_colored(Colors.RED, f"[ ✗ ] Error: {tool} not found in PATH")
            print_colored(Colors.YELLOW, f"Install {tool} using: brew install {tool}")
            return False
    
    # Check if we're on macOS ARM64
    import platform
    if platform.system() != 'Darwin':
        print_colored(Colors.RED, "[ ✗ ] Error: This script only works on macOS")
        return False
        
    if platform.machine() != 'arm64':
        print_colored(Colors.YELLOW, "[ ! ] Warning: Not running on ARM64 architecture")
    
    print_colored(Colors.GREEN, "[ ✓ ] All prerequisites satisfied")
    return True

def compute_file_hash(file_path):
    """Compute MD5 hash of a file"""
    hasher = hashlib.md5()
    with open(file_path, 'rb') as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hasher.update(chunk)
    return hasher.hexdigest()

def load_build_cache(cache_file):
    """Load build cache from JSON file"""
    if not os.path.exists(cache_file):
        return {}
    try:
        with open(cache_file, 'r') as f:
            return json.load(f)
    except:
        return {}

def save_build_cache(cache, cache_file):
    """Save build cache to JSON file"""
    os.makedirs(os.path.dirname(cache_file), exist_ok=True)
    with open(cache_file, 'w') as f:
        json.dump(cache, f, indent=2)

def needs_recompile(source_file, cache, skip_cache=False):
    """Check if source file needs recompilation"""
    if skip_cache:
        return True
        
    if not os.path.exists(source_file):
        return True
        
    abs_path = os.path.abspath(source_file)
    if abs_path not in cache:
        return True
        
    cached_entry = cache[abs_path]
    current_mtime = os.path.getmtime(source_file)
    current_hash = compute_file_hash(source_file)
    
    return (cached_entry.get('mtime') != current_mtime or 
            cached_entry.get('hash') != current_hash)

def update_cache_entry(source_file, cache):
    """Update cache entry for a source file"""
    abs_path = os.path.abspath(source_file)
    cache[abs_path] = {
        'mtime': os.path.getmtime(source_file),
        'hash': compute_file_hash(source_file)
    }

def download_dependencies():
    """Download and extract dependencies package"""
    if os.path.exists("./Dependencies"):
        print_colored(Colors.YELLOW, "[ ! ] Dependencies already exist, skipping download")
        return
        
    deps_url = f"https://jenova-framework.github.io/download/development/Jenova-Runtime-Dependencies-Universal-{DEPS_VERSION}.jnvpkg"
    deps_file = "dependencies.jnvpkg"
    
    print_colored(Colors.BLUE, "[ ↓ ] Downloading dependencies package...")
    
    try:
        response = requests.get(deps_url, stream=True)
        response.raise_for_status()
        
        total_size = int(response.headers.get('content-length', 0))
        downloaded = 0
        
        with open(deps_file, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                if chunk:
                    f.write(chunk)
                    downloaded += len(chunk)
                    if total_size > 0:
                        percent = (downloaded / total_size) * 100
                        print(f"\r[ ↓ ] Progress: {percent:.1f}%", end='', flush=True)
        
        print()  # New line after progress
        print_colored(Colors.GREEN, "[ ✓ ] Dependencies downloaded successfully")
        
        # Extract package
        print_colored(Colors.BLUE, "[ ↗ ] Extracting dependencies...")
        with py7zr.SevenZipFile(deps_file, mode='r') as archive:
            archive.extractall(path="./Dependencies")
        
        os.remove(deps_file)
        print_colored(Colors.GREEN, "[ ✓ ] Dependencies extracted successfully")
        
    except Exception as e:
        print_colored(Colors.RED, f"[ ✗ ] Failed to download dependencies: {e}")
        sys.exit(1)

def run_cmake_build(source_dir, build_dir, cmake_args, target_lib):
    """Run CMake configuration and build"""
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir)
    
    os.makedirs(build_dir, exist_ok=True)
    
    # Configure
    cmd = ['cmake', '-S', source_dir, '-B', build_dir, '-G', 'Ninja'] + cmake_args
    subprocess.run(cmd, check=True, capture_output=True)
    
    # Build
    subprocess.run(['ninja', '-C', build_dir], check=True, capture_output=True)
    
    return target_lib

def build_dependencies(cache_dir, skip_deps=False):
    """Build all required dependencies"""
    if skip_deps:
        print_colored(Colors.YELLOW, "[ ! ] Skipping dependency build (--skip-deps)")
        return
        
    print_colored(Colors.BLUE, "[ ⚙ ] Building dependencies...")
    
    # Download dependencies first
    download_dependencies()
    
    # Create Libs directory
    os.makedirs("Libs", exist_ok=True)
    if os.path.exists("./Dependencies/libjenova"):
        shutil.copytree("./Dependencies/libjenova", "./Libs", dirs_exist_ok=True)
    
    # Set environment for all builds
    os.environ.update({
        'CC': 'clang',
        'CXX': 'clang++',
        'CFLAGS': '-fPIC -w -arch arm64',
        'CXXFLAGS': '-std=c++20 -w -fPIC -arch arm64',
        'LDFLAGS': '-framework Security -framework CoreFoundation -arch arm64'
    })
    
    dependencies = [
        {
            'name': 'AsmJIT',
            'lib_file': './Libs/libasmjit-static-arm64.a',
            'source_dir': './Dependencies/libasmjit',
            'build_dir': f'{cache_dir}/asmjit',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DASMJIT_STATIC=ON',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'libasmjit.a'
        },
        {
            'name': 'Curl',
            'lib_file': './Libs/libcurl-static-arm64.a',
            'source_dir': './Dependencies/libcurl',
            'build_dir': f'{cache_dir}/curl',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DCURL_BROTLI=OFF',
                '-DCURL_USE_LIBPSL=OFF',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'lib/libcurl.a'
        },
        {
            'name': 'LZMA',
            'lib_file': './Libs/liblzma-static-arm64.a',
            'source_dir': './Dependencies/liblzma',
            'build_dir': f'{cache_dir}/lzma',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'liblzma.a'
        },
        {
            'name': 'ZLIB',
            'lib_file': './Libs/libzlib-static-arm64.a',
            'source_dir': './Dependencies/libzlib',
            'build_dir': f'{cache_dir}/zlib',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DZLIB_BUILD_TESTING=OFF',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'libz.a'
        },
        {
            'name': 'XML2',
            'lib_file': './Libs/libxml2-static-arm64.a',
            'source_dir': './Dependencies/libxml2',
            'build_dir': f'{cache_dir}/xml2',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DLIBXML2_WITH_MODULES=OFF',
                '-DLIBXML2_WITH_PYTHON=OFF',
                '-DLIBXML2_WITH_TESTS=OFF',
                '-DLIBXML2_WITH_ICONV=OFF',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'libxml2.a'
        },
        {
            'name': 'TinyCC',
            'lib_file': './Libs/libtcc-static-arm64.a',
            'source_dir': './Dependencies/libtinycc',
            'build_dir': f'{cache_dir}/tinycc',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'liblibtcc.a'
        }
    ]
    
    # Build Archive (needs LZMA)
    if not os.path.exists('./Libs/libarchive-static-arm64.a'):
        lzma_include = os.path.abspath('./Dependencies/liblzma/src/liblzma/api')
        archive_args = [
            '-DCMAKE_BUILD_TYPE=MinSizeRel',
            '-DBUILD_SHARED_LIBS=OFF',
            '-DENABLE_LZMA=ON',
            '-DHAVE_LZMA_H=ON',
            '-DBUILD_TESTING=OFF',
            '-DENABLE_TEST=OFF',
            '-DENABLE_TAR=OFF',
            '-DENABLE_CAT=OFF',
            '-DENABLE_CPIO=OFF',
            '-DENABLE_EXPAT=OFF',
            '-DENABLE_BZip2=OFF',
            f'-DCMAKE_C_FLAGS=-fPIC -w -arch arm64 -DLZMA_API_STATIC -I{lzma_include}',
            '-DCMAKE_OSX_ARCHITECTURES=arm64'
        ]
        
        dependencies.append({
            'name': 'Archive',
            'lib_file': './Libs/libarchive-static-arm64.a',
            'source_dir': './Dependencies/libarchive',
            'build_dir': f'{cache_dir}/archive',
            'cmake_args': archive_args,
            'target_lib': 'libarchive/libarchive.a'
        })
    
    # Build GodotSDK
    if not os.path.exists('./Libs/libgodotcpp-static-arm64.a'):
        dependencies.append({
            'name': 'GodotSDK',
            'lib_file': './Libs/libgodotcpp-static-arm64.a',
            'source_dir': './Dependencies/libgodot',
            'build_dir': f'{cache_dir}/godotcpp',
            'cmake_args': [
                '-DCMAKE_BUILD_TYPE=MinSizeRel',
                '-DGODOT_ENABLE_HOT_RELOAD=ON',
                '-DBUILD_SHARED_LIBS=OFF',
                '-DCMAKE_OSX_ARCHITECTURES=arm64'
            ],
            'target_lib': 'bin/libgodot-cpp.darwin.minsizerel.64.a'
        })
    
    # Build each dependency
    for dep in dependencies:
        if os.path.exists(dep['lib_file']):
            print_colored(Colors.YELLOW, f"[ ! ] {dep['name']} already built, skipping")
            continue
            
        if not os.path.exists(dep['source_dir']):
            print_colored(Colors.YELLOW, f"[ ! ] {dep['name']} source not found, skipping")
            continue
            
        print_colored(Colors.BLUE, f"[ ⚙ ] Building {dep['name']}...")
        try:
            run_cmake_build(dep['source_dir'], dep['build_dir'], dep['cmake_args'], dep['target_lib'])
            shutil.copyfile(f"{dep['build_dir']}/{dep['target_lib']}", dep['lib_file'])
            print_colored(Colors.GREEN, f"[ ✓ ] {dep['name']} built successfully")
        except Exception as e:
            print_colored(Colors.RED, f"[ ✗ ] Failed to build {dep['name']}: {e}")
            sys.exit(1)
    
    # Setup GodotSDK headers
    setup_godot_sdk(cache_dir)

def setup_godot_sdk(cache_dir):
    """Setup GodotSDK headers"""
    sdk_path = "./Libs/GodotSDK"
    build_path = f"{cache_dir}/godotcpp"
    
    if os.path.exists(sdk_path):
        return
        
    print_colored(Colors.BLUE, "[ ⚙ ] Setting up GodotSDK headers...")
    os.makedirs(sdk_path, exist_ok=True)
    
    # Copy headers
    if os.path.exists("./Dependencies/libgodot/gdextension/gdextension_interface.h"):
        shutil.copyfile("./Dependencies/libgodot/gdextension/gdextension_interface.h", 
                       f"{sdk_path}/gdextension_interface.h")
    
    if os.path.exists("./Dependencies/libgodot/include"):
        shutil.copytree("./Dependencies/libgodot/include", sdk_path, dirs_exist_ok=True)
        
    if os.path.exists(f"{build_path}/gen/include"):
        shutil.copytree(f"{build_path}/gen/include", sdk_path, dirs_exist_ok=True)

def compile_sources(cache_dir, skip_cache=False):
    """Compile all source files"""
    print_colored(Colors.BLUE, "[ ⚙ ] Compiling source files...")
    
    cache_file = f"{cache_dir}/build_cache.json"
    cache = load_build_cache(cache_file)
    
    # Prepare compilation commands
    compile_tasks = []
    object_files = []
    
    for source in SOURCE_FILES:
        if not os.path.exists(source):
            print_colored(Colors.RED, f"[ ✗ ] Source file not found: {source}")
            continue
            
        obj_file = f"{cache_dir}/{Path(source).stem}.o"
        object_files.append(obj_file)
        
        if needs_recompile(source, cache, skip_cache):
            compile_cmd = [
                'clang++',
                '-arch', 'arm64',
                '-O3', '-fPIC', '-pipe', '-w',
                '-std=c++20', '-pthread', '-fexceptions'
            ]
            
            # Add defines
            for flag in BUILD_FLAGS:
                compile_cmd.extend(['-D', flag])
            
            # Add includes
            for inc_dir in INCLUDE_DIRS:
                compile_cmd.extend(['-I', inc_dir])
            
            compile_cmd.extend(['-c', source, '-o', obj_file])
            
            compile_tasks.append((source, compile_cmd, obj_file))
            update_cache_entry(source, cache)
        else:
            print_colored(Colors.YELLOW, f"[ ! ] Skipping {Path(source).name} (unchanged)")
    
    # Compile in parallel
    if compile_tasks:
        def compile_file(task):
            source, cmd, obj_file = task
            try:
                print_colored(Colors.BLUE, f"[ ⚙ ] Compiling {Path(source).name}...")
                subprocess.run(cmd, check=True, capture_output=True)
                print_colored(Colors.GREEN, f"[ ✓ ] Compiled {Path(source).name}")
                return True
            except subprocess.CalledProcessError as e:
                print_colored(Colors.RED, f"[ ✗ ] Failed to compile {Path(source).name}")
                print(f"Command: {' '.join(cmd)}")
                print(f"Error: {e.stderr.decode() if e.stderr else 'Unknown error'}")
                return False
        
        with ThreadPoolExecutor(max_workers=os.cpu_count()) as executor:
            results = list(executor.map(compile_file, compile_tasks))
            
        if not all(results):
            print_colored(Colors.RED, "[ ✗ ] Compilation failed")
            sys.exit(1)
    
    # Save cache
    save_build_cache(cache, cache_file)
    
    return object_files

def link_binary(object_files, output_dir):
	"""Link the final binary"""
	print_colored(Colors.BLUE, "[ ⚙ ] Linking binary...")
	
	output_path = f"{output_dir}/{OUTPUT_NAME}"
	map_path = f"{output_dir}/{MAP_FILE}"
	
	link_cmd = [
		'clang++',
		'-shared', '-fPIC',
		'-arch', 'arm64',
		'-stdlib=libc++',
		'-mmacosx-version-min=11.0',
		'-Wl,-undefined,dynamic_lookup',
		'-Wl,-install_name,@rpath/Jenova.Runtime.DarwinARM64.dylib',
		'-Wl,-map,' + map_path
	]
	
	link_cmd.extend(object_files)
	link_cmd.extend(STATIC_LIBS)
	
	# Add all required frameworks and libraries for ARM64 macOS
	frameworks = [
		'CoreFoundation', 'Security', 'Foundation', 'AppKit', 'IOKit',
		'DiskArbitration', 'Cocoa', 'Carbon', 'QuartzCore', 'Metal', 'MetalKit'
	]
	
	for framework in frameworks:
		link_cmd.extend(['-framework', framework])
	
	# Add system libraries
	system_libs = ['pthread', 'dl', 'm', 'xml2', 'resolv', 'c++']
	for lib in system_libs:
		link_cmd.extend(['-l' + lib])
	
	# Add Homebrew libraries (if available)
	homebrew_libs = ['/opt/homebrew/lib/libbrotlidec.dylib', 
					 '/opt/homebrew/lib/libbrotlienc.dylib',
					 '/opt/homebrew/lib/libbrotlicommon.dylib',
					 '/opt/homebrew/lib/libunistring.dylib']
	
	for lib in homebrew_libs:
		if os.path.exists(lib):
			link_cmd.append(lib)
	
	link_cmd.extend(['-o', output_path])
	
	try:
		subprocess.run(link_cmd, check=True, capture_output=True)
		print_colored(Colors.GREEN, f"[ ✓ ] Binary linked successfully: {output_path}")
		
		# Verify the binary
		subprocess.run(['file', output_path], check=True)
		
		return output_path
	except subprocess.CalledProcessError as e:
		print_colored(Colors.RED, "[ ✗ ] Linking failed")
		print(f"Command: {' '.join(link_cmd)}")
		print(f"Error: {e.stderr.decode() if e.stderr else 'Unknown error'}")
		sys.exit(1)

def prepare_release(output_dir, skip_packaging=False):
    """Prepare release files"""
    print_colored(Colors.BLUE, "[ ⚙ ] Preparing release...")
    
    sdk_dir = f"{output_dir}/JenovaSDK"
    os.makedirs(sdk_dir, exist_ok=True)
    
    # Copy SDK files
    if os.path.exists("./Source/JenovaSDK.h"):
        shutil.copy2("./Source/JenovaSDK.h", f"{sdk_dir}/JenovaSDK.h")
    
    if os.path.exists("./Jenova.Runtime.gdextension"):
        shutil.copy2("./Jenova.Runtime.gdextension", f"{output_dir}/Jenova.Runtime.gdextension")
    
    # Create .gitignore
    with open(f"{sdk_dir}/.gitignore", 'w') as f:
        f.write("*\n")
    
    if skip_packaging:
        print_colored(Colors.YELLOW, "[ ! ] Skipping packaging (--skip-packaging)")
        return
        
    # Create distribution package
    print_colored(Colors.BLUE, "[ ⚙ ] Creating distribution package...")
    
    dist_dir = f"{output_dir}/Distribution"
    os.makedirs(dist_dir, exist_ok=True)
    
    package_files = [
        (f"{output_dir}/{OUTPUT_NAME}", "Jenova/Jenova.Runtime.DarwinARM64.dylib"),
        (f"{output_dir}/Jenova.Runtime.gdextension", "Jenova/Jenova.Runtime.gdextension"),
        (f"{sdk_dir}/JenovaSDK.h", "Jenova/JenovaSDK/JenovaSDK.h"),
        (f"{sdk_dir}/.gitignore", "Jenova/JenovaSDK/.gitignore")
    ]
    
    package_path = f"{dist_dir}/Jenova-Runtime-macOS-ARM64.7z"
    
    try:
        with py7zr.SevenZipFile(package_path, 'w') as archive:
            for src, dst in package_files:
                if os.path.exists(src):
                    archive.write(src, dst)
        
        print_colored(Colors.GREEN, f"[ ✓ ] Distribution package created: {package_path}")
    except Exception as e:
        print_colored(Colors.RED, f"[ ✗ ] Failed to create package: {e}")

def clean_build(deep_clean=False):
    """Clean build artifacts"""
    print_colored(Colors.BLUE, "[ ⚙ ] Cleaning build artifacts...")
    
    dirs_to_clean = [OUTPUT_DIR, "Libs"]
    
    if deep_clean:
        dirs_to_clean.extend(["Dependencies", "Toolchain"])
        
    for dir_path in dirs_to_clean:
        if os.path.exists(dir_path):
            shutil.rmtree(dir_path)
            print_colored(Colors.GREEN, f"[ ✓ ] Removed {dir_path}")
    
    print_colored(Colors.GREEN, "[ ✓ ] Clean completed")

def main():
    parser = argparse.ArgumentParser(description='Jenova Runtime Builder for macOS ARM64')
    parser.add_argument('--skip-deps', action='store_true', help='Skip dependency building')
    parser.add_argument('--skip-cache', action='store_true', help='Skip build cache')
    parser.add_argument('--skip-packaging', action='store_true', help='Skip packaging')
    parser.add_argument('--clean', action='store_true', help='Clean build artifacts')
    parser.add_argument('--deep-clean', action='store_true', help='Deep clean (includes dependencies)')
    parser.add_argument('--no-banner', action='store_true', help='Skip banner')
    
    args = parser.parse_args()
    
    if not args.no_banner:
        print_banner()
    
    if args.clean or args.deep_clean:
        clean_build(args.deep_clean)
        return
    
    # Check prerequisites
    if not check_prerequisites():
        sys.exit(1)
    
    # Setup directories
    cache_dir = f"{OUTPUT_DIR}/Cache"
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    os.makedirs(cache_dir, exist_ok=True)
    
    start_time = time.time()
    
    try:
        # Build dependencies
        build_dependencies(cache_dir, args.skip_deps)
        
        # Compile sources
        object_files = compile_sources(cache_dir, args.skip_cache)
        
        # Link binary
        binary_path = link_binary(object_files, OUTPUT_DIR)
        
        # Prepare release
        prepare_release(OUTPUT_DIR, args.skip_packaging)
        
        elapsed = time.time() - start_time
        print_colored(Colors.GREEN, f"\n[ ✓ ] Build completed successfully in {elapsed:.2f} seconds!")
        print_colored(Colors.CYAN, f"[ ✓ ] Output: {binary_path}")
        
    except KeyboardInterrupt:
        print_colored(Colors.RED, "\n[ ✗ ] Build interrupted by user")
        sys.exit(1)
    except Exception as e:
        print_colored(Colors.RED, f"\n[ ✗ ] Build failed: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()