#pragma once

#include <cmath>

class Vector2D {
private:
	float x;
	float y;
public:
	Vector2D();
	Vector2D(float x, float y);

	Vector2D operator+(const Vector2D& other) const;
	Vector2D& operator+=(const Vector2D& other);
	Vector2D operator*(float scalar) const;
	float length() const;
	Vector2D normalized() const;
	Vector2D rotated(float angle) const; // Поворот (в радианах)

	float getX();
	float getY();

	void setY(float y);
	void setX(float x);
};
