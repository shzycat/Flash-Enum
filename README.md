# Introduce Flash Enum
A tiny header-only C++11 library, provides Reflection for enums in C++.  

# Demo
```C++
enum EnumType
{
    EnumValue1 = 1,
    EnumValue2,
    EnumValue3,
};

int main() {
    
    std::string enum_name = flash_enum::reflect_enum<EnumType, EnumValue2>();
    std::cout << "enum: " << enum_name << "\n";

    std::string enum_type = flash_enum::reflect_type(EnumValue3);
    std::cout << "type: " << enum_type << "\n";

    std::string type_with_val = flash_enum::reflect_type_with_val<EnumType, static_cast<EnumType>(2)>();
    std::cout << "type with enum: " << type_with_val << std::endl;

}

/* 
* output:
* enum: EnumValue2
* type: EnumType
* type with enum: EnumType::EnumValue2
*
*/

```

# Notes
### 1. It is not static reflection.
If need it to be calculated at compile time, it require higher version of each platform/compiler's version, and some functions need to be 'constexpr', and also we need 'std::string_view', which means at least c++17, but this header is written with c++11.  
  
But I will try to make it as static reflection one day in the future.  
     
### 2. Compiler version compatibility
* Clang >= 3.6
* MSVC version >= 12.0 (VS2013)
* GCC >= 9.1
* MinGW gcc >= 9.1.0
  
  
  
