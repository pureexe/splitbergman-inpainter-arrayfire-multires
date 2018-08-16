#pragma once
#include "stdafx.h"

/*
//Manuel Divergence
array Divergence(array T) {
	int total_height = T.dims(0);
	int height = total_height / 2;
	int width = T.dims(1);
	array T1 = T.rows(0, height-1);
	array T2 = T.rows(height, total_height-1);
	array zeroImage = constant(0, height, width);
	array T1_previous = zeroImage.copy();
	T1_previous.rows(1, end) = T1.rows(0, end - 1);
	T1 -= T1_previous;
	array T2_previous = zeroImage.copy();
	T2_previous.cols(1, end) = T2.cols(0, end - 1);
	T2 -= T2_previous;
	return T1 + T2;
}
*/

// Divergence by built-in diff1 arrayfire  (convergence faster?)
array Divergence(array T) {
	int total_height = T.dims(0);
	int height = total_height / 2;
	int width = T.dims(1);
	array T1 = T.rows(0, height - 1);
	array T2 = T.rows(height, total_height - 1);
	array Tx = join(0, T1.row(0), diff1(T1, 0));
	array Ty = join(1, T2.col(0), diff1(T2, 1));
	return Tx + Ty;
}
