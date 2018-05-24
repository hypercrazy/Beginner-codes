//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <limits>
#include <limits.h>
using namespace std;

//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions 
//
#ifndef MARMOSET_TESTING
struct Student{
	int studentID;
	int grade;
};

struct Dataset{
	int numStudents;
	Student* students;
};

struct Rejects{
	int numRejects;
	int* rejects;
};

struct Mode{
	int numModes;
	int* modes;
};

struct Statistics{
	int   minimum;
	float average;
	int   maximum;
	float popStdDev;
	float smplStdDev;
	Mode  mode;
	int   histogram[10];
};
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//
bool sort(int dataset[], const int size);
bool selection(int dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
float popStdDev(const int dataset[], const int size);
float maximum(const int dataset[], const int size);
float average(const int dataset[], const int size);
float minimum(const int dataset[], const int size);
float smplStdDev(const int dataset[], const int size);
void parseline (char line[], int& value, int& grade);
int readCSV(const char filename[],const int minAcceptableID, 
				const int maxAcceptableID,Dataset& data, 
				Rejects& rejects);

int computeStatistics(Dataset& data, Statistics& stats);

int writeCSV(const char filename[], const Statistics& stats);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//
float minimum(const int dataset[], const int size) {
    
    float mnm = dataset[0];
    int argument_index = 1;
    while(argument_index < size){
        
        float value = dataset[argument_index];
             
        if(value < mnm){
            mnm = value;
        }
        
        argument_index++;
    }
    return mnm;
}

float average(const int dataset[], const int size) {
    
    float total = 0;
    int argument_index2 = 0;
    
    while(argument_index2 < size){
        float value2 = dataset[argument_index2];
        total += value2;
        argument_index2++;
    }
    
    float avrg = total/(float)size;
	//cout << "avg" << avrg << endl;
    return avrg;   
}

float maximum(const int dataset[], const int size) {
    
    float maxm = dataset[0];
    int argument_index3 = 1;
    
    while(argument_index3 < size){
        float value3 = dataset[argument_index3];
        if(value3 > maxm){
            maxm = value3;
        }        
        argument_index3++;
    }
    return maxm;
}

float popStdDev(const int dataset[], const int size) {
    
    if(size == 0){
        return std::numeric_limits<float>::quiet_NaN();
    }
    
	float sum = 0;
    float tmp = 0;
    int k = 0;
    
	while(k < size){
		float value4 = dataset[k];
		tmp = value4 - average(dataset, size);
        sum += pow(tmp,2);
		k++;
	}
    
    float poptemp = sum*(1/(float)size);
	float popStdDev = sqrt(poptemp);
    return popStdDev;
}

float smplStdDev(const int dataset[], const int size) {

    if(size == 1){
        return std::numeric_limits<float>::quiet_NaN();
    }
	
    float add = 0;
	float tmpry = 0;
    float t = 0;
    int j = 0;
    
	while(j < size){
		float value5 = dataset[j];
		tmpry = value5 - average(dataset, size);
		add += pow(tmpry,2);
		j++;
	}
  
    float sampletemp = add*((float)1/(float)(size-1));
    float sampleStdDev = sqrt(sampletemp);
    return sampleStdDev;
 
}

bool sort(int dataset[], const int size){
    bool tmp = selection(dataset, size);
    return true;
}

bool selection(int dataset[], const int size){
    
    int max = INT_MIN;
    int maxIndex = 0;
    
    if(size == 1){
        return true;
    }
    
    for(int i = 0; i < size; i++){
        if(dataset[i] > max){
            max = dataset[i];
            maxIndex = i; 
        }
    }
    
    int temp = dataset[size-1];
    dataset[size-1] = max;
    dataset[maxIndex] = temp;
    
    return selection(dataset, size-1); 
    
}

int mode(const int dataset[], const int size, int mode[]){
    
    if(size < 1){
        return -1;
    }
    
    int newdata[size];
    
    for(int i = 0; i < size; i++)
        newdata[i] = dataset[i];
    
    bool temp = sort(newdata, size);
       
    int counter = 1;
    int occurencesArray[size];
    int index = 0;
    
    for(int i = 0; i < size; i++){
        if(newdata[i]==newdata[i+1]){
            occurencesArray[index]=counter;
            index++;
            counter++;
        }
        if(newdata[i]!=newdata[i+1]){
            occurencesArray[index]=counter;
            index++;
            counter = 1;
        }   
    }
    
    int max = occurencesArray[0];
    int numModes = 1;
    
    for(int j = 1; j < size; j++){
        if(occurencesArray[j]>max){
            max = occurencesArray[j];
            numModes = 1;
        }
        else if(occurencesArray[j] == max)
            numModes++;
    }
    
    int count = 1;
    int k = 0;
    
    for(int i = 0; i < size; i++){
        if(newdata[i] != newdata[i+1]){
            if(count == max){
                mode[k] = newdata[i];
                k++;
                count = 1;
            }
            count = 1;
        }
            
        if(newdata[i] == newdata[i+1]){
            count++;
            if(count == max){
                mode[k] = newdata[i];
                k++;
                count = 1;
            }
        }   
    }
	//cout << "in mode"<< numModes << endl;
	return numModes;
}

void histogram(int dataset[], int histogram[], int size)
{
	for (int k = 0; k < 10; k++)
		histogram[k] = 0;
	
	for (int i = 0; i < size; i++)
	{
		histogram[dataset[i]/10] += 1;
	}
}

void parseline (char line[], int& value, int& grade, bool& flag) // value is id
{
	value = 0;
	grade = 0;
	flag = false;
	int i = 0;
	int x = 0;
	int sign1 = 0;
	int sign2 = 0;
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
				else if (line[i] >= '0' && line[i] <= '9')
				{
					value = x;
					currentstate = STUDENTID;
				}
				else if (line[i] == '-')
					sign1 = -1;
				else if(line[i] == 0){
					currentstate = EOL;
				}
				else{
					flag = true;
					currentstate = EOL;
				}
				break;
				
			case STUDENTID:
				if (line[i] >= '0' && line[i] <= '9')
					value = value*10 + x;
				else if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS2;
				else if (line[i] == ',')
					currentstate = COMMA;
				else if (line[i] == '-')
					sign1 = -1;
				else
					flag = true;
				//cout << "v: " << value << endl;
				break;
				
			case WS1:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS1;
				else if (line[i] >= '0' && line[i] <= '9')
				{
					value = value*10 + x;
					currentstate = STUDENTID;
				}
				else if (line[i] == '-')
					sign1 = -1;
				else if (line[i] == 0)
					currentstate = EOL;
				else
					flag = true;
				break;				
				
			case WS2:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS2;
				else if (line[i] == ',')
					currentstate = COMMA;
				else if (line[i] == 0)
					currentstate = EOL;
				else
					flag = true;
				break;
				
			case COMMA:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS3;
				else if (line[i] >= '0' && line[i] <= '9')
				{
					grade = x;
					currentstate = GRADE;
				}
				else if (line[i] == '-')
					sign2 = -1;
				else if (line[i] == 0 || line[i] == ','){
					currentstate = EOL;
					flag = true;
				}					
				else
					flag = true;
				break;
				
			case WS3:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS3;
				else if (line[i] >= '0' && line[i] <= '9')
				{
					grade = x;
					currentstate = GRADE;
				}
				else if (line[i] == 0 || line[i] == ',')
				{
					flag = true;
					currentstate = EOL;
				}
				else
					flag = true;
				break;
				
			case GRADE:
				if (line[i] == 0) 
				{
					currentstate = EOL;
					if (sign1 == -1)
						value = -value;
					if (sign2 == -1)
						grade = -grade;
					if (grade < INT_MIN || value < INT_MIN || grade > INT_MAX || value > INT_MAX)
						flag = true;
				}
				else if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS4;
				else if (line[i] >= '0' && line[i] <= '9')
				{
					grade = grade*10 + x;
					currentstate = GRADE;
				}
				else if (line[i] == ',')
				{
					//cout << "in here: " << endl;
					flag = true;
					currentstate = EOL;
				}
				else
					flag = true;
				break;
				
			case WS4:
				if (line[i] == ' ' || line[i] == '\t')
					currentstate = WS4;
				else if (line[i] == 0) 
				{
					currentstate = EOL;
					if (sign1 == -1)
						value = -value;
					if (sign2 == -1)
						grade = -grade;
					if (grade < INT_MIN || value < INT_MIN || grade > INT_MAX || value > INT_MAX)
						flag = true;
				}
				else if (line[i] == ',')
				{
					//cout << "in here 2: " << endl;
					flag = true;
					currentstate = EOL;
				}
				else
					flag = true;
				break;
				
			case EOL:
				currentstate = EOL;
				break;
			
		}
		
		i++;
		//add a case for when line[i] > INTMAX and vice versa
		//if line[i] is not an int
	}
	//cout << "grade: " << grade << endl;
	//cout << "id: " << value << endl;

}

