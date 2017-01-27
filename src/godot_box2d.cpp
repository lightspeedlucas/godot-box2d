
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
    return GD(new b2World(B2(gravity)));
}

b2BodyRef Box2DFactory::body(b2WorldWrapper *world, b2BodyDefinition *def)
{
    ERR_FAIL_NULL_V(world, NULL);
    ERR_FAIL_NULL_V(def, NULL);
    return GD((*world)->CreateBody(*def));
}

void Box2DFactory::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("world:b2WorldWrapper", "gravity:Vector2"), &Box2DFactory::world);
}
