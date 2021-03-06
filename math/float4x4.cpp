#include "float4x4.h"

float4x4::float4x4()
{
	memset(m,0,sizeof(double)*16);
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

float4x4::float4x4(double t[])
{
	memcpy(m, t, sizeof(double)*16);
}

float4x4::float4x4(float3x3 mat)
{
	/*fillMat(mat.m[0], mat.m[1], 0, mat.m[2],
			mat.m[3], mat.m[4], 0, mat.m[5],
			mat.m[6], mat.m[7], 1, mat.m[8],
			0, 0, 0, 1);*/

	m[0] = mat.m[0];
	m[1] = mat.m[1];
	m[2] = mat.m[2];
	m[3] = 0;
	
	m[4] = mat.m[3];
	m[5] = mat.m[4];
	m[6] = mat.m[5];
	m[7] = 0;
	
	m[8] = 0;
	m[9] = 0;
	m[10]= 1;
	m[11]= 0;
	
	m[12]= mat.m[6];
	m[13]= mat.m[7];
	m[14]= 0; // was mat.m[8]
	m[15]= 1;
}

float4x4::float4x4(double m0, double m1, double m2, double m3,
				double m4, double m5, double m6, double m7,
				double m8, double m9, double m10, double m11,
				double m12, double m13, double m14, double m15)
{
	m[0]  = m0;
	m[1]  = m1;
	m[2]  = m2;
	m[3]  = m3;

	m[4]  = m4;
	m[5]  = m5;
	m[6]  = m6;
	m[7]  = m7;

	m[8]  = m8;
	m[9]  = m9;
	m[10] = m10;
	m[11] = m11;

	m[12] = m12;
	m[13] = m13;
	m[14] = m14;
	m[15] = m15;
}

float4x4::~float4x4()
{
}

void float4x4::fillMat(float4x4 matrix)
{
	for(int i=0; i<16; i++)
		m[i] = matrix.m[i];
}

void float4x4::fillMat(double m0, double m1, double m2, double m3,
					double m4, double m5, double m6, double m7,
					double m8, double m9, double m10, double m11,
					double m12, double m13, double m14, double m15)
{
	m[0]  = m0;
	m[1]  = m1;
	m[2]  = m2;
	m[3]  = m3;

	m[4]  = m4;
	m[5]  = m5;
	m[6]  = m6;
	m[7]  = m7;

	m[8]  = m8;
	m[9]  = m9;
	m[10] = m10;
	m[11] = m11;

	m[12] = m12;
	m[13] = m13;
	m[14] = m14;
	m[15] = m15;
}

void float4x4::print()
{
	cout << m[0] << ' ' << m[4] << ' ' << m[8] << ' ' << m[12]<< endl;
	cout << m[1] << ' ' << m[5] << ' ' << m[9] << ' ' << m[13]<< endl;
	cout << m[2] << ' ' << m[6] << ' ' << m[10]<< ' ' << m[14]<< endl;
	cout << m[3] << ' ' << m[7] << ' ' << m[11]<< ' ' << m[15]<< endl;
}

void		float4x4::operator=(float4x4 mat2)
{
	memcpy(m,mat2.m,sizeof(float)*16);
}

float4x4	float4x4::operator+(float4x4 mat2)
{
	float4x4 temp;
	for(int x=0; x<16; x++)
		temp.m[x] = m[x] + mat2.m[x];
	return temp;
}

float4x4	float4x4::operator-(float4x4 mat2)
{
	for(int x=0; x<16; x++)
		mat2.m[x] = m[x] - mat2.m[x];
	return mat2;
}

float4x4	float4x4::operator*(float4x4 mat2)
{
	float4x4 temp;

	temp.m[0] = (m[0]*mat2.m[0]) + (m[4]*mat2.m[1]) + (m[8]*mat2.m[2]) + (m[12]*mat2.m[3]);
	temp.m[1] = (m[1]*mat2.m[0]) + (m[5]*mat2.m[1]) + (m[9]*mat2.m[2]) + (m[13]*mat2.m[3]);
	temp.m[2] = (m[2]*mat2.m[0]) + (m[6]*mat2.m[1]) + (m[10]*mat2.m[2])+ (m[14]*mat2.m[3]);
	temp.m[3] = (m[3]*mat2.m[0]) + (m[7]*mat2.m[1]) + (m[11]*mat2.m[2])+ (m[15]*mat2.m[3]);

	temp.m[4] = (m[0]*mat2.m[4]) + (m[4]*mat2.m[5]) + (m[8]*mat2.m[6]) + (m[12]*mat2.m[7]);
	temp.m[5] = (m[1]*mat2.m[4]) + (m[5]*mat2.m[5]) + (m[9]*mat2.m[6]) + (m[13]*mat2.m[7]);
	temp.m[6] = (m[2]*mat2.m[4]) + (m[6]*mat2.m[5]) + (m[10]*mat2.m[6])+ (m[14]*mat2.m[7]);
	temp.m[7] = (m[3]*mat2.m[4]) + (m[7]*mat2.m[5]) + (m[11]*mat2.m[6])+ (m[15]*mat2.m[7]);

	temp.m[8] = (m[0]*mat2.m[8]) + (m[4]*mat2.m[9]) + (m[8]*mat2.m[10]) + (m[12]*mat2.m[11]);
	temp.m[9] = (m[1]*mat2.m[8]) + (m[5]*mat2.m[9]) + (m[9]*mat2.m[10]) + (m[13]*mat2.m[11]);
	temp.m[10]= (m[2]*mat2.m[8]) + (m[6]*mat2.m[9]) + (m[10]*mat2.m[10])+ (m[14]*mat2.m[11]);
	temp.m[11]= (m[3]*mat2.m[8]) + (m[7]*mat2.m[9]) + (m[11]*mat2.m[10])+ (m[15]*mat2.m[11]);

	temp.m[12]= (m[0]*mat2.m[12]) + (m[4]*mat2.m[13]) + (m[8]*mat2.m[14]) + (m[12]*mat2.m[15]);
	temp.m[13]= (m[1]*mat2.m[12]) + (m[5]*mat2.m[13]) + (m[9]*mat2.m[14]) + (m[13]*mat2.m[15]);
	temp.m[14]= (m[2]*mat2.m[12]) + (m[6]*mat2.m[13]) + (m[10]*mat2.m[14])+ (m[14]*mat2.m[15]);
	temp.m[15]= (m[3]*mat2.m[12]) + (m[7]*mat2.m[13]) + (m[11]*mat2.m[14])+ (m[15]*mat2.m[15]);

	return temp;
}

float4x4	float4x4::operator*(double scalar)
{
	float4x4 temp;

	for(int x=0; x<16; x++)
		temp.m[x] = scalar * m[x];

	return temp;
}

Vector3		float4x4::operator*(Vector3 v)
{
	/*
	|x|   |Tx Ty Tz|   |Lx|
	|y| = |Bx By Bz| x |Ly|
	|z|   |Nx Ny Nz|   |Lz|
	*/
	Vector3 r;

	/*r.x = m[0]*v.x + m[1]*v.y + m[2]*v.z + m[3];
	r.y = m[4]*v.x + m[5]*v.y + m[6]*v.z + m[7];
	r.z = m[8]*v.x + m[9]*v.y + m[10]*v.z + m[11];*/
	r.x = m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12];
	r.y = m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13];
	r.z = m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14];

	return r;
}