int readCSV(const char filename[],const int minAcceptableID, 
				const int maxAcceptableID,Dataset& data, 
				Rejects& rejects){
	
	if (minAcceptableID > maxAcceptableID)
		return -1;
	
	if(histogram == NULL)
		return -1;
	
	const int maxLineLength = 100;
	int fileLineNumber = 0;
	char myfile[maxLineLength] = {0};
	char line[maxLineLength];
	
	for (int k = 0; filename[k] != 0; k++)
		myfile[k] = filename[k];
	
	bool flag = false;
	int i = 0;
	
	if (maxLineLength <= 0)
		return -1;
	
	while (myfile[i] != 0)
	{		
		if (myfile[i] == '.')
		{
			flag = true;
			if (myfile[i+1] == 'c' && myfile[i+2] == 's' && myfile[i+3] == 'v' && myfile[i+4] == '\0')
			{
				myfile[i+1] = 'c';
				myfile[i+2] = 's';
				myfile[i+3] = 'v';	
				myfile[i+4] = '\0';

			}
		}
		i++;
	}
	
	if (flag == false)
	{
		myfile[i] = '.';
		myfile[i+1] = 'c';
		myfile[i+2] = 's';
		myfile[i+3] = 'v';
		myfile[i+4] = '\0';
	}
	
	ifstream infile;
	infile.open(myfile);

	if (!infile.is_open())
		return -1;
	
	bool done = false;
	int index_rejects = 0;
	int count = 0;
	data.students = new Student[100];
	rejects.rejects = new int[10];
	int k = 0;
	
	while (!done)
	{
		++fileLineNumber;
		if (!infile.getline(line, maxLineLength))
		{
			if (infile.eof())
			{
				done = true;
			}
			//if file is empty
		}
		
	//cout << "hey!" << endl;
	
	Student stud;
	//cout << "line number " << fileLineNumber << endl;
	parseline(line, stud.studentID, stud.grade, flag);
	
	int x = 0;
	bool check = true;
	
	
	//cout << "students: " << stud.studentID << endl;

		if (line[0] != 0)
		{
			 //cout << "in here" << endl;
			if(stud.studentID < minAcceptableID || stud.studentID > maxAcceptableID || stud.grade < 0 || stud.grade > 100 || check == false || flag == true)
			{
				rejects.rejects[index_rejects] = fileLineNumber;
				index_rejects++;
				count++;
				x = -1; 
				//cout << "rejects" << rejects.rejects[i] << endl;
			}
			
			else
			{
				data.students[k].grade = stud.grade;
				//cout << "student grade " << data.students[k].grade << endl;
				data.students[k].studentID = stud.studentID;
				data.numStudents++;
				k++;
			}
		}
	}
	if (count >10)
		return -1;
	rejects.numRejects = count;
	//cout << "num: " << count << endl;
	//	data.students = new Student[i];
	//data.students = new Student[change every loop];
	//array with all the grades data.students[i].grade should hold grade
	//allocating a new location every time
	//delete previous pointer
	
	
	// if it wasn't rejected, store student in array
	return rejects.numRejects;
}

