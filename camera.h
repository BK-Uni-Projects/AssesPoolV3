#pragma once

#include "keyboard.h"

void DoCamera(int ms)
{
	static const vec3 up(0.0, 1.0, 0.0);

	if (gCamRotate)
	{
		if (gCamL)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localL = up.Cross(camDir);
			vec3 inc = (localL* ((gCamRotSpeed*ms) / 1000.0));
			gCamLookAt = gCamPos + camDir + inc;
		}
		if (gCamR)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = up.Cross(camDir);
			vec3 inc = (localR* ((gCamRotSpeed*ms) / 1000.0));
			gCamLookAt = gCamPos + camDir - inc;
		}
		if (gCamU)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp* ((gCamMoveSpeed*ms) / 1000.0));
			gCamLookAt = gCamPos + camDir + inc;
		}
		if (gCamD)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp* ((gCamMoveSpeed*ms) / 1000.0));
			gCamLookAt = gCamPos + camDir - inc;
		}
	}
	else
	{
		if (gCamL)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localL = up.Cross(camDir);
			vec3 inc = (localL* ((gCamMoveSpeed*ms) / 1000.0));
			gCamPos += inc;
			gCamLookAt += inc;
		}
		if (gCamR)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 inc = (localR* ((gCamMoveSpeed*ms) / 1000.0));
			gCamPos += inc;
			gCamLookAt += inc;
		}
		if (gCamU)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp* ((gCamMoveSpeed*ms) / 1000.0));
			gCamPos += inc;
			gCamLookAt += inc;
		}
		if (gCamD)
		{
			vec3 camDir = (gCamLookAt - gCamPos).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localDown = camDir.Cross(localR);
			vec3 inc = (localDown* ((gCamMoveSpeed*ms) / 1000.0));
			gCamPos += inc;
			gCamLookAt += inc;
		}
	}

	if (gCamZin)
	{
		vec3 camDir = (gCamLookAt - gCamPos).Normalised();
		vec3 inc = (camDir* ((gCamMoveSpeed*ms) / 1000.0));
		gCamPos += inc;
		gCamLookAt += inc;
	}
	if (gCamZout)
	{
		vec3 camDir = (gCamLookAt - gCamPos).Normalised();
		vec3 inc = (camDir* ((gCamMoveSpeed*ms) / 1000.0));
		gCamPos -= inc;
		gCamLookAt -= inc;
	}
}
