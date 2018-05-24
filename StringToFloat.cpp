//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h
#include <float.h>
#include <cmath>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

bool stringToFloat(const char input[], float& value) {
	
	int i = 0;
	int x = 0;
	int sign =0;
	char in =0; 
	int count = 1;
	value = 0;
	char dot = 0;
	char Eten = 0;
	int num = 0;
	
	enum state{START, INT1, SIGN, DOT, INT2, E, MULTTEN, DIVTEN, DONE, FAIL};
	state mystate = START;
	
	while (mystate != DONE)
	{
		in = input[i];
		
		if (in >= '0' || in <= '9')
			x = in - '0';

		//cout << x << endl;
		switch (mystate)
		{
			case (START):
				if (in == '-')
				{
					sign = -1;
					mystate = SIGN;
				}
				
				else if (in == '+')
				{
					sign = 1;
					mystate = SIGN;
				}
				
				else if (in >= '0' && in <= '9')
				{
					value = x;
					//cout << "value1: " << value << endl;
					mystate = INT1;
				}
				else if (in == '.')
					mystate = INT2;
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
				
			case (SIGN):
				if (in >= '0' && in <= '9')
				{
					value = value*10 + x;
					mystate = INT1;
				}
				
				else if (in == '.')
					mystate = INT2;
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
				
			case (INT1):
				if (in >= '0' && in <= '9')
				{
					value = value*10 + x;
					//cout << "value: " << value << endl;
				}
				
				else if (in == '.')
				{
					dot = '.';
					//cout << "dot: " << dot << endl;
					mystate = DOT;
				}
				
				else if (in == 0)
				{
					if (sign == -1)
						value = -value;
					else 
						value = value;
					mystate = DONE;
				}
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true; 
				
				break;
				
			case (DOT):
				if (in >= '0' && in <= '9')
				{
					value = value + x/pow(10, count);
					mystate = INT2;
					count++;
				}
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
				
			case (INT2):
				if (in >= '0' && in <= '9')
				{
					value = value + x/pow(10, count);
					count++;
				}
				
				else if (in == 0)
				{
					if (sign == -1)
						value = -value;
					else 
						value = value;
					mystate = DONE;
				}
				
				else if (in == 'e')
				{
					Eten = 'e';
					mystate = E;
				}
				
				else if (in == 'E')
				{
					Eten = 'E';
					//cout << "Eten: " << Eten << endl;
					mystate = E; //do something when there's an e
				}
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
			
			case (E):
				if (in == '-'){
					mystate = DIVTEN;
				}
				
				else if (in == '+')
					mystate = MULTTEN;
				
				else if (in >= '0' && in <= '9')
					num = num*10 + x;
					
				else if (in == 0)
				{
					value = value*(pow(10, num));
					if (sign == -1)
						value = -value;
					else 
						value = value;
					mystate = DONE;
				}
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
				
			case (DIVTEN):
				if (in >= '0' && in <= '9')
				{
					num = num*10 + x;
					//cout << "num: " << num << endl;
				}
				
				else if (in == 0)
				{
					value = value/pow(10, num);
					if (sign == -1)
						value = -value;
					else 
						value = value;
					mystate = DONE;
				}
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
			
			case (MULTTEN):
				if (in >= '0' && in <= '9')
					num = num*10 + x;
				
				else if (in == 0)
				{
					value = value*pow(10,num);
					if (sign == -1)
						value = -value;
					else 
						value = value;
					mystate = DONE;
				}
				
				else 
				{
					mystate = FAIL;
					return false;
				}
				//return true;
				
				break;
			
			case (DONE):				
				if (sign == -1)
					value = -value;
				
				else 
					value = value;
				//cout << "valuedone: " << value << endl;
				mystate = DONE;
				//return true;
				break;
				
			case (FAIL):
				return -1;
				break;
		}
		i++;
	}
	return true;
	
  // Your code here ...
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING
int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1)) 
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
  return 0;
}

#endif
