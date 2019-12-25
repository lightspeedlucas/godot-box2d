#pragma once

#include <core/reference.h>

class BodyB2 : public Object
{
    GDCLASS(BodyB2, Object);
    BOX2D_CLASS(Body);
public:
    /** Box2D methods */
    Transform2D get_transform() const;
    void set_transform(const Transform2D&);
    
    void set_position_and_angle(const Vector2 &position, float angle);

    Vector2 get_position() const;
    void set_position(const Vector2&);

    float get_angle() const;
    void set_angle(float);

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

class BodyDefB2 : public Reference
{
    GDCLASS(BodyDefB2, Reference);
public:
    /** Lifecycle */
    BodyDefB2();
    ~BodyDefB2();

    /** Getters/setters */
    BOX2D_GET_SET(int, body_type);
    BOX2D_GET_SET_DATA(Vector2, position);
    BOX2D_GET_SET(float, angle);
    BOX2D_GET_SET_DATA(Vector2, linear_velocity);
    BOX2D_GET_SET(float, angular_velocity);
    BOX2D_GET_SET(float, linear_damping);
    BOX2D_GET_SET(float, angular_damping);
    BOX2D_GET_SET(bool, allow_sleep);
    BOX2D_GET_SET(bool, awake);
    BOX2D_GET_SET(bool, fixed_rotation);
    BOX2D_GET_SET(bool, bullet);
    BOX2D_GET_SET(bool, active);
    BOX2D_GET_SET(float, gravity_scale);
    BOX2D_GET_SET_DATA(Variant, metadata);

    /** Create body */
    class BodyB2 *instance(class WorldB2*);

protected:
    /** Internal definition */
    struct b2BodyDef *def;
    Variant metadata;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

// BOX2D_GET_SET\(([^,]+), (\w+)\);
// $1 FixtureDefB2::get_$2() const\n{\n\treturn def->$2;\n}\n\nvoid FixtureDefB2::set_$2($1 rhs)\n{\n\tdef->$2 = rhs;\n}\n
