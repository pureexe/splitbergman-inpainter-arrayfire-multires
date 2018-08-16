#pragma once
#include "stdafx.h"

array Signum(array input) {
	array positive = (input > 0) * 1.0;
	array negative = (input < 0) * -1.0;
	return  positive + negative;
}
