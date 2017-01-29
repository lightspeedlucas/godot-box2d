#ifndef GODOT_MOUSE_JOINT_B2_H
#define GODOT_MOUSE_JOINT_B2_H

#include "joint.h"

class MouseJointB2 : public JointB2
{
    OBJ_TYPE(MouseJointB2, JointB2);
    BOX2D_JOINT(MouseJoint);
public:
    /** Box2D methods */
    Vector2 get_target() const;
    void set_target(const Vector2&);

    float get_max_force() const;
    void set_max_force(float);

    float get_frequency() const;
    void set_frequency(float);

    float get_damping() const;
    void set_damping(float);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class MouseJointDefB2 : public JointDefB2
{
    OBJ_TYPE(MouseJointDefB2, JointDefB2);
public:
    /** Lifecycle */
    MouseJointDefB2();
    class JointB2 *instance(class WorldB2*);

    /** Getters/setters */
    Vector2 get_target() const;
    void set_target(const Vector2&);

    float get_max_force() const;
    void set_max_force(float);

    float get_frequency() const;
    void set_frequency(float);

    float get_damping() const;
    void set_damping(float);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
