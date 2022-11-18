#pragma once
#include <cmath>

namespace nbp
{
	struct Vector2
	{
		// Vector's x component
		float x;

		// Vector's y component
		float y;

	public:
		Vector2();

		// Constructor to initialize values for each component
		Vector2(float iX, float iY);

		// Returns the sum of two vectors
		Vector2 operator+(const Vector2& V) const;

		// Returns the difference of two vectors
		Vector2 operator-(const Vector2& V) const;

		// Returns the component-wise product of two vectors
		Vector2 operator*(const Vector2& V) const;

		// Returns the component-wise division of two vectors
		Vector2 operator/(const Vector2& V) const;

		// Assignment operator
		void operator=(const Vector2& V);

		// Adds a number to each component of the vector
		Vector2 operator+(const float n) const;

		// Subtracts a number from each component of the vector
		Vector2 operator-(const float n) const;

		// Multiplies each component by a const;
		Vector2 operator*(const float n) const;

		Vector2 operator-();

		void operator+=(const Vector2& V);

		void operator-=(const Vector2& V);

		void operator*=(const Vector2& V);

		//Rotates
		Vector2 rotate(Vector2 center, float angleDeg);

		// Returns the magnitude of vector of type T
		float getLength() const;

		// Returns the squared magnitude of the vector of type T
		float getLengthSquared() const;

		// Takes the dot product of with vector V, returns a scalar of T
		float dot(const Vector2& V) const;

		float dot(const Vector2& V, const Vector2& W);

		// Normalizes the vector so it's magnitude is 1
		void normalize();

		// Returns the value of x or y 
		float index(int i) const;

		// Returns a normalized vector
		Vector2 getNormal() const;

		float distance(const Vector2& V);
	};

}