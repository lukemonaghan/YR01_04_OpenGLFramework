//---------------------------
//------ Luke Monaghan ------
//----- Xbox Controller -----
//-------- 16/07/2013 -------
//---------------------------
#if defined(_WIN32)
#include "Common/XboxController.h"
#include <iostream>
//--------------------------- Windows/Xinput (YES! this is windows only for now)
#include <windows.h>
#include <XInput.h>
//--------------------------- Xinput Library
#pragma comment(lib, "XInput.lib")
XINPUT_STATE xisConState;
//--------------------------- Constructor
cXboxController::cXboxController(unsigned int playernumber){
	//set the ID
	iID = playernumber;
	Connected();
}
//--------------------------- Checks
bool cXboxController::Connected(){
	//zeroify
	ZeroMemory(&xisConState, sizeof(XINPUT_STATE));
	DWORD Result = XInputGetState(iID, &xisConState);
	//check if its connected
	if (Result == ERROR_SUCCESS){
	printf("!!Controller with ID : '%d' is connected!!\n",iID);
	return true;
	}
	printf("!!Controller with ID : '%d' is NOT connected!!\n",iID);
	return false;
}
bool cXboxController::Button(int ButtonID){
	//zeroify
	ZeroMemory(&xisConState, sizeof(XINPUT_STATE));
	XInputGetState(iID,&xisConState);
	if (xisConState.Gamepad.wButtons == ButtonID) {return true;}
	//else this buttons is not pressed
	return false;
}
bool cXboxController::Thumbstick(bool L0_R1,bool X0_Y1,float &ReturnVal){ // TODO fix deadzones
	short ThumbAmount,ThumbDead;
	//zeroify
	ZeroMemory(&xisConState, sizeof(XINPUT_STATE));
	XInputGetState(iID,&xisConState);
	//check what we are testing
	//left or right
	//   x or y
	switch (L0_R1){
	case 0:
		switch (X0_Y1){
		case 0: ThumbAmount = xisConState.Gamepad.sThumbLX; break;
		case 1: ThumbAmount = xisConState.Gamepad.sThumbLY; break;
		}
		ThumbDead = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break;
	case 1:
		switch (X0_Y1){
		case 0: ThumbAmount = xisConState.Gamepad.sThumbRX; break;
		case 1: ThumbAmount = xisConState.Gamepad.sThumbRY; break;
		}
		ThumbDead = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;		
		break;
	}
	//check if the thumb is positive or negative, also check if its greater then the deadzone
	if (ThumbAmount > 0 && ThumbAmount>ThumbDead){
		ReturnVal = (float)ThumbAmount / (float)(32767);
		return 1;
	}
	if (ThumbAmount < 0 && ThumbAmount<-ThumbDead){
		ReturnVal = -(float)ThumbAmount / (float)(-32767);
		return 1;
	}
	//else say we arent pressing anything
	return 0;
}
bool cXboxController::Trigger(bool L0_R1,float &ReturnVal){
	unsigned char TriggerAmount;
	//zeroify
	ZeroMemory(&xisConState, sizeof(XINPUT_STATE));
	XInputGetState(iID,&xisConState);
	//check what trigger the user wants to use
	switch (L0_R1){
	case 0: TriggerAmount = xisConState.Gamepad.bLeftTrigger;  break;
	case 1: TriggerAmount = xisConState.Gamepad.bRightTrigger; break;
	}
	//check if the trigger is above than the threshold 
	if (TriggerAmount>XINPUT_GAMEPAD_TRIGGER_THRESHOLD){
		ReturnVal = (float)TriggerAmount / 255;
		return 1;
	}
	//else say we arent pressing anything
	return 0;		
}
void cXboxController::Vibrate(unsigned short leftamount,unsigned short rightamount){
	//create vib
	XINPUT_VIBRATION Vibration;
	//zeroify
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
	//set the vibs
	Vibration.wLeftMotorSpeed = leftamount;
	Vibration.wRightMotorSpeed = rightamount;
	//push to controller
	XInputSetState(iID, &Vibration);
}
#endif