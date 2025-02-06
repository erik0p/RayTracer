#include <ostream>
#include "Sphere.h"
#include "Vector3.h"
#include "Color.h"
#include "Object.h"

Sphere::Sphere(Vector3& center_, float radius_, Color& color_) {
    center = center_;
    radius = radius_;
    color = color_;
}

/*bool Object::intersects(const Ray& ray, float *distance) const {*/
/*    float x = ray.getOrigin().getX();*/
/*    float y = ray.getOrigin().getY();*/
/*    float z = ray.getOrigin().getZ();*/
/*    float dx = ray.getDir().getX();*/
/*    float dy = ray.getDir().getY();*/
/*    float dz = ray.getDir().getZ();*/
/*    float cx = sphere.getCenter().getX();*/
/*    float cy = sphere.getCenter().getY();*/
/*    float cz = sphere.getCenter().getZ();*/
/**/
/*    float a = 1.0f;*/
/*    float b = 2.0f * (dx * (x - cx) + dy * (y - cy) + dz * (z - cz));*/
/*    float c = pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) - pow(sphere.getRadius(), 2);*/
/*    float t1 = -b + sqrt(pow(b, 2) - 4.0f * c) / 2.0f;*/
/*    float t2 = -b - sqrt(pow(b, 2) - 4.0f * c) / 2.0f;*/
/*    float discriminant = pow(b, 2) - 4.0f * a * c;*/
/**/
/*    if (discriminant > 0.0f) { // pierces sphere*/
/*        if (t1 < minT && t1 > 0.0f) {*/
/*            minT = t1;*/
/*            closestSphere = sphere;*/
/*        }*/
/*        if (t2 < minT && t2 > 0.0f) {*/
/*            minT = t2;*/
/*            closestSphere = sphere;*/
/*        }*/
/*    } else if (discriminant == 0.0f) { // grazes sphere*/
/*        closestSphere = sphere;*/
/*    }*/
/**/
/*}*/

std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
    out <<"sphere: "
        << "center: " << sphere.center
        << " radius: " << sphere.radius
        << " color: " << sphere.color;
    return out;
}
