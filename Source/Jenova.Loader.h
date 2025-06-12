/*-------------------------------------------------------------+
|                                                              |
|                   _________   ______ *    *____              |
|                  / / ____/ | / / __ \ |  / /   |             |
|             **  / / __/ /  |/ / / / / | / / /| |             |
|            / /_/ / /___/ /|  / /_/ /| |/ / ___ |             |
|            \____/_____/_/ |_/\____/ |___/_/  |_|             |
|                                                              |
|                        Jenova Runtime                        |
|                   Developed by Hamid.Memar                   |
|                                                              |
+-------------------------------------------------------------*/

// Jenova Loader (macOS ARM64 Only)
#pragma once

// Standard Headers
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unordered_map>
#include <cstdio>
#include <fstream>       
#include <cstring>
#include <string>

// Jenova Headers
#include "Jenova.hpp"

// Load Flags
#define LOAD_FLAGS_NORMAL                                               0x00000000
#define LOAD_FLAGS_LAZY                                                 0x00000001
#define LOAD_FLAGS_GLOBAL                                               0x00000100
#define LOAD_FLAGS_LOCAL                                                0x00000000
#define LOAD_FLAGS_DEEP                                                 0x00000008

// Loader Interface [macOS ARM64]
class JenovaLoader
{
public:
	static bool Initialize()
	{
		return true;
	}
	
	static bool Release()
	{
		return true;
	}
	
	static bool SetAgressiveMode(bool agrState)
	{
		aggressiveMode = agrState;
		return true;
	}
	
	static jenova::ModuleHandle LoadModule(void* bufferPtr, size_t bufferSize, int flags = 0)
	{
		// Create temporary file for module loading
		char tempPath[] = "/tmp/jenova_module_XXXXXX";
		int fd = mkstemp(tempPath);
		if (fd == -1)
		{
			perror("[Jenova Loader] Failed to create temporary file");
			return nullptr;
		}
		
		// Write module data to temporary file
		ssize_t written = write(fd, bufferPtr, bufferSize);
		if (written != static_cast<ssize_t>(bufferSize))
		{
			perror("[Jenova Loader] Failed to write module data");
			close(fd);
			unlink(tempPath);
			return nullptr;
		}
		
		// Close file descriptor and make executable
		close(fd);
		chmod(tempPath, 0755);
		
		// Load the dynamic library
		int dlFlags = RTLD_NOW;
		if (flags & LOAD_FLAGS_LAZY) dlFlags = RTLD_LAZY;
		if (flags & LOAD_FLAGS_GLOBAL) dlFlags |= RTLD_GLOBAL;
		
		void* handle = dlopen(tempPath, dlFlags);
		if (!handle)
		{
			fprintf(stderr, "[Jenova Loader] dlopen failed: %s\n", dlerror());
			unlink(tempPath);
			return nullptr;
		}
		
		// Store temporary file path for cleanup
		tempFileMap[handle] = std::string(tempPath);
		
		return reinterpret_cast<jenova::ModuleHandle>(handle);
	}
	
	static jenova::ModuleHandle LoadModuleAsVirtual(void* bufferPtr, size_t bufferSize, const char* moduleName, const char* modulePath, int flags = 0)
	{
		// For macOS, we use the same approach as LoadModule
		return LoadModule(bufferPtr, bufferSize, flags);
	}
	
	static jenova::ModuleAddress GetModuleBaseAddress(jenova::ModuleHandle moduleHandle)
	{
		// Get module info using dladdr
		Dl_info info;
		if (dladdr(moduleHandle, &info) != 0)
		{
			return jenova::ModuleAddress(reinterpret_cast<uintptr_t>(info.dli_fbase));
		}
		return jenova::ModuleAddress(0);
	}
	
	static void* GetVirtualFunction(jenova::ModuleHandle moduleHandle, const char* functionName)
	{
		return dlsym(moduleHandle, functionName);
	}
	
	static bool ReleaseModule(jenova::ModuleHandle moduleHandle)
	{
		if (!moduleHandle) return false;
		if (!aggressiveMode) return true;
		
		// Close dynamic library
		dlclose(moduleHandle);
		
		// Clean up temporary file
		auto it = tempFileMap.find(moduleHandle);
		if (it != tempFileMap.end())
		{
			unlink(it->second.c_str());
			tempFileMap.erase(it);
		}
		
		return true;
	}

private:
	static inline bool aggressiveMode = false;
	static inline std::unordered_map<jenova::ModuleHandle, std::string> tempFileMap;
};