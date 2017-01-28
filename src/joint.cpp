
#include <godot_box2d.h>
#include "joint.h"

#include <Box2D/Box2D.h>

JointB2::JointB2(b2Joint *entity)
    : entity(entity)
{
    entity->SetUserData(this);
    b2Log("Created joint...");
}

JointB2::~JointB2()
{
    b2Log("Deleting joint...");
    entity->GetBodyA()->GetWorld()->DestroyJoint(entity);
}

void JointB2::_bind_methods()
{
}

JointB2 *JointB2::get(const b2Joint *o)
{
    return (JointB2*)o->GetUserData();
}

JointDefB2::JointDefB2(b2JointDef *def) : def(def) {}
JointDefB2::~JointDefB2() { delete def; }
#define DEF (def)

BodyB2 *JointDefB2::get_body_a() const { return BodyB2::get(DEF->bodyA); }
void JointDefB2::set_body_a(BodyB2 *o) { DEF->bodyA = o ? o->get_b2() : NULL; }

BodyB2 *JointDefB2::get_body_b() const { return BodyB2::get(DEF->bodyB); }
void JointDefB2::set_body_b(BodyB2 *o) { DEF->bodyB = o ? o->get_b2() : NULL; }

bool JointDefB2::get_collide_connected() const { return DEF->collideConnected; }
void JointDefB2::set_collide_connected(bool o) { DEF->collideConnected = o; }

const b2JointDef *JointDefB2::get_b2() const { return def; }

void JointDefB2::_bind_methods()
{
    BOX2D_PROPERTY(JointDefB2, body_a, Variant::OBJECT, "BodyB2");
    BOX2D_PROPERTY(JointDefB2, body_b, Variant::OBJECT, "BodyB2");
    BOX2D_PROPERTY(JointDefB2, collide_connected, Variant::BOOL, "bool");
}

#undef DEF
RevoluteJointDefB2::RevoluteJointDefB2() : JointDefB2(new b2RevoluteJointDef) {}
#define DEF ((b2RevoluteJointDef*)def)

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
