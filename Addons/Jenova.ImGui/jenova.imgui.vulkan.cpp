
/*-------------------------------------------------------------+
|                                                              |
|                   _________   ______ _    _____              |
|                  / / ____/ | / / __ \ |  / /   |             |
|             __  / / __/ /  |/ / / / / | / / /| |             |
|            / /_/ / /___/ /|  / /_/ /| |/ / ___ |             |
|            \____/_____/_/ |_/\____/ |___/_/  |_|             |
|                                                              |
|                         Jenova ImGui                         |
|                   Developed by Hamid.Memar                   |
|                                                              |
+-------------------------------------------------------------*/

// Windows SDK
#include <Windows.h>

// C++ Runtime SDK
#include <iostream>
#include <unordered_map>

// MinHook SDK
#include <MinHook.h>

// Vulkan SDK
#include <vulkan/vulkan.h>

// ImGui SDK
#include "imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_vulkan.h"

// JenovaImGui SDK
#include "JenovaImGui.h"

// Namespaces
using namespace std;

// Log Helpers
#define log(fmt,...) printf("[Jenova-ImGui] ::> " fmt "\n", __VA_ARGS__);

// Imports
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Jenova Runtime Interface
namespace JenovaRuntime
{
    // Internal Objects
    HMODULE jenovaRuntime = nullptr;

    // JenovaSDK Enumerators
    enum RuntimeEvent
    {
        Initialized,
        Started,
        Stopped,
        Ready,
        EnterTree,
        ExitTree,
        FrameBegin,
        FrameIdle,
        FrameEnd,
        FramePresent,
        Process,
        PhysicsProcess,
        ReceivedDebuggerMessage
    };

    // JenovaSDK Types
    typedef void (*RuntimeCallback)(const int&, void*, size_t);

    // JenovaSDK Functions
    namespace JenovaSDK
    {
        void* (*GetSDKFunction)(const char* sdkFunctionName);
        HWND(*GetGameWindowHandle)() = nullptr;
        const char* (*GetRenderingDriverName)() = nullptr;
        void* (*GetRenderingDriverResource)(int) = nullptr;
        bool (*RegisterRuntimeCallback)(RuntimeCallback) = nullptr;
        bool (*UnregisterRuntimeCallback)(RuntimeCallback) = nullptr;
    } 

    // Internal Functions
    static bool SolveJenovaRuntimeModule()
    {
        jenovaRuntime = LoadLibraryW(L"Jenova.Runtime.Win64.dll");
        if (!jenovaRuntime) return false;
        return true;
    }
    static bool SolveJenovaRuntimeSDKFunctions()
    {
        // Validate Runtime Module
        if (!jenovaRuntime) return false;

        // Get SDK Function Solver
        JenovaSDK::GetSDKFunction = (void*(*)(const char*))GetProcAddress(jenovaRuntime, "GetSDKFunction");
        if (!JenovaSDK::GetSDKFunction) return false;

        // Solve SDK Functions
        JenovaSDK::GetGameWindowHandle = (HWND(*)())JenovaSDK::GetSDKFunction("GetGameWindowHandle");
        if (!JenovaSDK::GetGameWindowHandle) return false;
        JenovaSDK::GetRenderingDriverName = (const char*(*)())JenovaSDK::GetSDKFunction("GetRenderingDriverName");
        if (!JenovaSDK::GetRenderingDriverName) return false;
        JenovaSDK::GetRenderingDriverResource = (void*(*)(int))JenovaSDK::GetSDKFunction("GetRenderingDriverResource");
        if (!JenovaSDK::GetRenderingDriverResource) return false;
        JenovaSDK::RegisterRuntimeCallback = (bool(*)(RuntimeCallback))JenovaSDK::GetSDKFunction("RegisterRuntimeCallback");
        if (!JenovaSDK::RegisterRuntimeCallback) return false;
        JenovaSDK::UnregisterRuntimeCallback = (bool(*)(RuntimeCallback))JenovaSDK::GetSDKFunction("UnregisterRuntimeCallback");
        if (!JenovaSDK::UnregisterRuntimeCallback) return false;

        // All Good
        return true;
    }
}

