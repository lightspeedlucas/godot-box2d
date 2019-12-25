
#include <godot_box2d.h>
#include "mouse_joint.h"

#include <Box2D/Box2D.h>

#define JOINT ((b2MouseJoint*)entity)
#define DEF ((b2MouseJointDef*)def)

Vector2 MouseJointB2::get_target() const
{
	return GD(JOINT->GetTarget());
}

void MouseJointB2::set_target(const Vector2 &rhs)
{
	return JOINT->SetTarget(B2(rhs));
}

float MouseJointB2::get_max_force() const
{
	return JOINT->GetMaxForce();
}

void MouseJointB2::set_max_force(float rhs)
{
	JOINT->SetMaxForce(rhs);
}

float MouseJointB2::get_frequency() const
{
	return JOINT->GetFrequency();
}

void MouseJointB2::set_frequency(float rhs)
{
	JOINT->SetFrequency(rhs);
}

float MouseJointB2::get_damping() const
{
	return JOINT->GetDampingRatio();
}

void MouseJointB2::set_damping(float rhs)
{
	JOINT->SetDampingRatio(rhs);
}

void MouseJointB2::_bind_methods()
{
    BOX2D_PROPERTY(MouseJointB2, target, Variant::VECTOR2);
    BOX2D_PROPERTY(MouseJointB2, max_force, Variant::REAL);
    BOX2D_PROPERTY(MouseJointB2, frequency, Variant::REAL);
    BOX2D_PROPERTY(MouseJointB2, damping, Variant::REAL);
}

JointB2 *MouseJointDefB2::instance(WorldB2 *world)
{
    ERR_FAIL_NULL_V(world, NULL);
    auto o = world->get_b2()->CreateJoint(def);
    return memnew(MouseJointB2(o));
}

MouseJointDefB2::MouseJointDefB2()
    : JointDefB2(new b2MouseJointDef)
{
}

Vector2 MouseJointDefB2::get_target() const
{
	return GD(DEF->target);
}

void MouseJointDefB2::set_target(const Vector2 &rhs)
{
	DEF->target = B2(rhs);
}

float MouseJointDefB2::get_max_force() const
{
	return DEF->maxForce;
}

void MouseJointDefB2::set_max_force(float rhs)
{
	DEF->maxForce = rhs;
}

float MouseJointDefB2::get_frequency() const
{
	return DEF->frequencyHz;
}

void MouseJointDefB2::set_frequency(float rhs)
{
	DEF->frequencyHz = rhs;
}

float MouseJointDefB2::get_damping() const
{
	return DEF->dampingRatio;
}

void MouseJointDefB2::set_damping(float rhs)
{
	DEF->dampingRatio = rhs;
}

void MouseJointDefB2::_bind_methods()
{
    BOX2D_PROPERTY(MouseJointDefB2, target, Variant::VECTOR2);
    BOX2D_PROPERTY(MouseJointDefB2, max_force, Variant::REAL);
    BOX2D_PROPERTY(MouseJointDefB2, frequency, Variant::REAL);
    BOX2D_PROPERTY(MouseJointDefB2, damping, Variant::REAL);
}
