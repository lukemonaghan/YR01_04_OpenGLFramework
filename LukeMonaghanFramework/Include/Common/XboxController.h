//---------------------------
//------ Luke Monaghan ------
//---------------------------
#if defined(_WIN32)
#ifndef XBOXINPUT_H_
#define XBOXINPUT_H_
//--------------------------- Controller Class
class cXboxController{
public:
	//setup
	cXboxController(unsigned int playernumber);
	bool Connected();
	//input checks
	bool Button(int ButtonID);
	bool Thumbstick(bool L0_R1,bool X0_Y1,float &ReturnVal);
	bool Trigger(bool L0_R1,float &ReturnVal);
	void Vibrate(unsigned short leftamount = 65535,unsigned short rightamount = 65535);
	int iID;
};
#endif
#endif