// JenovaImGui Internals
namespace JenovaImGui
{
    // JenovaImGui :: Core
    bool InitializeImGuiCore();
    bool UninitializeImGuiCore();

    // JenovaImGui :: Helpers
    void ConfigureImGuiStyle();

    // JenovaImGui :: Events
    void OnRuntimeEvent(const int& runtimeEvent, void* dataPtr, size_t dataSize);

    // JenovaImGui :: Window Message Handler
    LRESULT CALLBACK HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

// Static Library API
static void InitializeJenovaImGui()
{
    // Solve Runtime Module
    if (!JenovaRuntime::SolveJenovaRuntimeModule())
    {
        log("[Error] Failed to Solve Runtime Module.");
        return;
    };

    // Solve Runtime SDK Functions
    if (!JenovaRuntime::SolveJenovaRuntimeSDKFunctions())
    {
        log("[Error] Failed to Solve Runtime SDK Functions.");
        return;
    };

    // Register Runtime Event
    if (!JenovaRuntime::JenovaSDK::RegisterRuntimeCallback(JenovaImGui::OnRuntimeEvent))
    {
        log("[Error] Failed to Register Runtime Event Callback.");
        return;
    };
}
static void ReleaseJenovaImGui()
{
    // Unregister Runtime Event
    if (!JenovaRuntime::JenovaSDK::UnregisterRuntimeCallback(JenovaImGui::OnRuntimeEvent))
    {
        log("[Error] Failed to Unregister Runtime Event Callback.");
        return;
    };

	// Uninitialize Core
    if (!JenovaImGui::UninitializeImGuiCore())
    {
        log("[Error] Failed to Uninitialize Core.");
    };
}

// Entrypoint
#ifdef _WINDLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved)
{
	// Handle Events
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// Disable Thread Calls
		DisableThreadLibraryCalls(hinstDLL);

		// Initialize JenovaImGui
		InitializeJenovaImGui();
	}
    if (fdwReason == DLL_PROCESS_DETACH)
    {
		// Release JenovaImGui
		ReleaseJenovaImGui();
    }

	// All Good
	return TRUE;
}
#endif // _DLL

// Enumerators
enum GodotDriverResource 
{
    DRIVER_RESOURCE_LOGICAL_DEVICE = 0,
    DRIVER_RESOURCE_PHYSICAL_DEVICE = 1,
    DRIVER_RESOURCE_TOPMOST_OBJECT = 2,
    DRIVER_RESOURCE_COMMAND_QUEUE = 3,
    DRIVER_RESOURCE_QUEUE_FAMILY = 4,
    DRIVER_RESOURCE_TEXTURE = 5,
    DRIVER_RESOURCE_TEXTURE_VIEW = 6,
    DRIVER_RESOURCE_TEXTURE_DATA_FORMAT = 7,
    DRIVER_RESOURCE_SAMPLER = 8,
    DRIVER_RESOURCE_UNIFORM_SET = 9,
    DRIVER_RESOURCE_BUFFER = 10,
    DRIVER_RESOURCE_COMPUTE_PIPELINE = 11,
    DRIVER_RESOURCE_RENDER_PIPELINE = 12,
    DRIVER_RESOURCE_VULKAN_DEVICE = 0,
    DRIVER_RESOURCE_VULKAN_PHYSICAL_DEVICE = 1,
    DRIVER_RESOURCE_VULKAN_INSTANCE = 2,
    DRIVER_RESOURCE_VULKAN_QUEUE = 3,
    DRIVER_RESOURCE_VULKAN_QUEUE_FAMILY_INDEX = 4,
    DRIVER_RESOURCE_VULKAN_IMAGE = 5,
    DRIVER_RESOURCE_VULKAN_IMAGE_VIEW = 6,
    DRIVER_RESOURCE_VULKAN_IMAGE_NATIVE_TEXTURE_FORMAT = 7,
    DRIVER_RESOURCE_VULKAN_SAMPLER = 8,
    DRIVER_RESOURCE_VULKAN_DESCRIPTOR_SET = 9,
    DRIVER_RESOURCE_VULKAN_BUFFER = 10,
    DRIVER_RESOURCE_VULKAN_COMPUTE_PIPELINE = 11,
    DRIVER_RESOURCE_VULKAN_RENDER_PIPELINE = 12,
};

