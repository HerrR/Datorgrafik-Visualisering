#include "PhongMaterial.hpp"
#include "Light.hpp"
#include "Math.hpp"
#include "Ray.hpp"
#include "math.h"

namespace rt
{

  PhongMaterial::PhongMaterial(const Vec3d& color, double reflectance, double shininess) :  
    Material(color,reflectance), mShininess(shininess)
  {

  }

  Vec4d PhongMaterial::shade(const RayIntersection& intersection,
    const Light& light) const 
  {
	  // get normal and light direction
	  Vec3d N = intersection.normal();
	  Vec3d L = (light.position() - intersection.position()).normalize();

	  double cosNL = std::max(dot(N, L), double(0));
      
      // 2. The incident radiance from the light source is the light intensity divided by
      //    the quadratic distance of the light source from the point of intersection. (quadratic falloff)
      auto i_r = light.spectralIntensity() / pow( (light.position() - intersection.position()).length(), 2);
      
      // 3. The irradiance c_l is obtained by multiplying the incident radiance
      //    to the cosine of the angle between the vectors L and N.
      auto c_l = i_r * cosNL;
      
      // 4. The view vector V is the direction of the ray which intersects the object.
      auto V = intersection.position(); // <-- ytterst oklar, tror inte den stämmer
      
      // 5. The reflection vector R can be obtained by using the predefined function reflect (raytracer/Vector3.hpp)
      auto R = reflect(L,N);
      
      // 6. The rest of the terms as per the slides are as follows (including normalization)
      //    c_r = material_color / PI
      auto c_r = color() / 3.1415926536;
      
      //    p = mShininess
      double p = mShininess;
      
      //    c_p = r_f0 * (mShininess + 2) / (2 * PI)
      double c_p = 0.04 * (mShininess + 2) / (2 * 3.1415926536);
      
      auto ambient = c_r * 0.25;
      auto specular = c_p * c_l * pow(dot(R.normalize(), V.normalize()),p);
      auto diffuse = c_r * c_l * dot(N,L);
      
      return Vec4d(ambient + diffuse + specular, 1.0);
    // return Vec4d(this->color()*cosNL, 1.0);
  }

} //namespace rt
