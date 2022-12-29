
#include <godot_box2d.h>
#include "fixture.h"

#include <Box2D/Box2D.h>

FixtureB2::FixtureB2(b2Fixture *entity)
    : entity(entity)
{
    entity->SetUserData(this);
}

FixtureB2::~FixtureB2()
{
    entity->GetBody()->DestroyFixture(entity);
}

Ref<ShapeB2> FixtureB2::get_shape() const
{
    return memnew(ShapeB2(entity->GetShape(), false));
}

bool FixtureB2::is_sensor() const
{
    return entity->IsSensor();
}

void FixtureB2::set_sensor(bool rhs)
{
    entity->SetSensor(rhs);
}

int FixtureB2::get_filter_category() const
{
    return entity->GetFilterData().categoryBits;
}

void FixtureB2::set_filter_category(int rhs)
{
    auto data = entity->GetFilterData();
    data.categoryBits = (uint16)rhs;
    entity->SetFilterData(data);
}

int FixtureB2::get_filter_mask() const
{
    return entity->GetFilterData().maskBits;
}

void FixtureB2::set_filter_mask(int rhs)
{
    auto data = entity->GetFilterData();
    data.maskBits = (uint16)rhs;
    entity->SetFilterData(data);
}

int FixtureB2::get_filter_group() const
{
    return entity->GetFilterData().groupIndex;
}

void FixtureB2::set_filter_group(int rhs)
{
    auto data = entity->GetFilterData();
    data.groupIndex = (int16)rhs;
    entity->SetFilterData(data);
}

void FixtureB2::refilter()
{
    entity->Refilter();
}

BodyB2 *FixtureB2::get_body() const
{
    return BodyB2::get(entity->GetBody());
}

Variant FixtureB2::get_metadata() const
{
    return metadata;
}

void FixtureB2::set_metadata(const Variant &rhs)
{
    metadata = rhs;
}

bool FixtureB2::test_point(const Vector2 &point) const
{
    return entity->TestPoint(B2(point));
}

Dictionary FixtureB2::ray_cast(const Vector2 &a, const Vector2 &b, int child) const
{
    b2RayCastInput input { B2(a), B2(b), 1.f };
    b2RayCastOutput out;
    Dictionary r;

    if (entity->RayCast(&out, input, child))
    {
        r["normal"] = GD(out.normal);
        r["fraction"] = out.fraction;
    }

    return r;
}

Dictionary FixtureB2::get_mass_data() const
{
    b2MassData data;
    entity->GetMassData(&data);

    Dictionary r;
    r["mass"] = data.mass;
    r["center"] = GD(data.center);
    r["inertia"] = data.I;
    return r;
}

float FixtureB2::get_density() const
{
    return entity->GetDensity();
}

void FixtureB2::set_density(float rhs)
{
    entity->SetDensity(rhs);
}

float FixtureB2::get_friction() const
{
    return entity->GetFriction();
}

void FixtureB2::set_friction(float rhs)
{
    entity->SetFriction(rhs);
}

float FixtureB2::get_restitution() const
{
    return entity->GetRestitution();
}

void FixtureB2::set_restitution(float rhs)
{
    entity->SetRestitution(rhs);
}

Rect2 FixtureB2::get_aabb(int child) const
{
    return GD(entity->GetAABB(child));
}

