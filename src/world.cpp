
#include <func_ref.h>
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

void WorldB2::clear_forces()
{
    entity->ClearForces();
}

void WorldB2::query_aabb(FuncRef *callback, const Rect2 &aabb) const
{
    static struct CB : public b2QueryCallback
    {
        FuncRef *func;
        bool ReportFixture(b2Fixture *fixture)
        {
            // declare stuff necessary for the call
            static Variant arg;
            static Variant::CallError ce;
            static const Variant *args[] = { &arg };
            // get fixture object
            arg = FixtureB2::get(fixture);
            // call function
            Variant ret = func->call_func(args, 1, ce);
            return ce.error == Variant::CallError::CALL_OK && ret;
        }
    } cb;

    ERR_FAIL_NULL(callback);
    cb.func = callback;
    entity->QueryAABB(&cb, B2(aabb));
}

void WorldB2::ray_cast(FuncRef *callback, const Vector2 &a, const Vector2 &b) const
{
    static struct CB : public b2RayCastCallback
    {
        FuncRef *func;
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
        {
            // declare stuff necessary for the call
            static Variant arg[4];
            static Variant::CallError ce;
            static const Variant *args[] = { &arg[0], &arg[1], &arg[2], &arg[3] };
            // get fixture object
            arg[0] = FixtureB2::get(fixture);
            arg[1] = GD(point);
            arg[2] = GD(normal);
            arg[3] = fraction;
            // call function
            Variant ret = func->call_func(args, 4, ce);
            return ce.error == Variant::CallError::CALL_OK ? (float)ret : .0f;
        }
    } cb;

    ERR_FAIL_NULL(callback);
    cb.func = callback;
    entity->RayCast(&cb, B2(a), B2(b));
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

bool WorldB2::get_auto_clear_forces() const
{
    return entity->GetAutoClearForces();
}

void WorldB2::set_auto_clear_forces(bool rhs)
{
    entity->SetAutoClearForces(rhs);
}

void WorldB2::shift_origin(const Vector2 &origin)
{
    entity->ShiftOrigin(B2(origin));
}

Variant WorldB2::get_metadata() const
{
    return metadata;
}

void WorldB2::set_metadata(const Variant &rhs)
{
    metadata = rhs;
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