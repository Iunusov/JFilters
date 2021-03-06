#include "Plugin.h"

void Plugin::updateCutoffValue(void) {
	guard lock(recursiveMutex);
	const float freq(getSampleRate() * 0.5);
	const float p = pow(params[VST_INDEX_CUTOFF].raw_value, params[VST_INDEX_SLOPE].value + 1);
	params[VST_INDEX_CUTOFF].value = 1 + p * freq - 2 * p;
}
void Plugin::updateSlopeValue(void) {
	guard lock(recursiveMutex);
	params[VST_INDEX_SLOPE].value = params[VST_INDEX_SLOPE].raw_value * FILTER_SLOPE_MAX;
	updateCutoffValue();
}
Plugin::Plugin(audioMasterCallback audioMaster, AFilter *filter) :
	AudioEffectX(audioMaster, VST_PROGRAMS_COUNT, VST_PARAMS_COUNT) {
	setUniqueID(CCONST(UID[0], UID[1], UID[2], UID[3]));
	currentFilter = filter;
	params[VST_INDEX_SLOPE].name = "Slope";
	params[VST_INDEX_SLOPE].label = "";
	params[VST_INDEX_SLOPE].raw_value = 0.3;
	params[VST_INDEX_CUTOFF].name = "Cutoff";
	params[VST_INDEX_CUTOFF].label = "Hz";
	params[VST_INDEX_CUTOFF].raw_value = 0.5;
	setNumInputs(CHANNELS_COUNT);
	setNumOutputs(CHANNELS_COUNT);
	isSynth(false);
	noTail(true);
	canProcessReplacing(true);
	canDoubleReplacing(true);
}

void Plugin::setupFilter(void) {
	guard lock(recursiveMutex);
	currentFilter->setup(getSampleRate(), FILTER_CHEBYSHEV_ORDER, params[VST_INDEX_CUTOFF].value, FILTER_RIPPLE);
}

void Plugin::open() {
	guard lock(recursiveMutex);
	updateSlopeValue();
	setupFilter();
	isEnabled = true;
}

void Plugin::close() {
	guard lock(recursiveMutex);
	isEnabled = false;
}

void Plugin::suspend() {
	guard lock(recursiveMutex);
	isEnabled = false;
}

void Plugin::resume() {
	guard lock(recursiveMutex);
	updateSlopeValue();
	setupFilter();
	isEnabled = true;
}

Plugin::~Plugin() {
	delete currentFilter;
}

void Plugin::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {
	guard lock(recursiveMutex);
	if (!isEnabled) return;
	currentFilter->process(inputs, outputs, sampleFrames);
}
void Plugin::processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) {
	guard lock(recursiveMutex);
	if (!isEnabled) return;
	currentFilter->process(inputs, outputs, sampleFrames);
}

void Plugin::setParameter(VstInt32 index, float value) {
	guard lock(recursiveMutex);
	params[index].raw_value = value;
	if (index == VST_INDEX_SLOPE) {
		updateSlopeValue();
		setupFilter();
	}
	if (index == VST_INDEX_CUTOFF) {
		updateCutoffValue();
		setupFilter();
	}
}
float Plugin::getParameter(VstInt32 index) {
	return params[index].raw_value;
}
void Plugin::getParameterLabel(VstInt32 index, char* label) {
	vst_strncpy(label, params[index].label.c_str(), kVstMaxParamStrLen);
}
void Plugin::getParameterDisplay(VstInt32 index, char* text) {
	float2string(params[index].value, text, kVstMaxParamStrLen);
}
void Plugin::getParameterName(VstInt32 index, char* label) {
	vst_strncpy(label, params[index].name.c_str(), kVstMaxParamStrLen);
}

bool Plugin::getEffectName(char* name) {
	vst_strncpy(name, EFFECT_NAME, kVstMaxEffectNameLen);
	return true;
}
bool Plugin::getVendorString(char* text) {
	vst_strncpy(text, VENDOR_STRING, kVstMaxVendorStrLen);
	return true;
}
bool Plugin::getProductString(char* text) {
	vst_strncpy(text, PRODUCT_NAME, kVstMaxProductStrLen);
	return true;
}
VstInt32 Plugin::getVendorVersion() {
	return VENDOR_VERSION;
}

void Plugin::setProgramName(char* name) {
	programName = name;
}

void Plugin::getProgramName(char* name) {
	vst_strncpy(name, programName.c_str(), kVstMaxProgNameLen);
}
