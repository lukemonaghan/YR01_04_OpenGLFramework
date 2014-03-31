//---------------------------
//------ Luke Monaghan ------
//---------------------------
#include "MATH/Matrix4.h"
#include <math.h>
#include <iostream>
//constructors
Matrix4::Matrix4(){
	Zero();
}
Matrix4::Matrix4(float fm00 ,float fm01,float fm02,float fm03,
				 float fm10, float fm11,float fm12,float fm13,
				 float fm20, float fm21,float fm22,float fm23,
				 float fm30, float fm31,float fm32,float fm33){
				 m00 = fm00; m01 = fm01; m02 =fm02; m03 =fm03;
				 m10 = fm10; m11 = fm11; m12 =fm12;	m13 =fm13;
				 m20 = fm20; m21 = fm21; m22 =fm22;	m23 =fm23;
				 m30 = fm30; m31 = fm31; m32 =fm32;	m33 =fm33;
}
Matrix4::Matrix4(float fIdentity){
	m00 = fIdentity; m01 = 0.0f;	  m02 = 0.0f;	   m03 = 0.0f;
	m10 = 0.0f;		 m11 = fIdentity; m12 = 0.0f;	   m13 = 0.0f;
	m20 = 0.0f;		 m21 = 0.0f;	  m22 = fIdentity; m23 = 0.0f;
	m30 = 0.0f;		 m31 = 0.0f;	  m32 = 0.0f;      m33 = fIdentity;
}
//Translate
void Matrix4::Translate(float x, float y, float z){
	m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 =    x;
	m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 =    y;
	m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 =    z;
	m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}
void  Matrix4::RotateZ( float angle ){
	float cosine = cosf( angle );
	float sine = sinf( angle ); 
	m00 =  cosine; m01 =  -sine; m02 = 0.0f; m03 = 0.0f;
	m10 =    sine; m11 = cosine; m12 = 0.0f; m13 = 0.0f;
	m20 = 0.0f;	   m21 = 0.0f;   m22 = 1.0f; m23 = 0.0f;
	m30 = 0.0f;	   m31 = 0.0f;   m32 = 0.0f; m33 = 1.0f;
}

//scalars	  
void  Matrix4::Scale( Vector3 vect ){
	Scale(vect.x,vect.y,vect.z);
}
void  Matrix4::Scale( float scalarx, float scalary, float scalarz ){
	m00 = scalarx; m01 = 0.0f;	  m02 = 0.0f;	 m03 = 0.0f;
	m10 = 0.0f;	   m11 = scalary; m12 = 0.0f;	 m13 = 0.0f;
	m20 = 0.0f;	   m21 = 0.0f;	  m22 = scalarz; m23 = 0.0f;
	m30 = 0.0f;	   m31 = 0.0f;	  m32 = 0.0f;    m33 = 1.0f;
}
//ortho
bool Matrix4::Ortho( float fLeft, float fRight, float fBottom, float fTop, float fNear, float fFar ){
	m00 =                2.0f / (fRight - fLeft);
	m11 =                2.0f / (fTop   - fBottom);
	m22 =               -2.0f / (fFar   - fNear);
	m33 = 1.0f;

	m03 = - ((fRight + fLeft)  / (fRight - fLeft));
	m13 = - ((fTop   + fBottom)/ (fTop   - fBottom));
	m23 = - ((fFar   + fNear)  / (fFar   - fNear));
	return true;
}
void  Matrix4::cout(char* Name){
	std::cout << Name <<  std::endl
			  <<  m00 << " : " << m01 << " : " << m02 << " : " << m03 << std::endl
			  <<  m10 << " : " << m11 << " : " << m12 << " : " << m13 << std::endl
			  <<  m20 << " : " << m21 << " : " << m22 << " : " << m23 << std::endl
			  <<  m30 << " : " << m31 << " : " << m32 << " : " << m33 << std::endl;
}
//reseters		  
void  Matrix4::Identity(){
 m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
 m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
 m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
 m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}