float4x4 float4x4::adjoint()
{
	float4x4 mat;

	return mat;
}

float4x4 float4x4::transpose()
{
	float4x4 temp;

	temp.m[4] = m[1]; temp.m[8] = m[2]; temp.m[12] = m[3];
	temp.m[1] = m[4]; temp.m[9] = m[6]; temp.m[13] = m[7];
	temp.m[2] = m[8]; temp.m[6] = m[9]; temp.m[14] = m[11];
	temp.m[3] = m[12];temp.m[7] = m[13];temp.m[11]= m[14];

	return temp;
}

float4x4 float4x4::inverse()
{
	double det;
	double invDet;
	float4x4 mat;

	double s0 = m[0]*m[5] - m[1]*m[4];
	double s1 = m[0]*m[9] - m[1]*m[8];
	double s2 = m[0]*m[13]- m[1]*m[12];
	double s3 = m[4]*m[9] - m[5]*m[8];
	double s4 = m[4]*m[13]- m[5]*m[12];
	double s5 = m[8]*m[13]- m[9]*m[12];

	double c0 = m[2]*m[7]  - m[3]*m[6];
	double c1 = m[2]*m[11] - m[3]*m[10];
	double c2 = m[2]*m[15] - m[3]*m[14];
	double c3 = m[6]*m[11] - m[7]*m[10];
	double c4 = m[6]*m[15] - m[7]*m[14];
	double c5 = m[10]*m[15]- m[11]*m[14];

	det = s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;

	if(fabs(det) < 0.001)
		return mat;

	invDet = 1.0f/det;

	/*
	+a11c5 − a12c4 + a13c3		−a01c5 + a02c4 − a03c3		+a31s5 − a32s4 + a33s3		−a21s5 + a22s4 − a23s3
	−a10c5 + a12c2 − a13c1		+a00c5 − a02c2 + a03c1		−a30s5 + a32s2 − a33s1		+a20s5 − a22s2 + a23s1
	+a10c4 − a11c2 + a13c0		−a00c4 + a01c2 − a03c0		+a30s4 − a31s2 + a33s0		−a20s4 + a21s2 − a23s0
	−a10c3 + a11c1 − a12c0		+a00c3 − a01c1 + a02c0		−a30s3 + a31s1 − a32s0		+a20s3 − a21s1 + a22s0

	00 01 02 03		0  4  8  12
	10 11 12 13		1  5  9  13
	20 21 22 23		2  6  10 14
	30 31 32 33		3  7  11 15
	*/

	mat.m[0] = +m[5]*c5 - m[9]*c4  + m[13]*c3;
	mat.m[1] = -m[4]*c5 + m[8]*c4  - m[12]*c3;
	mat.m[2] = +m[7]*s5 - m[11]*s4 + m[15]*s3;
	mat.m[3] = -m[6]*s5 + m[10]*s4 - m[14]*s3;

	mat.m[4] = -m[1]*c5 + m[9]*c2  - m[13]*c1;
	mat.m[5] = +m[0]*c5 - m[8]*c2  + m[12]*c1;
	mat.m[6] = -m[3]*s5 + m[11]*s2 - m[15]*s1;
	mat.m[7] = +m[2]*s5 - m[10]*s2 + m[14]*s1;

	mat.m[8] = +m[1]*c4 - m[5]*c2 + m[13]*c0;
	mat.m[9] = -m[0]*c4 + m[4]*c2 - m[12]*c0;
	mat.m[10]= +m[3]*s4 - m[7]*s2 + m[15]*s0;
	mat.m[11]= -m[2]*s4 + m[6]*s2 - m[14]*s0;

	mat.m[12]= -m[1]*c3 + m[5]*c1 - m[9]*c0;
	mat.m[13]= +m[0]*c3 - m[4]*c1 + m[8]*c0;
	mat.m[14]= -m[3]*s3 + m[7]*s1 - m[11]*s0;
	mat.m[15]= +m[2]*s3 - m[6]*s1 + m[10]*s0;

	mat.m[0] *= invDet;
	mat.m[1] *= invDet;
	mat.m[2] *= invDet;
	mat.m[3] *= invDet;

	mat.m[4] *= invDet;
	mat.m[5] *= invDet;
	mat.m[6] *= invDet;
	mat.m[7] *= invDet;

	mat.m[8] *= invDet;
	mat.m[9] *= invDet;
	mat.m[10]*= invDet;
	mat.m[11]*= invDet;

	mat.m[12]*= invDet;
	mat.m[13]*= invDet;
	mat.m[14]*= invDet;
	mat.m[15]*= invDet;


	return mat;
}