// Storages
static unordered_map<JenovaImGui::UIRenderEventID, JenovaImGui::UIRenderCallback> renderCallbacks;

// Global Values
static bool isImGuiInitialized      = false;
static bool isRenderingAllowed      = true;

// Vulkan Functions
static PFN_vkQueuePresentKHR	    original_vkQueuePresentKHR		= nullptr;
static PFN_vkQueuePresentKHR        g_vkQueuePresentKHR             = nullptr;

// Vulkan Objects
static VkInstance				    g_VkInstance					= VK_NULL_HANDLE;
static VkDevice					    g_VkDevice						= VK_NULL_HANDLE;
static VkPhysicalDevice			    g_PhysicalDevice				= VK_NULL_HANDLE;
static VkQueue					    g_Queue							= VK_NULL_HANDLE;
static VkCommandPool			    g_CommandPool					= VK_NULL_HANDLE;
static VkCommandBuffer			    g_CommandBuffer					= VK_NULL_HANDLE;
static VkDescriptorPool             g_DescriptorPool                = VK_NULL_HANDLE;

// Global Objects
static HWND                         gameWindowHandle                = nullptr;
static WNDPROC                      originalWndProc                 = nullptr;

// Detoured Functions Implementations
static VKAPI_ATTR VkResult VKAPI_CALL Detour_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
    // Skip Rendering If Disabled
    if (!isRenderingAllowed) return original_vkQueuePresentKHR(queue, pPresentInfo);

    // Draw ImGui Draw Data If It's Ready
    if (ImGui::GetDrawData() && ImGui::GetDrawData()->CmdListsCount > 0)
    {
        // Record ImGui draw commands
        VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(g_CommandBuffer, &beginInfo);
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), g_CommandBuffer);
        vkEndCommandBuffer(g_CommandBuffer);

        // Submit to Queue
        VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &g_CommandBuffer;
        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    }

    // Call Original Present
    return original_vkQueuePresentKHR(queue, pPresentInfo);
}

