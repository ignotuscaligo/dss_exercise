#include "utility/string.h"

#include <locale>
#include <codecvt>

namespace utility
{

std::string as_std_string(std::wstring input)
{
    using convert_type = std::codecvt_utf8<wchar_t>;

    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.to_bytes(input);
}

std::string as_std_string(std::string input)
{
    return input;
}

}

