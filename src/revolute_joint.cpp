
#include <godot_box2d.h>
#include "revolute_joint.h"

#include <Box2D/Box2D.h>

#define JOINT ((b2RevoluteJoint*)entity)
#define DEF ((b2RevoluteJointDef*)def)

float RevoluteJointB2::get_reference_angle() const { return JOINT->GetReferenceAngle(); }

float RevoluteJointB2::get_joint_angle() const { return JOINT->GetJointAngle(); }
float RevoluteJointB2::get_joint_speed() const { return JOINT->GetJointSpeed(); }

bool RevoluteJointB2::is_limit_enabled() const { return JOINT->IsLimitEnabled(); }
void RevoluteJointB2::set_limit_enabled(bool rhs) { return JOINT->EnableLimit(rhs); }

float RevoluteJointB2::get_lower_limit() const { return JOINT->GetLowerLimit(); }
void RevoluteJointB2::set_lower_limit(float rhs) { JOINT->SetLimits(rhs, JOINT->GetUpperLimit()); }

float RevoluteJointB2::get_upper_limit() const { return JOINT->GetUpperLimit(); }
void RevoluteJointB2::set_upper_limit(float rhs) { JOINT->SetLimits(JOINT->GetLowerLimit(), rhs); }

bool RevoluteJointB2::is_motor_enabled() const { return JOINT->IsMotorEnabled(); }
void RevoluteJointB2::set_motor_enabled(bool rhs) { return JOINT->EnableMotor(rhs); }

float RevoluteJointB2::get_motor_speed() const { return JOINT->GetMotorSpeed(); }
void RevoluteJointB2::set_motor_speed(float rhs) { JOINT->SetMotorSpeed(rhs); }

float RevoluteJointB2::get_max_motor_torque() const { return JOINT->GetMaxMotorTorque(); }
void RevoluteJointB2::set_max_motor_torque(float rhs) { JOINT->SetMaxMotorTorque(rhs); }

float RevoluteJointB2::get_motor_torque(float inv_dt) const { return JOINT->GetMotorTorque(inv_dt); }

void RevoluteJointB2::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_reference_angle:real"), &RevoluteJointB2::get_reference_angle);

    ObjectTypeDB::bind_method(_MD("get_joint_angle:real"), &RevoluteJointB2::get_joint_angle);
    ObjectTypeDB::bind_method(_MD("get_joint_speed:real"), &RevoluteJointB2::get_joint_speed);

    BOX2D_PROPERTY_BOOL(RevoluteJointB2, limit_enabled);
    BOX2D_PROPERTY(RevoluteJointB2, lower_limit, Variant::REAL, "real");
    BOX2D_PROPERTY(RevoluteJointB2, upper_limit, Variant::REAL, "real");
    BOX2D_PROPERTY_BOOL(RevoluteJointB2, motor_enabled);
    BOX2D_PROPERTY(RevoluteJointB2, motor_speed, Variant::REAL, "real");
    BOX2D_PROPERTY(RevoluteJointB2, max_motor_torque, Variant::REAL, "real");

    ObjectTypeDB::bind_method(_MD("get_motor_torque:real", "inv_dt:real"), &RevoluteJointB2::get_motor_torque);
}

JointB2 *RevoluteJointDefB2::instance(WorldB2 *world)
{
    ERR_FAIL_NULL_V(world, NULL);
    auto o = world->get_b2()->CreateJoint(get_b2());
    return memnew(RevoluteJointB2(o));
}

RevoluteJointDefB2::RevoluteJointDefB2() : JointDefB2(new b2RevoluteJointDef) {}

Vector2 RevoluteJointDefB2::get_anchor_a() const { return GD(DEF->localAnchorA); }
void RevoluteJointDefB2::set_anchor_a(const Vector2 &o) { DEF->localAnchorA = B2(o); }

Vector2 RevoluteJointDefB2::get_anchor_b() const { return GD(DEF->localAnchorB); }
void RevoluteJointDefB2::set_anchor_b(const Vector2 &o) { DEF->localAnchorB = B2(o); }

float RevoluteJointDefB2::get_reference_angle() const { return DEF->referenceAngle; }
void RevoluteJointDefB2::set_reference_angle(float o) { DEF->referenceAngle = o; }

bool RevoluteJointDefB2::get_enable_limit() const { return DEF->enableLimit; }
void RevoluteJointDefB2::set_enable_limit(bool o) { DEF->enableLimit = o; }

float RevoluteJointDefB2::get_lower_angle() const { return DEF->lowerAngle; }
void RevoluteJointDefB2::set_lower_angle(float o) { DEF->lowerAngle = o; }

float RevoluteJointDefB2::get_upper_angle() const { return DEF->upperAngle; }
void RevoluteJointDefB2::set_upper_angle(float o) { DEF->upperAngle = o; }

bool RevoluteJointDefB2::get_enable_motor() const { return DEF->enableMotor; }
void RevoluteJointDefB2::set_enable_motor(bool o) { DEF->enableMotor = o; }

float RevoluteJointDefB2::get_motor_speed() const { return DEF->motorSpeed; }
void RevoluteJointDefB2::set_motor_speed(float o) { DEF->motorSpeed = o; }

float RevoluteJointDefB2::get_max_motor_torque() const { return DEF->maxMotorTorque; }
void RevoluteJointDefB2::set_max_motor_torque(float o) { DEF->maxMotorTorque = o; }

void RevoluteJointDefB2::_bind_methods()
{
    BOX2D_PROPERTY(RevoluteJointDefB2, anchor_a, Variant::VECTOR2, "Vector2");
    BOX2D_PROPERTY(RevoluteJointDefB2, anchor_b, Variant::VECTOR2, "Vector2");
    BOX2D_PROPERTY(RevoluteJointDefB2, reference_angle, Variant::REAL, "real");
    BOX2D_PROPERTY(RevoluteJointDefB2, enable_limit, Variant::BOOL, "bool");
    BOX2D_PROPERTY(RevoluteJointDefB2, lower_angle, Variant::REAL, "real");
    BOX2D_PROPERTY(RevoluteJointDefB2, upper_angle, Variant::REAL, "real");
    BOX2D_PROPERTY(RevoluteJointDefB2, enable_motor, Variant::BOOL, "bool");
    BOX2D_PROPERTY(RevoluteJointDefB2, motor_speed, Variant::REAL, "real");
    BOX2D_PROPERTY(RevoluteJointDefB2, max_motor_torque, Variant::REAL, "real");
}
