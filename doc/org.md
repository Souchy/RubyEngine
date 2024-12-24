
Stage {
 ent["view"](Camera, Viewport)
 ent["view2"](Camera, Viewport)
 ent["world"](models...)
}

Stage2 {
 ent["view3"](Camera, Viewport)
 ent["world2"](models2...)
}

---

Maybe each stage should build its own mesh Query then use it in the rendering.
Filter with a Stage{id} component perhaps
