/*Task: Expand the number into simple multipliers. Example: 72=1*2*2*2*3*3
*******Boldyrev Alexander 13501/3********/
#include <iostream>
using namespace std;

int main()
{
    long long Num;
    cout << "Fracturing the random number into simple multipliers" << endl;
    cout << "Enter your number: ";
    cin >> Num;
    cout << Num << " = 1 ";
    long long i = 2;
    while (Num != 1)
    {
        while (i <= Num)
        {
            if (Num % i == 0)
            {
                cout << "* " << i << " ";
                Num /= i;
                break;
            }
            i++;
        }
        i = 2;
    }
    cout << endl;
    return 0;
}
