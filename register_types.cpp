/* register_types.cpp */
#include "register_types.h"

#include <core/class_db.h>
#include <core/engine.h>
#include <godot_box2d.h>
#include <Box2D/Box2D.h>

void register_box2d_types()
{
    b2Log("Box2D version: %d.%d.%d\n", b2_version.major, b2_version.minor, b2_version.revision);

    ClassDB::register_virtual_class<WorldB2>();
    ClassDB::register_virtual_class<ShapeB2>();

    ClassDB::register_virtual_class<BodyB2>();
    ClassDB::register_class<BodyDefB2>();

    ClassDB::register_virtual_class<FixtureB2>();
    ClassDB::register_class<FixtureDefB2>();

    ClassDB::register_virtual_class<JointB2>();
    ClassDB::register_virtual_class<RevoluteJointB2>();
    ClassDB::register_virtual_class<MouseJointB2>();

    ClassDB::register_virtual_class<JointDefB2>();
    ClassDB::register_class<RevoluteJointDefB2>();
    ClassDB::register_class<MouseJointDefB2>();

	Engine::get_singleton()->add_singleton(Engine::Singleton("Box2D", memnew(Box2D)));
}

void unregister_box2d_types()
{
    memdelete(Box2D::get());
}
