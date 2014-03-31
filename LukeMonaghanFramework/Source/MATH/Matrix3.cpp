//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "MATH/Matrix3.h"
#include <math.h>

//constructors
Matrix3::Matrix3(){
	Identity();//calls the identity setup
}
Matrix3::Matrix3(float fm00 ,float fm01,float fm02,
				 float fm10, float fm11,float fm12,
				 float fm20, float fm21,float fm22){
				 m00 = fm00; m01 = fm01; m02 =fm02;
				 m10 = fm10; m11 = fm11; m12 =fm12;
				 m20 = fm20; m21 = fm21; m22 =fm22;
}
//Determinant
float Matrix3::Determinant(){
	return	( m00 * ( m11 * m22 - m12 * m21 ) +
			  m01 * ( m12 * m20 - m10 * m22 ) +
			  m02 * ( m10 * m21 - m11 * m20 ) );
	}
//Inverse
bool  Matrix3::Inverse(){
	float fDeterm = Determinant();
	if (fDeterm != 0.0f){
		const float fInvDet = Recipf(fDeterm);

		const Matrix3 tmat = *this;
		m00 = ( tmat.m11 * tmat.m22 - tmat.m12 * tmat.m21 ) * fInvDet;
		m01 = ( tmat.m02 * tmat.m21 - tmat.m01 * tmat.m22 ) * fInvDet;
		m02 = ( tmat.m01 * tmat.m12 - tmat.m02 * tmat.m11 ) * fInvDet;

		m10 = ( tmat.m12 * tmat.m20 - tmat.m10 * tmat.m22 ) * fInvDet;
		m11 = ( tmat.m00 * tmat.m22 - tmat.m02 * tmat.m20 ) * fInvDet;
		m12 = ( tmat.m02 * tmat.m10 - tmat.m00 * tmat.m12 ) * fInvDet;
			  
		m20 = ( tmat.m10 * tmat.m21 - tmat.m11 * tmat.m20 ) * fInvDet;
		m21 = ( tmat.m01 * tmat.m20 - tmat.m00 * tmat.m21 ) * fInvDet;
		m22 = ( tmat.m00 * tmat.m11 - tmat.m01 * tmat.m10 ) * fInvDet;
	 return true;
	}return false;
}
bool  Matrix3::InverseGet(Matrix3 &mat3){
	float fDeterm = Determinant();
	if (fDeterm != 0.0f){
		const float fInvDet = Recipf(fDeterm);

		mat3.m00 = ( m11 * m22 - m12 * m21 ) * fInvDet;
		mat3.m01 = ( m02 * m21 - m01 * m22 ) * fInvDet;
		mat3.m02 = ( m01 * m12 - m02 * m11 ) * fInvDet;

		mat3.m10 = ( m12 * m20 - m10 * m22 ) * fInvDet;
		mat3.m11 = ( m00 * m22 - m02 * m20 ) * fInvDet;
		mat3.m12 = ( m02 * m10 - m00 * m12 ) * fInvDet;

		mat3.m20 = ( m10 * m21 - m11 * m20 ) * fInvDet;
		mat3.m21 = ( m01 * m20 - m00 * m21 ) * fInvDet;
		mat3.m22 = ( m00 * m11 - m01 * m10 ) * fInvDet;
	 return true;
	}return false;
}
//1D rots
void  Matrix3::RotateX (float angle){
	const float co = cosf(angle);
	const float si = sinf(angle);
	m00	= 1.0f; m01	= 0.0f; m02	= 0.0f;
	m10	= 0.0f;	m11	=   co;	m12	=   si;
	m20	= 0.0f;	m21	=  -si;	m22	=   co;
}
void  Matrix3::RotateY (float angle){
	const float co = cosf(angle);
	const float si = sinf(angle);
	m00	=   co; m01	= 0.0f; m02	=  -si;
	m10	= 0.0f;	m11	= 1.0f;	m12	= 0.0f;
	m20	=   si;	m21	= 0.0f;	m22	=   co;
}
void  Matrix3::RotateZ (float angle){
	const float co = cosf(angle);
	const float si = sinf(angle);
	m00	=   co; m01	=   si; m02	= 0.0f;
	m10	=  -si;	m11	=   si;	m12	= 0.0f;
	m20	= 0.0f;	m21	= 0.0f;	m22	= 1.0f;
}
//3D rots	  
void  Matrix3::RotateXYZ (Vector3 v3Angles){
	Matrix3 m3x, m3y, m3z;
	m3x.RotateX( v3Angles.x );
	m3y.RotateY( v3Angles.y );
	m3z.RotateZ( v3Angles.z );
	*this = m3x * m3y * m3z;
}
void  Matrix3::RotateYXZ (Vector3 v3Angles){
	Matrix3 m3x, m3y, m3z;
	m3x.RotateX( v3Angles.x );
	m3y.RotateY( v3Angles.y );
	m3z.RotateZ( v3Angles.z );
	*this = m3y * m3x * m3z;
}
void  Matrix3::RotateZXY (Vector3 v3Angles){
	Matrix3 m3x, m3y, m3z;
	m3x.RotateX( v3Angles.x );
	m3y.RotateY( v3Angles.y );
	m3z.RotateZ( v3Angles.z );
	*this = m3z * m3x * m3y;
}
void  Matrix3::RotateZYX (Vector3 v3Angles){
	Matrix3 m3x, m3y, m3z;
	m3x.RotateX( v3Angles.x );
	m3y.RotateY( v3Angles.y );
	m3z.RotateZ( v3Angles.z );
	*this = m3z * m3y * m3x;
}
//ortho
void  Matrix3::Ortho(){
	Vector3 v3x(m00,m01,m02);
	Vector3 v3y(m10,m11,m12);
	Vector3 v3z(m20,m21,m22);

	v3y = v3y - (v3z * v3z.Dot(v3y));
	v3y.Normalize();
	v3x.Cross(v3y,v3z);
	v3x.Normalize();

	m00 = v3x.x; m01 = v3x.y; m02 = v3x.z;
	m10 = v3y.x; m11 = v3y.y; m12 = v3y.z;
	m20 = v3z.x; m21 = v3z.y; m22 = v3z.z;
}
void  Matrix3::OrthoNormalize(){
	Vector3 v3x(m00,m01,m02);
	Vector3 v3y(m10,m11,m12);
	Vector3 v3z(m20,m21,m22);

	v3z.Cross(v3x,v3y);
	v3y.Cross(v3z,v3x);

	v3x.Normalize();
	v3y.Normalize();
	v3x.Normalize();

	m00 = v3x.x; m01 = v3x.y; m02 = v3x.z;
	m10 = v3y.x; m11 = v3y.y; m12 = v3y.z;
	m20 = v3z.x; m21 = v3z.y; m22 = v3z.z;
}
//scalars	  
void  Matrix3::Scale(Vector3 vect){
	m00 = vect.x; m01 =   0.0f; m02 =   0.0f;
	m10 =   0.0f; m11 = vect.y; m12 =   0.0f;
	m20 =   0.0f; m21 =   0.0f; m22 = vect.z;
}
void  Matrix3::Scale(float scalar){
	m00 = scalar; m01 =   0.0f; m02 =   0.0f;
	m10 =   0.0f; m11 = scalar; m12 =   0.0f;
	m20 =   0.0f; m21 =   0.0f; m22 = scalar;
}
//reseters		  
void  Matrix3::Identity(){
 m00 = 1.0f; m01 = 0.0f; m02 = 0.0f;
 m10 = 0.0f; m11 = 1.0f; m12 = 0.0f;
 m20 = 0.0f; m21 = 0.0f; m22 = 1.0f;
}
void  Matrix3::Zero(){
 m00 = 0.0f; m01 = 0.0f; m02 = 0.0f;
 m10 = 0.0f; m11 = 0.0f; m12 = 0.0f;
 m20 = 0.0f; m21 = 0.0f; m22 = 0.0f;
}
//overloads
//Comparitors
bool    Matrix3::operator   == (Matrix3 mat3){
	if (m00 == mat3.m00 &&
	    m01 == mat3.m01 &&
	    m02 == mat3.m02 &&
	    m10 == mat3.m10 &&
	    m11 == mat3.m11 &&
	    m12 == mat3.m12 &&
	    m20 == mat3.m20 &&
	    m21 == mat3.m21 &&
	    m22 == mat3.m22) {return true;}
	return false;
}
bool    Matrix3::operator   != (Matrix3 mat3){
	if (m00 != mat3.m00 &&
	    m01 != mat3.m01 &&
	    m02 != mat3.m02 &&
	    m10 != mat3.m10 &&
	    m11 != mat3.m11 &&
	    m12 != mat3.m12 &&
	    m20 != mat3.m20 &&
	    m21 != mat3.m21 &&
	    m22 != mat3.m22) {return true;}
	return false;
}
void    Matrix3::operator    = (Matrix3 mat3){
	m00 = mat3.m00;
	m01 = mat3.m01;
	m02 = mat3.m02;
	m10 = mat3.m10;
	m11 = mat3.m11;
	m12 = mat3.m12;
	m20 = mat3.m20;
	m21 = mat3.m21;
	m22 = mat3.m22;
}
void    Matrix3::operator    = (float scalar){
	m00 = scalar;
	m01 = scalar;
	m02 = scalar;
	m10 = scalar;
	m11 = scalar;
	m12 = scalar;
	m20 = scalar;
	m21 = scalar;
	m22 = scalar;
}
//negate		   					
Matrix3 Matrix3::operator   -  (            ){
	return Matrix3(-m00,-m01,-m02,
				   -m10,-m11,-m12,
				   -m20,-m21,-m22);
}
//Addition		   							 
Matrix3 Matrix3::operator   ++ (            ){
	return Matrix3(++m00,++m01,++m02,
				   ++m10,++m11,++m12,
				   ++m20,++m21,++m22);
}
Matrix3 Matrix3::operator   +  (Matrix3 mat3){
	return Matrix3(m00+mat3.m00,m01+mat3.m01,m02+mat3.m02,
				   m10+mat3.m10,m11+mat3.m11,m12+mat3.m12,
				   m20+mat3.m20,m21+mat3.m21,m22+mat3.m22);
}
Matrix3 Matrix3::operator   += (Matrix3 mat3){
	return ((*this) + mat3);
}
//Subtraction	   							 
Matrix3 Matrix3::operator   -- (            ){
	return Matrix3(--m00,--m01,--m02,
				   --m10,--m11,--m12,
				   --m20,--m21,--m22);
}
Matrix3 Matrix3::operator   -  (Matrix3 mat3){
	return Matrix3(m00-mat3.m00,m01-mat3.m01,m02-mat3.m02,
				   m10-mat3.m10,m11-mat3.m11,m12-mat3.m12,
				   m20-mat3.m20,m21-mat3.m21,m22-mat3.m22);
}
Matrix3 Matrix3::operator   -= (Matrix3 mat3){
	return ((*this) - mat3);
}
//Multiplication  							 
Matrix3 Matrix3::operator   *  (Matrix3 mat3){
	return Matrix3( m00 * mat3.m00 + m01 * mat3.m10 + m02 * mat3.m20,
					m00 * mat3.m01 + m01 * mat3.m11 + m02 * mat3.m21,
					m00 * mat3.m02 + m01 * mat3.m12 + m02 * mat3.m22,
						  				  					 
					m10 * mat3.m00 + m11 * mat3.m10 + m12 * mat3.m20,
					m10 * mat3.m01 + m11 * mat3.m11 + m12 * mat3.m21,
					m10 * mat3.m02 + m11 * mat3.m12 + m12 * mat3.m22,
						  				   					  
					m20 * mat3.m00 + m21 * mat3.m10 + m22 * mat3.m20,
					m20 * mat3.m01 + m21 * mat3.m11 + m22 * mat3.m21,
					m20 * mat3.m02 + m21 * mat3.m12 + m22 * mat3.m22 );
}
Matrix3 Matrix3::operator   *= (Matrix3 mat3){
	return (*this) * mat3;
}
Vector3 Matrix3::operator   *  (Vector3 vect){
	return Vector3( m00 * vect.x + m01 * vect.y + m02 * vect.z,
					m10 * vect.x + m11 * vect.y + m12 * vect.z,
					m20 * vect.x + m21 * vect.y + m22 * vect.z );
}
Vector3 Matrix3::operator   *= (Vector3 vect){
	return ((*this) * vect);
}
Matrix3 Matrix3::operator   *  (float scalar){
	return Matrix3(m00*scalar,m01*scalar,m02*scalar,
				   m10*scalar,m11*scalar,m12*scalar,
				   m20*scalar,m21*scalar,m22*scalar);
}
Matrix3 Matrix3::operator   *= (float scalar){
	return ((*this) * scalar);
}
//End Of File