int computeStatistics(Dataset& data, Statistics& stats){ //in read, store everything in data
	//Your code here ...
	
	int dataset[data.numStudents];
	int modes[data.numStudents];
	
	Mode m;
	m.modes = new int[data.numStudents];
	
	for(int i = 0; i < data.numStudents; i++)
        dataset[i] = data.students[i].grade;
	
	stats.minimum = minimum (dataset, data.numStudents);
	stats.average = average (dataset, data.numStudents);
	stats.maximum = maximum (dataset, data.numStudents);
	stats.popStdDev = popStdDev (dataset, data.numStudents);
	stats.smplStdDev = smplStdDev (dataset, data.numStudents);
	m.numModes = mode (dataset, data.numStudents, modes);
    //stats.mode.numModes = 6;
	histogram (dataset, stats.histogram, data.numStudents);
	
	//cout << m.numModes << endl;
    stats.mode.modes = new int[m.numModes];
    stats.mode.numModes = m.numModes;
	
	for(int i = 0; i < m.numModes; i++){
        m.modes[i] = modes[i];
        stats.mode.modes[i] = modes[i];
        //cout << stats.mode.modes[i] << endl;;
    }
        //
	if (stats.minimum < 0 || stats.average < 0 || stats.maximum < 0 || stats.popStdDev < 0 || stats.smplStdDev < 0 || m.numModes < 0 || stats.mode.modes < 0 || stats.mode.numModes < 0)
	/*
	put dataset array into another array
	-easier because all function accept arrays
	*/
	return 0;
}

