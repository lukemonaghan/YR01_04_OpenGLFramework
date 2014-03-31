//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "Common/Framework.h"
//--------------------------- OpenGL
#include "GL/glew.h"
#include "GL/glfw.h"
//--------------------------- Maths
#include "MATH/Maths.h"
#include <iostream>
//--------------------------- Global Vars
bool g_bWindowClosed = false;
//--------------------------- Closer
static int GLFWCALL windowCloseListener(){
	g_bWindowClosed = true;
	return 0;
}
//--------------------------- CONSTRUCTOR
cFramework::cFramework(){}
cFramework::cFramework(char* Title,const unsigned int a_Width, const unsigned int a_Height, bool a_Fullscreen, float f_Left,float f_Right,float f_Bottom,float f_Top){
	csTitle = Title;
	uiWidth = a_Width;
	uiHeight = a_Height;
	bFullscreen = a_Fullscreen;
	fLeft = f_Left;
	fRight = f_Right;
	fBottom = f_Bottom;
	fTop = f_Top;
	Create();
	if (bError){Exit();}
}
/*
void cFramework::Create(char* Title,const unsigned int a_Width, const unsigned int a_Height, bool a_Fullscreen, float f_Left,float f_Right,float f_Bottom,float f_Top){
	csTitle = Title;
	uiWidth = a_Width;
	uiHeight = a_Height;
	bFullscreen = a_Fullscreen;
	Create( f_Left, f_Right, f_Bottom, f_Top);
	if (bError){Exit();}
}*/
//--------------------------- Colours
void cFramework::ColourVertex(Vector4 vColour){
	glColor4f(vColour.r,vColour.g,vColour.b,vColour.a);
}
void cFramework::ColourBackground(Vector4 vColour){
	glClearColor(vColour.r,vColour.g,vColour.b,vColour.a);
}
void cFramework::ResizeWindow(int width, int height){
	glfwSetWindowSize(width,height);
	glViewport(0,0,width,height);
	WorldProj.Ortho((-(float)width  * fLeft),
					( (float)width  * fRight),
					(-(float)height * fBottom),
					( (float)height * fTop),
					0.0f,100.0f);
	CamMVP = WorldProj;
	WorldMVP = WorldProj * WorldViewT * WorldViewR;
}
void cFramework::Fullscreen(bool fullscr){
	GLFWvidmode desktopMode;
	glfwGetDesktopMode(&desktopMode);

	if (fullscr){
		glfwSetWindowPos(0, 0);
		ResizeWindow(desktopMode.Width,desktopMode.Height);
	}else{
		ResizeWindow(uiWidth,uiHeight);
		glfwSetWindowPos(int((desktopMode.Width-uiWidth)*0.5),int((desktopMode.Height-uiHeight)*0.5));
	}
}
//--------------------------- UPDATE
bool cFramework::Update(){
	if (glfwGetWindowParam(GLFW_OPENED) != GLEW_OK && !bError && !g_bWindowClosed){
//--------------------------- DEBUG
		if (glfwGetKey(287) && glfwGetKey(289) && glfwGetKey(291) && glfwGetKey('Z')){
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		}else{
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
//--------------------------- DEBUG
		return true;
	}
	return false;
}
//--------------------------- CLEAR
void cFramework::Clear(){
	glfwSwapBuffers();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
//--------------------------- EXIT
void cFramework::Exit(){
	glfwTerminate();
}
//--------------------------- CreateFW - Private
void cFramework::Create(){
	if( !glfwInit()){
        std::cout << "GLFW FAILED\n";
		bError = true;
		return;
	}
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES,4);
    
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
    
	//OpenWindow
	glfwOpenWindow( uiWidth,uiHeight, 8, 8, 8, 8, 24, 8, GLFW_WINDOW );
	//GLEW
    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
        std::cout << "GLEW FAILED\n";
		bError = true;
		glfwTerminate();
		return;
	}
    std::cout << glGetString(GL_RENDERER) << glGetString(GL_VERSION) << std::endl;
    std::cout << glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR) << ":" << glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR) << std::endl;
	glfwSwapInterval(0);//start off with NO vsync
	//Title
	glfwSetWindowTitle(csTitle);
	//Colours
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//Texture
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	//Transparancy
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_ADD);
	//Depth
	glEnable (GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//Error
	glfwSetWindowCloseCallback(&windowCloseListener);
	WorldViewT = Matrix4(1.0f);
	WorldViewR = Matrix4(1.0f);
	WorldProj  = Matrix4(1.0f);
	WorldProj.Ortho((-(float)uiWidth  * fLeft),
					( (float)uiWidth  * fRight),
					(-(float)uiHeight * fBottom),
					( (float)uiHeight * fTop),
					0.0f,100.0f);
	CamMVP = WorldProj;
	WorldMVP = WorldProj * WorldViewT * WorldViewR;
	bError = false;	
}
void cFramework::BlendMode(int i_Begin, int i_Final, int i_Equation){
	glBlendFunc(i_Begin,i_Final);
	glBlendEquation(i_Equation);
}
//--------------------------- Camera
void cFramework::Translate(float x, float y){
	WorldViewT.Identity();
	WorldViewT.Translate(x,y,0.0f);
	WorldMVP = WorldProj * WorldViewT * WorldViewR;
}
void cFramework::Rotate(float angle){
	WorldViewR.Identity();
	angle = radToDegree(angle);
	WorldViewR.RotateZ(angle);
	WorldMVP = WorldProj * WorldViewT * WorldViewR;
}
void cFramework::Scale(float amount){
	WorldProj.Identity();
	WorldProj.Ortho((-(float)uiWidth  * fLeft   * amount),
					( (float)uiWidth  * fRight  * amount),
					(-(float)uiHeight * fBottom * amount),
					( (float)uiHeight * fTop    * amount),
					0.0f,100.0f);
	WorldMVP = WorldProj * WorldViewT * WorldViewR;
}