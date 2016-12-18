#pragma once

#include "ball.h"
#include "cushion.h"
#include "particleset.h"

/*-----------------------------------------------------------
Macros
-----------------------------------------------------------*/
const float TABLE_X = 0.6f;
const float TABLE_Z = 1.2f;
const float TABLE_Y = 0.1f;

const int NUM_BALLS = 7;
const int NUM_CUSHIONS = 5;

class table
{
public:
	ball balls[NUM_BALLS];	
	cushion cushions[NUM_CUSHIONS];
	particleSet parts;

	void SetupCushions(void);
	void Update(int ms);	
	bool AnyBallsMoving(void) const;
};
