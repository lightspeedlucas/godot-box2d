#pragma once

#include <core/reference.h>

class ShapeB2 : public Reference
{
    GDCLASS(ShapeB2, Reference);
public:
    /** Lifecycle */
    ShapeB2(class b2Shape*, bool);
    ~ShapeB2();

    /** Box2D methods */
    bool test_point(const Transform2D &xf, const Vector2 &point);

    /** Box2D accessor */
    const class b2Shape *get_b2() const;

protected:
    /** Box2D entity */
    class b2Shape *entity;
    bool exclusive;

    /** Godot bindings */
	static void _bind_methods();
};
