#ifndef GODOT_B2_WORLD_H
#define GODOT_B2_WORLD_H

#include <reference.h>

class b2WorldWrapper : public Reference
{
    OBJ_TYPE(b2WorldWrapper, Reference);
    WRAP_BOX2D(b2World);
public:
    /** Box2D methods */
    b2BodyRef create_body(class b2BodyDefinition*);
    void destroy_body(class b2BodyWrapper*);

    void step(float timeStep, int velocityIterations, int positionIterations);

    Vector2 get_gravity() const;
    void set_gravity(const Vector2&);

    bool is_locked() const;

    /** Helpers methods */
    void destroy();

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