void  Matrix4::Zero(){
 m00 = 0.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
 m10 = 0.0f; m11 = 0.0f; m12 = 0.0f; m13 = 0.0f;
 m20 = 0.0f; m21 = 0.0f; m22 = 0.0f; m23 = 0.0f;
 m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 0.0f;
}
//overloads
//Comparitors
bool    Matrix4::operator   == (Matrix4  mat)const{
	if (m00 == mat.m00 && m01 == mat.m01 && m02 == mat.m02 && m03 == mat.m03 &&
	    m10 == mat.m10 && m11 == mat.m11 && m12 == mat.m12 && m13 == mat.m13 &&
	    m20 == mat.m20 && m21 == mat.m21 && m22 == mat.m22 && m23 == mat.m23 &&
	    m30 == mat.m30 && m31 == mat.m31 && m32 == mat.m32 && m33 == mat.m33) {return true;}
	return false;
}
bool    Matrix4::operator   != (Matrix4  mat)const{
	if (m00 != mat.m00 && m01 != mat.m01 && m02 != mat.m02 && m03 != mat.m03 &&
	    m10 != mat.m10 && m11 != mat.m11 && m12 != mat.m12 && m13 != mat.m13 &&
	    m20 != mat.m20 && m21 != mat.m21 && m22 != mat.m22 && m23 != mat.m23 &&
	    m30 != mat.m30 && m31 != mat.m31 && m32 != mat.m32 && m33 != mat.m33) {return true;}
	return false;
}
void    Matrix4::operator    = (Matrix4  mat){
	m00 = mat.m00;	m01 = mat.m01;	m02 = mat.m02;	m03 = mat.m03;
	m10 = mat.m10;	m11 = mat.m11;	m12 = mat.m12;	m13 = mat.m13;
	m20 = mat.m20;	m21 = mat.m21;	m22 = mat.m22;	m23 = mat.m23;
	m30 = mat.m30;	m31 = mat.m31;	m32 = mat.m32;	m33 = mat.m33;
}
void    Matrix4::operator    = (float scalar){
	m00 = scalar;	m01 = scalar;	m02 = scalar;	m03 = scalar;
	m10 = scalar;	m11 = scalar;	m12 = scalar;	m13 = scalar;
	m20 = scalar;	m21 = scalar;	m22 = scalar;	m23 = scalar;
	m30 = scalar;	m31 = scalar;	m32 = scalar;	m33 = scalar;
}
//negate		   				
Matrix4 Matrix4::operator   -  (            ){
	return Matrix4(-m00,-m01,-m02,-m03,
				   -m10,-m11,-m12,-m13,
				   -m20,-m21,-m22,-m23,
				   -m30,-m31,-m32,-m33);
}
//Addition		   							 
Matrix4 Matrix4::operator   ++ (            ){
	return Matrix4(++m00,++m01,++m02,++m03,
				   ++m10,++m11,++m12,++m13,
				   ++m20,++m21,++m22,++m23,
				   ++m30,++m31,++m32,++m33);
}
Matrix4 Matrix4::operator   +  (Matrix4  mat)const{
	return Matrix4(m00+mat.m00,m01+mat.m01,m02+mat.m02,m03+mat.m03,
				   m10+mat.m10,m11+mat.m11,m12+mat.m12,m13+mat.m13,
				   m20+mat.m20,m21+mat.m21,m22+mat.m22,m23+mat.m23,
				   m30+mat.m30,m31+mat.m31,m32+mat.m32,m33+mat.m33);
}
Matrix4 Matrix4::operator   += (Matrix4  mat){
	return ((*this) + mat);
}
//Subtraction	   							 
Matrix4 Matrix4::operator   -- (            ){
	return Matrix4(--m00,--m01,--m02,--m03,
				   --m10,--m11,--m12,--m13,
				   --m20,--m21,--m22,--m23,
				   --m30,--m31,--m32,--m33);
}
Matrix4 Matrix4::operator   -  (Matrix4  mat)const{
	return Matrix4(m00-mat.m00,m01-mat.m01,m02-mat.m02,m03-mat.m03,
				   m10-mat.m10,m11-mat.m11,m12-mat.m12,m13-mat.m13,
				   m20-mat.m20,m21-mat.m21,m22-mat.m22,m23-mat.m23,
				   m30-mat.m30,m31-mat.m31,m32-mat.m32,m33-mat.m33);
}
Matrix4 Matrix4::operator   -= (Matrix4  mat){
	return ((*this) - mat);
}
//Multiplication  							 
Matrix4 Matrix4::operator   *  (Matrix4  mat)const{
	return Matrix4( m00 * mat.m00 + m01 * mat.m10 + m02 * mat.m20 + m03 * mat.m30,
					m00 * mat.m01 + m01 * mat.m11 + m02 * mat.m21 + m03 * mat.m31,
					m00 * mat.m02 + m01 * mat.m12 + m02 * mat.m22 + m03 * mat.m32,
					m00 * mat.m03 + m01 * mat.m13 + m02 * mat.m23 + m03 * mat.m33,
						  			  				 		
					m10 * mat.m00 + m11 * mat.m10 + m12 * mat.m20 + m13 * mat.m30,
					m10 * mat.m01 + m11 * mat.m11 + m12 * mat.m21 + m13 * mat.m31,
					m10 * mat.m02 + m11 * mat.m12 + m12 * mat.m22 + m13 * mat.m32,
					m10 * mat.m03 + m11 * mat.m13 + m12 * mat.m23 + m13 * mat.m33,
						  			   				  		
					m20 * mat.m00 + m21 * mat.m10 + m22 * mat.m20 + m23 * mat.m30,
					m20 * mat.m01 + m21 * mat.m11 + m22 * mat.m21 + m23 * mat.m31,
					m20 * mat.m02 + m21 * mat.m12 + m22 * mat.m22 + m23 * mat.m32,
					m20 * mat.m03 + m21 * mat.m13 + m22 * mat.m23 + m23 * mat.m33,
					
					m30 * mat.m00 + m31 * mat.m10 + m32 * mat.m20 + m33 * mat.m30,
					m30 * mat.m01 + m31 * mat.m11 + m32 * mat.m21 + m33 * mat.m31,
					m30 * mat.m02 + m31 * mat.m12 + m32 * mat.m22 + m33 * mat.m32,
					m30 * mat.m03 + m31 * mat.m13 + m32 * mat.m23 + m33 * mat.m33);
}
Matrix4 Matrix4::operator   *= (Matrix4  mat){
	return (*this) * mat;
}

Vector4 Matrix4::operator   *  (Vector4 vect)const{
	return Vector4( m00 * vect.w + m01 * vect.x + m02 * vect.y + m03 * vect.z,
					m10 * vect.w + m11 * vect.x + m12 * vect.y + m13 * vect.z,
					m20 * vect.w + m21 * vect.x + m22 * vect.y + m23 * vect.z,
					m30 * vect.w + m31 * vect.x + m32 * vect.y + m33 * vect.z );
}
Vector4 Matrix4::operator   *= (Vector4 vect){
	return (*this) * vect;
}

Matrix4 Matrix4::operator   *  (float scalar)const{
	return Matrix4(m00*scalar,m01*scalar,m02*scalar,m03*scalar,
				   m10*scalar,m11*scalar,m12*scalar,m13*scalar,
				   m20*scalar,m21*scalar,m22*scalar,m23*scalar,
				   m30*scalar,m31*scalar,m32*scalar,m33*scalar);
}
Matrix4 Matrix4::operator   *= (float scalar){
	return (*this) *scalar;
}

//End Of File