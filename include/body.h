#ifndef GODOT_BODY_B2_H
#define GODOT_BODY_B2_H

#include <object.h>

class BodyB2 : public Object
{
    OBJ_TYPE(BodyB2, Object);
    BOX2D_CLASS(Body, WorldB2);
public:
    /** Box2D methods */
    class FixtureB2 *create_fixture(const Ref<class ShapeB2> &shape, float density = 0);
    void destroy_fixture(class FixtureB2*);

    void set_transform(const Vector2 &position, float angle);
    Vector2 get_position() const;
    float get_angle() const;

    Vector2 get_world_center() const;
    Vector2 get_local_center() const;

    Vector2 get_linear_velocity() const;
    void set_linear_velocity(const Vector2&);

    float get_angular_velocity() const;
    void set_angular_velocity(float);

    void apply_force_at(const Vector2 &force, const Vector2 &point, bool wake = true);
    void apply_force(const Vector2 &force, bool wake = true);

    void apply_torque(float torque, bool wake = true);
    void apply_angular_impulse(float impulse, bool wake = true);

    void apply_impulse_at(const Vector2 &impulse, const Vector2 &point, bool wake = true);
    void apply_impulse(const Vector2 &impulse, bool wake = true);

    float get_mass() const;
    float get_inertia() const;

    Dictionary get_mass_data() const;
    void set_mass_data(float mass, float inertia, const Vector2 &com);

    void reset_mass_data();

    Vector2 get_linear_velocity_at(const Vector2 &point) const;

    float get_linear_damping() const;
    void set_linear_damping(float);

    float get_angular_damping() const;
    void set_angular_damping(float);

    float get_gravity_scale() const;
    void set_gravity_scale(float);

    int get_body_type() const;
    void set_body_type(int);

    bool is_bullet() const;
    void set_bullet(bool);

    bool is_sleeping_allowed();
    void set_sleeping_allowed(bool);

    bool is_awake() const;
    void set_awake(bool);

    bool is_active() const;
    void set_active(bool);

    bool is_fixed_rotation() const;
    void set_fixed_rotation(bool);

    Array get_fixture_list() const;
    Array get_joint_list() const;

    Variant get_metadata() const;
    void set_metadata(const Variant&);

    class WorldB2 *get_world() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
