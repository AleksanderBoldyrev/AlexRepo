#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class fatint
{
    private:
    fstream 	value;

    public:
    char*		filename;
				fatint(char* fname);
	void		KillFI();
	//ostream&	operator <<(ostream& out);
	fatint&		operator =(fatint& a);
	fatint& 	operator +(fatint& a);
	fatint& 	operator -(fatint& a);
	fatint& 	operator *(fatint& a);
	int			CountLen();
    void		ReverseFI();
	void		ScanFI(char* data);
	void 		PrintFI();
	int 		FItoInt();
};

fatint::fatint(char* fname)
{
	value.open(fname, value.in | value.out);
	if (!value.is_open()) value.open(fname, value.in | value.out | value.trunc);
	filename = fname;
}

void fatint::KillFI()
{
	value.close();
	filename = '\0';
}

/*ostream& fatint::operator <<(ostream& out)
{
	char sym[1];
	sym[1] = '\0';
	for (int i = 0; i < CountLen() - 1; i++)
	{
		value.seekg(i);
		value.get(sym[0]);
		out << sym[0];
	}
	return out;
}*/

fatint& fatint::operator =(fatint& a)
{
    value.close();
    value.open(filename, value.in | value.out | value.trunc);
	char sym[1];
	sym[1] = '\0';
	for (int i = 0; i < a.CountLen(); i++)
	{
		a.value.seekg(i);
		a.value.get(sym[0]);
		value.put(sym[0]);
	}
	return *this;
}

fatint& fatint::operator +(fatint& a)
{
	static fatint sumfi("sum.tmp");
	sumfi.value.close();
	sumfi.value.open(filename, value.in | value.out | value.trunc);
	char sym1[1], sym2[1];
	sym1[1] = '\0';
	sym2[1] = '\0';
	unsigned short over = 0;
	int minc, i = CountLen(), j = a.CountLen();
	int sum;
	if (i < j) minc = i;
		else minc = j;
	for (minc; minc != 0; minc--)
	{
		i--;
		j--;
		value.seekg(i);
		a.value.seekg(j);
		value.get(sym1[0]);
		a.value.get(sym2[0]);
		sym1[0] -= 0x30;
	    sym2[0] -= 0x30;
		sum = sym1[0] + sym2[0] + over;
		sym1[0] = sum % 10;
		over = sum / 10;
		sym1[0] += 0x30;
		sumfi.value.put(sym1[0]); //cout << '*' << sym1[0];
	}
	if (i != j)
	{
		if (i == 0)
		{
			j--;
			a.value.seekg(j);
			a.value.get(sym2[0]);
			sym2[0] -= 0x30;
			sum = sym2[0] + over;
			sym2[0] = sum % 10;
			sym2[0] += 0x30;
			sumfi.value.put(sym2[0]);  //cout << '#' << sym2[0];
			j--;
			for (j; j > -1; j--)
			{
				a.value.seekg(j);
				a.value.get(sym2[0]);
				sumfi.value.put(sym2[0]);  //cout << '!' << sym2[0];
			}
		}
		else
		{
			i--;
			value.seekg(i);
			value.get(sym1[0]);
			sym1[0] -= 0x30;
			sum = sym1[0] + over;
			sym1[0] = sum % 10;
			sym1[0] += 0x30;
			sumfi.value.put(sym1[0]);
			i--;
			for (i; i > -1; i--)
			{
				value.seekg(i);
				value.get(sym1[0]);
				sumfi.value.put(sym1[0]);
			}
		}
	}
	else if (over != 0) sumfi.value.put(over + 0x30);
	sumfi.ReverseFI();
	return sumfi;
}

fatint& fatint::operator -(fatint& a)
{
	static fatint diffi("dif.tmp");
	diffi.value.close();
	diffi.value.open(filename, value.in | value.out | value.trunc);
	char sym1[1], sym2[1];
	bool isbor = false;
	int minc, i = CountLen(), j = a.CountLen();
	sym1[1] = '\0';
	sym2[1] = '\0';
	if (i >= j)
	{
		minc = j;
		for (minc; minc != 0; minc--)
		{
			i--;
			j--;
			value.seekg(i);
			a.value.seekg(j);
			value.get(sym1[0]);
			a.value.get(sym2[0]);
			sym1[0] -= 0x30;
			sym2[0] -= 0x30;
			if (isbor)
			{
				sym1[0]--;
				isbor = false;
			}
			if (sym1[0] < sym2[0])
			{
				sym1[0] = (sym1[0] + 10) - sym2[0];
				isbor = true;
			}
			else sym1[0] = sym1[0] - sym2[0];
			sym1[0] += 0x30;
			diffi.value.put(sym1[0]);
		}
		if (i != j)
		{
			i--;
			value.seekg(i);
			value.get(sym1[0]);
			sym1[0] -= 0x30;
			if (isbor)
			{
				if (sym1[0] != 0) sym1[0]--;
				else
				{
					while (sym1[0] == 0)
					{
						sym1[0] += 9;
						sym1[0] += 0x30;
						diffi.value.put(sym1[0]);
						i--;
						value.seekg(i);
						value.get(sym1[0]);
						sym1[0] -= 0x30;
					}
					sym1[0]--;
				}
				isbor = false;
			}
			sym1[0] += 0x30;
			diffi.value.put(sym1[0]);
			i--;
			for (i; i > -1; i--)
			{
				value.seekg(i);
				value.get(sym1[0]);
				diffi.value.put(sym1[0]);
			}
		}
		else if (isbor) diffi.value.put((sym1[0] - 1) + 0x30);
		diffi.ReverseFI();
		return diffi;
	}
	else
	{
		diffi.value.put('!');
		return diffi;
	}
}

