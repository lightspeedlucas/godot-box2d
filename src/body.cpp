
#include <godot_box2d.h>
#include "body.h"

#include <Box2D/Box2D.h>

BodyB2::BodyB2(b2Body *entity)
    : entity(entity)
{
    entity->SetUserData(this);
    b2Log("Created body...");
}

BodyB2::~BodyB2()
{
    // Destroy all joints
    while (auto *e = entity->GetJointList())
        memdelete_notnull(JointB2::get(e->joint));

    // Destroy all fixtures
    while (auto *o = entity->GetFixtureList())
        memdelete_notnull(FixtureB2::get(o));

    b2Log("Deleting body...");
    entity->GetWorld()->DestroyBody(entity);
}

FixtureB2 *BodyB2::create_fixture(const Ref<ShapeB2> &shape, float density)
{
    static b2FixtureDef def;
    def.shape = shape->get_b2();
    def.density = density;
    return memnew(FixtureB2(entity->CreateFixture(&def)));
}

void BodyB2::destroy_fixture(FixtureB2 *fixture)
{
    ERR_FAIL_NULL(fixture);
    memdelete(fixture);
}

Vector2 BodyB2::get_position() const
{
    return GD(entity->GetPosition());
}

WorldB2 *BodyB2::get_world() const
{
    return WorldB2::get(entity->GetWorld());
}

void BodyB2::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("create_fixture:FixtureB2", "shape:ShapeB2", "density:real"), &BodyB2::create_fixture, DEFVAL(1.f));
    ObjectTypeDB::bind_method(_MD("destroy_fixture", "fixture:FixtureB2"), &BodyB2::destroy_fixture);

    ObjectTypeDB::bind_method(_MD("get_position:Vector2"), &BodyB2::get_position);

    ObjectTypeDB::bind_method(_MD("get_world:WorldB2"), &BodyB2::get_world);

    ObjectTypeDB::bind_integer_constant(get_type_static(), "DYNAMIC", b2_dynamicBody);
    ObjectTypeDB::bind_integer_constant(get_type_static(), "KINEMATIC", b2_kinematicBody);
    ObjectTypeDB::bind_integer_constant(get_type_static(), "STATIC", b2_staticBody);
}

BodyB2 *BodyB2::get(const b2Body *o)
{
    return (BodyB2*)o->GetUserData();
}
