
#include <godot_box2d.h>
#include "b2_world.h"

b2BodyRef b2WorldWrapper::create_body(b2BodyDefinition *def)
{
    ERR_FAIL_NULL_V(def, NULL);
    return BOX2D_REF(b2Body, wrapped->CreateBody(*def));
}

void b2WorldWrapper::destroy_body(b2BodyWrapper *body)
{
    ERR_FAIL_NULL(body);
    wrapped->DestroyBody(*body);
}

void b2WorldWrapper::step(float timeStep, int velocityIterations, int positionIterations)
{
    wrapped->Step(timeStep, velocityIterations, positionIterations);
}

Vector2 b2WorldWrapper::get_gravity() const
{
    return GD(wrapped->GetGravity());
}

void b2WorldWrapper::set_gravity(const Vector2 &value)
{
    wrapped->SetGravity(B2(value));
}

bool b2WorldWrapper::is_locked() const
{
    return wrapped->IsLocked();
}

void b2WorldWrapper::destroy()
{
    delete wrapped;
}

void b2WorldWrapper::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("create_body:b2BodyWrapper", "def:b2BodyDefinition"), &b2WorldWrapper::create_body);
    ObjectTypeDB::bind_method(_MD("destroy_body", "body:b2BodyWrapper"), &b2WorldWrapper::destroy_body);

    ObjectTypeDB::bind_method(_MD("step", "timeStep:real", "velocityIterations:int", "positionIterations:int"), &b2WorldWrapper::step);

    ObjectTypeDB::bind_method(_MD("get_gravity"), &b2WorldWrapper::get_gravity);
    ObjectTypeDB::bind_method(_MD("set_gravity", "gravity:Vector2"), &b2WorldWrapper::set_gravity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "gravity"), _SCS("set_gravity"), _SCS("get_gravity"));
    
    ObjectTypeDB::bind_method(_MD("is_locked"), &b2WorldWrapper::is_locked);

    ObjectTypeDB::bind_method(_MD("destroy"), &b2WorldWrapper::destroy);
}
