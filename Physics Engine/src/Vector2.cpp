#include "../includes/Vector2.h"
#include "../includes/NMath.h"

namespace nbp
{
Vector2::Vector2()
	:x(0.0), y(0.0)
{
}

Vector2::Vector2(float iX, float iY)
	:x(iX), y(iY)
{
}

Vector2 Vector2::operator+(const Vector2& V) const
{
	return Vector2(x + V.x, y + V.y);
}

Vector2 Vector2::operator-(const Vector2& V) const
{
	return Vector2(x - V.x, y - V.y);
}

void Vector2::operator-=(const Vector2& V)
{
	x -= V.x;
	y -= V.y;
}

void Vector2::operator+=(const Vector2& V)
{
	x += V.x;
	y += V.y;
}

Vector2 Vector2::operator*(const Vector2& V) const
{
	return Vector2(x * V.x, y * V.y);
}

Vector2 Vector2::operator*(const float n) const
{
	return Vector2(x * n, y * n);
}

Vector2 Vector2::operator/(const Vector2& V) const
{
	return Vector2(x / V.x, y / V.y);
}

Vector2 Vector2::operator+(const float n) const
{
	return Vector2(x + n, y + n);
}

Vector2 Vector2::operator-(const float n) const
{
	return Vector2(x - n, y - n);
}

void Vector2::operator=(const Vector2& V)
{
	x = V.x;
	y = V.y;
}

void Vector2::operator*=(const Vector2& V)
{
	x *= V.x;
	y *= V.y;
}

Vector2 Vector2::rotate(Vector2 center, float angleDeg)
{
	const Vector2 dist = *this - center;

	const float cos_angle = std::cos(angleDeg * PI / 180.0);
	const float sin_angle = std::sin(angleDeg * PI / 180.0);

	const Vector2 newLoc = {
		(dist.x * cos_angle) - (dist.y * sin_angle) + center.x,
		(dist.y * cos_angle) + (dist.x * sin_angle) + center.y
	};

	return newLoc;
}

void Vector2::normalize()
{
	float temp = x * x;
	const float invLength = 1 / getLength();
	x *= invLength;
	y *= invLength;
}

float Vector2::index(int i) const
{
	return i == 0 ? x : y;
}

float Vector2::getLength() const
{
	return std::sqrt((x * x) + (y * y));
}

float Vector2::dot(const Vector2& V) const
{
	return (x * V.x) + (y * V.y);
}

float Vector2::dot(const Vector2& V, const Vector2& W)
{
	return V.x * W.x + V.y * W.y;
}

float Vector2::getLengthSquared() const
{
	return (x * x) + (y * y);
}

Vector2 Vector2::getNormal() const
{
	if (getLength() == 0)
	{
		int i = 0;
	}
	const float invLength = 1 / getLength();
	return Vector2(x * invLength, y * invLength);
}

float Vector2::distance(const Vector2& V)
{
	Vector2 dist = V - *this;
	return dist.getLength();
}

}
