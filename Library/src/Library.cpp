#include <Library/Library.h>
#include <algorithm>

namespace Library
{

void sortNumStrAndInsertKB(std::string& s)
{
    std::sort(s.begin(), s.end(), std::greater<std::string::value_type>());
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (isdigit(s[i]) && s[i] % 2 == 0) {
            s.replace(i, 1, "KB");
            ++i;
        }
    }
}

digits_sum_t digitsSum(const std::string& s)
{
    digits_sum_t sum = 0;
    for (char c : s) {
        if (isdigit(c)) {
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
