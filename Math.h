#ifndef MATH_H
#define MATH_H

#define DEGREE_TO_RAD 0.01745329251994329576923690768489
#define RAD_TO_DEGREE 57.295779513082320876798154814105

class Vector2
{
public:
	float x;
	float y;

	Vector2()
	{
		x = y = 0;
	}
	Vector2(float X, float Y)
	{
		x = X;
		y = Y;
	}
};

#endif