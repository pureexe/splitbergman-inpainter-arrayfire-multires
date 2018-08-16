#pragma once
#include "stdafx.h"
#include "MeanSquareError.h"
#include <cmath>

double PeakSignalToNoiseRatio(array input, array reference) {
	double MSE = MeanSquareError(input, reference);
	return 10 * log10(1 / MSE); //if use [0-255] please change 1 to 255*255
}