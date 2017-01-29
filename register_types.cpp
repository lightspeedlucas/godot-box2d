/* register_types.cpp */
#include <object_type_db.h>
#include <globals.h>

#include <godot_box2d.h>
#include <Box2D/Box2D.h>

#include "register_types.h"

void register_box2d_types()
{
    b2Log("Box2D version: %d.%d.%d\n", b2_version.major, b2_version.minor, b2_version.revision);

    ObjectTypeDB::register_virtual_type<WorldB2>();

    ObjectTypeDB::register_virtual_type<BodyB2>();
    ObjectTypeDB::register_type<BodyDefB2>();

    ObjectTypeDB::register_virtual_type<FixtureB2>();
    ObjectTypeDB::register_virtual_type<ShapeB2>();

    ObjectTypeDB::register_virtual_type<JointB2>();
    ObjectTypeDB::register_virtual_type<RevoluteJointB2>();
    ObjectTypeDB::register_virtual_type<MouseJointB2>();

    ObjectTypeDB::register_virtual_type<JointDefB2>();
    ObjectTypeDB::register_type<RevoluteJointDefB2>();
    ObjectTypeDB::register_type<MouseJointDefB2>();

    Globals::get_singleton()->add_singleton(Globals::Singleton("Box2D", memnew(Box2D)));
}

void unregister_box2d_types()
{
    memdelete(Box2D::get());
}
