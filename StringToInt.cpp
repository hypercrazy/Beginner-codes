//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

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
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//
bool stringToInt(const char input[], int& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool stringToInt(const char input[], int& value) {
	
	int sign;
	value = 0;
	unsigned int currDigit = 0;
	char in = input[0];

	unsigned int INT_MAX = 2147483647;
	unsigned int INT_MIN = -2147483648;
	
	bool minusSign = (in == '-');
	bool plusSign = (in == '+');
	
	if (minusSign || plusSign)
	{
		currDigit = 1;
		in = input[1];
	}

		
	unsigned int maxValue = INT_MAX + (minusSign?1:0);
	
	//if (in == 0)
		//return 0;
	
	while (in != '\0')
	{
		if (input[currDigit + 1] == '-' || input[currDigit + 1] == '+') //if next value after input[0] is not a digit
			return false;
			
		if (in < '0' || in > '9'){ //out of bound error
			return false;
		}
		
		if (input[currDigit] == char(32)) //false if there are any whitespaces
			return -1;
		
		if (in - '0' > INT_MAX-value  ) //out of bound error
			return false;
		
		if (value > maxValue/10 ){ //out of bound erro
			return -1;
		}
		
		if (in == '-' )
			sign = -1;
		if (in == '+')
			sign = 1;
		if(in >= '0' && in <= '9'){
				value = value*10 + (in - '0');
			}
		if (value > INT_MAX)
			return false;
		
		currDigit++;
		in = input[currDigit];
	}
	/*
	if (INT_MAX - value < 0)
		return false;
	
	if (INT_MIN - value > 0)
		return false; 
	else 
		value = value; */
	
	value = minusSign? (-value) : value;
	return true;
	
	if (value < INT_MIN - 1)
			return false;
	else
		return true;
		
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

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  int argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
    return -1;
  }

  if (stringToInt(argv[1],argv1)) 
    cout << "argv[1] is an int with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not an int." << endl;
  return 0;
}

#endif
