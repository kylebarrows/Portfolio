#include "../includes/World.h"

namespace nbp
{ 

World::World()
{
}

World::~World()
{
	for (int i = 0; i < m_RigidBodies.size(); i++)
	{
		delete m_RigidBodies[i];
	}
}

RigidBody* World::createBody(Vector2 pos, Vector2 scale, float rotDeg, float restitution, float friciton)
{
	RigidBody* rb = new RigidBody(pos, scale, rotDeg, restitution, friciton);
	registerBody(rb);

	return rb;
}

// Registers a rigidbody with world
void World::registerBody(RigidBody* rb)
{
	m_RigidBodies.push_back(rb);
}

// Removes a rigidbody from world
void World::removeBody(RigidBody* rb)
{
	for (auto it = m_RigidBodies.begin(); it != m_RigidBodies.end(); it++)
	{
		if (*it == rb)
		{
			m_RigidBodies.erase(it);
		}
	}
}

void World::resolveCollisionWithAngularVelocity(RigidBody* rb1, RigidBody* rb2, Contact contact)
{
	int nContacts = 1;
	bool shouldApplyFriction = true;
	Vector2 contacts[2] = { contact.pos1, contact.pos2 };

	// Mix restitution
	float restitution = NMath::Min(rb1->Restitution(), rb2->Restitution());

	// Mix frictions
	float friction = (rb1->Friction() * rb2->Friction());

	// First separate the bodies so they no longer overlap
	rb1->move(contact.normal * contact.depth * -1);
	rb2->move(contact.normal * contact.depth);

	if (!NMath::NearlyEqual(contact.pos1, contact.pos2))
	{
		nContacts = 2;
	}

	for (int i = 0; i < nContacts; i++)
	{
		Vector2 v1 = rb1->getVelocityFromWorldPoint(contacts[i]);
		Vector2 v2 = rb2->getVelocityFromWorldPoint(contacts[i]);
		Vector2 rVelocity = v2 - v1;

		float relativeNormalVelocity = NMath::Dot(rVelocity, contact.normal);

		// Check if objects are already moving apart
		if (relativeNormalVelocity > 0)
		{
			continue;
		}

		Vector2 perpA = NMath::Cross(1.0, contacts[i] - rb1->getPos());
		Vector2 perpB = NMath::Cross(1.0, contacts[i] - rb2->getPos());

		float v1dotN = NMath::Dot(perpA, contact.normal);
		float v2dotN = NMath::Dot(perpB, contact.normal);

		// Formula for impulse taken from http://www.chrishecker.com/Rigid_Body_Dynamics
		float j = -(1 + restitution) * relativeNormalVelocity;
		j /= (rb1->InvMass() + rb2->InvMass() +
			(v1dotN * v1dotN) * rb1->InvInertia() +
			(v2dotN * v2dotN) * rb2->InvInertia());
		j /= nContacts;

		// Apply normal impulse
		rb1->applyImpulseAtPoint(contact.normal * -j, contacts[i]);
		rb2->applyImpulseAtPoint(contact.normal * j, contacts[i]);

		float fMax = j * friction;
		
		// Friction calculations
		Vector2 tangentDir = rVelocity - (contact.normal * NMath::Dot(rVelocity, contact.normal));
		if (NMath::NearlyZero(tangentDir.getLengthSquared()))
		{
			continue;
		}

		tangentDir.normalize();
		float v1dotT = NMath::Dot(perpA, tangentDir);
		float v2dotT = NMath::Dot(perpB, tangentDir);

		// Calculate friction impulse, not quite sure if this model is right
		// applying impulse in the tangent direction to prevent sliding
		float frictionImpulse = -NMath::Dot(rVelocity, tangentDir);
		frictionImpulse /= (rb1->InvMass() + rb2->InvMass() +
			(v1dotT * v1dotT) * rb1->InvInertia() +
			(v2dotT * v2dotT) * rb2->InvInertia());
		frictionImpulse /= nContacts;

		frictionImpulse = NMath::Clamp(frictionImpulse, -fMax, fMax);


		// Apply friction impulse
		rb1->applyImpulseAtPoint(tangentDir * -frictionImpulse, contacts[i]);
		rb2->applyImpulseAtPoint(tangentDir * frictionImpulse, contacts[i]);
	}

}

// Detects and resolves collisions
bool World::detectCollisions(float deltaTime)
{
	std::vector<Pair> pairs = broadphase.sweepAndPrune(m_RigidBodies);
	for (int i = 0; i < pairs.size(); i++)
	{
		RigidBody* rb1 = pairs[i].a;
		RigidBody* rb2 = pairs[i].b;
		Collider2D* c1 = rb1->getCollider();
		Collider2D* c2 = rb2->getCollider();

		if (rb1->getType() == nbp_static && rb2->getType() == nbp_static)
		{
			continue;
		}

		Contact contact;
		if (c1->getType() == Collider2D::colliderType::box)
		{
			Box2D* box = (Box2D*)c1;
			if (c2->getType() == Collider2D::colliderType::box)
			{
				Box2D* box2 = (Box2D*)c2;
				if (solver.boxVBox(box, rb1->getPos(), rb1->getRotation(),
					box2, rb2->getPos(), rb2->getRotation(), contact))
				{
					resolveCollisionWithAngularVelocity(rb1, rb2, contact);
				}
			}
			else if (c2->getType() == Collider2D::colliderType::circle)
			{
				Circle* circle = (Circle*)c2;
				if (solver.boxVCircle(circle, rb2->getPos(), circle->getRadius(),
					box, rb1->getPos(), rb1->getRotation(), contact))
				{
					resolveCollisionWithAngularVelocity(rb2, rb1, contact);
				}
			}
		}
		else if (c1->getType() == Collider2D::colliderType::circle)
		{
			Circle* circle = (Circle*)c1;
			if (c2->getType() == Collider2D::colliderType::box)
			{
				Box2D* box = (Box2D*)c2;
				if (solver.boxVCircle(circle, rb1->getPos(), circle->getRadius(),
					box, rb2->getPos(), rb2->getRotation(), contact))
				{
					resolveCollisionWithAngularVelocity(rb1, rb2, contact);
				}
				
			}
			else if (c2->getType() == Collider2D::colliderType::circle)
			{
				Circle* circle2 = (Circle*)c2;
				if (solver.circleVCircle(circle, rb1->getPos(), circle->getRadius(),
					circle2, rb2->getPos(), circle2->getRadius(), contact))
				{
					resolveCollisionWithAngularVelocity(rb1, rb2, contact);
				}
			}
		}
	}
	
	return false;
}

void World::ApplyForces()
{
	for (int i = 0; i < m_RigidBodies.size(); i++)
	{
		m_RigidBodies[i]->applyForce(nbp::Vector2(0.0, -2.0));
	}
}

void World::moveObjects(float deltaTime)
{
	for (int i = 0; i < m_RigidBodies.size(); i++)
	{
		m_RigidBodies[i]->update(deltaTime);
	}
}

// Updates each object within the physics world
void World::step(float deltaTime)
{
	detectCollisions(deltaTime);
	moveObjects(deltaTime);
	ApplyForces();
}

}

