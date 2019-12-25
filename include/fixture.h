#pragma once

#include <core/reference.h>

class FixtureB2 : public Object
{
    GDCLASS(FixtureB2, Object);
    BOX2D_CLASS(Fixture);
public:
    /** Box2D methods */
    Ref<class ShapeB2> get_shape() const;

    bool is_sensor() const;
    void set_sensor(bool);

    int get_filter_category() const;
    void set_filter_category(int);

    int get_filter_mask() const;
    void set_filter_mask(int);

    int get_filter_group() const;
    void set_filter_group(int);

    void refilter();

    class BodyB2 *get_body() const;

    Variant get_metadata() const;
    void set_metadata(const Variant&);

    bool test_point(const Vector2&) const;
    Dictionary ray_cast(const Vector2 &a, const Vector2 &b, int child = 0) const;

    Dictionary get_mass_data() const;

    float get_density() const;
    void set_density(float);

    float get_friction() const;
    void set_friction(float);

    float get_restitution() const;
    void set_restitution(float);

    Rect2 get_aabb(int child = 0) const;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

class FixtureDefB2 : public Reference
{
    GDCLASS(FixtureDefB2, Reference);
public:
    /** Lifecycle */
    FixtureDefB2();
    ~FixtureDefB2();

    /** Getters/setters */
    BOX2D_GET_SET_DATA(Ref<class ShapeB2>, shape);
    BOX2D_GET_SET(float, friction);
    BOX2D_GET_SET(float, restitution);
    BOX2D_GET_SET(float, density);
    BOX2D_GET_SET(bool, sensor);
    BOX2D_GET_SET(int, filter_category);
    BOX2D_GET_SET(int, filter_mask);
    BOX2D_GET_SET(int, filter_group);
    BOX2D_GET_SET_DATA(Variant, metadata);

    /** Create fixture */
    class FixtureB2 *instance(class BodyB2*);

protected:
    /** Internal definition */
    struct b2FixtureDef *def;
    Ref<class ShapeB2> shape;
    Variant metadata;

protected:
    /** Godot bindings */
	static void _bind_methods();
};
