#pragma once

#include "DspFilters/Dsp.h"

class AFilter {
protected:
	Dsp::Filter *Filter;
	Dsp::Params filter_params;
	AFilter(void);
public:
	template <typename T, typename L>
	void process(T** inputs, T** outputs, L sampleFrames) {
		T* in1 = inputs[0];
		T* in2 = inputs[1];
		T* out1 = outputs[0];
		T* out2 = outputs[1];
		Filter->process(sampleFrames, inputs);
		while (--sampleFrames >= 0) {
			(*out1++) = (*in1++);
			(*out2++) = (*in2++);
		}
	}
	virtual void setup(double sRate, int order, double cutoff, double ripple) = 0;
	virtual ~AFilter();
};
