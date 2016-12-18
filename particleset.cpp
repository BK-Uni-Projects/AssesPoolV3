#include "particleset.h"
#include <random>

void particleSet::AddParticle(const vec3 &pos)
{
	if(num >= MAX_PARTICLES) return;
	particles[num] = new particle;
	particles[num]->position = pos;

	particles[num]->velocity(0) = ((rand() % 200)-100)/200.0;
	particles[num]->velocity(2) = ((rand() % 200)-100)/200.0;
	particles[num]->velocity(1) = 2.0*((rand() % 100)/100.0);

	num++;
}

void particleSet::update(int ms)
{
	int i=0;
	while(i<num)
	{
		particles[i]->update(ms);
		if((particles[i]->position(1) < 0.0) && (particles[i]->velocity(1)<0.0))
		{
			delete particles[i];
			particles[i] = particles[num-1];
			num--;
		}
		else i++;
	}
}