// JenovaImGui Implementation
namespace JenovaImGui
{
	// JenovaImGui :: Core
	bool InitializeImGuiCore()
	{
        // Get Vulkan Module
        HMODULE vulkanModule = LoadLibrary(L"vulkan-1.dll");
        if (!vulkanModule) return false;

        // Get Godot Vulkan Objects
        g_VkInstance = (VkInstance)JenovaRuntime::JenovaSDK::GetRenderingDriverResource(GodotDriverResource::DRIVER_RESOURCE_VULKAN_INSTANCE);
        if (!g_VkInstance) return false;
        g_VkDevice = (VkDevice)JenovaRuntime::JenovaSDK::GetRenderingDriverResource(GodotDriverResource::DRIVER_RESOURCE_VULKAN_DEVICE);
        if (!g_VkDevice) return false;
        g_PhysicalDevice = (VkPhysicalDevice)JenovaRuntime::JenovaSDK::GetRenderingDriverResource(GodotDriverResource::DRIVER_RESOURCE_VULKAN_PHYSICAL_DEVICE);
        if (!g_PhysicalDevice) return false;
        g_Queue = (VkQueue)JenovaRuntime::JenovaSDK::GetRenderingDriverResource(GodotDriverResource::DRIVER_RESOURCE_VULKAN_QUEUE);
        if (!g_Queue) return false;

        // Create Command Pool
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = uint32_t((uint64_t)JenovaRuntime::JenovaSDK::GetRenderingDriverResource(GodotDriverResource::DRIVER_RESOURCE_VULKAN_QUEUE_FAMILY_INDEX));
        if (vkCreateCommandPool(g_VkDevice, &poolInfo, nullptr, &g_CommandPool) != VK_SUCCESS) return false;

        // Create Command Buffer
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = g_CommandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        if (vkAllocateCommandBuffers(g_VkDevice, &allocInfo, &g_CommandBuffer) != VK_SUCCESS) return false;

        // Solve Godot Vulkan Functions
        g_vkQueuePresentKHR = (PFN_vkQueuePresentKHR)vkGetDeviceProcAddr(g_VkDevice, "vkQueuePresentKHR");
        if (!g_vkQueuePresentKHR) return false;

        // Function Solver
        auto VulkanFunctionSolver = [&](const char* functionName) -> void* { return GetProcAddress(vulkanModule, functionName); };

        // Initialize Hook Engine
        MH_STATUS status = MH_Initialize();
        if (status != MH_STATUS::MH_OK && status != MH_STATUS::MH_ERROR_ALREADY_INITIALIZED) return false;

        // Create Hooks
        if (MH_CreateHook(g_vkQueuePresentKHR, Detour_vkQueuePresentKHR, reinterpret_cast<PVOID*>(&original_vkQueuePresentKHR)) != MH_STATUS::MH_OK) return false;

        // Enable Hooks
        if (MH_EnableHook(g_vkQueuePresentKHR) != MH_STATUS::MH_OK) return false;

        // Initialize ImGui
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.IniFilename = nullptr;

        // Set ImGui Style
        ConfigureImGuiStyle();

        // Create Descriptor Pool
        VkDescriptorPoolSize pool_sizes[] = {
        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }};

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        if (vkCreateDescriptorPool(g_VkDevice, &pool_info, nullptr, &g_DescriptorPool) != VK_SUCCESS) return false;

        // Initialize ImGui Vulkan
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = g_VkInstance;
        init_info.PhysicalDevice = g_PhysicalDevice;
        init_info.Device = g_VkDevice;
        init_info.QueueFamily = poolInfo.queueFamilyIndex;
        init_info.Queue = g_Queue;
        init_info.DescriptorPool = g_DescriptorPool;
        init_info.MinImageCount = 2;
        init_info.ImageCount = 1;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        if (!ImGui_ImplVulkan_Init(&init_info)) return false;

        // Get Godot Game Window Handle
        gameWindowHandle = JenovaRuntime::JenovaSDK::GetGameWindowHandle();
        if (!gameWindowHandle) return false;

        // Initialize ImGui Win32
        if (!ImGui_ImplWin32_Init(gameWindowHandle)) return false;

        // Hook Window Message Handler
        originalWndProc = (WNDPROC)SetWindowLongPtr(gameWindowHandle, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);

