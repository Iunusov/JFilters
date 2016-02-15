#include "LPFilter.h"
#include "Plugin.h"

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new Plugin (audioMaster, new LPFilter);
}

LPFilter::LPFilter(void) {
	Filter = new Dsp::SmoothedFilterDesign<Dsp::ChebyshevI::Design::LowPass<FILTER_CHEBYSHEV_ORDER>, 2>(2048);
}

void LPFilter::setup(double sRate, int order, double cutoff, double ripple) {
	filter_params[0] = sRate; // sample rate
	filter_params[1] = order;
	filter_params[2] = cutoff; // corner frequency
	filter_params[3] = ripple; // passband ripple
	Filter->setParams(filter_params);
}
