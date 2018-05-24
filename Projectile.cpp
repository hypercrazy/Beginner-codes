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

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
  
	if (theta == 0)
	{
		destX = 0;
		destY = h;
	}
	
	if (theta < -90 || theta > 270)
		return false;
	
	if (h < 0 || v < 0 || m < 0 || d < 0 || b < 0 || w < 0)
		return false;
	
	float distance = d;
	float build = b;
	float width = w;
	float angle = theta;
	float height = h;
	float vrtd = t;
	float vi = v;
	float destx = destX;
	float desty = destY;
	float range;
	float time;
	float g = 9.8;
	double Pi = 3.1415926535897;
	
	angle = (theta*Pi)/180;
	
	float vx = vi*cos(angle);
	
	float vy = vi*sin(angle);
	
	if (v == 0 || theta == 90)
	{
		destY = h;
		destX = 0;
		return true;
	}
	
	time = vy/g;
	
	float y = pow(vy, 2)/(2*g);
	float timecheck = time + sqrt(2*g*(h+y))/g;

	
	range = vx*timecheck;
	
	if (b < range && range < b+w)
	{
		destY = t;
		destX = range;
		return true;
	}
	
	if (range < b)
	{
		destY = 0;
		destX = range;
		return true;
	}
	
	if (range > b+w)
	{
		destY = 0;
		destX = range;
		return true;
	}
	
	if (range == b)
	{
		destX = b;
		destY = vy*time - 0.5*g*pow(time, 2);
		return true;
	}
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

  float h = 50;
  float v = 24.2;
  float m = 1;
  float theta = 27.89;        // Angle in degrees; will need to be converted by function
  float d = 100;
  float t = 20;
  float b = 30;
  float w = 20;

  float hitsAtX;
  float hitsAtY;

  if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
    cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
  else
    cout << "Unable to calculate where projectile hits." << endl;
  return 0;
}

#endif
