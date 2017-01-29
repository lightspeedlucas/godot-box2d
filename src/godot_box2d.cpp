
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

BodyB2 *Box2D::body(WorldB2 *world, int type, const Matrix32 &xf)
{
    ERR_FAIL_NULL_V(world, NULL);

    static b2BodyDef def;
    def.type = (b2BodyType)type;
    def.position = B2(xf.get_origin());
    def.angle = xf.get_rotation();

    auto *o = world->get_b2()->CreateBody(&def);
    return memnew(BodyB2(o));
}

FixtureB2 *Box2D::fixture(BodyB2 *body, const ShapeB2 *shape, float density)
{
    ERR_FAIL_NULL_V(body, NULL);
    ERR_FAIL_NULL_V(shape, NULL);

    auto *o = body->get_b2()->CreateFixture(shape->get_b2(), density);
    return memnew(FixtureB2(o));
}

Ref<ShapeB2> Box2D::circle(const Vector2 &offset, float radius)
{
    auto o = new b2CircleShape;
    o->m_p = B2(offset);
    o->m_radius = radius;
    return memnew(ShapeB2(o));
}

Ref<ShapeB2> Box2D::box(const Vector2 &extents, const Vector2 &offset, float angle)
{
    auto o = new b2PolygonShape;
    o->SetAsBox(extents.x, extents.y, B2(offset), angle);
    return memnew(ShapeB2(o));
}

Ref<ShapeB2> Box2D::poly(const Vector2Array &vertices)
{
    auto r = vertices.read();
    auto o = new b2PolygonShape;
    o->Set((b2Vec2*)r.ptr(), vertices.size());
    return memnew(ShapeB2(o));
}

Ref<ShapeB2> Box2D::edge(const Vector2 &a, const Vector2 &b)
{
    auto o = new b2EdgeShape;
    o->Set(B2(a), B2(b));
    return memnew(ShapeB2(o));
}

Ref<ShapeB2> Box2D::chain(const Vector2Array &vertices, bool loop)
{
    auto r = vertices.read();
    auto o = new b2ChainShape;
    if (loop)
        o->CreateLoop((b2Vec2*)r.ptr(), vertices.size());
    else
        o->CreateChain((b2Vec2*)r.ptr(), vertices.size());
    return memnew(ShapeB2(o));
}

void Box2D::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("world:WorldB2", "gravity:Vector2"), &Box2D::world);
    ObjectTypeDB::bind_method(_MD("body:BodyB2", "world:WorldB2", "type:int", "transform:Matrix32"), &Box2D::body, DEFVAL(Matrix32()));
    ObjectTypeDB::bind_method(_MD("fixture:FixtureB2", "body:BodyB2", "shape:ShapeB2", "density:real"), &Box2D::fixture);

    ObjectTypeDB::bind_method(_MD("circle:ShapeB2", "offset:Vector2", "radius:real"), &Box2D::circle);
    ObjectTypeDB::bind_method(_MD("box:ShapeB2", "extents:Vector2", "offset:Vector2", "angle:real"), &Box2D::box, DEFVAL(Vector2()), DEFVAL(.0f));
    ObjectTypeDB::bind_method(_MD("poly:ShapeB2", "vertices:Vector2Array"), &Box2D::poly);
    ObjectTypeDB::bind_method(_MD("edge:ShapeB2", "a:Vector2", "b:Vector2"), &Box2D::edge);
    ObjectTypeDB::bind_method(_MD("chain:ShapeB2", "vertices:Vector2Array", "loop:bool"), &Box2D::poly, DEFVAL(false));
}

b2Vec2 B2(const Vector2 &v) { return b2Vec2(v.x, v.y); }
Vector2 GD(const b2Vec2 &v) { return Vector2(v.x, v.y); }

b2AABB B2(const Rect2 &v) { return b2AABB { B2(v.pos), B2(v.pos + v.size) }; }
Rect2 GD(const b2AABB &v) { return Rect2(GD(v.lowerBound), GD(v.upperBound - v.lowerBound)); }

b2Transform B2(const Matrix32 &v)
{
    b2Transform xf;
    xf.p = { v.elements[2].x, v.elements[2].y };
    xf.q.s = v.elements[1].x;
    xf.q.c = v.elements[1].y;
    return xf;
}

Matrix32 GD(const b2Transform &v)
{
    return Matrix32(v.q.c, -v.q.s, v.q.s, v.q.c, v.p.x, v.p.y);
}
