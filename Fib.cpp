/*�������: ������ ����� ����� �� ���� ��������� � ������� ��� �����. ��������: ���� 8 �����. ������� ������ ����� ����� 3.
*******�������� ��������� 13501/3********/
#include <iostream>
using namespace std;

int main()
{
    //Initiating task...
    int DigNum;
    cout << "Choose which digit do you wish for, gentle sir: ";
    cin >> DigNum;
    //Formating the input...
    while (cin.fail())
    {
        cin.clear();
        cin.sync();
        cout << endl << "* ERROR: NAN when number expected. Please write a numeral. *" << endl;
        cin >> DigNum;
    }
    cout << DigNum;
    cout << endl << "Now thou shalt have the Fibonacci sequence till the digit thou have requested: " << endl;

    //Main algorithm...
    short int DigCh = 11;                 //A digit can't be 2 digits.
    long long int FibR = 1;         //1st sequence number...
    long long int Fib = 1;          //...and 2nd.
    long long int FibAux = 0;       //Can be anything.
    long long int FibBuf = 0;       //Same.
    cout << "\t<" << FibR << ">\n";
    if (DigNum == 1) DigCh = 1;     //1st member = 1st digit, special case.
    short int DigAux = 1;                 //Digits index.
    while(DigAux < DigNum)
    {
        cout << "\t<" << Fib << ">\n";
        FibBuf = Fib;
        do
        {
            DigAux++;
            FibBuf /= 10;
        }   while(FibBuf != 0);
        FibBuf = Fib;
        Fib += FibR;
        FibR = FibBuf;
    }
    DigAux -= DigNum;
    for (DigAux; DigAux != 0; DigAux--) FibR /= 10;
    //Solution output...
    cout << endl << "Here you have it, sir: " << FibR%10 << endl;
    return 0;
}

