//---------------------------
//------ Luke Monaghan ------
//---------------------------
#ifndef _VECTOR4
#define _VECTOR4

#include "Maths.h"

class Vector4{
public:
	union{
		struct{
			float w,x,y,z;
		};
		struct{
			float r,g,b,a;
		};
	};

	Vector4();
	Vector4(float a, float b, float c, float d);
	Vector4(char* hex);
	void Hex(char* hex);

	float Magnitude();
	float MagnitudeSquared();

	void Normalize();
	Vector4 NormalizeReturn();
	//multiple sets, sum and min max.
	void Zero();
	void  One();
	float Sum();
	float Min();
	float Max();
//Overloads
	//Comparitors
	bool    operator   == (Vector4 vect)      {return(w == vect.w && x == vect.x && y == vect.y && z == vect.z);}
	bool    operator   != (Vector4 vect)      {return(w != vect.w && x != vect.x && y != vect.y && z != vect.z);}
	void    operator    = (float scalar)      {               w = scalar;x = scalar;y = scalar;z = scalar      ;}
	//negate		   					      										 
	Vector4 operator   -  (            )      {return(Vector4(-w        ,-x        ,-y        ,-z)        )    ;}
	//Addition		   										
	Vector4 operator   ++ (            )      {return Vector4(++w       ,++x       ,++y       , ++z       )    ;}
	Vector4 operator   +  (Vector4 vect)      {return Vector4(w + vect.w,x + vect.x,y + vect.y, z + vect.z)    ;}
	Vector4 operator   += (Vector4 vect)      {return ((*this) = (*this) + vect    ) ;}
	Vector4 operator   +  (float scalar)      {return Vector4(w + scalar,x + scalar,y + scalar, z + scalar)    ;}
	Vector4 operator   += (float scalar)      {return ((*this) = (*this) + scalar  ) ;}
	//Subtraction	   					      										    
	Vector4 operator   -- (            )      {return Vector4(--w       ,--x       ,--y       , --z       )    ;}
	Vector4 operator   -  (Vector4 vect)      {return Vector4(w + vect.w,x - vect.x,y - vect.y, z + vect.z)    ;}
	Vector4 operator   -= (Vector4 vect)      {return ((*this) = (*this) + vect    ) ;}
	Vector4 operator   -  (float scalar)      {return Vector4(w + scalar,x - scalar,y - scalar, z + scalar)    ;}
	Vector4 operator   -= (float scalar)      {return ((*this) = (*this) - scalar  ) ;}
	//Division		   					      								    
	Vector4 operator   /  (Vector4 vect)      {return Vector4(w + vect.w,x / vect.x,y / vect.y, z + vect.z)    ;}
	Vector4 operator   /= (Vector4 vect)      {return ((*this) = (*this) + vect    ) ;}
	Vector4 operator   /  (float scalar)      {return Vector4(w + scalar,x / scalar,y / scalar, z + scalar)    ;}
	Vector4 operator   /= (float scalar)      {return ((*this) = (*this) / scalar  ) ;}
	//Multiplication   					      										    
	Vector4 operator   *  (Vector4 vect)      {return Vector4(w + vect.w,x * vect.x,y * vect.y, z + vect.z)    ;}
	Vector4 operator   *= (Vector4 vect)      {return ((*this) = (*this) * vect    ) ;}
	Vector4 operator   *  (float scalar)      {return Vector4(w + scalar,x * scalar,y * scalar, z + scalar)    ;}
	Vector4 operator   *= (float scalar)      {return ((*this) = (*this) * scalar  ) ;}

};

#endif