		// All Good
        isImGuiInitialized = true;
		return true;
	}
	bool UninitializeImGuiCore()
	{
        // Disable Rendering
        isRenderingAllowed = false;

        // Validate
        if (!isImGuiInitialized) return true;

        // Restore Original Window Procedure
        if (originalWndProc && gameWindowHandle) 
        {
            SetWindowLongPtr(gameWindowHandle, GWLP_WNDPROC, (LONG_PTR)originalWndProc);
            originalWndProc = nullptr;
        }

        // Shutdown ImGui Vulkan Backend
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        // Destroy Vulkan Descriptor Pool
        if (g_DescriptorPool)
        {
            vkDestroyDescriptorPool(g_VkDevice, g_DescriptorPool, nullptr);
            g_DescriptorPool = VK_NULL_HANDLE;
        }

        // Destroy Vulkan Command Pool
        if (g_CommandPool)
        {
            vkDestroyCommandPool(g_VkDevice, g_CommandPool, nullptr);
            g_CommandPool = VK_NULL_HANDLE;
        }

        // Disable and Remove Hooks
        if (MH_DisableHook(g_vkQueuePresentKHR) != MH_STATUS::MH_OK) return false;
        if (MH_RemoveHook(g_vkQueuePresentKHR) != MH_STATUS::MH_OK) return false;

        // Reset Vulkan Globals
        g_VkInstance = VK_NULL_HANDLE;
        g_VkDevice = VK_NULL_HANDLE;
        g_PhysicalDevice = VK_NULL_HANDLE;
        g_Queue = VK_NULL_HANDLE;
        g_CommandBuffer = VK_NULL_HANDLE;

		// All Good
        isImGuiInitialized = false;
		return true;
	}

    // JenovaImGui :: Helpers
    void ConfigureImGuiStyle()
    {
        // Jenova ImGui Theme style from ImThemes
        ImGuiStyle& style = ImGui::GetStyle();

        // Layout
        style.Alpha = 1.0f;
        style.DisabledAlpha = 0.4000000059604645f;
        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.WindowRounding = 0.0f;
        style.WindowBorderSize = 0.0f;
        style.WindowMinSize = ImVec2(50.0f, 50.0f);
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_Right;
        style.ChildRounding = 0.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupRounding = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FramePadding = ImVec2(4.0f, 4.0f);
        style.FrameRounding = 0.0f;
        style.FrameBorderSize = 0.0f;
        style.ItemSpacing = ImVec2(8.0f, 8.0f);
        style.ItemInnerSpacing = ImVec2(8.0f, 4.0f);
        style.CellPadding = ImVec2(4.0f, 4.0f);
        style.IndentSpacing = 4.0f;
        style.ColumnsMinSpacing = 40.0f;
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabMinSize = 8.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;
        style.TabBorderSize = 0.0f;
        style.TabMinWidthForCloseButton = 0.0f;
        style.ColorButtonPosition = ImGuiDir_Right;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.SelectableTextAlign = ImVec2(0.009999999776482582f, 0.0f);

        // Colors
        style.Colors[ImGuiCol_Text] = ImVec4(0.9999899864196777f, 1.0f, 0.9999948143959045f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.716731071472168f, 0.716738224029541f, 0.7167356610298157f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.07087992876768112f, 0.07088249921798706f, 0.1115880012512207f, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09431008249521255f, 0.09431344270706177f, 0.1373390555381775f, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.1949566006660461f, 0.1949706077575684f, 0.2403433322906494f, 1.0f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1538064926862717f, 0.1538121104240417f, 0.2145922780036926f, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3377848267555237f, 0.3448304533958435f, 0.454935610294342f, 0.7725322246551514f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1960784494876862f, 0.4549019634723663f, 0.3715896606445312f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.239215686917305f, 0.5137255191802979f, 0.3843137323856354f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.8240343332290649f, 0.4294259250164032f, 1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1070382818579674f, 0.1070418730378151f, 0.1673820018768311f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1803921610116959f, 0.7372549176216125f, 0.4705882370471954f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1930593550205231f, 0.9570815563201904f, 0.5912113785743713f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1803921461105347f, 0.7372549176216125f, 0.3572497963905334f, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.2630367279052734f, 0.9012875556945801f, 0.5956460237503052f, 1.0f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1803921610116959f, 0.7372549176216125f, 0.4705882370471954f, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2546740770339966f, 0.9570815563201904f, 0.6207175850868225f, 1.0f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.1815837621688843f, 0.6824034452438354f, 0.4425744116306305f, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.06074896827340126f, 0.8326179981231689f, 0.4629907310009003f, 1.0f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1106301695108414f, 0.6609442234039307f, 0.5404891967773438f, 1.0f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.1960784494876862f, 0.4549019634723663f, 0.3715896606445312f, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1803921610116959f, 0.7372549176216125f, 0.4705882370471954f, 1.0f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.1803921461105347f, 0.7372549176216125f, 0.6153664588928223f, 1.0f);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.1335077285766602f, 0.1390856504440308f, 0.2060086131095886f, 1.0f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1707896590232849f, 0.1777946203947067f, 0.2618025541305542f, 1.0f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.2401591539382935f, 0.2487652450799942f, 0.3519313335418701f, 1.0f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.239215686917305f, 0.5137255191802979f, 0.3843137323856354f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.8798283338546753f, 0.46505206823349f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06189097464084625f, 0.9613733887672424f, 0.5373316407203674f, 1.0f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.1753577888011932f, 0.1803658902645111f, 0.2403433322906494f, 1.0f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.0f, 0.7725322246551514f, 0.4043721556663513f, 1.0f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.1803921610116959f, 0.6823529601097107f, 0.4431372582912445f, 1.0f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1098039224743843f, 0.1137254908680916f, 0.168627455830574f, 1.0f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1538064926862717f, 0.1578627675771713f, 0.2145922780036926f, 1.0f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.1279080659151077f, 0.9613733887672424f, 0.5622489452362061f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.1503067016601562f, 0.8755365014076233f, 0.5336424112319946f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.07813739776611328f, 0.8669527769088745f, 0.430226743221283f, 1.0f);
        style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1850098669528961f, 0.185012012720108f, 0.2317596673965454f, 1.0f);
        style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.236714631319046f, 0.2367187291383743f, 0.3047210574150085f, 1.0f);
        style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.178452342748642f, 0.178460493683815f, 0.2403433322906494f, 1.0f);
        style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.07058823853731155f, 0.07450980693101883f, 0.1137254908680916f, 1.0f);
        style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.1091934144496918f, 0.1091939657926559f, 0.1673820018768311f, 1.0f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.1529411822557449f, 0.7921568751335144f, 0.501960813999176f, 0.545064389705658f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 0.09012877941131592f, 0.4415817260742188f, 1.0f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.9484978318214417f, 0.6596974730491638f, 0.2401775717735291f, 1.0f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 1.0f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.300000011920929f);
    }

    // JenovaImGui :: Events
    void OnRuntimeEvent(const int& runtimeEvent, void* dataPtr, size_t dataSize)
    {
        // On Runtime Started
        if (runtimeEvent == JenovaRuntime::RuntimeEvent::Started)
        {
            // Initialize Core
            if (!JenovaImGui::InitializeImGuiCore()) log("[Error] Failed to Initialize Core.");
        }

        // Validate ImGui
        if (!isImGuiInitialized) return;

        // On Runtime Frame Begin
        if (runtimeEvent == JenovaRuntime::RuntimeEvent::FrameBegin)
        {
            // Create New ImGui Frame
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        // On Runtime Process
        if (runtimeEvent == JenovaRuntime::RuntimeEvent::Process)
        {
            // Skip Processing Frame If Disabled
            if (!isRenderingAllowed) return;

            // Draw UI Render Callbacks
            for (const auto& renderCallback : renderCallbacks)
            {
                if (renderCallback.second) renderCallback.second();
            }
        }

        // On Runtime Frame End
        if (runtimeEvent == JenovaRuntime::RuntimeEvent::FrameEnd)
        {
            // Render ImGui Frame
            ImGui::Render();
        }
    }

    // JenovaImGui :: Window Message Handler
    LRESULT CALLBACK HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // Handle ImGui Input If Rendering is Enabled
        if (isRenderingAllowed)
        {
            // Process ImGui Input
            if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;

            // Prevent Input When A ImGui Window Hovered
            if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered()) return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        // Process Godot Input
        return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
    }

	// JenovaImGui :: API Functions
    bool AddUserInterfaceRenderEvent(UIRenderEventID eventID, UIRenderCallback callbackPtr)
    {
        auto it = renderCallbacks.find(eventID);
        if (it != renderCallbacks.end() && *it->second.target<void()>() == callbackPtr.target<void()>()) return false;
        renderCallbacks[eventID] = callbackPtr;
        return true;
    }
    bool RemoveUserInterfaceRenderEvent(UIRenderEventID eventID)
    {
        auto it = renderCallbacks.find(eventID);
        if (it != renderCallbacks.end())
        {
            renderCallbacks.erase(it);
            return true;
        }
        return false;
    }
    void SetUserInterfaceRenderingState(bool renderState)
    {
        isRenderingAllowed = renderState;
    }
}