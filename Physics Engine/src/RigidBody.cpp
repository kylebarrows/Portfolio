#include "../includes/RigidBody.h"
#include "../includes/NMath.h"
#include "../includes/collisions/AABB.h"
#include "../includes/collisions/Circle.h"
#include "../includes/collisions/Box2D.h"

namespace nbp
{
RigidBody::RigidBody()
{   
	m_Type = nbp_dynamic;
    reset();
}

RigidBody::RigidBody(Vector2 pos, Vector2 scale, float rotDeg, 
    float restitution, float friciton):
    CollisionObject(pos, scale, rotDeg), m_Restitution(restitution), m_Friction(friciton)
{
	m_Type = nbp_dynamic;
}

RigidBody::~RigidBody()
{
	delete m_Collider;
}

Collider2D* RigidBody::getCollider() const
{
	return m_Collider;
}

void RigidBody::setCollider(Collider2D* collider)
{
	m_Collider = collider;
	setInertia();
}

AABB RigidBody::getAABB() const
{
	AABB aabb = m_Collider->getAABB(m_Pos);

	return aabb;
}

Vector2 RigidBody::getVelocity()
{
    return m_Vel;
}

void RigidBody::setAngularVelocity(float angVel)
{
    m_angularVel = angVel;
}

void RigidBody::setAngle(float ang)
{
	m_Rotation = ang;
}

void RigidBody::move(Vector2 amount)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_Pos += amount;
}

float RigidBody::Mass()
{
	return m_Mass;
}

float RigidBody::InvMass()
{
	return m_invMass;
}

float RigidBody::InvInertia()
{
	return m_invInertia;
}

float RigidBody::Restitution()
{
	return m_Restitution;
}

float RigidBody::Friction()
{
	return m_Friction;
}

bodyType RigidBody::getType()
{
	return m_Type;
}

void RigidBody::setType(bodyType type)
{
	m_Type = type;
	if (m_Type == nbp_static)
	{
		m_invMass = 0.0;
	}
	else
	{
		m_invMass = 1 / m_Mass;
	}
}

// Apply force to the center of the object
void RigidBody::applyForce(Vector2 force)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_Force += force;
}

// Applies force to a point on the body, generates torque
void RigidBody::applyForceAtPoint(Vector2 force, Vector2 point)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_Force += force;
	m_Torque += NMath::Cross(point - m_Pos, force);
}

// Apply impulse to the center of the body, does not affect rotation
void RigidBody::applyImpulse(Vector2 impulse)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_Vel += impulse * m_invMass;
}

// Apply impulse to a point on the body, updates linear and angular velocity
void RigidBody::applyImpulseAtPoint(Vector2 impulse, Vector2 point)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_Vel += impulse * m_invMass;
	m_angularVel += m_invInertia * NMath::Cross(point - m_Pos, impulse);
}

// Apply torque to the object
void RigidBody::applyTorque(float torque)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_Torque += torque;
}

// Applies angular impulse to the object
void RigidBody::applyAngularImpulse(float impulse)
{
	if (m_Type == nbp_static)
	{
		return;
	}

	m_angularVel += m_invInertia * impulse;
}

// Updates the position, angle, and velocity of the rigidbody with integration
void RigidBody::update(float deltaTime)
{
	if (m_Type == nbp_static)
	{
		return;
	}

    m_Pos += m_Vel * deltaTime;
    m_Vel += m_Force * m_invMass * deltaTime;
    m_Rotation += m_angularVel * (180 / 3.141592) * deltaTime;

	m_angularVel += m_Torque * m_invInertia * deltaTime;

    m_Force.x = 0;
    m_Force.y = 0;
	m_Torque = 0;
}

// Gets local velocity from point, sum of linear velocity and angular velocity at point
Vector2 RigidBody::getVelocityFromWorldPoint(Vector2 point)
{
	return m_Vel + NMath::Cross(m_angularVel, point - m_Pos);
}

// Default values
void RigidBody::reset()
{
	m_Pos = Vector2(0.0, 0.0);
	m_Scale = Vector2(1.0, 1.0);
	m_Rotation = 0.0;
	m_Vel = Vector2(0.0, 0.0);
	m_angularVel = 0.0;
	m_Force = Vector2(0.0, 0.0);
	m_Mass = 1.0;
	m_invMass = 1 / m_Mass;
	m_Inertia = 0.0;
	m_invInertia = 0.0;
	m_Restitution = 0.5;
	m_Friction = 0.5;
}

// Sets the inertia of the body
void RigidBody::setInertia()
{
	if (m_Collider)
	{
		float inertia = m_Collider->computeInertia(m_Mass, m_Pos);
		m_Inertia = inertia;
		m_invInertia = 1 / m_Inertia;
	}
}

}
