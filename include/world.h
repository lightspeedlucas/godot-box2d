#ifndef GODOT_WORLD_B2_H
#define GODOT_WORLD_B2_H

#include <object.h>

class WorldB2 : public Object
{
    OBJ_TYPE(WorldB2, Object);
    BOX2D_CLASS(World, Box2D);
public:
    /** Box2D methods */
    class BodyB2 *create_body(int type, const Vector2 &position = Vector2(), float angle = .0f);
    void destroy_body(class BodyB2*);

    class JointB2 *create_joint(const class JointDefB2*);
    void destroy_joint(class JointB2*);

    void step(float timeStep, int velocityIterations, int positionIterations);

    Vector2 get_gravity() const;
    void set_gravity(const Vector2&);

    bool is_locked() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
