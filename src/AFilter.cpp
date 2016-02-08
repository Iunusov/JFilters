#include "AFilter.h"

void AFilter::process(int numSamples, double **arr) {
	Filter->process(numSamples, arr);
}

void AFilter::process(int numSamples, float **arr) {
	Filter->process(numSamples, arr);
}

AFilter::~AFilter() {
	delete Filter;
}
