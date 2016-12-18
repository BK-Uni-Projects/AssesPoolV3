#pragma once

#include "ball.h"
#include "cushion.h"
#include "particleset.h"

/*-----------------------------------------------------------
Macros
-----------------------------------------------------------*/
#define TABLE_X			(0.6f) 
#define TABLE_Z			(1.2f)
#define TABLE_Y			(0.1f)
#define NUM_BALLS		(7)		
#define NUM_CUSHIONS	(5)		



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
