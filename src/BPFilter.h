#pragma once

#include "AFilter.h"

class BPFilter: public AFilter {
public:
	BPFilter(void);
	void setup(double sRate, int order, double cutoff, double ripple);
};

