
#include <godot_box2d.h>
#include "shape.h"

#include <Box2D/Box2D.h>

ShapeB2::ShapeB2(b2Shape *entity, bool exclusive)
    : entity(entity), exclusive(exclusive)
{
}

ShapeB2::~ShapeB2()
{
    if (exclusive && entity) memdelete(entity);
}

bool ShapeB2::test_point(const Transform2D &xf, const Vector2 &point)
{
    return entity->TestPoint(B2(xf), B2(point));
}

void ShapeB2::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_point", "transform", "point"), &ShapeB2::test_point);
}

const b2Shape *ShapeB2::get_b2() const
{
    return entity;
}