void FixtureB2::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_shape"), &FixtureB2::get_shape);

    BOX2D_PROPERTY_BOOL(FixtureB2, sensor);

    BOX2D_PROPERTY(FixtureB2, filter_category, Variant::INT);
    BOX2D_PROPERTY(FixtureB2, filter_mask, Variant::INT);
    BOX2D_PROPERTY(FixtureB2, filter_group, Variant::INT);

    ClassDB::bind_method(D_METHOD("refilter"), &FixtureB2::refilter);

    ClassDB::bind_method(D_METHOD("get_body"), &FixtureB2::get_body);

    BOX2D_PROPERTY(FixtureB2, metadata, Variant::NIL);

    ClassDB::bind_method(D_METHOD("test_point", "point"), &FixtureB2::test_point);
    ClassDB::bind_method(D_METHOD("ray_cast", "a", "b", "childIndex"), &FixtureB2::ray_cast, DEFVAL(0));

    ClassDB::bind_method(D_METHOD("get_mass_data"), &FixtureB2::get_mass_data);

    BOX2D_PROPERTY(FixtureB2, density, Variant::REAL);
    BOX2D_PROPERTY(FixtureB2, friction, Variant::REAL);
    BOX2D_PROPERTY(FixtureB2, restitution, Variant::REAL);

    ClassDB::bind_method(D_METHOD("get_aabb", "childIndex"), &FixtureB2::get_aabb, DEFVAL(0));
}

FixtureB2 *FixtureB2::get(const b2Fixture *o)
{
    return (FixtureB2*)o->GetUserData();
}

FixtureDefB2::FixtureDefB2()
    : def(memnew(b2FixtureDef))
{
}

FixtureDefB2::~FixtureDefB2()
{
    memdelete(def);
}

FixtureB2 *FixtureDefB2::instance(BodyB2 *body)
{
    ERR_FAIL_NULL_V(body, NULL);
    auto *o = body->get_b2()->CreateFixture(def);

    auto *fixture = memnew(FixtureB2(o));
    fixture->set_metadata(metadata);

    return fixture;
}

Ref<ShapeB2> FixtureDefB2::get_shape() const
{
	return shape;
}

void FixtureDefB2::set_shape(const Ref<ShapeB2> &rhs)
{
    def->shape = rhs.is_null() ? NULL : rhs->get_b2();
	shape = rhs;
}

float FixtureDefB2::get_friction() const
{
	return def->friction;
}

void FixtureDefB2::set_friction(float rhs)
{
	def->friction = rhs;
}

float FixtureDefB2::get_restitution() const
{
	return def->restitution;
}

void FixtureDefB2::set_restitution(float rhs)
{
	def->restitution = rhs;
}

float FixtureDefB2::get_density() const
{
	return def->density;
}

void FixtureDefB2::set_density(float rhs)
{
	def->density = rhs;
}

bool FixtureDefB2::get_sensor() const
{
	return def->isSensor;
}

void FixtureDefB2::set_sensor(bool rhs)
{
	def->isSensor = rhs;
}

int FixtureDefB2::get_filter_category() const
{
	return def->filter.categoryBits;
}

void FixtureDefB2::set_filter_category(int rhs)
{
    def->filter.categoryBits = (uint16)rhs;
}

int FixtureDefB2::get_filter_mask() const
{
	return def->filter.maskBits;
}

void FixtureDefB2::set_filter_mask(int rhs)
{
    def->filter.maskBits = (uint16)rhs;
}

int FixtureDefB2::get_filter_group() const
{
	return def->filter.groupIndex;
}

void FixtureDefB2::set_filter_group(int rhs)
{
    def->filter.groupIndex = (int16)rhs;
}

Variant FixtureDefB2::get_metadata() const
{
	return metadata;
}

void FixtureDefB2::set_metadata(const Variant& rhs)
{
	metadata = rhs;
}

void FixtureDefB2::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("instance", "body"), &FixtureDefB2::instance);

    BOX2D_PROPERTY(FixtureDefB2, shape, Variant::OBJECT);
    BOX2D_PROPERTY(FixtureDefB2, friction, Variant::REAL);
    BOX2D_PROPERTY(FixtureDefB2, restitution, Variant::REAL);
    BOX2D_PROPERTY(FixtureDefB2, density, Variant::REAL);
    BOX2D_PROPERTY(FixtureDefB2, sensor, Variant::BOOL);
    BOX2D_PROPERTY(FixtureDefB2, filter_category, Variant::INT);
    BOX2D_PROPERTY(FixtureDefB2, filter_mask, Variant::INT);
    BOX2D_PROPERTY(FixtureDefB2, filter_group, Variant::INT);
}
