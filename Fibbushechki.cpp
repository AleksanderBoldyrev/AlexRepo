/*Task: We have a sequence of Fibbonacci and we should get the exact numeral by it's number in the sequence.
*******Boldyrev Alexander 13501/3********/
#include <iostream>
#include <windows.h>
using namespace std;

int EasterDemon();                          //Some forward-declared surpriiiise! :)

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

    //Easter)))...
    
    if (DigNum == 666) EasterDemon();
    cout << endl << "Now thou shalt have the Fibonacci sequence till the digit thou have requested: " << endl;

    //Main algorithm...
    
    short int DigCh      = 11;             //A digit can't be 2 digits. :)
    long long int FibR   = 1;              //1st sequence number...
    long long int Fib    = 1;              //...and 2nd.
    long long int FibAux = 0;              //Can be anything really.
    long long int FibBuf = 0;              //Same.
    cout << "\t<" << FibR << ">\n";
    if (DigNum == 1) DigCh = 1;            //1st member = 1st digit, special case.
    short int DigAux = 1;                  //Digits index.
    while(DigAux < DigNum)
    {
        cout << "\t<" << Fib << ">\n";
        FibBuf = Fib;
        do
        {
            DigAux++;
            FibBuf /= 10;
        }   while(FibBuf != 0);
        FibBuf =  Fib;
        Fib    += FibR;
        FibR   =  FibBuf;
    }
    DigAux -= DigNum;
    for (DigAux; DigAux != 0; DigAux--) FibR /= 10;
    
    //Solution output...
    
    cout << endl << "Here you have it, gentle sir: " << FibR % 10 << endl;
    return 0;
}

int EasterDemon()
{
    cout << endl << "* I've heard thy call, my Master! Command me! *" << endl;
    Sleep(2700);
    cout << "...wait..." << endl;
    Sleep(2700);
    cout << "NO!" << endl;
    Sleep(1300);
    cout << "Just kiddin'!!! ];)" << endl;
    Sleep(1300);
    return 0;
}
