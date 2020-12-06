#pragma once
struct Vector2
{
	float x;
	float y;

	/*Vector2(float newx, float newy)
	{
		x = newx;
		y = newy;
	}*/
	Vector2& operator +=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator -=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}
	
	

};

