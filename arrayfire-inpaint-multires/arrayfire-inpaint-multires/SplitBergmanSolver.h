#pragma once

#include "stdafx.h"
#include "uSolver.h"
#include "wSolver.h"
#include "Gradient.h"

array SplitBergmanSolver(array original_image, array lambda, double theta, double tolerant, double omega, int max_gauss_seidel,int max_iteration) {
	double image_norm = 9999999;
	int i = 1;
	array last_image;
	array u = original_image.copy();
	int height = original_image.dims(0);
	int width = original_image.dims(1);
	array b = constant(0, height*2,width, f64);
	array w = constant(0, height * 2, width, f64);
	while (image_norm > tolerant && i < max_iteration) {
		last_image = u.copy();
		w = wSolver(u, b, theta);
		u = uSolver(u, w, original_image, b, lambda, theta, omega, max_gauss_seidel);
		b = b + Gradient(u) - w;
		image_norm = norm(u - last_image) / norm(u);
		i++;
	}
	printf("processed with %d loops\n", i);
	return u;
}