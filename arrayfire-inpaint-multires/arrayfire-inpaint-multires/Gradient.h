#pragma once
#include "stdafx.h"


//Manuel Gradeint (Faster convergence?)
array Gradient(array u)
{
	int height = u.dims(0);
	int width = u.dims(1);
	array u_left = u.copy();
	array u_up = u.copy();
	u_left.cols(0, end - 1) = u.cols(1, end);
	u_up.rows(0, end - 1) = u.rows(1, end);
	u_left = u_left - u;
	u_up = u_up - u;
	return join(0, u_up, u_left);
}

/*
//using ArrayFire built-in grad
array Gradient(array u)
{
		array ux, uy;
		grad(ux, uy, u);
		return join(0, ux, uy);
}
*/

