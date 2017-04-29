/*

      This file is part of the Goptical Core library.
  
      The Goptical library is free software; you can redistribute it
      and/or modify it under the terms of the GNU General Public
      License as published by the Free Software Foundation; either
      version 3 of the License, or (at your option) any later version.
  
      The Goptical library is distributed in the hope that it will be
      useful, but WITHOUT ANY WARRANTY; without even the implied
      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
      See the GNU General Public License for more details.
  
      You should have received a copy of the GNU General Public
      License along with the Goptical library; if not, write to the
      Free Software Foundation, Inc., 59 Temple Place, Suite 330,
      Boston, MA 02111-1307 USA
  
      Copyright (C) 2010-2011 Free Software Foundation, Inc
      Author: Alexandre Becoulet

*/

#include <cstdio>
#include <stdlib.h>

#include "config.hh"

#include <Goptical/Io/Renderer>
#include <Goptical/Io/RendererViewport>
#include <Goptical/Io/Rgb>
#include <Goptical/Io/RendererSvg>

#include <Goptical/Trace/Distribution>

#include <Goptical/Shape/Base>
#include <Goptical/Shape/Disk>
#include <Goptical/Shape/Ring>
#include <Goptical/Shape/Ellipse>
#include <Goptical/Shape/EllipticalRing>
#include <Goptical/Shape/Rectangle>
#include <Goptical/Shape/RegularPolygon>
#include <Goptical/Shape/Polygon>
#include <Goptical/Shape/Composer>


#include <Goptical/Material/Base>
#include <Goptical/Material/Sellmeier>


#include <Goptical/Math/Vector>

#include <Goptical/Sys/System>
#include <Goptical/Sys/OpticalSurface>
#include <Goptical/Sys/SourcePoint>
#include <Goptical/Sys/Image>
#include <Goptical/Sys/Element>

#include <Goptical/Curve/Sphere>
#include <Goptical/Shape/Disk>
#include <Goptical/Light/SpectralLine>

#include <Goptical/Analysis/PSF>

using namespace Goptical;

int main()
{
  //**********************************************************************
  // Glass material models
                                                                  /* anchor material */
  Material::Sellmeier bk7(1.03961212, 6.00069867e-3, 0.231792344,
                          2.00179144e-2, 1.01046945, 1.03560653e2);

  Material::Sellmeier f3(8.23583145e-1, 6.41147253e-12, 7.11376975e-1,
                         3.07327658e-2, 3.12425113e-2, 4.02094988);
                                                                  /* anchor end */

  //**********************************************************************
  // Optical system definition

                                                            /* anchor lens_shape */
  Shape::Disk   lens_shape(100); // lens diameter is 100mm

  // 1st lens, left surface
  Curve::Sphere curve1(2009.753); // spherical curve with given radius of curvature
  Curve::Sphere curve2(-976.245);
                                                            /* anchor lens1 */
  Sys::OpticalSurface s1(Math::Vector3(0, 0, 0), // position,
                         curve1, lens_shape,     // curve & aperture shape
                         Material::none, bk7);   // materials

  // 1st lens, right surface
  Sys::OpticalSurface s2(Math::Vector3(0, 0, 31.336),
                         curve2, lens_shape,
                         bk7, Material::none);
                                                            /* anchor lens2 */
  // 2nd lens, left surface
  Sys::OpticalSurface s3(Math::Vector3(0, 0, 37.765), // position,
                         -985.291, 100,        // roc & circular aperture radius,
                         Material::none, f3);  // materials

  // 2nd lens, right surface
  Sys::OpticalSurface s4(Math::Vector3(0, 0, 37.765+25.109),
                         -3636.839, 100,
                         f3, Material::none);
                                                                  /* anchor src */
  // light source
  Sys::SourcePoint source(Sys::SourceAtInfinity,
                          Math::Vector3(0, 0, 1));
  // select light source wavelens
  source.clear_spectrum();
  double wave = 780.246;  //in nanometers
  source.add_spectral_line(Light::SpectralLine(wave));

                                                                  /* anchor image */
  // image plane
  Sys::Image    image(Math::Vector3(0, 0, 3014.5),  // position
                      60);                           // square size,
                                                                  /* anchor sys */
  Sys::System   sys;

  // add components
  sys.add(source);
  sys.add(s1);
  sys.add(s2);
  sys.add(s3);
  sys.add(s4);
  sys.add(image);
                                                                  /* anchor end */

  //**********************************************************************
  //std::cout << "system:" << std::endl << sys;
  std::cout << sys.get_element_count() << std::endl;
  for (uint ii = 0; ii < sys.get_element_count(); ii++){
      std::cout << "ii = " << ii << std::endl;
}

  std::cout << "This is a PSF Test!!!" << std::endl;

  Analysis::PSF psf1(sys);
  double z = 1.0; // mm
  double value = psf1.compute_Fresnel_number(wave,z);
  std::cout << "Fresnel Number = " << value << std::endl;


}