inline double float4x4::determinant2x2(double m[])
{
	double det = (m[0]*m[3]) - (m[1]*m[2]);
	return det;
}

inline double float4x4::determinant3x3(double m[])
{
	double det1 = 0;
	double det2 = 0;
	double det3 = 0;

	double mat2x2[4];

	mat2x2[0] = m[4]; mat2x2[2] = m[7];
	mat2x2[1] = m[5]; mat2x2[3] = m[8];
	det1 = (determinant2x2(mat2x2) * m[0]);

	mat2x2[0] = m[1]; mat2x2[2] = m[7];
	mat2x2[1] = m[2]; mat2x2[3] = m[8];
	det2 = (determinant2x2(mat2x2) * m[3]);

	mat2x2[0] = m[1]; mat2x2[2] = m[4];
	mat2x2[1] = m[2]; mat2x2[3] = m[5];
	det3 = (determinant2x2(mat2x2) * m[6]);

	return det1 - det2 + det3;
}

double float4x4::determinant()
{
	//Laplace Expansion Theorem
	double s0 = m[0]*m[5] - m[1]*m[4];
	double s1 = m[0]*m[9] - m[1]*m[8];
	double s2 = m[0]*m[13]- m[1]*m[12];
	double s3 = m[4]*m[9] - m[5]*m[8];
	double s4 = m[4]*m[13]- m[5]*m[12];
	double s5 = m[8]*m[13]- m[9]*m[12];

	double c0 = m[2]*m[7]  - m[3]*m[6];
	double c1 = m[2]*m[11] - m[3]*m[10];
	double c2 = m[2]*m[15] - m[3]*m[14];
	double c3 = m[6]*m[11] - m[7]*m[10];
	double c4 = m[6]*m[15] - m[7]*m[14];
	double c5 = m[10]*m[15]- m[11]*m[14];

	return s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;
}

void float4x4::makeIdentity()
{
	memset(m, 0, sizeof(double)*16);
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

float4x4 float4x4::rotate(double angle, double x, double y, double z)
{
	float4x4 mat = float4x4(m);

	double ct = cos(angle);	// 7
	double st = sin(angle);	// 6
	double t = 1 - ct;		// 3
	double xz = x * z;		// 2
	double xy = x * y;		// 2
	double yz = y * z;		// 2
	double xst = x * st;		// 2
	double yst = y * st;		// 2
	double zst = z * st;		// 2

	mat.m[0] = ct + (x*x * ct);
	mat.m[1] = xy * ct + zst;
	mat.m[2] = xz * ct - yst;

	mat.m[4] = xy * ct - zst;
	mat.m[5] = ct + y*y * t;
	mat.m[6] = yz * t + xst;

	mat.m[8] = xz * t + yst;
	mat.m[9] = yz * t - xst;
	mat.m[10]= ct + z*z * t;

	return mat;
}