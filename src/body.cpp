
#include <godot_box2d.h>
#include "body.h"

#include <Box2D/Box2D.h>

BodyB2::BodyB2(b2Body *entity)
    : entity(entity)
{
    entity->SetUserData(this);
    b2Log("Created body...\n");
}

BodyB2::~BodyB2()
{
    // Destroy all joints
    while (auto *e = entity->GetJointList())
        memdelete_notnull(JointB2::get(e->joint));

    // Destroy all fixtures
    while (auto *o = entity->GetFixtureList())
        memdelete_notnull(FixtureB2::get(o));

    b2Log("Deleting body...\n");
    entity->GetWorld()->DestroyBody(entity);
}

FixtureB2 *BodyB2::create_fixture(const Ref<ShapeB2> &shape, float density)
{
    ERR_FAIL_COND_V(shape.is_null(), NULL);
    auto *fixture = entity->CreateFixture(shape->get_b2(), density);
    return memnew(FixtureB2(fixture));
}

void BodyB2::destroy_fixture(FixtureB2 *fixture)
{
    ERR_FAIL_NULL(fixture);
    memdelete(fixture);
}

void BodyB2::set_transform(const Vector2 &position, float angle)
{
    entity->SetTransform(B2(position), angle);
}

Vector2 BodyB2::get_position() const
{
    return GD(entity->GetPosition());
}

float BodyB2::get_angle() const
{
    return entity->GetAngle();
}

Vector2 BodyB2::get_world_center() const
{
    return GD(entity->GetWorldCenter());
}

Vector2 BodyB2::get_local_center() const
{
    return GD(entity->GetLocalCenter());
}

Vector2 BodyB2::get_linear_velocity() const
{
    return GD(entity->GetLinearVelocity());
}

void BodyB2::set_linear_velocity(const Vector2 &rhs)
{
    entity->SetLinearVelocity(B2(rhs));
}

float BodyB2::get_angular_velocity() const
{
    return entity->GetAngularVelocity();
}

void BodyB2::set_angular_velocity(float rhs)
{
    entity->SetAngularVelocity(rhs);
}

void BodyB2::apply_force_at(const Vector2 &force, const Vector2 &point, bool wake)
{
    entity->ApplyForce(B2(force), B2(point), wake);
}

void BodyB2::apply_force(const Vector2 &force, bool wake)
{
    entity->ApplyForceToCenter(B2(force), wake);
}

void BodyB2::apply_torque(float torque, bool wake)
{
    entity->ApplyTorque(torque, wake);
}

void BodyB2::apply_angular_impulse(float impulse, bool wake)
{
    entity->ApplyAngularImpulse(impulse, wake);
}

void BodyB2::apply_impulse_at(const Vector2 &impulse, const Vector2 &point, bool wake)
{
    entity->ApplyLinearImpulse(B2(impulse), B2(point), wake);
}

void BodyB2::apply_impulse(const Vector2 &impulse, bool wake)
{
    entity->ApplyLinearImpulseToCenter(B2(impulse), wake);
}

float BodyB2::get_mass() const
{
    return entity->GetMass();
}

float BodyB2::get_inertia() const
{
    return entity->GetInertia();
}

Dictionary BodyB2::get_mass_data() const
{
    b2MassData data;
    entity->GetMassData(&data);

    Dictionary r(true);
    r["mass"] = data.mass;
    r["center"] = GD(data.center);
    r["inertia"] = data.I;
    return r;
}

void BodyB2::set_mass_data(float mass, float inertia, const Vector2 &com)
{
    b2MassData data { mass, B2(com), inertia };
    entity->SetMassData(&data);
}

void BodyB2::reset_mass_data()
{
    entity->ResetMassData();
}

Vector2 BodyB2::get_linear_velocity_at(const Vector2 &point) const
{
    return GD(entity->GetLinearVelocityFromWorldPoint(B2(point)));
}

float BodyB2::get_linear_damping() const
{
    return entity->GetLinearDamping();
}

void BodyB2::set_linear_damping(float rhs)
{
    entity->SetLinearDamping(rhs);
}

float BodyB2::get_angular_damping() const
{
    return entity->GetAngularDamping();
}

void BodyB2::set_angular_damping(float rhs)
{
    entity->SetAngularDamping(rhs);
}

float BodyB2::get_gravity_scale() const
{
    return entity->GetGravityScale();
}

void BodyB2::set_gravity_scale(float rhs)
{
    entity->SetGravityScale(rhs);
}

int BodyB2::get_body_type() const
{
    return entity->GetType();
}

void BodyB2::set_body_type(int rhs)
{
    entity->SetType((b2BodyType)rhs);
}

bool BodyB2::is_bullet() const
{
    return entity->IsBullet();
}

void BodyB2::set_bullet(bool rhs)
{
    entity->SetBullet(rhs);
}

bool BodyB2::is_sleeping_allowed()
{
    return entity->IsSleepingAllowed();
}

void BodyB2::set_sleeping_allowed(bool rhs)
{
    entity->SetSleepingAllowed(rhs);
}

