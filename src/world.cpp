
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
    ObjectTypeDB::bind_method(_MD("step", "timeStep:real", "velocityIterations:int", "positionIterations:int"), &WorldB2::step);
    ObjectTypeDB::bind_method(_MD("clear_forces"), &WorldB2::clear_forces);

    ObjectTypeDB::bind_method(_MD("query_aabb", "callback:FuncRef", "aabb:Rect2"), &WorldB2::query_aabb);
    ObjectTypeDB::bind_method(_MD("ray_cast", "callback:FuncRef", "a:Vector2", "b:Vector2"), &WorldB2::ray_cast);

    BOX2D_PROPERTY(WorldB2, gravity, Variant::VECTOR2, "Vector2");

    ObjectTypeDB::bind_method(_MD("is_locked"), &WorldB2::is_locked);

    BOX2D_PROPERTY(WorldB2, auto_clear_forces, Variant::BOOL, "bool");

    ObjectTypeDB::bind_method(_MD("shift_origin", "new_origin:Vector2"), &WorldB2::shift_origin);

    BOX2D_PROPERTY(WorldB2, metadata, Variant::NIL, "Variant");
}

WorldB2 *WorldB2::get(const b2World *o)
{
    return (WorldB2*)o->GetUserData();
}