## Box2D integration module for Godot Engine

A simple C++ module integrating the Box2D physics library into Godot Engine. **Development is still in very early stages, everything is untested.**

- Godot: https://godotengine.org
- Box2D: http://box2d.org

### Why?

Godot Engine already contains a very good, albeit simple, 2D physics engine implementation that is more than enough for most games. However, 2D games that require a bit more control and flexibility over its physics could benefit from a bigger and more complex implementation.

### Features

- Integrates Box2D 2.3.2 into Godot as a C++ module.
- No setup required. If you can build Godot from source, you can use this module.
- Does not disable or replace Godot's 2D physics engine.
- Provides easy-to-use Object wrappers for every Box2D entity
  - i.e. `b2World::CreateBody` becomes `b2WorldWrapper.create_body()`
- Full access from C++ and GDScript

### Compilation

- Clone the contents of this repository into `<Your Godot source folder>/modules/box2d`
  - Please note that this project is meant to be used with Godot's **2.1** branch.
- Build and run Godot normally

### License

Released under the [MIT License](LICENSE).
