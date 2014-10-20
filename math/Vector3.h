#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <emmintrin.h>

#include <iostream>

using namespace std;


class Vector3
{
public:
#if 1	// Constructors
	Vector3() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	Vector3(float x, float y, float z) :
		x(x), y(y), z(z), w(0.0f)
	{}

	Vector3(float x, float y, float z, float w) :
		x(x), y(y), z(z), w(w)
	{}

	Vector3(float* v) :
		x(*v), y(*v + 1), z(*v + 2), w(0.0f)
	{}

	Vector3(__m128 &v) : xmm(v)
	{}

	Vector3(const Vector3 &rhs) : xmm(rhs.xmm)
	{}
#endif 	// Constructors

#if 1	// Operator Region
	inline Vector3 operator+(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(rhs);
		return Vector3(_mm_add_ps(xmm, scalar));
	}

	inline Vector3 operator-(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(rhs);
		return Vector3(_mm_sub_ps(xmm, scalar));
	}

	inline Vector3 operator*(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(rhs);
		return Vector3(_mm_mul_ps(xmm, scalar));
	}

	inline Vector3 operator/(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(1.0f / rhs);
		return Vector3(_mm_mul_ps(xmm, scalar));
	}

	inline Vector3 operator+(const Vector3 &rhs) const
	{
		return Vector3(_mm_add_ps(xmm, rhs.xmm));
	}

	inline Vector3 operator-(const Vector3 &rhs) const
	{
		return Vector3(_mm_sub_ps(xmm, rhs.xmm));
	}

	inline Vector3 operator*(const Vector3 &rhs) const
	{
		return Vector3(_mm_mul_ps(xmm, rhs.xmm));
	}
#endif	// Operator Region

	inline float dot(Vector3 &rhs) const
	{
		// 0x71 = 0111 0001 (use lower 3 floats and store in lower float)
		return _mm_cvtss_f32(_mm_dp_ps(xmm, rhs.xmm, 0x71));
	}

	inline float length() const
	{
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(xmm, xmm, 0x71)));
	}

	inline Vector3 normal() const
	{
		// find invSqrt and store in lower 3 floats
		__m128 invNormal = _mm_rsqrt_ss(_mm_dp_ps(xmm, xmm, 0x77));
		return _mm_mul_ps(xmm, invNormal);
	}

	inline Vector3 normal_accurate() const
	{
		__m128 norm = _mm_sqrt_ps(_mm_dp_ps(xmm, xmm, 0x7F));
		return _mm_div_ps(xmm, norm);
	}

	inline void normalize()
	{
		// find invSqrt and store in lower 3 floats
		__m128 invNormal = _mm_rsqrt_ss(_mm_dp_ps(xmm, xmm, 0x77));
		xmm = _mm_mul_ps(xmm, invNormal);
	}

	inline void normalize_accurate()
	{
		__m128 norm = _mm_sqrt_ps(_mm_dp_ps(xmm, xmm, 0x7F));
		xmm = _mm_div_ps(xmm, norm);
	}

	inline Vector3 cross_product(Vector3 &rhs) const
	{
		// TODO: Can be made faster with SSE instructions
		return Vector3(y * rhs.z - z * rhs.y,
						z * rhs.x - x * rhs.z,
						x * rhs.y - y * rhs.x);
	}

	static inline Vector3 lerp(Vector3 &a, Vector3 &b, float t)
	{
		return _mm_add_ps(_mm_mul_ps(_mm_sub_ps(b.xmm, a.xmm), _mm_set1_ps(t)), a.xmm);
		/*return Vector3(((b.x - a.x) * t) + a.x,
						((b.y - a.y) * t) + a.y,
						((b.z - a.z) * t) + a.z);*/
	}

	inline Vector3 reflect(Vector3 &n) const
	{
		// float nDotI = dot(n) * 2.0f;
		__m128 nDotI = _mm_mul_ps(_mm_dp_ps(xmm, n.xmm, 0x77), _mm_set1_ps(2.0f));

		// return (n * nDotI) - xmm;
		return _mm_sub_ps(_mm_mul_ps(n.xmm, nDotI), xmm);
	}
	
	void print()
	{
		printf("Vector3: [%3.3f %3.3f %3.3f]\n", x, y, z);
	}

	union
	{
		__m128	xmm;
		float	data[4];
		struct { float x; float y; float z; float w; };
	};
};

#endif