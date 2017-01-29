#ifndef GODOT_REVOLUTE_JOINT_B2_H
#define GODOT_REVOLUTE_JOINT_B2_H

#include "joint.h"

class RevoluteJointB2 : public JointB2
{
    OBJ_TYPE(RevoluteJointB2, JointB2);
    BOX2D_JOINT(RevoluteJoint);
public:
    /** Box2D methods */
    float get_reference_angle() const;

    float get_joint_angle() const;
    float get_joint_speed() const;

    bool is_limit_enabled() const;
    void set_limit_enabled(bool);

    float get_lower_limit() const;
    void set_lower_limit(float);

    float get_upper_limit() const;
    void set_upper_limit(float);

    bool is_motor_enabled() const;
    void set_motor_enabled(bool);

    float get_motor_speed() const;
    void set_motor_speed(float);

    float get_max_motor_torque() const;
    void set_max_motor_torque(float);

    float get_motor_torque(float inv_dt) const;

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
    class JointB2 *instance(class WorldB2*);

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
