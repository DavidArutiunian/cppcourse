#include <cmath>
#include <iostream>

int main()
{
	float a = 0;
	float b = 0;
	float c = 0;

	std::cout << "Enter a,b and c for `ax^2 + bx + c=0`: ";
	std::cin >> a >> b >> c;

	auto d = static_cast<float>(pow(b, 2) - (4 * a * c));

	std::cout << "D: " << d << std::endl;

	if (d < 0)
	{
		std::cout << "No roots" << std::endl;
		return 0;
	}

	auto x1 = static_cast<float>((-b - sqrt(d)) / (2 * a));
	auto x2 = static_cast<float>((-b + sqrt(d)) / (2 * a));

	if (x1 == x2)
	{
		std::cout << "Solution: " << x1 << std::endl;
	}
	else
	{
		std::cout << "Solutions: " << x1 << " and " << x2 << std::endl;
	}
}