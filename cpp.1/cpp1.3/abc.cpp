#include <iostream>

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;

    std::cout << "Enter a, b and c: ";
    std::cin >> a >> b >> c;

    float result = a + b + c;
    std::cout << "Total: " << result << std::endl;
}