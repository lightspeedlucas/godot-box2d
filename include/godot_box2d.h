#pragma once

#include <core/reference.h>

/***********************************************************************
 * Helpers macros
 **********************************************************************/

#define BOX2D_CLASS(name) \
    protected: class b2##name *entity; Variant metadata; \
    public: name##B2(class b2##name *); ~name##B2(); \
    class b2##name *get_b2() const { return entity; } \
    static name##B2 *get(const b2##name *);

#define BOX2D_PROPERTY(cls, name, type) \
    ClassDB::bind_method(D_METHOD("get_" #name), &cls::get_##name); \
    ClassDB::bind_method(D_METHOD("set_" #name, "value"), &cls::set_##name); \
    ADD_PROPERTY(PropertyInfo(type, #name), "set_" #name, "get_" #name);

#define BOX2D_PROPERTY_ENUM(cls, name, enum) \
    ClassDB::bind_method(D_METHOD("get_" #name), &cls::get_##name); \
    ClassDB::bind_method(D_METHOD("set_" #name, "value"), &cls::set_##name); \
    ADD_PROPERTY(PropertyInfo(Variant::INT, #name, PROPERTY_HINT_ENUM, #enum), "set_" #name, "get_" #name);

#define BOX2D_PROPERTY_BOOL(cls, name) \
    ClassDB::bind_method(D_METHOD("is_" #name), &cls::is_##name); \
    ClassDB::bind_method(D_METHOD("set_" #name, "value"), &cls::set_##name); \
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, #name), "set_" #name, "is_" #name);

#define BOX2D_JOINT(name) \
    private: name##B2(class b2Joint *o) : JointB2(o) {} \
    friend class name##DefB2;

#define BOX2D_GET_SET(type, name) type get_##name() const; void set_##name(type);
#define BOX2D_GET_SET_DATA(type, name) type get_##name() const; void set_##name(const type &);
#define BOX2D_IS_SET(name) bool is_##name() const; void set_##name(bool);

/***********************************************************************
 * Enable conversion from Variant to any class derived from Object
 **********************************************************************/

template<class T>
struct VariantCaster<T*>
{
	static T *cast(const Variant &p_variant)
    {
        return Object::cast_to<T>(p_variant);
	}
};

/***********************************************************************
 * Math interoperability
 **********************************************************************/

struct b2Vec2 B2(const struct Vector2&);
struct Vector2 GD(const struct b2Vec2&);

struct b2AABB B2(const struct Rect2&);
struct Rect2 GD(const struct b2AABB&);

struct b2Transform B2(const struct Transform2D&);
struct Transform2D GD(const struct b2Transform&);

/***********************************************************************
 * Include entities
 **********************************************************************/

#include "world.h"
#include "body.h"
#include "fixture.h"
#include "shape.h"
#include "contact.h"

#include "joint.h"
#include "revolute_joint.h"
#include "mouse_joint.h"

/***********************************************************************
 * Type Factory
 **********************************************************************/
class Box2D : public Object
{
    GDCLASS(Box2D, Object);
public:
    /** Lifecycle */
    Box2D();
    ~Box2D();

    /** Singleton */
    static Box2D *get() { return singleton; }

    /** Creation methods */
    WorldB2 *world(const Vector2 &gravity);
    BodyB2 *body(WorldB2 *world, int type, const Transform2D &xf = Transform2D());
    FixtureB2 *fixture(BodyB2 *body, const ShapeB2 *shape, float density);

    Ref<ShapeB2> circle(const Vector2 &offset, float radius);
    Ref<ShapeB2> box(const Vector2 &extents, const Vector2 &offset = Vector2(), float angle = 0);
    Ref<ShapeB2> poly(const PoolVector2Array &vertices);
    Ref<ShapeB2> edge(const Vector2 &a, const Vector2 &b);
    Ref<ShapeB2> chain(const PoolVector2Array &vertices, bool loop = false);

    /** Query methods */
    bool overlap_fixtures(FixtureB2 *a, FixtureB2 *b);
    bool overlap_shapes(ShapeB2 *a, ShapeB2 *b, const Transform2D &xf_a, const Transform2D &xf_b);

protected:
    /** Godot bindings */
	static void _bind_methods();

    /** Singleton */
    static Box2D *singleton;
};
