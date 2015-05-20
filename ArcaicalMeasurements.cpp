/*Task: The conversion between the SI system and old russian measures.
*******Boldyrev Alexander 13501/3********/
#include <iostream>
using namespace std;

int main()
{
    double x, y, z; //X measure is 'sajen', Y is 'arshin' and Z is 'vershki'
    cout << "Type the rope's length in arcaical measurements: \n";
    cout << "\tSajen: ";
    cin >> x;
    cout << "\tArshin: ";
    cin >> y;
    cout << "\tVershkov: ";
    cin>> z;
    cout << endl;
    cout << "Now, let's turn it into meter's measurement: ";
    cout << x * 2.1336 + y * 0.7112 + z * 0.04445 << " meters" << endl;
    return 0;
}
