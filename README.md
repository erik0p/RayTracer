# RayTracer

# TODO
- add bi-linear interpolation for texture lookup
- add functionality to read normal maps

# Notes
- The file reader expects that vertices, normals, and texturecoords before the faces are defined.
- Textures must be placed in the `/input/texture/` directory for the program to find it.
- Program defaults to using hard-shadows. Add `softshadows 1` to the input description to use softshadows with point lights and attenuated point lights. This will significantly slow down the program.
- The `/images` directory contains images showcasing the different capabilities of the program. Their corresponding input file can be found in `/input`

# Overview
This program takes the name of a scene description file and outputs a `.ppm` file. The program has raytracing functionality. It can render spheres, and cast rays into the scene to determine if a ray intersects with a sphere. Spheres are shaded using the Blinn-Phong illumination model. Shading and raycasting is done inside of scene.cpp and pixels are written to the output file in render.cpp. Recursive raytracing is used to model the reflective and refractive properties of materials as described by their material properties.

The program is capable of mapping textures to both spheres and triangles. 

Input files should contain some or all of the following information:
```
imsize width height
eye x y z
viewdir x y z
vfov degrees
updir x y z
bkgcolor r g b refractionIndex
mtlcolor odr odg odb osr osg osb ka kd ks n opacity refractionIndex
sphere x y z r
light x y z w i
attlight x y z w i c1 c2 c3
depthcueing dcr dcg dcb aMin aMax distMin distMax
v x y z
vt u v
vn x y z
texture filename.ppm
f v1 v2 v3
f v1/vt1 v2/vt2 v3/vt3
f v1//vn1 v2//vn2 v3//vn3
f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3

softshadows flag

```
**Example scene description**
```
imsize 512 512
eye  0 0 5
viewdir  0 0 -1
updir  0 1 0
vfov 60

bkgcolor 0.7 0.7 0.7 1

light 4 0 0 1 1

mtlcolor 0.2 1 0.2 1 1 1 0.2 0.6 0.0 100 1.0 1.0
sphere -4 0 -3 2

mtlcolor 1 0 0 1 1 1 0.02 0.06 0.2 100 0.2 1.5
sphere 0 0 -3 2

softshadows 0



```
# Usage
Run the following commands
```
make
./raytracer1d input/showcase.txt
```
The output file will be in the same location where the input file is.

Clean the build files using.
```
make clean
```
