# LightEngine3 - Renderer Refactor

So far, due to preferring (unfortunately) shortcuts, many LE3 source files are tighly coupled with OpenGL calls.
Furthermore, the le3_scene.cpp source file in particular has become too cumbersome to handle, with many render phases.
Device enumeration could be significantly improved if we want a chance of actual deployable code.
Finally, the scene graph can be improved by rendering only culled objects and lighting.

## Refactor phases

1. We'll go through all source files and map files that have explicit OpenGL calls and which
2. Based on insights from previous steps, we'll decide the structure of the decoupled renderer components
3. Mush in also the render phases & device enumeration logic
4. Refactor the codebase until it (hopefully) works

BONUS: Allow displaying/exporting intermediate render phases (for debug purposes)

## Coupled source files

* le3_application.cpp - OpenGL initialization + SDL coupling
* 
