#pragma once

#include <string>
#include <locale>
#include <codecvt>

namespace utility
{

std::string as_std_string(std::wstring input);
std::string as_std_string(std::string input);

}
