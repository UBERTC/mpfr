/* Test file for mpfr_exp2.

Copyright (C) 2001 Free Software Foundation.
Adapted from tarctan.c.

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
#include <stdlib.h>
#include <gmp.h>
#include "gmp-impl.h"
#include <mpfr.h>
#include "mpfr-impl.h"

#define TEST_FUNCTION mpfr_exp2

int
main (int argc, char *argv[])
{
  unsigned int prec, yprec, n, p0 = 1, p1 = 100, N = 100;
  mp_rnd_t rnd;
  mpfr_t x, y, z, t;

  mpfr_init (x);
  mpfr_init (y);
  mpfr_init (z);
  mpfr_init (t);


  MPFR_SET_INF(x);
  TEST_FUNCTION(y,x,GMP_RNDN);
  if(!MPFR_IS_INF(y)){ printf("evaluation of function in INF do not retun INF"); exit(1);}
  MPFR_CHANGE_SIGN(x);
  TEST_FUNCTION(y,x,GMP_RNDN);
  if(!MPFR_IS_ZERO(y)){ printf("evaluation of function in -INF do not retun 0"); exit(1);}

   MPFR_SET_NAN(x);
  TEST_FUNCTION(y,x,GMP_RNDN);
  if(!MPFR_IS_NAN(y)){ printf("evaluation of function in NAN do not retun NAN"); exit(1);}





  /* tatanh prec - perform one random computation with precision prec */
  if (argc >= 2)
    {
      p0 = p1 = atoi (argv[1]);
      N = 1;
      
    }

  for (prec = p0; prec <= p1; prec++)
    {
      mpfr_set_prec (x, prec);
      mpfr_set_prec (z, prec);
      mpfr_set_prec (t, prec);
      yprec = prec + 10;
      for (n=0; n<N; n++)
	{
	  mpfr_random (x);
          if (random() % 2)
	    mpfr_neg (x, x, GMP_RNDZ);
	  rnd = random () % 4;
	  mpfr_set_prec (y, yprec);
	  TEST_FUNCTION (y, x, rnd);
	  if (mpfr_can_round (y, yprec, rnd, rnd, prec))
	    {
	      mpfr_set (t, y, rnd);
	      TEST_FUNCTION (z, x, rnd);
	      if (mpfr_cmp (t, z))
		{
		  printf ("results differ for x=");
		  mpfr_out_str (stdout, 2,prec, x, GMP_RNDN);
		  printf (" prec=%u rnd_mode=%s\n", prec,
			  mpfr_print_rnd_mode (rnd));
		  printf ("   got      ");
		  mpfr_out_str (stdout, 2, prec, z, GMP_RNDN);
		  putchar ('\n');
		  printf ("   expected ");
		  mpfr_out_str (stdout, 2, prec, t, GMP_RNDN);
		  putchar ('\n');
		  printf ("   approximation was ");
		  mpfr_print_raw (y);
		  putchar ('\n');
		  exit (1);
		}
	    }
	}
    }

  mpfr_clear (x);
  mpfr_clear (y);
  mpfr_clear (z);
  mpfr_clear (t);

  return 0;
}
