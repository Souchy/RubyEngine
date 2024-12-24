
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

# Org

Scenes within a render
Each have a Camera / Fbo

2 cameras : same scene
2 cameras : different scenes

## 1 cam at a time

Camera switching or Scene switching.

- Enter a new area
- Add underwater cam
- Add night vision cam

## 2 cams on screen

- Mini map cam
- Backview mirror, puddle, etc.
- side-by-side multiplayer couch
- Camera from another room (diff physical scene bundle)

# Better org

## Different bundles?

Just make a different world and render it as well?

## 2 cams same world

Make make a Layout to organize the cameras?
or just tell each cam to render at specific coordinates on the screen (viewport)?

# Ui

Also need different ui pages

# Saves

Scenes as saves and as nodes
