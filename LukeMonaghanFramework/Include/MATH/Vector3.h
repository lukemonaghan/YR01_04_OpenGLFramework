//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef _VECTOR3
#define _VECTOR3

#include "Maths.h"

class Vector3{
private:

public:
    union{
        struct {
            float x,y,z;
        };
        struct{
            float i[3];
        };
    };	
	Vector3();
	Vector3(float a,float b,float c);
//Member functions
	float Magnitude();
	float MagnitudeSquared();

	float Dot(Vector3 vect2);

	bool IsUnit();
	Vector3 GetUnit();

	Vector3 NormalizeReturn();
	void Normalize();

	Vector3 Cross(Vector3 vect);
	Vector3 Cross(Vector3 vect,Vector3 vect2);
	Vector3 Cross2(Vector3 vect,Vector3 vect2);

	void RotateXRad(float angle);
	void RotateXDeg(float angle);
	void RotateYRad(float angle);
	void RotateYDeg(float angle);	
	void RotateZRad(float angle);
	void RotateZDeg(float angle);

	void Project(Vector3 angles, float distance);
	void ProjectOrtho(Vector3 angles,float distance);

	Vector3 Lerp(Vector3 vect1,Vector3 vect2,float t);

	void Zero();
	void One();
	float Sum();
	float Min();
	float Max();
//Overloads
	//Comparitors
	bool    operator   == (Vector3 vect)      {return   (x == vect.x && y == vect.y && z == vect.z) ;}
	bool    operator   != (Vector3 vect)      {return   (x != vect.x && y != vect.y && z != vect.z) ;}
	void    operator    = (float scalar)      {               x = scalar;y = scalar;z = scalar      ;}
	//negate		   					      										 
	Vector3 operator   -  (            )      {return(Vector3(-x,-y,-z))                            ;}
	//Addition		   		
	Vector3 operator   ++ (            )      {return Vector3(++x       ,++y       , ++z       )    ;}
	Vector3 operator   +  (Vector3 vect)      {return Vector3(x + vect.x,y + vect.y, z + vect.z)    ;}
	Vector3 operator   += (Vector3 vect)      {return ((*this) = (*this) + vect    ) ;}
	Vector3 operator   +  (float scalar)      {return Vector3(x + scalar,y + scalar, z + scalar)    ;}
	Vector3 operator   += (float scalar)      {return ((*this) = (*this) + scalar  ) ;}
	//Subtraction	   					      													    
	Vector3 operator   -- (            )      {return Vector3(--x       ,--y       , --z       )    ;}
	Vector3 operator   -  (Vector3 vect)      {return Vector3(x - vect.x,y - vect.y, z + vect.z)    ;}
	Vector3 operator   -= (Vector3 vect)      {return ((*this) = (*this) - vect    ) ;}
	Vector3 operator   -  (float scalar)      {return Vector3(x - scalar,y - scalar, z + scalar)    ;}
	Vector3 operator   -= (float scalar)      {return ((*this) = (*this) - scalar  ) ;}
	//Division		   					      													    
	Vector3 operator   /  (Vector3 vect)      {return Vector3(x / vect.x,y / vect.y, z + vect.z)    ;}
	Vector3 operator   /= (Vector3 vect)      {return ((*this) = (*this) / vect    ) ;}
	Vector3 operator   /  (float scalar)      {return Vector3(x / scalar,y / scalar, z + scalar)    ;}
	Vector3 operator   /= (float scalar)      {return ((*this) = (*this) / scalar  ) ;}
	//Multiplication   					      													    
	Vector3 operator   *  (Vector3 vect)      {return Vector3(x * vect.x,y * vect.y, z + vect.z)    ;}
	Vector3 operator   *= (Vector3 vect)      {return ((*this) = (*this) * vect    ) ;}
	Vector3 operator   *  (float scalar)      {return Vector3(x * scalar,y * scalar, z + scalar)    ;}
	Vector3 operator   *= (float scalar)      {return ((*this) = (*this) * scalar  ) ;}

};

#endif