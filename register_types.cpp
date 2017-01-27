/* register_types.cpp */
#include <object_type_db.h>
#include <globals.h>

#include "register_types.h"
#include "godot_box2d.h"

void register_box2d_types()
{
    b2Log("Box2D version: %d.%d.%d\n", b2_version.major, b2_version.minor, b2_version.revision);

    ObjectTypeDB::register_virtual_type<b2WorldWrapper>();
    ObjectTypeDB::register_virtual_type<b2BodyWrapper>();

    ObjectTypeDB::register_type<b2BodyDefinition>();

    auto *factory = memnew(Box2DFactory);

    auto *globals = Globals::get_singleton();
    globals->add_singleton(Globals::Singleton("Box2DFactory", factory));
}

void unregister_box2d_types()
{
    memdelete(Box2DFactory::get());
}
