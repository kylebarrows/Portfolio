#include "../../includes/collisions/Broadphase.h"
#include "../../includes/collisions/AABB.h"
#include "../../includes/RigidBody.h"
#include <iostream>
#include <algorithm>

namespace nbp
{
	Broadphase::Broadphase()
	{
	}

	// Function used to sort the bodies into ascending order along the x-axis
	bool compareAABB(const void* a, const void* b)
	{
		const RigidBody* rb1 = (RigidBody*)a;
		const RigidBody* rb2 = (RigidBody*)b;
		const AABB c = rb1->getAABB();
		const AABB d = rb2->getAABB();
		return c.m_min.x < d.m_min.x;
	}

	// Broadphase using the sweep and prune algorithm, sorts the bodies based on their position 
	// on the x-axis and places them into pairs that could be colliding
	std::vector<Pair> Broadphase::sweepAndPrune(std::vector<RigidBody*>& bodies)
	{
		// Sort the bodies into ascending order along the x axis
		std::sort(bodies.begin(), bodies.end(), compareAABB);

		// Possible collision pairs
		std::vector<Pair> pairs;
		std::vector<RigidBody*> activeList;

		for (int i = 0; i < bodies.size(); i++)
		{
			for (int j = 0; j < activeList.size(); j++)
			{
				AABB a = bodies[i]->getAABB();
				AABB b = activeList[j]->getAABB();

				// Check if the objects are separated on the x-axis
				if (a.m_min.x > b.m_max.x)
				{
					activeList.erase(activeList.begin() + j);
					j--;
				}
				else
				{
					Pair pair;
					pair.a = bodies[i];
					pair.b = activeList[j];
					
					// prevent bodies from colliding with self
					if (pair.a == pair.b)
					{
						continue;
					}
					pairs.push_back(pair);
				}
			}

			activeList.push_back(bodies[i]);
		}

		return pairs;
	}


	

}
