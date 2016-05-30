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


#ifndef GOPTICAL_ANALYSIS_PSF_HH_
#define GOPTICAL_ANALYSIS_PSF_HH_


#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>


#include "Goptical/common.hh"

#include "Goptical/Math/vector_pair.hh"

#include "Goptical/Analysis/pointimage.hh"

namespace _Goptical
{

  namespace Analysis
  {

    /**
       @short PSF(Point Spread Function) Analysis
       @header Goptical/Analysis/PSF
       @module {Core}
       @main

       This class is designed to find the best point of PSF of
       an optical system.
    */
    class PSF : public PointImage
    {
    public:
      PSF(Sys::System &system);

      inline void invalidate();
    
      int get_num_points();
      
      
      
      double** get_PSF(int surface);
      double* get_crossX_PSF(int surface, int y);
      double* get_crossY_PSF(int surface, int x);

    private:
      void compute_PSF();
      void set_num_points(int N);
      int num_points; //this is will be converted to closet power of 2
      int type;
      bool              _processed_PSF;
      double** PSF;  
    };

  }
}

#endif

