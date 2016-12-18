#pragma once
#include "vecmath.h"
#include "cushion.h"

/*-----------------------------------------------------------
Macros
-----------------------------------------------------------*/
#define BALL_RADIUS		(0.05f)
#define BALL_MASS		(0.1f)
#define SMALL_VELOCITY		(0.01f)


static const float gRackPositionX[] = { 0.0f,0.0f,(BALL_RADIUS*2.0f),(-BALL_RADIUS*2.0f),(BALL_RADIUS*4.0f) };
static const float gRackPositionZ[] = { 0.5f,0.0f,(-BALL_RADIUS*3.0f),(-BALL_RADIUS*3.0f) };

const float gCoeffRestitution = 0.5f;
const float gCoeffFriction = 0.03f;
const float gGravityAccn = 9.8f;

class ball
{
private:
	static int ballIndexCnt;
public:
	vec2<float>	position;
	vec2<float>	velocity;
	float	radius;
	float	mass;
	int		index;

	ball(): position(0.0), velocity(0.0), radius(BALL_RADIUS), 
		mass(BALL_MASS) {index = ballIndexCnt++; Reset();}
	
	void Reset(void);
	void ApplyImpulse(vec2<float> imp);
	void ApplyFrictionForce(int ms);
	void DoPlaneCollision(const cushion &c);
	void DoBallCollision(ball &b);
	void Update(int ms);
	
	bool HasHitPlane(const cushion &c) const;
	bool HasHitBall(const ball &b) const;

	void HitPlane(const cushion &c);
	void HitBall(ball &b);
};
