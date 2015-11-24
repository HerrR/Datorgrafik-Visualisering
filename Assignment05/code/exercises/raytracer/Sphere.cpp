#include "Sphere.hpp"
#include "Ray.hpp"
#include <memory>
#include<iostream>
#include<cmath>
#include <string>
#include <math.h>

namespace rt
{
    
    bool
    Sphere::closestIntersectionModel(const Ray &ray, double maxLambda, RayIntersection& intersection) const
    {
        //Programming TASK 1: implement this method
        //Your code should compute the intersection between a ray and a unit sphere, with radius = 1, centered at origin (0,0,0);
        double lambda;
        double lambda1;
        double lambda2;
    
        Vec3d  t_r;
        Vec3d  p_r;
        Vec3d uvw(0,0,0);
        
        t_r = ray.direction();
        p_r = ray.origin();

        double discriminant = dot(t_r,p_r) * dot(t_r,p_r) - dot(p_r, p_r) + 1;
        
        if(discriminant>=0){
            lambda1 = -dot(t_r,p_r) - sqrt(discriminant);
            lambda2 = -dot(t_r,p_r) + sqrt(discriminant);
        } else {
            return false;
        }
        
        if(lambda1 < 0){
            lambda = lambda2;
        }else{
            lambda = lambda1;
        }
        
        if(lambda < maxLambda){
            intersection = RayIntersection(ray,shared_from_this(),lambda,ray.pointOnRay(lambda),uvw);
            return true;
        }else{
            return false;
        }
        
        // Hints :
        // As explained in Lecture 7 - Raytracing
        // 1. Ray origin p_r : ray.origin()
        //    Ray direction t_r : ray.direction()
        // 2. Solving the quadratic equation results in two solutions if the discriminant is positive
        //    i.e. if t_r . p_r - (p_r . p_r - 1) > 0 (Since t_r is a unit vector t_r . t_r = |t_r|^2 = 1)
        // 3. Solving for lambda we have the values  lambda1 = -(t_r . p_r) - sqrt(t_r . p_r - (p_r . p_r - 1)) and
        //    lambda2 = -(t_r . p_r) + sqrt(t_r . p_r - (p_r . p_r - 1))
        // 4. If lambda1 < 0, then the intersection lies inside the sphere. choose lambda2.
        // 5. lambda must be less than maxLambda, otherwise return false
        // 6. compute intersection point using ray.pointOnRay(lambda)
        
        //return false;
    }
    
    BoundingBox Sphere::computeBoundingBox() const
    {
        BoundingBox box;
        box.setMin(Vec3d(-1,-1,-1));
        box.setMax(Vec3d(1,1,1));
        return box;
    }
    
} //namespace rt
