#ifndef GODOT_BOX2D_H
#define GODOT_BOX2D_H

#include <object.h>
#include <reference.h>

/***********************************************************************
 * Helpers macros
 **********************************************************************/

#define BOX2D_CLASS(name, parent) \
    private: class b2##name *entity; Variant metadata; \
    name##B2(class b2##name *); friend class parent; \
    public: ~name##B2(); \
    class b2##name *get_b2() const { return entity; } \
    static name##B2 *get(const b2##name *);

#define BOX2D_PROPERTY(cls, name, type, typename) \
    ObjectTypeDB::bind_method(_MD("get_" #name ":" typename), &cls::get_##name); \
    ObjectTypeDB::bind_method(_MD("set_" #name, "value:" typename), &cls::set_##name); \
    ADD_PROPERTY(PropertyInfo(type, #name), _SCS("set_" #name), _SCS("get_" #name));


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

struct b2Vec2 B2(const struct Vector2&);
struct Vector2 GD(const struct b2Vec2&);
struct Rect2 GD(const struct b2AABB&);

/***********************************************************************
 * Include entities
 **********************************************************************/

#include "world.h"
#include "body.h"
#include "fixture.h"
#include "shape.h"
#include "joint.h"

/***********************************************************************
 * Type Factory
 **********************************************************************/
class Box2D : public Object
{
    OBJ_TYPE(Box2D, Object);
public:
    /** Lifecycle */
    Box2D();
    ~Box2D();

    /** Singleton */
    static Box2D *get() { return singleton; }

    /** Box2D methods */
    WorldB2 *world(const Vector2 &gravity);

    Ref<ShapeB2> circle(const Vector2 &offset, float radius);

protected:
    /** Godot bindings */
	static void _bind_methods();

    /** Singleton */
    static Box2D *singleton;
};

#endif