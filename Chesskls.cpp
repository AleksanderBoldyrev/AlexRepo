/*Задание: На шахматной доске расположены 3 шахматные фигуры: слон, король и ладья.
Определить, угрожает ли королю другие две фигуры.
*******Болдырев Александр 13501/3********/
#include <iostream>
#include <windows.h>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int xk, yk, xs, ys, xl, yl;
    cout << "Введите координаты короля: ";
    cin >> xk >> yk;
    cout << "Теперь введите координаты слона: ";
    cin >> xs >> ys;
    cout << "И наконец введите координаты ладьи: ";
    cin >> xl >> yl;
    Sleep(3000);
    if (abs(xk - xs) == abs(yk - ys)) cout << endl << "Слон угрожает королю! \n \n";
    else cout << endl << "Слон не угрожает королю! \n \n";
    Sleep(2000);
    if (xk == xl || yk == yl) cout << "Ладья угрожает королю! \n";
    else cout << "Ладья не угрожает королю! \n";
    return 0;
}
