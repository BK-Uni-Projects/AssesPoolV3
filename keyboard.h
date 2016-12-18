#pragma once
#include "vecmath.h"
#include "table.h"

extern table gTable;

//cue 
float gCueAngle = 0.0;
float gCuePower = 0.25;
bool gCueControl[4] = { false,false,false,false };
float gCueAngleSpeed = 2.0f; //radians per second
float gCuePowerSpeed = 0.25f;
float gCuePowerMax = 0.75;
float gCuePowerMin = 0.1;
float gCueBallFactor = 8.0;
bool gDoCue = true;

//camera
vec3 gCamPos(0.0, 0.7, 2.1);
vec3 gCamLookAt(0.0, 0.0, 0.0);

bool gCamRotate = true;

float gCamRotSpeed = 0.2;
float gCamMoveSpeed = 0.5;

bool gCamL = false;
bool gCamR = false;
bool gCamU = false;
bool gCamD = false;
bool gCamZin = false;
bool gCamZout = false;

inline void SpecKeyboardFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT: {
		gCueControl[0] = true;
		break;
	}

	case GLUT_KEY_RIGHT: {
		gCueControl[1] = true;
		break;
	}

	case GLUT_KEY_UP: {
		gCueControl[2] = true;
		break;
	}

	case GLUT_KEY_DOWN: {
		gCueControl[3] = true;
		break;
	}
	}
}

inline void SpecKeyboardUpFunc(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: {
			gCueControl[0] = false;
			break;
		}

		case GLUT_KEY_RIGHT: {
			gCueControl[1] = false;
			break;
		}

		case GLUT_KEY_UP: {
			gCueControl[2] = false;
			break;
		}

		case GLUT_KEY_DOWN: {
			gCueControl[3] = false;
			break;
		}
	}
}

inline void KeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		// enter key
		case(13): {
			if (gDoCue) {
				vec2 imp((-sin(gCueAngle) * gCuePower * gCueBallFactor),
					(-cos(gCueAngle) * gCuePower * gCueBallFactor));
				gTable.balls[0].ApplyImpulse(imp);
			}
			break;
		}
		// escape key
		case(27): {
			for (int i = 0; i < NUM_BALLS; i++) {
				gTable.balls[i].Reset();
			}
			break;
		}

		// spacebar		
		case(32): {
			gCamRotate = true;
			break;
		}

		case('z'): {
			gCamL = true;
			break;
		}

		case('c'): {
			gCamR = true;
			break;
		}

		case('s'): {
			gCamU = true;
			break;
		}

		case('x'): {
			gCamD = true;
			break;
		}

		case('f'): {
			gCamZin = true;
			break;
		}

		case('v'): {
			gCamZout = true;
			break;
		}
	}
}

inline void KeyboardUpFunc(unsigned char key, int x, int y) {
	switch (key) {
		case(32): {
			gCamRotate = false;
			break;
		}

		case('z'): {
			gCamL = false;
			break;
		}

		case('c'): {
			gCamR = false;
			break;
		}

		case('s'): {
			gCamU = false;
			break;
		}

		case('x'): {
			gCamD = false;
			break;
		}

		case('f'): {
			gCamZin = false;
			break;
		}

		case('v'): {
			gCamZout = false;
			break;
		}
	}
}
