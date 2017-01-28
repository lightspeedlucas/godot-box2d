#ifndef GODOT_SHAPE_B2_H
#define GODOT_SHAPE_B2_H

#include <reference.h>

class ShapeB2 : public Reference
{
    OBJ_TYPE(ShapeB2, Reference);
private:
    /** Lifecycle */
    ShapeB2(class b2Shape*);
    friend class Box2D;

    /** Box2D entity */
    class b2Shape *entity;
public:
    /** Lifecycle */
    ~ShapeB2();

    /** Box2D accessor */
    const class b2Shape *get_b2() const;
};

#endif
