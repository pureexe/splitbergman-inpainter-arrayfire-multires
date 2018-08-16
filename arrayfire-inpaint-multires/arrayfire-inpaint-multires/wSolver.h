#pragma once
#include "stdafx.h"
#include "Gradient.h"
#include "Signum.h"

//w = max(abs(gradU + b) - (1 / theta), 0) * signnum(gradU+b);


array wSolver(array u, array b, double theta) {	
	int height = u.dims(0);
	int width = u.dims(1);
	array gradB = Gradient(u) + b;
	array w = abs(gradB) - (1 / theta);
	array zeroMatrix = constant(0, height * 2, width, f64);
	w = max(w, zeroMatrix) * Signum(gradB);
	return w;
}

