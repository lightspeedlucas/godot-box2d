#pragma once

#include "joint.h"

class MouseJointB2 : public JointB2
{
    GDCLASS(MouseJointB2, JointB2);
    BOX2D_JOINT(MouseJoint);
public:
    /** Box2D methods */
    BOX2D_GET_SET_DATA(Vector2, target);
    BOX2D_GET_SET(float, max_force);
    BOX2D_GET_SET(float, frequency);
    BOX2D_GET_SET(float, damping);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class MouseJointDefB2 : public JointDefB2
{
    GDCLASS(MouseJointDefB2, JointDefB2);
public:
    /** Lifecycle */
    MouseJointDefB2();
    class JointB2 *instance(class WorldB2*);

    /** Getters/setters */
    BOX2D_GET_SET_DATA(Vector2, target);
    BOX2D_GET_SET(float, max_force);
    BOX2D_GET_SET(float, frequency);
    BOX2D_GET_SET(float, damping);

protected:
    /** Godot bindings */
	static void _bind_methods();
};
