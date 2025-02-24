#pragma once
#include "LibraryExports.h"
#include <cstdint>
#include <string>

namespace Library
{

using digits_sum_t = uint32_t;


void LIBRARY_API sortNumStrAndInsertKB(std::string& s);

digits_sum_t LIBRARY_API digitsSum(const std::string& s);

bool LIBRARY_API analize(digits_sum_t n) noexcept;

} // namespace Library
