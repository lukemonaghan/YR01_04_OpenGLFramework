//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef _VECTOR2
#define _VECTOR2

#include "Maths.h"

class Vector2{
private:

public:
	//Define data types (both x/y and u/v)
	union{
		struct{
			float x,y;
		};
		struct{
			float u,v;
		};
		struct{
			float i[2];
		};
	};
	//Constructors
	Vector2();
	Vector2(float a, float b);
	//Member functions
	float Magnitude();
	float MagnitudeSquared();

	float Dot(Vector2 vect2);

	bool IsUnit();
	Vector2 GetUnit();

	Vector2 NormalizeReturn();
	void Normalize();

	Vector2 GetPerpendicular();

	void RotateRad(float angle);
	void RotateDegree(float angle);

	void RadianToVect(float angle);
	void degreeToVect(float angle);

	void Project(float angle, float distance);

	Vector2 Lerp(Vector2 vect1,Vector2 vect2,float t);

	void Zero();
	void One();
	float Sum();
	float Min();
	float Max();
//Overloads
	//Comparitors
	bool    operator   == (Vector2 vect)      {return   (x == vect.x && y == vect.y) ;}
	bool    operator   != (Vector2 vect)      {return   (x != vect.x && y != vect.y) ;}
	void    operator    = (float scalar)      {               x = scalar;y = scalar  ;}
	//negate		   					      										 
	Vector2 operator   -  (            )      {return(Vector2(-x,-y));                }
	//Addition		   	
	Vector2 operator   ++ (            )      {return Vector2(++x       ,++y       ) ;}
	Vector2 operator   +  (Vector2 vect)      {return Vector2(x + vect.x,y + vect.y) ;}
	Vector2 operator   += (Vector2 vect)      {return ((*this) = (*this) + vect    ) ;}
	Vector2 operator   +  (float scalar)      {return Vector2(x + scalar,y + scalar) ;}
	Vector2 operator   += (float scalar)      {return ((*this) = (*this) + scalar  ) ;}
	//Subtraction	   
	Vector2 operator   -- (            )      {return Vector2(--x       ,--y       ) ;}
	Vector2 operator   -  (Vector2 vect)      {return Vector2(x - vect.x,y - vect.y) ;}
	Vector2 operator   -= (Vector2 vect)      {return ((*this) = (*this) - vect    ) ;}
	Vector2 operator   -  (float scalar)      {return Vector2(x - scalar,y - scalar) ;}
	Vector2 operator   -= (float scalar)      {return ((*this) = (*this) - scalar  ) ;}
	//Division	
	Vector2 operator   /  (Vector2 vect)      {return Vector2(x / vect.x,y / vect.y) ;}
	Vector2 operator   /= (Vector2 vect)      {return ((*this) = (*this) / vect    ) ;}
	Vector2 operator   /  (float scalar)      {return Vector2(x / scalar,y / scalar) ;}
	Vector2 operator   /= (float scalar)      {return ((*this) = (*this) / scalar  ) ;}
	//Multiplication   					      										 
	Vector2 operator   *  (Vector2 vect)      {return Vector2(x * vect.x,y * vect.y) ;}
	Vector2 operator   *= (Vector2 vect)      {return ((*this) = (*this) * vect    ) ;}
	Vector2 operator   *  (float scalar)      {return Vector2(x * scalar,y * scalar) ;}
	Vector2 operator   *= (float scalar)      {return ((*this) = (*this) * scalar  ) ;}

};

#endif