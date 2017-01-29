
#include <godot_box2d.h>
#include "shape.h"

#include <Box2D/Box2D.h>

ShapeB2::ShapeB2(b2Shape *entity)
    : entity(entity)
{
}

ShapeB2::~ShapeB2()
{
    memdelete(entity);
}

const b2Shape *ShapeB2::get_b2() const
{
    return entity;
}
