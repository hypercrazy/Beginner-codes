//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//


#include <fstream>
using namespace std;
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
int parseline (char line[], int& value, int& grade);
int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return -1 if you cannot compute the histogram for any
// reason;
// Return 0 if the histogram is correct and there are no
// rejections;
// Return the number of rejects if there are rejected
// records from the file
//
int parseline (char line[], int& value, int& grade) // value is id
{
	value = 0;
	grade = 0;
	int i = 0;
	int x = 0;
	enum state {START, WS1, STUDENTID, WS2, COMMA, WS3, GRADE, WS4, EOL};
	state currentstate = START;
	
	while (currentstate != EOL)
	{
		x = (line[i] - '0');
		switch (currentstate)
		{
			case START:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS1;
				if (line[i] >= '0' && line[i] <= '9')
				{
					value = x;
					currentstate = STUDENTID;
				}
				break;
				
			case STUDENTID:
				if (line[i] >= '0' && line[i] <= '9')
					value = value*10 + x;
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS2;
				if (line[i] == ',')
					currentstate = COMMA;
				//cout << "v: " << value << endl;
				break;
				
			case WS1:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS1;
				if (line[i] >= '0' && line[i] <= '9')
				{
					value = value*10 + x;
					currentstate = STUDENTID;
				}
				break;				
				
			case WS2:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS2;
				if (line[i] == ',')
					currentstate = COMMA;
				break;
				
			case COMMA:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS3;
				if (line[i] >= '0' && line[i] <= '9')
				{
					grade = x;
					currentstate = GRADE;
				}
				break;
				
			case WS3:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS3;
				if (line[i] >= '0' && line[i] <= '9')
				{
					grade = x;
					currentstate = GRADE;
				}
				break;
				
			case GRADE:
				if (line[i] == 0)
					currentstate = EOL;
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS4;
				if (line[i] >= '0' && line[i] <= '9')
				{
					grade = grade*10 + x;
					currentstate = GRADE;
				}
				break;
				
			case WS4:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS4;
				if (line[i] == 0)
					currentstate = EOL;
				break;
				
			case EOL:
				currentstate = EOL;
				break;
			
		}
		
		i++;
	}

}


int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects) {
	if(minAcceptableID>maxAcceptableID)
	{
		return -1;
	}
	if(histogram == NULL)
	{
		return -1;
	}
	
	for(int i = 0 ; i < 10 ; i++)
	{
		histogram[i] = 0;
	}
	
	
	bool check = true;
	int index_rejects = 0;
	rejects = new int[100];
	const int maxLineLength = 100;
	char line[maxLineLength];
	ifstream infile;
	infile.open(filename);
	
	if (!infile.is_open())
		return -1;
	
	bool done = false;
	int fileLineNumber = 0;
	int i = 0;
	int id = 0;
	int grade = 0;
	int count = 0;
	int x = 0;

	
	while (!done)
	{
		++fileLineNumber;
		if (!infile.getline(line, maxLineLength))
		{
			if (infile.eof())
			{
				done = true;
			}
			else 
				return -1;
			
		}

		
		parseline(line, id, grade);	
	//out << "grade: " << grade << " id: " << id << endl;
      if(line[0] != 0)
	  {
		 
		if(id < minAcceptableID || id > maxAcceptableID || grade < 0 || grade > 100 || check == false)
		{
			rejects[index_rejects] = fileLineNumber;
			index_rejects++;
	//fileLineNumber;
			 //increment the index
			 //increment the number of lines rejected
			count++;
			x = -1; 
		}
		
		if (x == 0)
			histogram[grade/10] += 1;
		x = 0;
	  }
	//out << "count: " << count << endl;
		
		//ut << "student id: " << id << " grade: " << grade << endl;

		/*
		if (grade == 100)
			{
			histogram[9] += 1;
			}
		
		else{
				histogram[grade/10] += 1;
		}	 */
		//doHistogramStuff();
		i++;
	}
	infile.close();
	return count;
	if (count ==0)
		return 0;
	else if (count >10)
		return -1;
	else
		return count;
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
  if (argc < 2) {

  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int  buckets[numBuckets];
  int* rejectedRecords;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
      cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i)
      if (i != numBuckets-1)
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
      else
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
    if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i)
	cout << " " << rejectedRecords[i];
      cout << endl;
      delete[] rejectedRecords;
    }
  }

  return 0;
}

#endif
