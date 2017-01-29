#ifndef GODOT_CONTACT_B2_H
#define GODOT_CONTACT_B2_H

#include <reference.h>

class ContactB2 : public Reference
{
    OBJ_TYPE(ContactB2, Reference);
public:
    /** Box2D methods */
    ContactB2(class b2Contact*);
    ~ContactB2();

    Dictionary get_world_manifold() const;

    bool is_touching() const;

    bool is_enabled() const;
    void set_enabled(bool);

    class FixtureB2 *get_fixture_a() const;
    int get_child_index_a() const;

    class FixtureB2 *get_fixture_b() const;
    int get_child_index_b() const;

    float get_friction() const;
    void set_friction(float);
    void reset_friction();

    float get_restitution() const;
    void set_restitution(float);
    void reset_restitution();

    float get_tangent_speed() const;
    void set_tangent_speed(float);

protected:
    class b2Contact *entity;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
