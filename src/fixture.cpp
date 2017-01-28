
#include <godot_box2d.h>
#include "fixture.h"

#include <Box2D/Box2D.h>

FixtureB2::FixtureB2(b2Fixture *entity)
    : entity(entity)
{
    entity->SetUserData(this);
    b2Log("Created fixture...\n");
}

FixtureB2::~FixtureB2()
{
    b2Log("Deleting fixture...\n");
    entity->GetBody()->DestroyFixture(entity);
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
    Dictionary r(true);

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

    Dictionary r(true);
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
    ObjectTypeDB::bind_method(_MD("is_sensor:bool"), &FixtureB2::is_sensor);
    ObjectTypeDB::bind_method(_MD("set_sensor", "enabled:bool"), &FixtureB2::set_sensor);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "sensor"), _SCS("set_sensor"), _SCS("is_sensor"));

    BOX2D_PROPERTY(FixtureB2, filter_category, Variant::INT, "int");
    BOX2D_PROPERTY(FixtureB2, filter_mask, Variant::INT, "int");
    BOX2D_PROPERTY(FixtureB2, filter_group, Variant::INT, "int");

    ObjectTypeDB::bind_method(_MD("refilter"), &FixtureB2::refilter);

    ObjectTypeDB::bind_method(_MD("get_body:BodyB2"), &FixtureB2::get_body);

    BOX2D_PROPERTY(FixtureB2, metadata, Variant::NIL, "Variant");

    ObjectTypeDB::bind_method(_MD("test_point:bool", "point:Vector2"), &FixtureB2::test_point);
    ObjectTypeDB::bind_method(_MD("ray_cast:Dictionary", "a:Vector2", "b:Vector2", "childIndex:int"), &FixtureB2::ray_cast, DEFVAL(0));

    ObjectTypeDB::bind_method(_MD("get_mass_data:Dictionary"), &FixtureB2::get_mass_data);

    BOX2D_PROPERTY(FixtureB2, density, Variant::REAL, "real");
    BOX2D_PROPERTY(FixtureB2, friction, Variant::REAL, "real");
    BOX2D_PROPERTY(FixtureB2, restitution, Variant::REAL, "real");

    ObjectTypeDB::bind_method(_MD("get_aabb:Rect2", "childIndex:int"), &FixtureB2::get_aabb, DEFVAL(0));
}

FixtureB2 *FixtureB2::get(const b2Fixture *o)
{
    return (FixtureB2*)o->GetUserData();
}

// FilterB2::FilterB2() : filter(new b2Filter) {}
// FilterB2::FilterB2(const b2Filter &filter) : filter(new b2Filter(filter)) {}
// FilterB2::~FilterB2() { delete filter; }

// int FilterB2::get_category() const { return filter->categoryBits; }
// void FilterB2::set_category(int o) { filter->categoryBits = (uint16)o; }

// int FilterB2::get_mask() const { return filter->maskBits; }
// void FilterB2::set_mask(int o) { filter->maskBits = (uint16)o; }

// int FilterB2::get_group() const { return filter->groupIndex; }
// void FilterB2::set_group(int o) { filter->groupIndex = (int16)o; }

// b2Filter FilterB2::get_b2() const { return *filter; }

// void FilterB2::_bind_methods()
// {
//     BOX2D_PROPERTY(FilterB2, category, Variant::INT, "int");
//     BOX2D_PROPERTY(FilterB2, mask, Variant::INT, "int");
//     BOX2D_PROPERTY(FilterB2, group, Variant::INT, "int");
// }