bool BodyB2::is_awake() const
{
    return entity->IsAwake();
}

void BodyB2::set_awake(bool rhs)
{
    entity->SetAwake(rhs);
}

bool BodyB2::is_active() const
{
    return entity->IsActive();
}

void BodyB2::set_active(bool rhs)
{
    entity->SetActive(rhs);
}

bool BodyB2::is_fixed_rotation() const
{
    return entity->IsFixedRotation();
}

void BodyB2::set_fixed_rotation(bool rhs)
{
    entity->SetFixedRotation(rhs);
}

Array BodyB2::get_fixture_list() const
{
    Array v;
    for (auto *e = entity->GetFixtureList(); e; e = e->GetNext())
        v.push_back(FixtureB2::get(e));
    return v;
}

Array BodyB2::get_joint_list() const
{
    Array v;
    for (auto *e = entity->GetJointList(); e; e = e->next)
        v.push_back(JointB2::get(e->joint));
    return v;
}

Variant BodyB2::get_metadata() const
{
    return metadata;
}

void BodyB2::set_metadata(const Variant &rhs)
{
    metadata = rhs;
}

WorldB2 *BodyB2::get_world() const
{
    return WorldB2::get(entity->GetWorld());
}

void BodyB2::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("create_fixture:FixtureB2", "shape:ShapeB2", "density:real"), &BodyB2::create_fixture, DEFVAL(1.f));
    ObjectTypeDB::bind_method(_MD("destroy_fixture", "fixture:FixtureB2"), &BodyB2::destroy_fixture);

    ObjectTypeDB::bind_method(_MD("set_transform", "position:Vector2", "angle:real"), &BodyB2::set_transform);
    ObjectTypeDB::bind_method(_MD("get_position:Vector2"), &BodyB2::get_position);
    ObjectTypeDB::bind_method(_MD("get_angle:real"), &BodyB2::get_angle);

    ObjectTypeDB::bind_method(_MD("get_world_center:Vector2"), &BodyB2::get_world_center);
    ObjectTypeDB::bind_method(_MD("get_local_center:Vector2"), &BodyB2::get_local_center);

    BOX2D_PROPERTY(BodyB2, linear_velocity, Variant::VECTOR2, "Vector2");
    BOX2D_PROPERTY(BodyB2, angular_velocity, Variant::REAL, "real");

    ObjectTypeDB::bind_method(_MD("apply_force_at", "force:Vector2", "point:Vector2", "wake:bool"), &BodyB2::apply_force_at, DEFVAL(true));
    ObjectTypeDB::bind_method(_MD("apply_force", "force:Vector2", "wake:bool"), &BodyB2::apply_force, DEFVAL(true));

    ObjectTypeDB::bind_method(_MD("apply_torque", "torque:real", "wake:bool"), &BodyB2::apply_torque, DEFVAL(true));
    ObjectTypeDB::bind_method(_MD("apply_angular_impulse", "impulse:real", "wake:bool"), &BodyB2::apply_angular_impulse, DEFVAL(true));

    ObjectTypeDB::bind_method(_MD("apply_impulse_at", "impulse:Vector2", "point:Vector2", "wake:bool"), &BodyB2::apply_impulse_at, DEFVAL(true));
    ObjectTypeDB::bind_method(_MD("apply_impulse", "impulse:Vector2", "wake:bool"), &BodyB2::apply_impulse, DEFVAL(true));

    ObjectTypeDB::bind_method(_MD("get_mass:real"), &BodyB2::get_mass);
    ObjectTypeDB::bind_method(_MD("get_inertia:real"), &BodyB2::get_inertia);

    ObjectTypeDB::bind_method(_MD("get_mass_data:Dictionary"), &BodyB2::get_mass_data);
    ObjectTypeDB::bind_method(_MD("set_mass_data", "mass:real", "inertia:real", "com:Vector2"), &BodyB2::set_mass_data);
    ObjectTypeDB::bind_method(_MD("reset_mass_data"), &BodyB2::reset_mass_data);

    ObjectTypeDB::bind_method(_MD("get_linear_velocity_at:Vector2", "point:Vector2"), &BodyB2::get_linear_velocity_at);

    BOX2D_PROPERTY(BodyB2, linear_damping, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyB2, angular_damping, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyB2, gravity_scale, Variant::REAL, "real");
    BOX2D_PROPERTY_ENUM(BodyB2, body_type, "STATIC,DYNAMIC,KINEMATIC");

    BOX2D_PROPERTY_BOOL(BodyB2, bullet);
    BOX2D_PROPERTY_BOOL(BodyB2, sleeping_allowed);
    BOX2D_PROPERTY_BOOL(BodyB2, awake);
    BOX2D_PROPERTY_BOOL(BodyB2, active);
    BOX2D_PROPERTY_BOOL(BodyB2, fixed_rotation);

    ObjectTypeDB::bind_method(_MD("get_fixture_list:Array"), &BodyB2::get_fixture_list);
    ObjectTypeDB::bind_method(_MD("get_joint_list:Array"), &BodyB2::get_joint_list);

    BOX2D_PROPERTY(BodyB2, metadata, Variant::NIL, "Variant");

    ObjectTypeDB::bind_method(_MD("get_world:WorldB2"), &BodyB2::get_world);

    ObjectTypeDB::bind_integer_constant(get_type_static(), "DYNAMIC", b2_dynamicBody);
    ObjectTypeDB::bind_integer_constant(get_type_static(), "KINEMATIC", b2_kinematicBody);
    ObjectTypeDB::bind_integer_constant(get_type_static(), "STATIC", b2_staticBody);
}

