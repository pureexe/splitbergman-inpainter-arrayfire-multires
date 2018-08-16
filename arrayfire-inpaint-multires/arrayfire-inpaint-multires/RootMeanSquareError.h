#pragma once
#include "stdafx.h"
#include "MeanSquareError.h"
#include <cmath>

double RootMeanSquareError(array input, array reference)
{
	return sqrt(MeanSquareError(input, reference));
}