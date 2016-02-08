#ifndef BP_Filter_H_
#define BP_Filter_H_

#include "AFilter.h"

class BPFilter: public AFilter {
public:
	BPFilter();
	void setup(double sRate, int order, double cutoff, double ripple);
};

#endif
