
#include <godot_box2d.h>
#include "contact.h"

#include <Box2D/Box2D.h>

ContactB2::ContactB2(b2Contact *entity)
    : entity(entity)
{
}

ContactB2::~ContactB2()
{
}

Dictionary ContactB2::get_world_manifold() const
{
    return Dictionary();
}

bool ContactB2::is_touching() const
{
    return entity->IsTouching();
}

bool ContactB2::is_enabled() const
{
    return entity->IsEnabled();
}

void ContactB2::set_enabled(bool rhs)
{
    entity->SetEnabled(rhs);
}

FixtureB2 *ContactB2::get_fixture_a() const
{
    return FixtureB2::get(entity->GetFixtureA());
}

int ContactB2::get_child_index_a() const
{
    return entity->GetChildIndexA();
}

FixtureB2 *ContactB2::get_fixture_b() const
{
    return FixtureB2::get(entity->GetFixtureB());
}

int ContactB2::get_child_index_b() const
{
    return entity->GetChildIndexB();
}

float ContactB2::get_friction() const
{
    return entity->GetFriction();
}

void ContactB2::set_friction(float rhs)
{
    entity->SetFriction(rhs);
}

void ContactB2::reset_friction()
{
    entity->ResetFriction();
}

float ContactB2::get_restitution() const
{
    return entity->GetRestitution();
}

void ContactB2::set_restitution(float rhs)
{
    entity->SetRestitution(rhs);
}

void ContactB2::reset_restitution()
{
    entity->ResetRestitution();
}

float ContactB2::get_tangent_speed() const
{
    return entity->GetTangentSpeed();
}

void ContactB2::set_tangent_speed(float rhs)
{
    entity->SetTangentSpeed(rhs);
}

void ContactB2::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("is_touching"), &ContactB2::is_touching);

    BOX2D_PROPERTY_BOOL(ContactB2, enabled);

    ClassDB::bind_method(D_METHOD("get_fixture_a"), &ContactB2::get_fixture_a);
    ClassDB::bind_method(D_METHOD("get_child_index_a"), &ContactB2::get_child_index_a);

    ClassDB::bind_method(D_METHOD("get_fixture_b"), &ContactB2::get_fixture_b);
    ClassDB::bind_method(D_METHOD("get_child_index_b"), &ContactB2::get_child_index_b);

    BOX2D_PROPERTY(ContactB2, friction, Variant::REAL);
    ClassDB::bind_method(D_METHOD("reset_friction"), &ContactB2::reset_friction);

    BOX2D_PROPERTY(ContactB2, restitution, Variant::REAL);
    ClassDB::bind_method(D_METHOD("reset_restitution"), &ContactB2::reset_restitution);

    BOX2D_PROPERTY(ContactB2, tangent_speed, Variant::REAL);
}
