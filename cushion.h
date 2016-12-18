#pragma once
#include "vecmath.h"
  
class cushion
{
public:
	vec2<float>	vertices[2]; //2d
	vec2<float>	centre;
	vec2<float>	normal;

	void MakeNormal(void);
	void MakeCentre(void);
};

