/*�������: �� ��������� ����� ����������� 3 ��������� ������: ����, ������ � �����.
����������, �������� �� ������ ������ ��� ������.
*******�������� ��������� 13501/3********/
#include <iostream>
#include <windows.h>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int xk, yk, xs, ys, xl, yl;
    cout << "������� ���������� ������: ";
    cin >> xk >> yk;
    cout << "������ ������� ���������� �����: ";
    cin >> xs >> ys;
    cout << "� ������� ������� ���������� �����: ";
    cin >> xl >> yl;
    Sleep(3000);
    if (abs(xk - xs) == abs(yk - ys)) cout << endl << "���� �������� ������! \n \n";
    else cout << endl << "���� �� �������� ������! \n \n";
    Sleep(2000);
    if (xk == xl || yk == yl) cout << "����� �������� ������! \n";
    else cout << "����� �� �������� ������! \n";
    return 0;
}
