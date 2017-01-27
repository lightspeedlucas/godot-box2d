#ifndef GODOT_BOX2D_H
#define GODOT_BOX2D_H

#include <object.h>
#include <reference.h>

#include <Box2D/Box2D.h>

/***********************************************************************
 * Wraps a Box2D type
 **********************************************************************/
#define WRAP_BOX2D(type) private: type *wrapped; \
    public: inline type##Wrapper(type *o) : wrapped(o) {} \
    operator type*() const { return wrapped; } \
    inline static Ref<type##Wrapper> wrap(type *o) { return o ? memnew(type##Wrapper(o)) : NULL; }

#define BOX2D_REF(type, value) type##Wrapper::wrap(value)

#define WRAP_BOX2D_DEF(type) private: type wrapped; \
    public: inline type##inition() {} \
    inline type##inition(const type &src) : wrapped(src) {} \
    operator const type*() const { return &wrapped; }

#define BOX2D_DEF_FIELD(type, gdname, b2name) \
    inline void set_##gdname(type v) { wrapped.##b2name = (decltype(wrapped.##b2name))v; } \
    inline type get_##gdname() const { return (type)wrapped.##b2name; }

#define BOX2D_DEF_FIELD_COMPLEX(type, gdname, b2name) \
    inline void set_##gdname(const type &v) { wrapped.##b2name = B2(v); } \
    inline type get_##gdname() const { return GD(wrapped.##b2name); }

#define BOX2D_BIND_PROPERTY(cls, name, type) \
    ObjectTypeDB::bind_method(_MD("get_" #name ":" #type), &cls::get_##name); \
    ObjectTypeDB::bind_method(_MD("set_" #name, "value:" #type), &cls::set_##name); \
    ADD_PROPERTY(PropertyInfo(Variant::type, #name), _SCS("set_" #name), _SCS("get_" #name));

/***********************************************************************
 * Enable conversion from Variant to any class derived from Object
 **********************************************************************/
template<class O>
struct VariantCaster<O*>
{
	static O *cast(const Variant &p_variant)
    {
        auto *obj = (Object*)p_variant;
        return obj ? obj->cast_to<O>() : NULL;
	}
};

/***********************************************************************
 * 2D Math interoperability
 **********************************************************************/
static inline b2Vec2 B2(const Vector2 &v) { return b2Vec2(v.x, v.y); }
static inline Vector2 GD(const b2Vec2 &v) { return Vector2(v.x, v.y); }

/***********************************************************************
 * Include entities
 **********************************************************************/
typedef Ref<class b2WorldWrapper> b2WorldRef;
typedef Ref<class b2BodyWrapper> b2BodyRef;

#include "b2_world.h"
#include "b2_body.h"

/***********************************************************************
 * Type Factory
 **********************************************************************/
class Box2DFactory : public Object
{
    OBJ_TYPE(Box2DFactory, Object);
public:
    /** Lifecycle */
    Box2DFactory();
    ~Box2DFactory();

    /** Singleton */
    static Box2DFactory *get() { return singleton; }

    /** Box2D methods */
    b2WorldRef world(const Vector2 &gravity);

protected:
    /** Godot bindings */
	static void _bind_methods();

    /** Singleton */
    static Box2DFactory *singleton;
};

#endif