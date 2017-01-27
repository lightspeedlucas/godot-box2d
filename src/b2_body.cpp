
#include <godot_box2d.h>
#include "b2_body.h"

void b2BodyWrapper::set_transform(const Vector2 &position, float angle)
{
    wrapped->SetTransform(B2(position), angle);
}

Vector2 b2BodyWrapper::get_position() const
{
    return GD(wrapped->GetPosition());
}

float b2BodyWrapper::get_angle() const
{
    return wrapped->GetAngle();
}

void b2BodyWrapper::set_body_type(int type)
{
    wrapped->SetType((b2BodyType)type);
}

int b2BodyWrapper::get_body_type() const
{
    return wrapped->GetType();
}

b2BodyRef b2BodyWrapper::get_next() const
{
    return GD(wrapped->GetNext());
}

Object *b2BodyWrapper::get_user_data() const
{
    return (Object*)wrapped->GetUserData();
}

void b2BodyWrapper::set_user_data(Object *data)
{
    wrapped->SetUserData(data);
}

b2WorldRef b2BodyWrapper::get_world() const
{
    return GD(wrapped->GetWorld());
}

void b2BodyWrapper::destroy()
{
    wrapped->GetWorld()->DestroyBody(wrapped);
}

void b2BodyWrapper::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("set_transform", "position:Vector2", "angle:real"), &b2BodyWrapper::set_transform);
    ObjectTypeDB::bind_method(_MD("get_position:Vector2"), &b2BodyWrapper::get_position);
    ObjectTypeDB::bind_method(_MD("get_angle:real"), &b2BodyWrapper::get_angle);

    ObjectTypeDB::bind_method(_MD("get_body_type"), &b2BodyWrapper::get_body_type);
    ObjectTypeDB::bind_method(_MD("set_body_type", "type:int"), &b2BodyWrapper::set_body_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "body_type"), _SCS("set_body_type"), _SCS("get_body_type"));
    
    ObjectTypeDB::bind_method(_MD("get_next:b2BodyWrapper"), &b2BodyWrapper::get_next);

    ObjectTypeDB::bind_method(_MD("get_user_data"), &b2BodyWrapper::get_user_data);
    ObjectTypeDB::bind_method(_MD("set_user_data", "data:Object"), &b2BodyWrapper::set_user_data);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "user_data"), _SCS("set_user_data"), _SCS("get_user_data"));    

    ObjectTypeDB::bind_method(_MD("get_world:b2WorldWrapper"), &b2BodyWrapper::get_world);

    ObjectTypeDB::bind_method(_MD("destroy"), &b2BodyWrapper::destroy);
}

void b2BodyDefinition::_bind_methods()
{
    BOX2D_BIND_PROPERTY(b2BodyDefinition, body_type, INT);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, position, VECTOR2);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, angle, REAL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, linear_velocity, VECTOR2);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, angular_velocity, REAL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, linear_damping, REAL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, angular_damping, REAL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, allow_sleep, BOOL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, awake, BOOL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, fixed_rotation, BOOL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, bullet, BOOL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, active, BOOL);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, user_data, OBJECT);
    BOX2D_BIND_PROPERTY(b2BodyDefinition, gravity_scale, REAL);
}
