//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
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

#define NaN std::numeric_limits<float>::quiet_NaN() 
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta);
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool hitTargetGivenVelocity (const float h, const float newv, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta) {
	
	if (h <= 0 || newv <= 0 || m <= 0 || d <= 0 || b <= 0 || w <= 0)
		return false;
	
	float distance = d;
	float build = b;
	float width = w;
	float angle = theta;
	//float vi = v;
	float height = h;
	float vrtd = t;
	float range;
	float time;
	float g = 9.8;
	double Pi = 3.1415926535897;
	
	
	angle = atan((pow(newv,2) + sqrt(pow(newv,4) - g*(g*pow(d,2) + 2*(t-h)*pow(newv, 2))))/(g*d));
	
	//if (angle < 0)
		//angle = atan((pow(newv,2) - sqrt(pow(newv,4) - g*(g*pow(d,2) + 2*t*pow(newv, 2))))/(g*d));
	if (g*d == 0)
		return false;
	
	theta = (angle/Pi)*180;
	return true;
	
	
	
	// Your code here...
}

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v) {
	// Your code here...
	if (h <= 0 || m <= 0 || d <= 0 || b <= 0 || w <= 0)
		return false;
	
	if (theta < -90 || theta > 270)
		return false;
	
	
	float distance = d;
	float build = b;
	float width = w;
	float angle = theta;
	//float vi = v;
	float height = h;
	float vrtd = t;
	float range;
	float time;
	float g = 9.8;
	double Pi = 3.1415926535897;
	
	
	angle = (theta*Pi)/180;
	
	
	v = d/cos(angle)*sqrt(g/(2*tan(angle)*d-2*t+2*h));
	return true;
	
	if (v <= 0)
		return false;
}
		

#ifndef MARMOSET_TESTING
int main() {
	
  // Some test driver code here ....
  
  float h = 50;
  float d = 60;
  float b = 40;
  float t = 0;
  float w = 30;
  float m = 1;

  float theta = 68.81; // Angle in degrees;
  float v = 45.21;	
 float newv = v;

  cout << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity\n\n";
  }

  cout << "Given initial velocity: " << newv << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenVelocity (h, newv, m, d, t, b, w, theta)) {
    cout << "required angle: " << theta << endl << endl;
  }
  else {
    cout << "cannot calculate the angle\n\n";  
  }
    
  return 0;
}
#endif
