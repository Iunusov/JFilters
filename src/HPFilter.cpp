#include "HPFilter.h"
#include "Plugin.h"

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new Plugin(audioMaster, new HPFilter);
}

HPFilter::HPFilter(void) {
	Filter = new Dsp::SmoothedFilterDesign<Dsp::ChebyshevI::Design::HighPass<FILTER_CHEBYSHEV_ORDER>, 2>(2048);
}

void HPFilter::setup(double sRate, int order, double cutoff, double ripple) {
	filter_params[0] = sRate; // sample rate
	filter_params[1] = order;
	filter_params[2] = cutoff; // corner frequency
	filter_params[3] = ripple; // passband ripple
	Filter->setParams(filter_params);
}
