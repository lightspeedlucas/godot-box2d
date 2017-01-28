
#include <godot_box2d.h>
#include "world.h"

#include <Box2D/Box2D.h>

WorldB2::WorldB2(b2World *entity)
    : entity(entity)
{
    entity->SetUserData(this);
}

WorldB2::~WorldB2()
{
    // Destroy all bodies
    while (auto *o = entity->GetBodyList())
        memdelete_notnull(BodyB2::get(o));

    delete entity;
}

BodyB2 *WorldB2::create_body(int type, const Vector2 &position, float angle)
{
    static b2BodyDef def;
    def.type = (b2BodyType)type;
    def.position = B2(position);
    def.angle = angle;
    return memnew(BodyB2(entity->CreateBody(&def)));
}

void WorldB2::destroy_body(BodyB2 *body)
{
    ERR_FAIL_NULL(body);
    memdelete(body);
}

JointB2 *WorldB2::create_joint(const JointDefB2 *def)
{
    ERR_FAIL_NULL_V(def, NULL);
    auto *joint = entity->CreateJoint(def->get_b2());
    return memnew(JointB2(joint));
}

void WorldB2::destroy_joint(JointB2 *joint)
{
    ERR_FAIL_NULL(joint);
    memdelete(joint);
}

void WorldB2::step(float timeStep, int velocityIterations, int positionIterations)
{
    entity->Step(timeStep, velocityIterations, positionIterations);
}

Vector2 WorldB2::get_gravity() const
{
    return GD(entity->GetGravity());
}

void WorldB2::set_gravity(const Vector2 &value)
{
    entity->SetGravity(B2(value));
}

bool WorldB2::is_locked() const
{
    return entity->IsLocked();
}

void WorldB2::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("create_body:BodyB2", "type:int", "position:Vector2", "angle:real"), &WorldB2::create_body, DEFVAL(Vector2()), DEFVAL(.0f));
    ObjectTypeDB::bind_method(_MD("destroy_body"), &WorldB2::destroy_body);

    ObjectTypeDB::bind_method(_MD("create_joint:BodyB2", "def:JointDefB2"), &WorldB2::create_joint);
    ObjectTypeDB::bind_method(_MD("destroy_joint"), &WorldB2::destroy_joint);

    ObjectTypeDB::bind_method(_MD("step", "timeStep:real", "velocityIterations:int", "positionIterations:int"), &WorldB2::step);

    ObjectTypeDB::bind_method(_MD("get_gravity"), &WorldB2::get_gravity);
    ObjectTypeDB::bind_method(_MD("set_gravity", "gravity:Vector2"), &WorldB2::set_gravity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "gravity"), _SCS("set_gravity"), _SCS("get_gravity"));

    ObjectTypeDB::bind_method(_MD("is_locked"), &WorldB2::is_locked);
}

WorldB2 *WorldB2::get(const b2World *o)
{
    return (WorldB2*)o->GetUserData();
}