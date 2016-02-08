#ifndef AFilter_H_
#define AFilter_H_

#include "DspFilters/Dsp.h"

class AFilter {
protected:
	Dsp::Filter *Filter;
	Dsp::Params filter_params;
public:
	void process(int numSamples, double **arr);
	void process(int numSamples, float **arr);
	~AFilter();
};

#endif
