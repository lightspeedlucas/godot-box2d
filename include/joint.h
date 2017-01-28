#ifndef GODOT_JOINT_B2_H
#define GODOT_JOINT_B2_H

#include <reference.h>

class JointB2 : public Object
{
    OBJ_TYPE(JointB2, Object);
    BOX2D_CLASS(Joint, WorldB2);
public:
    /** Box2D methods */

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class JointDefB2 : public Reference
{
    OBJ_TYPE(JointDefB2, Reference);
public:
    /** Lifecycle */
    ~JointDefB2();

    /** Getters/setters */
    class BodyB2 *get_body_a() const;
    void set_body_a(class BodyB2*);

    class BodyB2 *get_body_b() const;
    void set_body_b(class BodyB2*);

    bool get_collide_connected() const;
    void set_collide_connected(bool);

    /** Box2D accessor */
    const class b2JointDef *get_b2() const;

protected:
    /** Internal definition */
    JointDefB2(class b2JointDef*);
    class b2JointDef *def;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class RevoluteJointDefB2 : public JointDefB2
{
    OBJ_TYPE(RevoluteJointDefB2, JointDefB2);
public:
    /** Lifecycle */
    RevoluteJointDefB2();

    /** Getters/setters */
    Vector2 get_anchor_a() const;
    void set_anchor_a(const Vector2&);

    Vector2 get_anchor_b() const;
    void set_anchor_b(const Vector2&);

    float get_reference_angle() const;
    void set_reference_angle(float);

    bool get_enable_limit() const;
    void set_enable_limit(bool);

    float get_lower_angle() const;
    void set_lower_angle(float);

    float get_upper_angle() const;
    void set_upper_angle(float);

    bool get_enable_motor() const;
    void set_enable_motor(bool);

    float get_motor_speed() const;
    void set_motor_speed(float);

    float get_max_motor_torque() const;
    void set_max_motor_torque(float);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
