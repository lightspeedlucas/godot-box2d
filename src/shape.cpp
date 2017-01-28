
#include <godot_box2d.h>
#include "shape.h"

#include <Box2D/Box2D.h>

ShapeB2::ShapeB2(b2Shape *entity)
    : entity(entity)
{
    b2Log("Created a shape...");
}

ShapeB2::~ShapeB2()
{
    b2Log("Deleting shape...");
    memdelete(entity);
}

const class b2Shape *ShapeB2::get_b2() const
{
    return entity;
}