BodyB2 *BodyB2::get(const b2Body *o)
{
    return (BodyB2*)o->GetUserData();
}

BodyDefB2::BodyDefB2()
    : def(new b2BodyDef)
{
}

BodyDefB2::~BodyDefB2()
{
    delete def;
}

BodyB2 *BodyDefB2::instance(WorldB2 *world)
{
    ERR_FAIL_NULL_V(world, NULL);
    auto *o = world->get_b2()->CreateBody(def);

    auto *body = memnew(BodyB2(o));
    body->metadata = metadata;

    return body;
}

int BodyDefB2::get_body_type() const
{
    return def->type;
}

void BodyDefB2::set_body_type(int rhs)
{
    def->type = (b2BodyType)rhs;
}

Vector2 BodyDefB2::get_position() const
{
    return GD(def->position);
}

void BodyDefB2::set_position(const Vector2 &rhs)
{
    def->position = B2(rhs);
}

float BodyDefB2::get_angle() const
{
	return def->angle;
}

void BodyDefB2::set_angle(float rhs)
{
	def->angle = rhs;
}

Vector2 BodyDefB2::get_linear_velocity() const
{
    return GD(def->linearVelocity);
}

void BodyDefB2::set_linear_velocity(const Vector2& rhs)
{
    def->linearVelocity = B2(rhs);
}

float BodyDefB2::get_angular_velocity() const
{
	return def->angularVelocity;
}

void BodyDefB2::set_angular_velocity(float rhs)
{
	def->angularVelocity = rhs;
}

float BodyDefB2::get_linear_damping() const
{
	return def->linearDamping;
}

void BodyDefB2::set_linear_damping(float rhs)
{
	def->linearDamping = rhs;
}

float BodyDefB2::get_angular_damping() const
{
	return def->angularDamping;
}

void BodyDefB2::set_angular_damping(float rhs)
{
	def->angularDamping = rhs;
}

bool BodyDefB2::get_allow_sleep() const
{
	return def->allowSleep;
}

void BodyDefB2::set_allow_sleep(bool rhs)
{
	def->allowSleep = rhs;
}

bool BodyDefB2::get_awake() const
{
	return def->awake;
}

void BodyDefB2::set_awake(bool rhs)
{
	def->awake = rhs;
}

bool BodyDefB2::get_fixed_rotation() const
{
	return def->fixedRotation;
}

void BodyDefB2::set_fixed_rotation(bool rhs)
{
	def->fixedRotation = rhs;
}

bool BodyDefB2::get_bullet() const
{
	return def->bullet;
}

void BodyDefB2::set_bullet(bool rhs)
{
	def->bullet = rhs;
}

bool BodyDefB2::get_active() const
{
	return def->active;
}

void BodyDefB2::set_active(bool rhs)
{
	def->active = rhs;
}

float BodyDefB2::get_gravity_scale() const
{
	return def->gravityScale;
}

void BodyDefB2::set_gravity_scale(float rhs)
{
	def->gravityScale = rhs;
}

Variant BodyDefB2::get_metadata() const
{
	return metadata;
}

void BodyDefB2::set_metadata(const Variant& rhs)
{
	metadata = rhs;
}

void BodyDefB2::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("instance:BodyB2", "world:WorldB2"), &BodyDefB2::instance);

    BOX2D_PROPERTY(BodyDefB2, body_type, Variant::INT, "int");
    BOX2D_PROPERTY(BodyDefB2, position, Variant::VECTOR2, "Vector2");
    BOX2D_PROPERTY(BodyDefB2, angle, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyDefB2, linear_velocity, Variant::VECTOR2, "Vector2");
    BOX2D_PROPERTY(BodyDefB2, angular_velocity, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyDefB2, linear_damping, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyDefB2, angular_damping, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyDefB2, allow_sleep, Variant::BOOL, "bool");
    BOX2D_PROPERTY(BodyDefB2, awake, Variant::BOOL, "bool");
    BOX2D_PROPERTY(BodyDefB2, fixed_rotation, Variant::BOOL, "bool");
    BOX2D_PROPERTY(BodyDefB2, bullet, Variant::BOOL, "bool");
    BOX2D_PROPERTY(BodyDefB2, active, Variant::BOOL, "bool");
    BOX2D_PROPERTY(BodyDefB2, gravity_scale, Variant::REAL, "real");
    BOX2D_PROPERTY(BodyDefB2, metadata, Variant::NIL, "Variant");
}
