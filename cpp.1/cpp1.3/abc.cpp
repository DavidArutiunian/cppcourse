#include <iostream>

int main()
{
	float a = 0.f;
	float b = 0.f;
	float c = 0.f;

	std::cout << "Enter a, b and c: ";
	std::cin >> a >> b >> c;

	float result = a + b + c;
	std::cout << "Total: " << result << std::endl;
}