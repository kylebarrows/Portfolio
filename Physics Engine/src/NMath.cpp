#include "../includes/NMath.h"

namespace nbp
{
	namespace NMath
	{
		float Min(float f1, float f2)
		{
			return f1 < f2 ? f1 : f2;
		}

		float Dot(Vector2 v1, Vector2 v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		float Cross(Vector2 v1, Vector2 v2)
		{
			return v1.x * v2.y - v1.y * v2.x;
		}

		Vector2 Cross(float f, Vector2 v)
		{
			return Vector2(-f * v.y, f * v.x);
		}

		bool NearlyZero(float f)
		{
			return std::abs(f) < SMALL_NUMBER;
		}

		bool NearlyEqual(float f1, float f2)
		{
			return std::abs(f1 - f2) < SMALL_NUMBER;
		}

		bool NearlyEqual(Vector2 v1, Vector2 v2)
		{
			return v1.distance(v2) < SMALL_NUMBER * SMALL_NUMBER;
		}

		float Clamp(float f, float minimum, float maximum)
		{
			if (f > maximum)
			{
				return maximum;
			}
			else if (f < minimum)
			{
				return minimum;
			}

			return f;
		}

	}
}



