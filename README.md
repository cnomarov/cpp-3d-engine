<div align="center">

# Educational 3D Engine

**A from-scratch software renderer for learning how 3D engines work.**

![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Renderer](https://img.shields.io/badge/renderer-CPU%20%2F%20software-6C5CE7?style=flat-square)
![Status](https://img.shields.io/badge/status-learning%20%26%20planning-F2C94C?style=flat-square)

*3D math · rendering · animation · geometry · physics*

</div>

This project is a hands-on companion to *3D Math Primer for Graphics and Game Development*. It turns each concept from the book into a visible, working part of a small C++ engine.

The project is intentionally educational rather than production-oriented. The goal is to implement the important math and engine systems manually, understand why they work, and immediately visualize each concept instead of leaving it as abstract theory.

> **Current focus:** Phases 0 and 1 are complete. Phase 2 is in progress: `Vec3`, `Vec4`, `Mat3`, and the foundational `Mat4` operations are implemented and tested. The next step is composing scale, rotation, and translation transforms.

## Contents

- [Goals and philosophy](#project-goals)
- [Technology](#planned-tech-stack)
- [Roadmap](#roadmap)
- [Planned architecture](#intended-final-result)
- [Current status](#current-status)
- [Learning strategy](#learning-strategy-going-forward)

---

## Project Goals

- Build a working 3D engine from the ground up.
- Implement the core math layer manually:
  - vectors;
  - matrices;
  - quaternions;
  - coordinate-space transformations;
  - projections;
  - interpolation.
- Build a CPU/software rendering pipeline before relying on a graphics API for the actual 3D math.
- Use one continuously growing project instead of isolated chapter exercises.
- Apply every important math concept visually as soon as it is learned.
- Use a **3D human model** as the main visual test object instead of spending the whole project staring at a cube.
- Gradually extend the project into:
  - scene management;
  - geometry queries;
  - object picking;
  - lighting;
  - texturing;
  - skeletal animation;
  - basic physics;
  - curves and splines.

---

## Philosophy

This project follows one rule:

> Learn a concept → implement it → visualize it → move on.

The engine is not intended to compete with Unreal Engine, Unity, Godot, or other production engines.

The point is to understand what those engines are doing underneath.

Diagnostic primitives such as cubes, triangles, spheres, axes, and bounding boxes will still be used when they make a mathematical problem easier to inspect, but the main long-term test object will be a human character model.

---

## Planned Tech Stack

- **Language:** C++
- **Rendering:** CPU/software renderer
- **Window / input / framebuffer:** SDL or GLFW
- **Debug/editor UI later:** Dear ImGui or a similar lightweight library
- **Math:** custom implementation
- **3D assets:** simple low-poly human model initially

### Deliberately avoided in the learning phase

Libraries such as GLM or Eigen will not be used for the core educational math layer.

The project should contain its own implementations of concepts such as:

```text
Vec2
Vec3
Vec4
Mat3
Mat4
Quaternion
Transform
```

The point is not to reinvent these libraries forever. The point is to understand them first.

---

## Roadmap

### Phase 0 — C++ Foundation

Learn only the C++ required to build the project instead of studying the entire language before starting.

- [x] Project structure
- [x] Build system
- [x] Classes and structs
- [x] References and pointers
- [x] RAII and basic resource ownership
- [x] `std::vector`
- [x] File loading
- [x] Basic debugging

---

### Phase 1 — Window and Software Framebuffer

The first milestone is simply getting pixels onto the screen.

- [x] Create a window
- [x] Handle the application loop
- [x] Handle keyboard and mouse input
- [x] Create a software framebuffer
- [x] Draw a pixel
- [x] Draw a line
- [x] Draw a triangle

At this stage the engine does not need a real scene system.

The goal is only to establish:

```text
Application
    ↓
Update
    ↓
Render
    ↓
Framebuffer
    ↓
Window
```

---

### Phase 2 — Math Library

Implement the mathematical foundation manually.

#### Vectors

- [x] `Vec2`
- [x] `Vec3`
- [x] `Vec4`
- [x] Length
- [x] Normalization
- [x] Dot product
- [x] Cross product
- [x] Projection

#### Matrices

- [x] `Mat3`
- [x] `Mat4`
- [x] Matrix multiplication
- [x] Matrix × vector transformation
- [x] Translation
- [x] Rotation
- [x] Scaling
- [ ] Matrix inverse where needed
- [x] Transpose
- [x] Homogeneous coordinates

#### Quaternions

- [ ] Quaternion representation
- [ ] Normalize
- [ ] Conjugate
- [ ] Inverse
- [ ] Quaternion multiplication
- [ ] Axis-angle → quaternion
- [ ] Euler → quaternion
- [ ] Quaternion → Euler
- [ ] Quaternion → matrix
- [ ] Matrix → quaternion
- [ ] Quaternion difference
- [ ] SLERP

---

### Phase 3 — First 3D Rendering Pipeline

Build the core transformation pipeline:

```text
Object Space
    ↓
World Space
    ↓
Camera / View Space
    ↓
Projection
    ↓
Screen Space
```

- [ ] 3D vertices
- [ ] Model matrix
- [ ] View matrix
- [ ] Projection matrix
- [ ] Perspective divide
- [ ] Viewport transformation
- [ ] Wireframe mesh rendering

A cube or simple primitive may be used temporarily here because it is useful for debugging projection errors.

---

### Phase 4 — Camera

Build a controllable perspective camera.

- [ ] Camera transform
- [ ] Position
- [ ] Heading / yaw
- [ ] Pitch
- [ ] View matrix
- [ ] Perspective projection
- [ ] FOV control
- [ ] Near/far clipping configuration
- [ ] Free camera movement
- [ ] Orbit camera experiment

This phase should make concepts such as camera space, spherical coordinates, perspective projection, and FOV visible in real time.

---

### Phase 5 — Human Mesh

Replace the primitive as the main scene object with a simple low-poly human mesh.

Initial version:

```text
Human
└── Mesh
```

The character can initially be completely static.

- [ ] Load vertex data
- [ ] Load triangle/index data
- [ ] Render the mesh in wireframe
- [ ] Apply position
- [ ] Apply rotation
- [ ] Apply scale
- [ ] Move camera around the character

The renderer should treat the human exactly like any other triangle mesh.

---

### Phase 6 — Transform and Orientation Lab

The human character becomes the visual test object for Chapter 8 concepts.

Each entity should eventually contain something similar to:

```text
Transform
├── Position
├── Orientation (Quaternion)
└── Scale
```

Experiments:

- [ ] Rotate the character using Euler angles
- [ ] Convert Euler angles to a quaternion
- [ ] Store runtime orientation as a quaternion
- [ ] Convert quaternion to matrix for rendering
- [ ] Apply incremental quaternion rotation
- [ ] Use angular speed × `deltaTime`
- [ ] SLERP between two orientations
- [ ] Display Euler angles in debug UI
- [ ] Demonstrate Euler gimbal lock at pitch ≈ ±90°
- [ ] Compare Euler interpolation with SLERP

Conceptual runtime flow:

```text
Input / Animation / Physics
          ↓
       Quaternion
          ↓
      Orientation
          ↓
    Rotation Matrix
          ↓
       Vertices
          ↓
       Renderer
```

---

### Scene System

Once basic rendering works, hardcoded objects should become proper scene entities.

```text
Scene
├── Camera
├── Human
├── Ground
└── Other Entities
```

Each entity may gradually gain components such as:

```text
Entity
├── Transform
├── Mesh
├── Material
└── Physics
```

Planned features:

- [ ] Entity representation
- [ ] Scene container
- [ ] Transform component
- [ ] Mesh component
- [ ] Active camera
- [ ] Parent-child hierarchy
- [ ] Local transform
- [ ] World transform

---

#### Scene Hierarchy and Nested Coordinate Spaces

Hierarchy is one of the main practical applications of coordinate-space mathematics.

Example:

```text
Character
└── Arm
    └── Forearm
        └── Hand
```

A point on the hand may conceptually travel through:

```text
Hand Local Space
      ↓
Forearm Space
      ↓
Arm Space
      ↓
Character Space
      ↓
World Space
```

This will be used later for skeletal animation.

---

### Chapter 9 — Geometric Primitives

Chapter 9 concepts will be added directly to the existing engine.

Planned systems:

- [ ] Lines
- [ ] Rays
- [ ] Planes
- [ ] Spheres
- [ ] AABB
- [ ] Triangles
- [ ] Barycentric coordinates
- [ ] Polygon-related utilities

Practical experiments:

- [ ] Visualize rays
- [ ] Visualize planes
- [ ] Draw bounding boxes
- [ ] Draw bounding spheres
- [ ] Ray-plane intersection
- [ ] Ray-sphere intersection
- [ ] Ray-triangle intersection
- [ ] Ray-AABB intersection
- [ ] Mouse picking

Example:

```text
Mouse Position
      ↓
Screen Ray
      ↓
World Ray
      ↓
Intersection Test
      ↓
Selected Entity
```

This will allow clicking directly on the human model inside the scene.

---

### Chapter 10 — Graphics

This phase develops the software renderer into a more complete graphics pipeline.

Planned topics:

- [ ] View frustum
- [ ] Model space
- [ ] World space
- [ ] Camera space
- [ ] Clip space
- [ ] Screen space
- [ ] Indexed triangle meshes
- [ ] Surface normals
- [ ] Backface culling
- [ ] Clipping
- [ ] Triangle rasterization
- [ ] Depth buffer
- [ ] Shading
- [ ] Lighting
- [ ] Texture coordinates
- [ ] Texture mapping
- [ ] Tangent space

The human character should gradually progress from:

```text
wireframe
    ↓
solid triangles
    ↓
depth-tested mesh
    ↓
lit mesh
    ↓
textured character
```

---

### Skeletal Animation

The human model becomes especially useful when skeletal animation is introduced.

Possible hierarchy:

```text
Pelvis
├── Spine
│   └── Chest
│       ├── Neck
│       │   └── Head
│       ├── Left Shoulder
│       │   └── Left Arm
│       │       └── Left Forearm
│       │           └── Left Hand
│       └── Right Shoulder
│           └── Right Arm
├── Left Leg
└── Right Leg
```

Planned features:

- [ ] Skeleton hierarchy
- [ ] Bone local transforms
- [ ] Bone world transforms
- [ ] Quaternion bone orientation
- [ ] Parent-child transform propagation
- [ ] Bind pose
- [ ] Skinning
- [ ] Animation keyframes
- [ ] Quaternion interpolation
- [ ] Head-turn experiment using SLERP
- [ ] Arm and leg animation experiments

This phase should combine several earlier concepts:

```text
Coordinate Spaces
+
Matrices
+
Quaternions
+
Hierarchy
+
Interpolation
=
Skeletal Animation
```

---

### Chapter 11 — Linear Motion

The engine will then gain a basic physics/update layer.

Planned concepts:

- [ ] Position
- [ ] Velocity
- [ ] Acceleration
- [ ] `deltaTime`
- [ ] Numerical integration
- [ ] Constant acceleration
- [ ] Circular motion

Possible component:

```text
PhysicsBody
├── Velocity
└── Acceleration
```

Frame flow:

```text
Input
   ↓
Physics Update
   ↓
Transform
   ↓
Rendering
```

Experiments:

- [ ] Move an object using velocity
- [ ] Accelerate an object
- [ ] Gravity-like falling
- [ ] Circular movement
- [ ] Compare frame-dependent and `deltaTime`-based movement

---

### Chapter 12 — Mechanics and Rigid Bodies

This phase expands the physics system.

Planned concepts:

- [ ] Newton's laws
- [ ] Forces
- [ ] Gravity
- [ ] Friction
- [ ] Springs
- [ ] Momentum
- [ ] Center of mass
- [ ] Impulses
- [ ] Collision response
- [ ] Torque
- [ ] Angular velocity
- [ ] Rotational dynamics
- [ ] Rigid body simulation
- [ ] Rotation integration

Example:

```text
Force
  ↓
Acceleration
  ↓
Velocity
  ↓
Position
```

Rotational equivalent:

```text
Torque
   ↓
Angular Acceleration
   ↓
Angular Velocity
   ↓
Quaternion Orientation
```

Possible test scene:

```text
Scene
├── Human
├── Ground
├── Ball
└── Crate
```

Experiments may include falling objects, collisions, impulses, pushing objects, and rotating rigid bodies.

---

### Chapter 13 — Curves and Splines

Curves should also become visual engine tools rather than isolated equations.

Planned concepts:

- [ ] Hermite curves
- [ ] Bézier curves
- [ ] Splines
- [ ] Catmull-Rom splines

Possible applications:

#### Camera Paths

```text
Point A
   ↓
Point B
   ↓
Point C
   ↓
Point D
```

The camera smoothly follows the resulting curve.

#### NPC Paths

A character can follow a spline through the scene.

#### Debug Curve Editor

- [ ] Render control points
- [ ] Render curve
- [ ] Move control points
- [ ] Visualize tangent directions
- [ ] Move camera or object along the curve

---

### Debug / Editor Tools

A full Unreal-style editor is not a goal.

A small internal editor/debug interface may be added after the renderer and scene system are stable.

Possible layout:

```text
-----------------------------------------
| Scene Hierarchy |                     |
|                 |                     |
| Camera          |      Viewport       |
| Human           |                     |
| Ground          |                     |
|                 |                     |
-----------------------------------------
| Inspector                             |
| Position                              |
| Rotation                              |
| Scale                                 |
-----------------------------------------
```

Planned tools:

- [ ] Scene hierarchy
- [ ] Entity selection
- [ ] Transform inspector
- [ ] Euler rotation fields
- [ ] Bounding-volume visualization
- [ ] Coordinate-axis visualization
- [ ] Ray visualization
- [ ] Physics debug information
- [ ] Curve control points
- [ ] Skeleton visualization

Internally the character may use quaternion orientation while the editor exposes Euler angles for readability.

---

## Intended Final Result

The project is expected to grow into a small educational engine containing systems similar to:

```text
Engine
│
├── Core
│   ├── Application
│   ├── Time
│   └── Input
│
├── Math
│   ├── Vec2 / Vec3 / Vec4
│   ├── Mat3 / Mat4
│   └── Quaternion
│
├── Scene
│   ├── Entity
│   ├── Transform
│   ├── Camera
│   └── Hierarchy
│
├── Renderer
│   ├── Mesh
│   ├── Projection
│   ├── Clipping
│   ├── Rasterization
│   ├── Depth
│   ├── Lighting
│   └── Textures
│
├── Geometry
│   ├── Ray
│   ├── Plane
│   ├── Sphere
│   ├── AABB
│   └── Intersection Tests
│
├── Animation
│   ├── Skeleton
│   ├── Bones
│   ├── Skinning
│   └── Interpolation
│
├── Physics
│   ├── Velocity
│   ├── Forces
│   ├── Collisions
│   ├── Impulses
│   └── Angular Dynamics
│
└── Tools
    ├── Scene Hierarchy
    ├── Inspector
    ├── Debug Drawing
    └── Curve Editor
```

This architecture is a direction, not a requirement to build everything immediately.

---

## Current Status

The theoretical study has currently reached the end of **Chapter 8: Orientation and Angular Displacement**.

Topics already studied include:

- vectors;
- dot and cross products;
- coordinate spaces;
- basis vectors;
- matrices;
- affine transformations;
- homogeneous coordinates;
- perspective projection;
- polar coordinates;
- cylindrical coordinates;
- spherical coordinates;
- orientation;
- Euler angles;
- gimbal lock;
- axis-angle representation;
- exponential maps / rotation vectors;
- quaternions;
- quaternion multiplication;
- quaternion inverse;
- quaternion difference;
- quaternion interpolation;
- SLERP;
- conversions between Euler angles, matrices, and quaternions.

Implementation has completed the C++ foundation, the first visual milestone, and the foundational vector and matrix layer:

- SDL2 window creation and an application loop;
- keyboard and mouse events;
- a CPU-owned software framebuffer;
- pixel, DDA line, and triangle-outline drawing;
- a standalone `SoftwareRenderer` with automated tests;
- tested `Vec2` and `Vec3` implementations;
- `Vec4` point/direction construction using homogeneous `w` values;
- tested `Mat3` identity, scaling, axis rotations, matrix/vector multiplication, matrix multiplication, and transpose;
- tested foundational `Mat4` identity, scaling, axis rotations, translation, matrix/vector multiplication, matrix multiplication, and transpose;
- translation behavior that moves points (`w = 1`) while leaving directions (`w = 0`) unchanged.

The next implementation step is to compose scale, rotation, and translation as `T * R * S`, verify transformation order, and then continue Phase 2 toward quaternions before entering the first 3D rendering pipeline.

---

## Learning Strategy Going Forward

The remaining book should be studied in parallel with development.

Instead of:

```text
Finish the entire book
        ↓
Start engine
```

the project follows:

```text
Read
  ↓
Implement
  ↓
Visualize
  ↓
Experiment
  ↓
Continue Reading
```

The engine itself becomes the notebook.

---

## Non-Goals

At least initially, this project is **not** trying to provide:

- production-ready performance;
- a professional editor;
- a complete ECS;
- networking;
- a commercial asset pipeline;
- Vulkan/OpenGL abstraction;
- AAA rendering;
- a replacement for an existing engine.

Those may become future experiments, but they are not required to achieve the main learning goal.

---

## Why Build This?

Using matrices, quaternions, interpolation, coordinate spaces, physics, and geometry only on paper makes them easy to forget.

The purpose of this engine is to make those concepts visible.

If a quaternion rotates the character, a hierarchy moves the character's hand, a ray selects the mesh, gravity drops an object, or a spline moves the camera, the mathematics is no longer just a formula.

It becomes part of a working system.
