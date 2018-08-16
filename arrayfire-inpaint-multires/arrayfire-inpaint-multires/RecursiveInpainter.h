#pragma once
#include "stdafx.h"

#include "SplitBergmanSolver.h"
#include "MergeResult.h"

array RecusriveInpainter(array original_image,array inpainted_domain, double lambda,double theta,double tolerant,double omega, int max_guass_seidel,int max_iteration,int max_step,int current_step)
{
	array toinpaint_image;
	if (current_step < max_step) {
		array half_image = resize(0.5, original_image, AF_INTERP_BILINEAR);
		array half_domain = resize(0.5, inpainted_domain, AF_INTERP_BILINEAR);
		array half_result = RecusriveInpainter(half_image, half_domain, lambda, theta, tolerant, omega, max_guass_seidel, max_iteration, max_step, current_step + 1);
		int height = original_image.dims(0);
		int width = original_image.dims(1);
		array upscale_result = resize(half_result, height,width,AF_INTERP_BILINEAR);
		toinpaint_image = MergeResult(original_image, inpainted_domain, upscale_result);		
	}
	else {
		toinpaint_image = original_image;
	}
	array inpainted_lambda = (inpainted_domain == 0) *1.0;
	inpainted_lambda = inpainted_lambda * lambda;
	if (current_step != 1) {
		if (current_step == max_step) {
			max_iteration = 10;
		}
		else {
			max_iteration = 3;
		}
	}
	array result_image;
	/*
	if (current_step != 1) {
		result_image = SplitBergmanSolver(toinpaint_image, inpainted_lambda, theta, tolerant, omega, max_guass_seidel, max_iteration);
	}
	else {
		result_image = toinpaint_image;
	}*/
	result_image = SplitBergmanSolver(toinpaint_image, inpainted_lambda, theta, tolerant, omega, max_guass_seidel, max_iteration);
	return result_image;
}