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


#ifndef GOPTICAL_ANALYSIS_PSF_HXX_
#define GOPTICAL_ANALYSIS_PSF_HXX_

#include "Goptical/Math/vector_pair.hxx"
#include "Goptical/Analysis/pointimage.hxx"

namespace _Goptical
{

  namespace Analysis
  {

    void PSF::invalidate()
    {
      _processed_PSF= false;
      _processed_trace= false;
    }

    void PSF::set_num_points(int N)
    {
      if (N < 32)
        num_points= 32;
      else if (N > 2048)
        num_points= 2048;

      else {
          // find closet power of 2
          double exponent= ceil(log2(N)); // round up
          num_points= pow(2, exponent);
        }
    }
    int PSF::get_num_points()
    {
      return num_points;
    }
   }


}

#endif


