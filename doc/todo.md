
# Bugs

- renderableSystem crash -> read access denied

# Features

- Scenes
  - Each scene should have a camera and FBO (size..)
  - Scene save/loader + tabs in the engine
  - Scene instancing inside other scenes
  - Swappable Renderer per scene
    - Render to Fbo
    - Render color
    - Render depth
    - Render physic objects
- Instanced Rendering entity.
  - Transform[] component? + CustomData[] component?
  - Additional system for instanced groups
- Animation
  - CpuAnimationPlayer
  - GpuAnimationPlayer (Baked from CpuAnimationPlayer)
- Physics
