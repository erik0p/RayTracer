# RayTracer

# Overview
This program takes the name of a scene description file and outputs a `.ppm` file. The program has basic raytracing functionality. It can render spheres and cast rays into the scene to determine of a ray intersects with a sphere. the file should contain the following information:
```
imsize width height
eye x y z
viewdir x y z
vfov degrees
updir x y z
bkgcolor r g b
mtlcolor r g b
sphere x y z r
```
**Example scene description**
```
imsize 512 512
eye 0 0 1
viewdir 0 0.2 1
vfov 45
updir 0 1 0
bkgcolor 0.2 0.2 0.2
mtlcolor 1 0 0
sphere 0 0 15 2
mtlcolor 0 1 0
sphere 4 4 15 1
```

# Usage
Run the following commands
```
make
./raytracer1a input/scene.txt
```
