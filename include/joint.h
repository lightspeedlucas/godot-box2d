#ifndef GODOT_JOINT_B2_H
#define GODOT_JOINT_B2_H

#include <reference.h>

class JointB2 : public Object
{
    OBJ_TYPE(JointB2, Object);
    BOX2D_CLASS(Joint, JointDefB2);
public:
    /** Box2D methods */
    class BodyB2 *get_body_a() const;
    class BodyB2 *get_body_b() const;

    Vector2 get_anchor_a() const;
    Vector2 get_anchor_b() const;

    Vector2 get_reaction_force(float inv_dt) const;
    float get_reaction_torque(float inv_dt) const;

    Variant get_metadata() const;
    void set_metadata(const Variant&);

    bool is_active() const;

    bool get_collide_connected() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class JointDefB2 : public Reference
{
    OBJ_TYPE(JointDefB2, Reference);
public:
    /** Lifecycle */
    virtual class JointB2 *instance(class WorldB2*) = 0;
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

#endif
