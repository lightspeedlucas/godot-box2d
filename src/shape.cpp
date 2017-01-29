
#include <godot_box2d.h>
#include "shape.h"

#include <Box2D/Box2D.h>

ShapeB2::ShapeB2(b2Shape *entity, bool exclusive)
    : entity(entity), exclusive(exclusive)
{
}

ShapeB2::~ShapeB2()
{
    if (exclusive) memdelete(entity);
}

bool ShapeB2::test_point(const Matrix32 &xf, const Vector2 &point)
{
    return entity->TestPoint(B2(xf), B2(point));
}

void ShapeB2::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("test_point:bool", "transform:Matrix32", "point:Vector2"), &ShapeB2::test_point);
}

const b2Shape *ShapeB2::get_b2() const
{
    return entity;
}
