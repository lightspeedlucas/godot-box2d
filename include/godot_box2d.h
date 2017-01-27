#ifndef GODOT_BOX2D_H
#define GODOT_BOX2D_H

#include <object.h>
#include <reference.h>

#include <Box2D/Box2D.h>

/***********************************************************************
 * Helpers macros
 **********************************************************************/

#define WRAP_BOX2D(type) private: type *wrapped; \
    public: inline type##Wrapper(type *o) : wrapped(o) {} \
    operator type*() const { return wrapped; } \
    type *operator->() { return wrapped; } \
    inline static Ref<type##Wrapper> wrap(type *o) { return o ? memnew(type##Wrapper(o)) : NULL; }

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

#define BOX2D_GD(type) static inline Ref<type##Wrapper> GD(type *o) { return type##Wrapper::wrap(o); }

#define BOX2D_DECL(type) class type##Wrapper; class type##Definition; \
    typedef Ref<type##Wrapper> type##Ref;

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
 * Math interoperability
 **********************************************************************/

static inline b2Vec2 B2(const Vector2 &v) { return b2Vec2(v.x, v.y); }
static inline Vector2 GD(const b2Vec2 &v) { return Vector2(v.x, v.y); }

/***********************************************************************
 * Include entities
 **********************************************************************/

BOX2D_DECL(b2World);
BOX2D_DECL(b2Body);

#include "b2_world.h"
#include "b2_body.h"

BOX2D_GD(b2World);
BOX2D_GD(b2Body);

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
    b2BodyRef body(b2WorldWrapper *world, b2BodyDefinition *def);

protected:
    /** Godot bindings */
	static void _bind_methods();

    /** Singleton */
    static Box2DFactory *singleton;
};

#endif