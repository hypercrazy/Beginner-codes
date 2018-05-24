#include <iostream>
#include <stdlib.h>
using namespace std;
int main (const int argc, const char* const argv[])
{

if (argc < 3) {	
cerr << "Error: Unable to compute GCD and/or LCM because of insufficient arguments." << endl;
return -1;
}

if (argc > 3) {
cerr << "Warning: Expecting two command-line arguments." << endl;
return -1;
}

int a = atoi(argv[1]);
int b = atoi(argv[2]);
int LCM = 1;
int GCD = 1;
int g = 1;


if (a <= 0 || b <= 0) {
cerr << "Error: Unable to compute GCD and/or LCM because of invalid input." << endl;
return -1;
}


if (a%b==0)
{
g=b;
GCD = abs(g);
}

if (b%a==0)
{
g=a;
GCD = abs(g);
}


while (g != 0) {

if (a>b)
{
g = a%b;
a = b;
b = g;

	if (g!=0)
	{
	GCD = abs(g);
	}
}
if (a==b)
{
	g=0;
	GCD = a;
}

if (a<b)
{
	g = b%a;
	b = a;
	a = g;
	if (g!=0)
	{
		GCD = abs(g);
	}

}
}

a = atoi(argv[1]);
b = atoi(argv[2]);

LCM = abs((a/GCD)*b);

cout << "GCD (" << a << ", " << b << ") = " << GCD << endl;
cout << "LCM (" << a << ", " << b << ") = " << LCM << endl;


return 0;
}