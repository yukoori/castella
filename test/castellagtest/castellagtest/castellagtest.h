#pragma once

#include <algorithm>

template<typename T>
bool binary_eq(T const& lhs, T const& rhs) {
    auto lhs_i = reinterpret_cast<char const*>(&lhs);
    auto rhs_i = reinterpret_cast<char const*>(&rhs);
    return std::equal(lhs_i, lhs_i + sizeof(T), rhs_i);
}
