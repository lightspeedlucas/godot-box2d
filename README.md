## Box2D integration module for Godot Engine

A simple C++ module integrating the Box2D physics library into Godot Engine. **Development is still in very early stages, everything is untested.**

- Godot: https://godotengine.org
- Box2D: http://box2d.org

### Why?

Godot Engine already contains a very good, albeit simple, 2D physics engine implementation that is more than enough for most games. However, 2D games that require a bit more control and flexibility over its physics could benefit from a bigger and more complex implementation.

### Features

- Integrates Box2D 3.1.2 into Godot as a C++ module.
- No setup required. If you can build Godot from source, you can use this module.
- Does **not** disable or replace Godot's 2D physics engine.
- Provides Object wrappers for every Box2D entity
  - i.e. `b2World` becomes `WorldB2`
- Full access from C++ and GDScript

### Compilation

- Clone the contents of this repository into `<Your Godot source folder>/modules/box2d`
  - Please note that this project is meant to be used with Godot's **3.1** branch.
- Build and run Godot normally

### How to use

This module attempts to mimick Box2D's API while remining faithful to Godot's naming standard. Remember that units are all in the KMS system.

<table>
<tr><th>Box2D API</th><th>GDScript</th></tr>
<tr>
<td><pre><code class="language-c++">
// Create world
b2World world(b2Vec2(0.f, -10.f));
// Create a dynamic body
b2BodyDef bodyDef;
bodyDef.type = b2_dynamicBody;
bodyDef.position.Set(0.f, 4.f);
b2Body *body = world.CreateBody(&bodyDef);
// Define a box
b2PolygonShape dynamicBox;
dynamicBox.SetAsBox(1.f, 1.f);
// Attach the box to the dynamic body
b2FixtureDef fixtureDef;
fixtureDef.shape = &dynamicBox;
fixtureDef.density = 1.f;
body->CreateFixture(&fixtureDef);
// Simulate world
world.Step(1.f / 60.f, 6, 2);
</code></pre></td>
<td><pre><code class="language-python">
# Create world
var world = Box2D.world(Vector2(0, -10))
# Create a dynamic body
var bodyDef = BodyDefB2.new()
bodyDef.body_type = BodyB2.DYNAMIC
bodyDef.position = Vector2(0, 4)
var body = bodyDef.instance(world)
# Define a box
var dynamicBox = Box2D.box(Vector2(1, 1))
# Attach the box to the dynamic body
var fixtureDef = FixtureDefB2.new()
fixtureDef.shape = dynamicBox
fixtureDef.density = 1
fixtureDef.instance(body)
# Simulate world
world.step(1 / 60, 6, 2)
</code></pre></td>
</tr>
</table>

Instead of the `Create`/`Destroy` combo (i.e. `CreateJoint`/`DestroyJoint`), Godot's familiar `instance()`/`free()` functions are used.

<table>
<tr><th>Box2D API</th><th>GDScript</th></tr>
<tr>
<td><pre><code class="language-c++">
// Create and destroy a body
b2Body *body = world.CreateBody(&bodyDef);
world.DestroyBody(body);
// Create and destroy a joint
b2Joint *joint = world.CreateJoint(&jointDef);
world.DestroyJoint(joint);
</code></pre></td>
<td><pre><code class="language-python">
# Create and destroy a body
var body = bodyDef.instance(world)
body.free()
# Create and destroy a joint
var joint = jointDef.instance(world)
joint.free()
</code></pre></td>
</tr>
</table>

Same as Box2D's regular API, destroying a parent object automatically destroys its children.

<table>
<tr><th>Box2D API</th><th>GDScript</th></tr>
<tr>
<td><pre><code class="language-c++">
auto fixture = body->CreateFixture(&fixtureDef);
world.DestroyBody(body);
fixture->SetSensor(true); // ERROR
</code></pre></td>
<td><pre><code class="language-python">
var fixture = fixtureDef.instance(body)
body.free()
fixture.set_sensor(true) # ERROR
</code></pre></td>
</tr>
</table>

The singleton `Box2D` provides functions for creating shapes and shortcuts for bodies and fixtures. (bypassing the need to create `BodyDefB2` and `FixtureDefB2`)

```python
# Shapes
shape = Box2D.box(Vector2(1, 1))
shape = Box2D.circle(Vector2(), 0.5)
# Shortcuts
body = Box2D.body(world, BodyB2.STATIC)
fixture = Box2D.fixture(body, shape, density)
```

This is all the documentation I have for this module, since it's in very early stages. If you know Box2D's API well enough, looking into the headers should point you in the right direction.

### License

Released under the [MIT License](LICENSE).
