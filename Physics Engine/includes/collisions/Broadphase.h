#pragma once
#include <vector>


const int MAX_OBJECTS = 100;

namespace nbp
{
	class RigidBody;
	class AABB;

	struct Pair
	{
		RigidBody* a;
		RigidBody* b;
	};

	class Broadphase
	{
	public:
		Broadphase();

		std::vector<Pair> sweepAndPrune(std::vector<RigidBody*>& bodies);

	private:

		friend bool compareAABB(const void* a, const void* b);
	};
}