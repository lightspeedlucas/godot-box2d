
#include "godot_box2d.h"

Box2DFactory *Box2DFactory::singleton = NULL;

Box2DFactory::Box2DFactory()
{
    ERR_FAIL_COND(singleton);
    singleton = this;
}

Box2DFactory::~Box2DFactory()
{
    singleton = NULL;
}

b2WorldRef Box2DFactory::world(const Vector2 &gravity)
{
    return BOX2D_REF(b2World, new b2World(B2(gravity)));
}

void Box2DFactory::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("world:b2WorldWrapper", "gravity:Vector2"), &Box2DFactory::world);
}
