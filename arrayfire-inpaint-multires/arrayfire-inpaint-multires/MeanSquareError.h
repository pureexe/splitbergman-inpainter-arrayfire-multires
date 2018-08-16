#pragma once
#include "stdafx.h"

double MeanSquareError(array input, array reference)
{
	array difference = input - reference;
	return mean<double>(difference*difference);
}