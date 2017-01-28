#ifndef GODOT_FIXTURE_B2_H
#define GODOT_FIXTURE_B2_H

#include <reference.h>

class FixtureB2 : public Object
{
    OBJ_TYPE(FixtureB2, Object);
    BOX2D_CLASS(Fixture, BodyB2);
public:
    /** Box2D methods */
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

// class FilterB2 : public Reference
// {
//     OBJ_TYPE(FilterB2, Reference);
// public:
//     /** Lifecycle */
//     FilterB2();
//     FilterB2(const struct b2Filter&);
//     ~FilterB2();

//     /** Getters/setters */
//     int get_category() const;
//     void set_category(int);

//     int get_mask() const;
//     void set_mask(int);

//     int get_group() const;
//     void set_group(int);

//     /** Box2D accessor */
//     struct b2Filter get_b2() const;

// private:
//     /** Internal definition */
//     struct b2Filter *filter;

// protected:
//     /** Godot bindings */
// 	static void _bind_methods();
// };

#endif
