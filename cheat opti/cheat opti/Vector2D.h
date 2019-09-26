#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D() = default;

	float x = 0.0;
	float y = 0.0;
};

