#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;

    cout << "Enter a,b and c for `ax^2 + bx + c=0`: ";
    cin >> a >> b >> c;

    float d = pow(b, 2) - (4 * a * c);

    cout << "D: " << d << endl;

    if (d < 0)
    {
        cout << "No roots" << endl;
        return 0;
    }

    float x1 = (-b - sqrt(d)) / (2 * a);
    float x2 = (-b + sqrt(d)) / (2 * a);

    if (x1 == x2)
    {
        cout << "Solution: " << x1 << endl;
    }
    else
    {
        cout << "Solutions: " << x1 << " and " << x2 << endl;
    }
}