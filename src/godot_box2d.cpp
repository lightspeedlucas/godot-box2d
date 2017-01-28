
#include <godot_box2d.h>
#include <Box2D/Box2D.h>

Box2D *Box2D::singleton = NULL;

Box2D::Box2D()
{
    ERR_FAIL_COND(singleton);
    singleton = this;
}

Box2D::~Box2D()
{
    singleton = NULL;
}

WorldB2 *Box2D::world(const Vector2 &gravity)
{
    auto o = new b2World(B2(gravity));
    return memnew(WorldB2(o));
}

Ref<ShapeB2> Box2D::circle(const Vector2 &offset, float radius)
{
    auto o = new b2CircleShape;
    o->m_p = B2(offset);
    o->m_radius = radius;
    return memnew(ShapeB2(o));
}

void Box2D::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("world:WorldB2", "gravity:Vector2"), &Box2D::world);

    ObjectTypeDB::bind_method(_MD("circle:ShapeB2", "offset:Vector2", "radius:real"), &Box2D::circle);
}

b2Vec2 B2(const Vector2 &v) { return b2Vec2(v.x, v.y); }
Vector2 GD(const b2Vec2 &v) { return Vector2(v.x, v.y); }

b2AABB B2(const Rect2 &v) { return b2AABB { B2(v.pos), B2(v.pos + v.size) }; }
Rect2 GD(const b2AABB &v) { return Rect2(GD(v.lowerBound), GD(v.upperBound - v.lowerBound)); }
