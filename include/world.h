#pragma once

#include <core/object.h>

class WorldB2 : public Object
{
    GDCLASS(WorldB2, Object);
    BOX2D_CLASS(World);
public:
    /** Box2D methods */
    void step(float timeStep, int velocityIterations, int positionIterations);
    void clear_forces();

    void query_aabb(class FuncRef *callback, const Rect2 &aabb) const;
    void ray_cast(class FuncRef *callback, const Vector2 &a, const Vector2 &b) const;

    Vector2 get_gravity() const;
    void set_gravity(const Vector2&);

    bool is_locked() const;

    bool get_auto_clear_forces() const;
    void set_auto_clear_forces(bool);

    void shift_origin(const Vector2&);

    Variant get_metadata() const;
    void set_metadata(const Variant&);

protected:
    /** Godot bindings */
	static void _bind_methods();
};
