//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef _MATRIX4
#define _MATRIX4

#include "Maths.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"

class Matrix4{
public:
	union{ //so we can use individual or array;
		struct{
			float m[16];
		};
		struct{
			float mm[4][4];
		};
		struct{
			float m00,m10,m20,m30,
				  m01,m11,m21,m31,
				  m02,m12,m22,m32,
				  m03,m13,m23,m33;
		};
	};
	Matrix4();
	Matrix4(float fm00,float fm01,float fm02,float fm03,
			float fm10,float fm11,float fm12,float fm13,
			float fm20,float fm21,float fm22,float fm23,
			float fm30,float fm31,float fm32,float fm33);
	Matrix4(float fIdentity);

	void Translate(float x, float y, float z);

	void  RotateZ( float angle);
	void  Scale(Vector3 vect);
	void  Scale(float scalarx, float scalary, float scalarz);

	bool  Ortho(float fLeft, float fRight, float fBottom, float fTop, float fNear, float fFar );

	void  Identity();
	void  Zero();
	void  cout(char* Name);
//overloads
	//Comparitors
	bool    operator   == (Matrix4  mat)const;
	bool    operator   != (Matrix4  mat)const;
	void    operator    = (Matrix4  mat);
	void    operator    = (float scalar);
	//negate		   					
	Matrix4 operator   -  (            );
	//Addition		   					
	Matrix4 operator   ++ (            );
	Matrix4 operator   +  (Matrix4  mat)const;
	Matrix4 operator   += (Matrix4  mat);
	//Subtraction	   					
	Matrix4 operator   -- (            );
	Matrix4 operator   -  (Matrix4  mat)const;
	Matrix4 operator   -= (Matrix4  mat);
	//Multiplication  				  
	Matrix4 operator   *  (Matrix4  mat)const;
	Matrix4 operator   *= (Matrix4  mat);

	Vector4 operator   *  (Vector4 vect)const;
	Vector4 operator   *= (Vector4 vect);

	Matrix4 operator   *  (float scalar)const;
	Matrix4 operator   *= (float scalar);
};
#endif
/*

o Transform Point
o Transform Vector

*/