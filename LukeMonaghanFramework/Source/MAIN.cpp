//---------------------------
//------ Luke Monaghan ------
//---- Framework Tester -----
//------- 18/07/2013 --------
//---------------------------
#include "LukeMonaghanFramework.h"
#include <iostream>

int count = 1;
float FPS = 0.0f;
int main(){
	FrameworkInitialise("HelloWorld",1280,720,false);
	FrameworkBGColour(0.2f,0.4f,0.8f,1.0f);
	Sprite		sprCarpet		= SpriteLoad("./Images/Carpet.png",32,32,16,16);
	Font		fntCourierNew	= FontLoad("./Fonts/CourierNew.fnt");
//UPDATE
	while (FrameworkUpdate()){
//CLEAR AND DELTASET
		FrameworkClearScreen();
		DeltaTimeSet();

		count++;
		FPS = FPSGet();
		for (int index = 1;index <= count; index++){
			SpriteMove(sprCarpet,rand()%1280-640,rand()%720-360,rand()%99+1);
			SpriteDraw(sprCarpet);
		}
		if (FPS > 59.9f && FPS < 60.1f){
			std::cout << "FPS :" << FPS << " sprite count :" << count << " triangle count : " << count*2 << std::endl;
		}
		if (FPS > 29.9f && FPS < 30.1f){
			std::cout << "FPS :" << FPS << " sprite count :" << count << " triangle count : " << count*2 << std::endl;
		}
		DrawInt(fntCourierNew,GetInstanceCount(),0,360,0,true);
	}
	FrameworkShutdown();
	return 1+1-1-1;
}


/*


*/