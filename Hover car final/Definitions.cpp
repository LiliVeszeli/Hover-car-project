#include "Definitions.h"

//calculates the scalar of a certain number
vector2D scalar(float s, vector2D v)
{
	return { s * v.x, s* v.z };
}

//calucates the sum of 3 numbers
vector2D sum3(vector2D v1, vector2D v2, vector2D v3)
{
	return { v1.x + v2.x + v3.x, v1.z + v2.z + v3.z };
}