int writeCSV(const char filename[], const Statistics& stats){
	//Your code here ...
	
	const int maxLineLength = 100;
	int fileLineNumber = 0;
	char myfile[maxLineLength] = {0};
	char line[maxLineLength];
	
	for (int k = 0; filename[k] != 0; k++)
		myfile[k] = filename[k];
	
	bool flag = false;
	int i = 0;
	
	
	while (myfile[i] != 0)
	{		
		if (myfile[i] == '.')
		{
			flag = true;
			if (myfile[i+1] == 'c' && myfile[i+2] == 's' && myfile[i+3] == 'v' && myfile[i+4] == '\0')
			{
				myfile[i+1] = 's';
				myfile[i+2] = 't';
				myfile[i+3] = 'a';	
				myfile[i+4] = 't';
				myfile[i+5] = '\0';

			}
		}
		i++;
	}
	//cout << myfile << endl;
	ofstream outfile;
	outfile.open(myfile);
	if (!outfile.is_open())
		return -1;
		
	outfile << "Minimum: " << stats.minimum << std::endl;
	outfile << "Average: " << stats.average << std::endl;
	outfile << "Maximum: " << stats.maximum << std::endl;
	outfile << "Population Standard Deviation: " << stats.popStdDev << std::endl;
	outfile << "Sample Standard Deviation: " << stats.smplStdDev << std::endl;
	outfile << "Modes: ";
	for (int j = 0; j < stats.mode.numModes; j++)
	{
		outfile << stats.mode.modes[j];
		if (j != stats.mode.numModes -1)
			outfile << ", ";
	}
	outfile << std::endl;
	outfile << "Histogram: " << std::endl;
	for (unsigned char i = 0; i < 10; i++)
	{
		outfile << "[" << (i*10) << "-" << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	
	outfile.close();
	return 0;
}
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  	
	// Some test driver code here ....
	int minAcceptableID = 0;
	int maxAcceptableID = 2000000;

	Dataset data = {0};
	Rejects rejects = {0};
	Statistics stats = {0};

	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

	if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
	{
		std::cout << ".csv file could not be read" << std::endl;
	}

	if (computeStatistics(data, stats) < 0)
	{
		std::cout << "Stats could not be computed" << std::endl;
	}

	if (writeCSV(argv[1], stats) < 0)
	{
		std::cout << ".stat file could not be written" << std::endl;
	}
	
	
	std::cout << "Minimum: " << stats.minimum << std::endl;
	std::cout << "Average: " << stats.average << std::endl;
	std::cout << "Maximum: " << stats.maximum << std::endl;
	std::cout << "Population Standard Deviation: " << stats.popStdDev << std::endl;
	std::cout << "Sample Standard Deviation: " << stats.smplStdDev << std::endl;
	std::cout << "Modes: ";
	for (int j = 0; j < stats.mode.numModes; j++)
	{
		std::cout << stats.mode.modes[j];
		if (j != stats.mode.numModes -1)
			std::cout << ", ";
	}
	std::cout << std::endl;
	std::cout << "Histogram: " << std::endl;
	for (unsigned char i = 0; i < 10; i++)
	{
		std::cout << "[" << (i*10) << "-" << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	
/*
	std::cout << "Average: " << stats.average << std::endl;
	std::cout << "Minimum: " << stats.minimum << std::endl;
	std::cout << "Maximum: " << stats.maximum << std::endl;
	std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
	std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;
	cout << "Modes: ";
	for (int j = 0; j < stats.mode.numModes; j++)
	{
		std::cout << stats.mode.modes[j];
		if (j != stats.mode.numModes -1)
			std::cout << ", ";
	}
	std::cout << std::endl;
	/*
	for (unsigned char i = 0; i < stats.mode.numModes; i++)
	{
		std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
	}*/
	std::cout << "Histogram: " << std::endl;
	for (unsigned char i = 0; i < 10; i++)
	{
		std::cout << "[" << (i*10) << "-" << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	

	return 0;
}

#endif