/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_GR_PLL_FREQDET_CF_H
#define INCLUDED_GR_PLL_FREQDET_CF_H

#include <gr_sync_block.h>

class gr_pll_freqdet_cf;
typedef boost::shared_ptr<gr_pll_freqdet_cf> gr_pll_freqdet_cf_sptr;

gr_pll_freqdet_cf_sptr gr_make_pll_freqdet_cf (float alpha, float beta,
					       float max_freq, float min_freq);
/*!
 * \brief Implements a PLL which locks to the input frequency and outputs 
 * an estimate of that frequency.  Useful for FM Demod.
 * \ingroup sync_blk
 *
 * input: stream of complex; output: stream of floats
 *
 * This PLL locks onto a [possibly noisy] reference carrier on
 * the input and outputs an estimate of that frequency in radians per sample.
 * All settings max_freq and min_freq are in terms of radians per sample, 
 * NOT HERTZ.  Alpha is the phase gain (first order, units of radians per radian) 
 * and beta is the frequency gain (second order, units of radians per sample per radian)
 * \sa gr_pll_refout_cc, gr_pll_carriertracking_cc
 */

class gr_pll_freqdet_cf : public gr_sync_block
{
  friend gr_pll_freqdet_cf_sptr gr_make_pll_freqdet_cf (float alpha, float beta,
							float max_freq, float min_freq);

  float d_alpha,d_beta,d_max_freq,d_min_freq,d_phase,d_freq;
  gr_pll_freqdet_cf (float alpha, float beta, float max_freq, float min_freq);

  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
private:
  float mod_2pi (float in);
  float phase_detector(gr_complex sample,float ref_phase);
};

#endif
