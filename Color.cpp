#include "Color.h"


const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::GREY = Color(0.5f, 0.5f, 0.5f);
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::RED = Color(1.0f, 0.0f, 0.0f);
const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f);
const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f);


Color::Color()
{
	data[0] = data[1] = data[2] = data[3] = 0.0f;
}

Color::Color(float red, float green, float blue) :
r(red), g(green), b(blue), a(0.0f)
{}

Color::Color(float red, float green, float blue, float alpha) :
r(red), g(green), b(blue), a(alpha)
{}

// This ONLY copies 3 floats!!!
Color::Color(float* c) :
r(*c), g(*c + 1), b(*c + 2)
{}

Color::Color(__m128 &v)
{
	xmm = v;
}

Color::Color(const Color &rhs) : xmm(rhs.xmm)
{}