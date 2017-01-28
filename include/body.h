#ifndef GODOT_BODY_B2_H
#define GODOT_BODY_B2_H

#include <object.h>

class BodyB2 : public Object
{
    OBJ_TYPE(BodyB2, Object);
    BOX2D_CLASS(Body, WorldB2);
public:
    /** Box2D methods */
    class FixtureB2 *create_fixture(const Ref<class ShapeB2> &shape, float density = 1);
    void destroy_fixture(class FixtureB2*);

    Vector2 get_position() const;

    class WorldB2 *get_world() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
