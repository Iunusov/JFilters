#pragma once

#include "AFilter.h"

class HPFilter: public AFilter {
public:
	HPFilter(void);
	void setup(double sRate, int order, double cutoff, double ripple);
};

