#include <iostream>

template <int N>
constexpr int MaxInt() {
    return MaxInt<N - 1>()*10 + 9;
}

template <>
constexpr int MaxInt<1>() {
    return 9;
}

int main()
{
    std::cout << MaxInt<5>() << std::endl;
    return 0;
}