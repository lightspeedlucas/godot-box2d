
#include <godot_box2d.h>
#include "joint.h"

#include <Box2D/Box2D.h>

JointB2::JointB2(b2Joint *entity)
    : entity(entity)
{
    entity->SetUserData(this);
}

JointB2::~JointB2()
{
    entity->GetBodyB()->GetWorld()->DestroyJoint(entity);
}

BodyB2 *JointB2::get_body_a() const
{
    return BodyB2::get(entity->GetBodyA());
}

BodyB2 *JointB2::get_body_b() const
{
    return BodyB2::get(entity->GetBodyB());
}

Vector2 JointB2::get_anchor_a() const
{
    return GD(entity->GetAnchorA());
}

Vector2 JointB2::get_anchor_b() const
{
    return GD(entity->GetAnchorB());
}

Vector2 JointB2::get_reaction_force(float inv_dt) const
{
    return GD(entity->GetReactionForce(inv_dt));
}

float JointB2::get_reaction_torque(float inv_dt) const
{
    return entity->GetReactionTorque(inv_dt);
}

Variant JointB2::get_metadata() const
{
    return metadata;
}

void JointB2::set_metadata(const Variant &rhs)
{
    metadata = rhs;
}

bool JointB2::is_active() const
{
    return entity->IsActive();
}

bool JointB2::get_collide_connected() const
{
    return entity->GetCollideConnected();
}

void JointB2::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_body_a"), &JointB2::get_body_a);
    ClassDB::bind_method(D_METHOD("get_body_b"), &JointB2::get_body_b);

    ClassDB::bind_method(D_METHOD("get_anchor_a"), &JointB2::get_anchor_a);
    ClassDB::bind_method(D_METHOD("get_anchor_b"), &JointB2::get_anchor_b);

    ClassDB::bind_method(D_METHOD("get_reaction_force", "inv_dt"), &JointB2::get_reaction_force);
    ClassDB::bind_method(D_METHOD("get_reaction_torque", "inv_dt"), &JointB2::get_reaction_torque);

    BOX2D_PROPERTY(JointB2, metadata, Variant::NIL);

    ClassDB::bind_method(D_METHOD("is_active"), &JointB2::is_active);
    ClassDB::bind_method(D_METHOD("get_collide_connected"), &JointB2::get_collide_connected);
}

JointB2 *JointB2::get(const b2Joint *o)
{
    return (JointB2*)o->GetUserData();
}

JointDefB2::JointDefB2(b2JointDef *def)
    : def(def)
{
}

JointDefB2::~JointDefB2()
{
    memdelete(def);
}

BodyB2 *JointDefB2::get_body_a() const
{
    return BodyB2::get(def->bodyA);
}

void JointDefB2::set_body_a(BodyB2 *o)
{
    def->bodyA = o ? o->get_b2() : NULL;
}

BodyB2 *JointDefB2::get_body_b() const
{
    return BodyB2::get(def->bodyB);
}

void JointDefB2::set_body_b(BodyB2 *o)
{
    def->bodyB = o ? o->get_b2() : NULL;
}

bool JointDefB2::get_collide_connected() const
{
    return def->collideConnected;
}

void JointDefB2::set_collide_connected(bool o)
{
    def->collideConnected = o;
}

void JointDefB2::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("instance", "world"), &JointDefB2::instance);

    BOX2D_PROPERTY(JointDefB2, body_a, Variant::OBJECT);
    BOX2D_PROPERTY(JointDefB2, body_b, Variant::OBJECT);
    BOX2D_PROPERTY(JointDefB2, collide_connected, Variant::BOOL);
}
