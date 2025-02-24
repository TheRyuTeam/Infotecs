#include <Library/Library.h>
#include <algorithm>

namespace Library
{

std::string sortNumStrAndInsertKB(const std::string& s)
{
    auto result = s;
    std::sort(result.begin(), result.end(), std::greater<std::string::value_type>());
    for (std::size_t i = 0; i < result.size(); ++i) {
        if (result[i] % 2 == 0) {
            result.replace(i, 1, "KB");
            ++i;
        }
    }
    return result;
}

digits_sum_t digitsSum(const std::string& s)
{
    digits_sum_t sum = 0;
    for (char c : s) {
        if (c >= '0' && c <= '9') {
            sum += c - '0';
        }
    }
    return sum;
}

bool analize(digits_sum_t n) noexcept
{
    return n >= 100 && n % 32 == 0;
}

} // namespace Library
