#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <emmintrin.h>

#include <iostream>

using namespace std;


class Color
{
public:
#if 1	// Constructors
	Color();
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, float alpha);
	Color(float* c);	// This ONLY copies 3 floats!!!
	Color(__m128 &v);
	Color(const Color &rhs);
#endif 	// Constructors

#if 1	// Operator Region
	inline Color operator+(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(rhs);
		return Color(_mm_add_ps(xmm, scalar));
	}

	inline Color operator-(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(rhs);
		return Color(_mm_sub_ps(xmm, scalar));
	}

	inline Color operator*(float rhs) const
	{
		__m128 scalar = _mm_set1_ps(rhs);
		return Color(_mm_mul_ps(xmm, scalar));
	}

	inline Color operator+(const Color &rhs) const
	{
		return Color(_mm_add_ps(xmm, rhs.xmm));
	}

	inline Color operator-(const Color &rhs) const
	{
		return Color(_mm_sub_ps(xmm, rhs.xmm));
	}

	inline Color operator*(const Color &rhs) const
	{
		return Color(_mm_mul_ps(xmm, rhs.xmm));
	}
#endif	// Operator Region

	inline Color saturate() const
	{
		/*R = R > 1.0f ? 1.0f : R;
		R = R < 0.0f ? 0.0f : R;*/
		Color c;

		c.xmm = _mm_min_ps(xmm, _mm_set1_ps(1.0f));
		c.xmm = _mm_max_ps(c.xmm, _mm_set1_ps(0.0f));

		return c;
	}

	Color rgbToHSV() const
	{
		/*
		vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
		vec4 p = c.g < c.b ? vec4(c.bg, K.wz) : vec4(c.gb, K.xy);
		vec4 q = c.r < p.x ? vec4(p.xyw, c.r) : vec4(c.r, p.yzx);

		float d = q.x - min(q.w, q.y);
		float e = 1.0e-10;
		return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
		*/
		Color k = Color(0.0f, -1.0f / 3.0f, 2.0f / 3.0f, -1.0f);
		Color p = g < b ? Color(b, g, k.a, k.b) : Color(g, b, k.r, k.g);
		Color q = r < p.r ? Color(p.r, p.g, p.a, r) : Color(r, p.g, p.b, p.r);

		float d = q.r - min(q.a, q.g);
		float e = (float)1.0e-10;
		return Color(abs(q.b + (q.a - q.g) / (6.0f * d + e)), d / (q.r + e), q.r);
	}

	//Color hsvToRGB() const
	//{
	//	//1: vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	//	//Color K = Color(1.0f, 2.0f / 3.0f, 1.0f / 3.0f, 3.0f);
	//	__m128 k = _mm_set_ps(1.0f, 2.0f / 3.0f, 1.0f / 3.0f, 3.0f);
	//	Color hsv = Color(h/360.0f, s/100.0f, v/100.0f);
	//	hsv.printHSV();
	//	
	//	//2: vec3 p = abs(fract(rrr + K.rgb) * 6.0 - K.aaa);
	//	__m128 p = _mm_add_ps(_mm_set1_ps(hsv.r), k);			// p = rrr + K.rgb
	//	p.m128_f32[3] = 0.0f;									// 4th component should be 0
	//	p = _mm_sub_ps(p, _mm_floor_ps(p));						// p = fract(rrr + K.rgb) = fract(p)
	//	p = _mm_mul_ps(p, _mm_set1_ps(6.0f));					// p * 6.0
	//	p = _mm_sub_ps(p, _mm_set1_ps(k.m128_f32[3]));			// p - K.aaa
	//	__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	//	p = _mm_andnot_ps(mask, p);								// abs(p * 6.0 - K.aaa)
	//	printf("   p = [%3.3f %3.3f %3.3f %3.3f]\n", p.m128_f32[0], p.m128_f32[1], p.m128_f32[2], p.m128_f32[3]);

	//	//3: b * mix(Kr, clamp(p - Kr, 0.0, 1.0), y);
	//	__m128 kr = _mm_set1_ps(k.m128_f32[3]);

	//	// clamp(p.rgb - Kr, 0.0, 1.0)
	//	__m128 ret = _mm_sub_ps(p, kr);							// p.rgb - Kr
	//	ret = _mm_min_ps(ret, _mm_set1_ps(1.0f));				// clamp to max of 1
	//	ret = _mm_max_ps(ret, _mm_set1_ps(0.0f));				// clamp to min of 0

	//	// mix(Kr, tc, g)
	//	__m128 x = _mm_mul_ps(kr, _mm_set1_ps(1.0f - hsv.g));	// kr*(1-a)
	//	__m128 y = _mm_mul_ps(ret, _mm_set1_ps(hsv.g));			// clamp()*a
	//	ret = _mm_add_ps(x, y);									// x*(1-a) + y*a

	//	ret = _mm_mul_ps(_mm_set1_ps(hsv.b), ret);				// b * mix(Kr, tc, g)

	//	printf("   ret = [%3.3f %3.3f %3.3f %3.3f]\n", ret.m128_f32[0], ret.m128_f32[1], ret.m128_f32[2], ret.m128_f32[3]);

	//	return Color(ret);
	//}

	Color FASThsvToRGB() const
	{
		__m128 k = _mm_setr_ps(1.0f / 3.0f, 2.0f / 3.0f, 1.0f, 3.0f);	// z, y, x, w

		float H = fmod(h / 360.0f, 360.0f);
		float S = s / 100.0f;
		float V = v / 100.0f;

		// = abs(fract(c.rrr + K.rgb) * 6.0 - K.aaa);
		__m128 hue = _mm_set1_ps(H);
		__m128 p = _mm_add_ps(hue, k);								// c.rrr + K.rgb
		p = _mm_sub_ps(p, _mm_floor_ps(p));							// fract(c.rrr + K.rgb)
		p = _mm_mul_ps(p, _mm_set1_ps(6.0f));
		p = _mm_sub_ps(p, _mm_set1_ps(k.m128_f32[3]));
		__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
		p = _mm_andnot_ps(mask, p);									// abs(p * 6.0 - K.aaa)

		// clamp(p.rgb - K.rrr, 0.0, 1.0)
		__m128 clamp = _mm_sub_ps(p, _mm_set1_ps(1.0f));			// p.rgb - K.rrr
		clamp = _mm_min_ps(clamp, _mm_set1_ps(1.0f));				// clamp to max of 1
		clamp = _mm_max_ps(clamp, _mm_set1_ps(0.0f));				// clamp to min of 0

		// c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
		__m128 ret;
		__m128 x = _mm_set1_ps(k.m128_f32[2] * (1.0f - S));
		__m128 y = _mm_mul_ps(clamp, _mm_set1_ps(S));
		ret = _mm_add_ps(x, y);
		ret = _mm_mul_ps(ret, _mm_set1_ps(V));

		return Color(ret.m128_f32[2] * 255.0f, ret.m128_f32[1] * 255.0f, ret.m128_f32[0] * 255.0f);
	}

	Color hsvToRGB() const
	{
		Color K = Color(1.0f, 2.0f / 3.0f, 1.0f / 3.0f, 3.0f);

		float H = h / 360.0f;
		float S = s / 100.0f;
		float V = v / 100.0f;

		Color p;	// = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
		p.r = abs(((H + K.r - floor(H + K.r)) * 6.0f) - K.a);
		p.g = abs(((H + K.g - floor(H + K.g)) * 6.0f) - K.a);
		p.b = abs(((H + K.b - floor(H + K.b)) * 6.0f) - K.a);

		Color clamp;	// = clamp(p - K.xxx, 0.0, 1.0)
		clamp.r = p.r - K.r;
		clamp.g = p.g - K.r;
		clamp.b = p.b - K.r;
		clamp.r = clamp.r <= 0.0f ? 0.0f : clamp.r;
		clamp.g = clamp.g <= 0.0f ? 0.0f : clamp.g;
		clamp.b = clamp.b <= 0.0f ? 0.0f : clamp.b;
		clamp.r = clamp.r >= 1.0f ? 1.0f : clamp.r;
		clamp.g = clamp.g >= 1.0f ? 1.0f : clamp.g;
		clamp.b = clamp.b >= 1.0f ? 1.0f : clamp.b;

		Color ret;	// c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
		ret.r = V * (K.r*(1.0f - S) + clamp.r*S);
		ret.g = V * (K.r*(1.0f - S) + clamp.g*S);
		ret.b = V * (K.r*(1.0f - S) + clamp.b*S);

		return Color(ret.r * 255.0f, ret.g * 255.0f, ret.b * 255.0f);
	}

	Color rgbToHCV() const
	{
		float eps = 1e-10f;

		// Based on work by Sam Hocevar and Emil Persson
		Color p = (g < b) ? Color(b, g, -1.0f, 2.0f / 3.0f) : Color(g, b, 0.0f, -1.0f / 3.0f);
		Color q = (r < p.r) ? Color(p.r, p.g, p.a, r) : Color(r, p.g, p.b, p.r);
		float c = q.r - min(q.a, q.g);
		float hue = abs((q.a - q.g) / (6 * c + eps) + q.b);
		return Color(hue, c, q.r);
	}

	/*Color rgbToHSV() const
	{
	float eps = 1e-10f;
	Color hcv = rgbToHCV();
	float sat = hcv.g / (hcv.b + eps);
	return Color(hcv.r, sat, hcv.b);
	}*/

	static inline Color lerp(Color &a, Color &b, float t)
	{
		return _mm_add_ps(_mm_mul_ps(_mm_sub_ps(b.xmm, a.xmm), _mm_set1_ps(t)), a.xmm);
	}

	void printRGB()
	{
		//printf("RGB: [%3.3f %3.3f %3.3f]\n", r*255.0f, g*255.0f, b*255.0f);
		printf("RGB: [%3.3f %3.3f %3.3f]\n", r, g, b);
	}

	void printHSV()
	{
		printf("HSV: [%3.3f %3.3f %3.3f]\n", h, s, v);
	}

	static Color hueToRGB(float hue)
	{
		Color c;
		c.r = abs(hue * 6 - 3) - 1;
		c.g = 2 - abs(hue * 6 - 2);
		c.b = 2 - abs(hue * 6 - 4);
		return c.saturate();
	}

#if 1 // Color constants
	static const Color WHITE;
	static const Color GREY;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
#endif

	union
	{
		__m128	xmm;
		float	data[4];
		struct { float r; float g; float b; float a; };
		struct { float h; float s; float v; float a; };
	};
};

#endif