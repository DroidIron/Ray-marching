# Ray-marching
 A ray marching engine using C, OpenGL and Cglm. This project consists of 9 "modes/scenes" were a few diffrent ray marching algortihms are put to work.

 ![ray_marching_sphere](https://github.com/user-attachments/assets/f8cab48f-d62f-43c7-bfea-27248e35e6ff)

![ray_marching_outline](https://github.com/user-attachments/assets/8e24443d-10d8-453e-a05f-f51f868d7d0f)

![lava_light](https://github.com/user-attachments/assets/8b958923-0490-4ce8-b4b8-c1c77330ec8f)

# Running the program:
 To run the program use the main.exe file or build the program using the makefile included.
# How it works:
 The program uses SDF or signed distance functions to raycast diffrent objects and shapes. The perk of using signed distance functions or so called ray marching is that we simulate object collisions, seperation and volume instead of meshes and polygon and is similer to voxels. OpenGL does not directly support raycasting but we can get around this by creating a quad covering the entire screen and after that just do all our calculations in the fragment shader. This project contains 9 fragment shader which each contain their own raycasting but they all share the same vertex shader. When the project is created all 9 scenes are created as shader programs and then stored until the user switches mode and at that point we switch program.

# Sources:
* https://www.youtube.com/watch?v=khblXafu7iA
* https://iquilezles.org/articles/distfunctions/
