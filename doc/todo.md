
# Bugs

- renderableSystem crash -> read access denied

# Features

- Resize viewports on resize
- Resize fbos on resize
- Fbo to Imgui
- Fbo targets (depth, color, physics)
- ImGui entity properties -> render components

## More

- Stage
  - Each stage should have a camera and FBO (size..)
  - Swappable Renderer per stage
    - Render to Fbo
    - Render depth
    - Render color
    - Render physic objects
- Scene
  - Scene save/loader + ui tabs in the editor
  - Scene instancing inside other scenes
- Ui pages (ie. different scene, world or query)
- Instanced Rendering entity
  - Transform[] component? + CustomData[] component?
  - Additional system for instanced groups
- Shadows
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
