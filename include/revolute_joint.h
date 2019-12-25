#pragma once

#include "joint.h"

class RevoluteJointB2 : public JointB2
{
    GDCLASS(RevoluteJointB2, JointB2);
    BOX2D_JOINT(RevoluteJoint);
public:
    /** Box2D methods */
    float get_reference_angle() const;

    float get_joint_angle() const;
    float get_joint_speed() const;

    BOX2D_IS_SET(limit_enabled);
    BOX2D_GET_SET(float, lower_limit);
    BOX2D_GET_SET(float, upper_limit);
    BOX2D_IS_SET(motor_enabled);
    BOX2D_GET_SET(float, motor_speed);
    BOX2D_GET_SET(float, max_motor_torque);

    float get_motor_torque(float inv_dt) const;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class RevoluteJointDefB2 : public JointDefB2
{
    GDCLASS(RevoluteJointDefB2, JointDefB2);
public:
    /** Lifecycle */
    RevoluteJointDefB2();
    class JointB2 *instance(class WorldB2*);

    /** Getters/setters */
    BOX2D_GET_SET_DATA(Vector2, anchor_a);
    BOX2D_GET_SET_DATA(Vector2, anchor_b);
    BOX2D_GET_SET(float, reference_angle);
    BOX2D_GET_SET(bool, enable_limit);
    BOX2D_GET_SET(float, lower_angle);
    BOX2D_GET_SET(float, upper_angle);
    BOX2D_GET_SET(bool, enable_motor);
    BOX2D_GET_SET(float, motor_speed);
    BOX2D_GET_SET(float, max_motor_torque);

protected:
    /** Godot bindings */
	static void _bind_methods();
};
