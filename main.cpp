#include <iostream>
#include "sphere.h"
#include "hittable_list.h"
#include "vec3.h"
#include "camera.h"
#include <float.h>
#include "stb_image_write.h"
#include "main.h"
#include "material.h"
#include "lambertian.h"

vec3 color(const ray &r, hittable *world, int depth) {
    hit_records rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        } else {
            return vec3(0,0,0);
        }
    } 
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    } while (p.squared_length() > 1.0);
    return p;
}

int main(void)
{
    int nx = 800;
    int ny = 600;
    int ns = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    hittable *list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-1,0,-1),0.5, new metal(vec3(0.8, 0.8,0.8)));
    camera cam;
    hittable *world = new hittable_list(list, 4);
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0,0,0);
            for (int s = 0; s < ns; s++) {
                float u = float(i+drand48()) / float(nx);
                float v = float(j+drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}
