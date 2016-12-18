#pragma once
#include "vecmath.h"
  
class particle 
{
public:
	vec3 position;
	vec3 velocity;

	particle() {position=0;velocity=0;}
	void update(int ms);
};
  
