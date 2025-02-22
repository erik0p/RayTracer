# RayTracer

# Overview
This program takes the name of a scene description file and outputs a `.ppm` file. The program has raytracing functionality. It can render spheres, and cast rays into the scene to determine if a ray intersects with a sphere. Spheres are shaded using the Blinn-Phong illumination model. Shading and raycasting is done inside of scene.cpp and pixels are written to the output file in render.cpp. In this program all point lights (including attenuated point lights) use soft shadows, and all directional lights use hard shadows. The images directory contains various images showing the different capabilities of the raytracer program. Inside input/writeupImages are the input files that were used to generate those images. Input files should contain the following information:
```
imsize width height
eye x y z
viewdir x y z
vfov degrees
updir x y z
bkgcolor r g b
mtlcolor odr odg odb osr osg osb ka kd ks n
sphere x y z r
light x y z w i
attlight x y z w i c1 c2 c3
depthcueing dcr dcg dcb aMin aMax distMin distMax
```
**Example scene description**
```
imsize 512 512
eye 0 0 0
viewdir 0 0 -1
vfov 45
updir 0 1 0
bkgcolor 0 0 0
depthcueing 0 0 0 0.1 1 2 20
attlight -2 0 -7 1 1 0 0.5 0.5
mtlcolor 0 1 1 1 1 1 0.2 0.8 0.2 10
sphere 0 0 -8 1
```

# Usage
Run the following commands
```
make
./raytracer1b input/showcase.txt
```
The output file will be in the same location where the input file is.
