/* mpfr_exp2 -- power of 2 function 2^y 

Copyright (C) 1999 Free Software Foundation.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Library General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
License for more details.

You should have received a copy of the GNU Library General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include <stdio.h>
#include "gmp.h"
#include "gmp-impl.h"
#include "mpfr.h"
#include "mpfr-impl.h"

 /* The computation of y=pow(2,z) is done by

    y=exp(z*log(2))=2^z
 */
int mpfr_exp2 _PROTO((mpfr_ptr, mpfr_srcptr, mp_rnd_t));

int
#if __STDC__
mpfr_exp2 (mpfr_ptr y, mpfr_srcptr x, mp_rnd_t rnd_mode) 
#else
mpfr_exp2 (y, x, rnd_mode)
     mpfr_ptr y;
     mpfr_srcptr x;
     mp_rnd_t rnd_mode;
#endif
{    
  /****** Declaration ******/

    /* Variable of Intermediary Calculation*/
    mpfr_t t;       

    int round;
    int boucle;

    mp_prec_t Nx;   /* Precision of input variable */
    mp_prec_t Ny;   /* Precision of output variable */
    mp_prec_t Nt;   /* Precision of Intermediary Calculation variable */
    mp_prec_t err;  /* Precision of error */

    if (MPFR_IS_NAN(x)) {  MPFR_SET_NAN(y); return 1; }
    MPFR_CLEAR_NAN(y);

    if(mpfr_cmp_ui(x,0)==0){

      mpfr_set_ui(y,1,GMP_RNDN);return(0); 
    }
    else
      {

	if (MPFR_IS_INF(x))
	  {
	    if (MPFR_SIGN(x) < 0)
	      {
		MPFR_CLEAR_INF(y);
		MPFR_SET_ZERO(y);
		return(0);
	      }
	      else
		{
		  MPFR_SET_INF(y);
		  if(MPFR_SIGN(y) < 0) MPFR_CHANGE_SIGN(y);
		  return(1);
		}
	  }
      
    }
    MPFR_CLEAR_INF(y);

    
 

        /* Initialisation of the Precision */
	Nx=MPFR_PREC(x);
	Ny=MPFR_PREC(y);
	

	/* compute the size of intermediary variable */
	if(Ny>=Nx)
	  Nt=Ny+2*(BITS_PER_CHAR); 
	else
	  Nt=Nx+2*(BITS_PER_CHAR); 

	  boucle=1;

	  while(boucle==1){

	    /* initialise of intermediary	variable */
	    mpfr_init2(t,Nt);             

	    /* compute cosh */
	    mpfr_const_log2(t,GMP_RNDN);    /* ln(2) */
	    mpfr_mul(t,x,t,GMP_RNDN);       /* x*ln(2) */
	    mpfr_exp(t,t,GMP_RNDN);         /* exp(x*ln(2))*/

	    err=Nt-1;

	    round=mpfr_can_round(t,err,GMP_RNDN,rnd_mode,Ny);

	    if(round == 1){
	      mpfr_set(y,t,rnd_mode);
	      boucle=0;
	    }
	    else{
	      Nt=Nt+10;
	      boucle=1;
	    }

	  }

	  mpfr_clear(t);
          return(1);

    
 
    
}
