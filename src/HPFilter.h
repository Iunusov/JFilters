#ifndef HP_FILTER_
#define HP_FILTER_

#include "AFilter.h"

class HPFilter: public AFilter {
public:
	HPFilter();
	void setup(double sRate, int order, double cutoff, double ripple);
};

#endif
