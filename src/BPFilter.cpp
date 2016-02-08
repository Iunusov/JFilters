#include "BPFilter.h"
#include "plugin.h"

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new Plugin<BPFilter>(audioMaster);
}

BPFilter::BPFilter() {
	Filter = new Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::BandPass1, 2>(
			2048);
}

void BPFilter::setup(double sRate, int order, double cutoff, double ripple) {
	filter_params[0] = sRate; // sample rate
	filter_params[1] = cutoff; // corner frequency
	filter_params[2] = 2; //bandwidth
	Filter->setParams(filter_params);
}