fatint& fatint::operator *(fatint& a)
{
	static fatint mulfi("mul.tmp");
	fatint t1("t1.tmp");
	fatint ta1("ta1.tmp");
	fatint ta2("ta2.tmp");
	mulfi.value.close();
	mulfi.value.open(filename, value.in | value.out | value.trunc);
	char sym1[1], sym2[1], symo[1];
	sym1[1] = '\0';
	sym2[1] = '\0';
	symo[1] = '\0';
	symo[0] = '0';
	unsigned int over = 0;
	int dec = 0, i = CountLen(), j = a.CountLen(), sum, sumaux;
	for (i; i != 0; i--)
	{
		value.seekg(i);
		value.get(sym1[0]);
		for (j; j != 0; j--)
		{
			while (dec != 0)
			{
				t1.value.put(symo[0]);
				dec--;
			}
			a.value.seekg(j);
			a.value.get(sym2[0]);
			sym1[0] -= 0x30;
			ta2.ScanFI(sym2[0]);
			char* num = sym2[0];
			t2.ScanFI(num);
			while (sym1[0] != 0)
			{
				sym1[0]--;
				ta1 = ta1 + ta2;
			}
			sym1[0] += 0x30;
			t1.value.put(sym1[0]);
			dec++;
		}
		dec++;
		mulfi = mulfi + t1;
		//mulfi.PrintFI();
	}
	//else if (over != 0) sumfi.value.put(over + 0x30);
	mulfi.ReverseFI();
	return mulfi;
}

int fatint::CountLen()
{
	int len;
	value.seekg(0, value.end);
	len = value.tellg();
	value.seekg(0, value.beg);
    return len;
}

void fatint::ReverseFI()
{
	char sym1[1], sym2[1];
	sym1[1] = '\0';
	sym2[1] = '\0';
	int c = CountLen();
	int m = c / 2;
	for (int i = 0; i != m; i++)
	{
		value.seekg(i);
		value.get(sym1[0]);
		c--;
		value.seekg(c);
		value.get(sym2[0]);
		value.unget();
		value.put(sym1[0]);
		value.seekg(i);
		value.put(sym2[0]);
	}
}

void fatint::ScanFI(char* data)
{
    value.close();
    value.open(filename, value.in | value.out | value.trunc);
    char sym[1];
	sym[1] = '\0';
	int i = 0;
	for (i; i < strlen(data); i++)
	{
		sym[0] = data[i];
		value.put(sym[0]);
	}
}

void fatint::PrintFI()
{
	char sym[1];
	sym[1] = '\0';
	value.seekg(0, value.beg);
	for (int i = CountLen(); i > 0; i--)
	{
		value.get(sym[0]);
		cout << sym[0];
	}
}

int fatint::FItoInt()
{
	int dest = 0, dec = 1;
	char sym[1];
	sym[1] = '\0';
	int i = CountLen() - 1;
	if (i < 5)
	{
		for (i; i > -1; i--)
		{
			value.seekg(i);
			value.get(sym[0]);
			sym[0] -= 0x30;
			dest += sym[0] * dec;
			dec *= 10;
			if (dest > 32767)
			{
				dest = -1;
				break;
			}
		}
	}
	else dest = -1;
	return dest;
}

int main()
{
	int i = 0;
	fatint a("numa.txt");
	fatint b("numb.txt");
	char* number = "245";
	a.ScanFI(number);
	number = "4586";
	b.ScanFI(number);
	fatint& c = a;
	//cout << " Here here we are substracting two numbers: ";
	c = b * a;
	c.PrintFI();
	a.KillFI();
	b.KillFI();
	c.KillFI();
    return 0;
}
