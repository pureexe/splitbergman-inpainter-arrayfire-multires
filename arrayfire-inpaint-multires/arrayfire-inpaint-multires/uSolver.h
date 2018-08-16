#pragma once
#include "stdafx.h"
#include "Divergence.h"

//	u = (1 ./ (lambda + 4*theta)) .* (lambda .*original_image - theta .* divergence + theta .* lapacian);  % remove h^2 for speed improve   

array uSolver(array u, array w, array original_image, array b, array lambda, double theta,double omega,int max_gauss_seidel) {
	float lapacianFilterMatrix[]  = { 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	array lapacianKernel(3, 3, lapacianFilterMatrix);
	array lapacian;
	array divergence = Divergence(w - b);
	int last_height = original_image.dims(0) -1;
	int last_width = original_image.dims(1) -1;
	seq row, col;
	for (int i = 0; i < max_gauss_seidel; i++) {
		
		// Red state
		lapacian = convolve2(u, lapacianKernel);
		lapacian.row(0) += u.row(0);
		lapacian.col(0) += u.col(0);
		lapacian.row(end) += u.row(end);
		lapacian.col(end) += u.col(end);

		row = seq(0, last_height, 2);
		col = seq(1, last_width, 2);
		u(row, col) = (1-omega)*u(row,col) + omega*(1 / (lambda(row,col) + 4 * theta)) * (lambda(row, col)  * original_image(row, col) - theta * divergence(row, col) + theta * lapacian(row, col));

		row = seq(1, last_height, 2);
		col = seq(0, last_width, 2);
		u(row, col) = (1 - omega)*u(row, col) + omega * (1 / (lambda(row, col) + 4 * theta)) * (lambda(row, col)  * original_image(row, col) - theta * divergence(row, col) + theta * lapacian(row, col));

		//Black state
		lapacian = convolve2(u, lapacianKernel);
		lapacian.row(0) += u.row(0);
		lapacian.col(0) += u.col(0);
		lapacian.row(end) += u.row(end);
		lapacian.col(end) += u.col(end);

		row = seq(0, last_height, 2);
		col = seq(0, last_width, 2);
		u(row, col) = (1 - omega)*u(row, col) + omega * (1 / (lambda(row, col) + 4 * theta)) * (lambda(row, col)  * original_image(row, col) - theta * divergence(row, col) + theta * lapacian(row, col));

		row = seq(1, last_height, 2);
		col = seq(1, last_width, 2);
		u(row, col) = (1 - omega)*u(row, col) + omega * (1 / (lambda(row, col) + 4 * theta)) * (lambda(row, col)  * original_image(row, col) - theta * divergence(row, col) + theta * lapacian(row, col));
	}	
	return u;
}
