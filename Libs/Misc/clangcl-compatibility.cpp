// Imports
#include <string>
#include <functional>
#include <variant>

// Clang-Cl Variant Compatiblity
#if defined(__clang__) && defined(_MSC_VER)
namespace std 
{
	template _Variant_storage_<0, std::function<void(const std::string&)>>::~_Variant_storage_<0, std::function<void(const std::string&)>>();
}
#endif