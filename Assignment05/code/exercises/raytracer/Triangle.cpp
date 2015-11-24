#include "Triangle.hpp"
#include "Ray.hpp"
#include <memory>
#include <cmath>
#include <math.h>

namespace rt
{
    Triangle::Triangle(const Vec3d &v0, const Vec3d &v1, const Vec3d &v2,
                       const Vec3d &uvw0, const Vec3d &uvw1, const Vec3d &uvw2)
    {
        mVertices[0] = v0;
        mVertices[1] = v1;
        mVertices[2] = v2;
        mUVW[0] = uvw0;
        mUVW[1] = uvw1;
        mUVW[2] = uvw2;
    }
    
    
    bool SameSide(const Vec3d p1, const Vec3d p2, const Vec3d a, const Vec3d b){
        const Vec3d cp1 = cross(b - a, p1 - a);
        const Vec3d cp2 = cross(b - a, p2 - a);
        if (dot(cp1, cp2) >= 0)
            return true;
        return false;
    }
    
    bool InTriangle(const Vec3d p, const Vec3d a, const Vec3d b, const Vec3d c){
        if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b))
            return true;
        return false;
    }
    
    bool
    Triangle::closestIntersectionModel(const Ray &ray, double maxLambda, RayIntersection& intersection  ) const
    {
        double lambda;
        Vec3d t_r;
        Vec3d p_r;
        Vec3d t1;
        Vec3d t2;
        Vec3d n;
        
        t_r = ray.direction();
        p_r = ray.origin();
        
        t1 = mVertices[1] - mVertices[0];
        t2 = mVertices[2] - mVertices[0];
        n = cross(t1, t2);
        
        lambda = dot(mVertices[0]-p_r, n)/dot(t_r,n);
        
        if(0 <= lambda && lambda <= maxLambda){
            if(dot(t_r, n) != 0){
                if(InTriangle(ray.pointOnRay(lambda),mVertices[0],mVertices[1],mVertices[2])){
                    intersection = RayIntersection(ray, shared_from_this(), lambda, n, Vec3d());
                    return true;
                }
            }
        }
        return false;
    }
    
    BoundingBox Triangle::computeBoundingBox() const
    {
        BoundingBox bbox;
        bbox.expandByPoint(mVertices[0]);
        bbox.expandByPoint(mVertices[1]);
        bbox.expandByPoint(mVertices[2]);
        return bbox;
    }
    
} //namespace rt