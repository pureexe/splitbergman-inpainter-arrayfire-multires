#pragma once
#include "stdafx.h"

array MergeResult(array original_image, array inpainted_domain, array upscale_result)
{
	array upscale_condition = (inpainted_domain > 0) * 1.0;
	array original_condition = (inpainted_domain == 0) * 1.0;
	return (upscale_result*upscale_condition) + (original_image*original_condition);
}