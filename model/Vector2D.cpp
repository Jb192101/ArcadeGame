#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
	return Vector2D(x + other.x, y + other.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

float Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalized() const {
    float len = length();
    if (len > 0) {
        return Vector2D(x / len, y / len);
    }
    return *this;
}

Vector2D Vector2D::rotated(float angle) const {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    return Vector2D(
        x * cosA - y * sinA,
        x * sinA + y * cosA
    );
}

float Vector2D::getX()
{
    return this->x;
}

float Vector2D::getY()
{
    return this->y;
}

void Vector2D::setX(float x) {
    this->x = x;
}

void Vector2D::setY(float y) {
    this->y = y;
}