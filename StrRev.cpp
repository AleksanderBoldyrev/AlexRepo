/*-----Переворот строки-----
*******Болдырев Александр 13501/3********/
#include <iostream>
using namespace std;

void strrev(char* strnorm)
{
    int len = 0;
    while (strnorm[len]) len++;
    for (int i=0; i < len; i++)
    {
        char strbuf = strnorm[len-i-1];
        strnorm[len-i-1] = strnorm[i];
        strnorm[i] = strbuf;
        cout << strnorm[i];
    }
}

int main()
{
    char str[10];
    cout << "Enter the string you would like to reverse: ";
    cin.getline(str, 10);
    strrev(str);
    return 0;
}
