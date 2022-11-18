#include <cmath>
#include "Vector2.h"

#define SMALL_NUMBER (0.0001)
#define PI (3.1415926535)
#define e (2.71828182)
#define sqrt2()

namespace nbp
{
	namespace NMath
	{
		float Min(float f1, float f2);

		float Dot(Vector2 v1, Vector2 v2);

		float Cross(Vector2 v1, Vector2 v2);

		Vector2 Cross(float f, Vector2 v);

		bool NearlyZero(float f);

		bool NearlyEqual(float f1, float f2);

		bool NearlyEqual(Vector2 v1, Vector2 v2);

		float Clamp(float f, float minimum, float maximum);
	}
}