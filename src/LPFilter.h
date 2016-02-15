#pragma once

#include "AFilter.h"

class LPFilter: public AFilter {
public:
	LPFilter(void);
	void setup(double sRate, int order, double cutoff, double ripple);
};

