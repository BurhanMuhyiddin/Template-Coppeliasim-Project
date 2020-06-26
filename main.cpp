#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "extApi.h"
}

using namespace std;

#define PI 3.14

int leftMotorHandle = 0;
int rightMotorHandle = 0;
int ultrasonicSensorFiveHandle = 0;
char detectionState = 0;
float detectedPoint[3];

float get_distance(float* pointCoordinates)
{
	float x = pointCoordinates[0], y = pointCoordinates[1], z = pointCoordinates[2];
	return sqrt(x * x + y * y + z * z);
}

int main()
{
	int clientID = 0;

	simxFinish(-1);
	clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 5000, 5);
	Sleep(1);

	if (clientID != -1)
	{
		cout << " Connection status to VREP: SUCCESS" << endl;
		int returnValue = 0;

		// Handle
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_leftMotor", &leftMotorHandle, simx_opmode_blocking);
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_rightMotor", &rightMotorHandle, simx_opmode_blocking);
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_ultrasonicSensor5", &ultrasonicSensorFiveHandle, simx_opmode_blocking);

		//Other part
		//returnValue = simxSetJointTargetVelocity(clientID, leftMotorHandle, 0.2, simx_opmode_oneshot);
		//returnValue = simxSetJointTargetVelocity(clientID, leftMotorHandle, 0.0, simx_opmode_oneshot);
		returnValue = simxReadProximitySensor(clientID, ultrasonicSensorFiveHandle, (simxUChar*)detectionState, detectedPoint, NULL, NULL, simx_opmode_streaming);

		for (int i = 0; i < 50; i++)
		{
			returnValue = simxReadProximitySensor(clientID, ultrasonicSensorFiveHandle, (simxUChar*)detectionState, detectedPoint, NULL, NULL, simx_opmode_buffer);
			cout << get_distance(detectedPoint) << endl;
			Sleep(100);
		}

		simxFinish(-1);
	}
	else
	{
		cout << " Connection status to VREP: FAILED" << endl;
	}
	simxFinish(clientID);
	return clientID;
}
