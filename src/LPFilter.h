#ifndef LP_FILTER_H_
#define LP_FILTER_H_

#include "AFilter.h"

class LPFilter: public AFilter {
public:
	LPFilter();
	void setup(double sRate, int order, double cutoff, double ripple);
};

#endif
