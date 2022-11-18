#pragma once
#include "CollisionObject.h"
#include "collisions/AABB.h"
#include "Vector2.h"


enum bodyType
{
	nbp_static = 0,
	nbp_dynamic
};

namespace nbp
{
class World;
class Collider2D;

class RigidBody : public CollisionObject
{
public:
	RigidBody();
	RigidBody(Vector2 pos, Vector2 scale, float rotDeg, float restitution, float friciton);
	~RigidBody();

	Collider2D* getCollider() const;
	void setCollider(Collider2D* collider);
	AABB getAABB() const;

	Vector2 getVelocity();
	float Mass();
	float InvMass();
	float InvInertia();
	float Restitution();
	float Friction();

	bodyType getType();
	void setType(bodyType type);

	void setAngularVelocity(float angVel);
	void setAngle(float ang);

	void move(Vector2 amount);

	void applyForce(Vector2 force);
	void applyForceAtPoint(Vector2 force, Vector2 point);
	void applyImpulse(Vector2 impulse);
	void applyImpulseAtPoint(Vector2 impulse, Vector2 point);
	void applyTorque(float torque);
	void applyAngularImpulse(float impulse);
	void update(float deltaTime);

	Vector2 getVelocityFromWorldPoint(Vector2 point);


protected:
	// Linear velocity
	Vector2 m_Vel;

	// Angular velocity in radians/sec
	float m_angularVel;

	// Accumulated forces 
	Vector2 m_Force;
	float m_Torque;

	float m_Mass;
	float m_invMass;

	float m_Inertia;
	float m_invInertia;

	float m_Restitution;
	float m_Friction;

	enum bodyType m_Type;

	Collider2D* m_Collider;
	AABB m_aabb;

	void reset();
	void setInertia();

	friend class World;
};
}