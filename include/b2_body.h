#ifndef GODOT_B2_BODY_H
#define GODOT_B2_BODY_H

#include <reference.h>

class b2BodyWrapper : public Reference
{
    OBJ_TYPE(b2BodyWrapper, Reference);
    WRAP_BOX2D(b2Body);
public:
    /** Box2D methods */
    void set_transform(const Vector2&, float);
    Vector2 get_position() const;
    float get_angle() const;

    void set_body_type(int);
    int get_body_type() const;

    b2BodyRef get_next() const;

    Object *get_user_data() const;
    void set_user_data(Object*);

    b2WorldRef get_world() const;

    /** Auxiliary methods */
    void destroy();

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class b2BodyDefinition : public Reference
{
    OBJ_TYPE(b2BodyDefinition, Reference);
    WRAP_BOX2D_DEF(b2BodyDef);
public:
    /** Box2D fields */
    BOX2D_DEF_FIELD(int, body_type, type);
    BOX2D_DEF_FIELD_COMPLEX(Vector2, position, position);
    BOX2D_DEF_FIELD(float, angle, angle);
    BOX2D_DEF_FIELD_COMPLEX(Vector2, linear_velocity, linearVelocity);
    BOX2D_DEF_FIELD(float, angular_velocity, angularVelocity);
    BOX2D_DEF_FIELD(float, linear_damping, linearDamping);
    BOX2D_DEF_FIELD(float, angular_damping, angularDamping);
    BOX2D_DEF_FIELD(bool, allow_sleep, allowSleep);
    BOX2D_DEF_FIELD(bool, awake, awake);
    BOX2D_DEF_FIELD(bool, fixed_rotation, fixedRotation);
    BOX2D_DEF_FIELD(bool, bullet, bullet);
    BOX2D_DEF_FIELD(bool, active, active);
    BOX2D_DEF_FIELD(Object*, user_data, userData);
    BOX2D_DEF_FIELD(float, gravity_scale, gravityScale);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
