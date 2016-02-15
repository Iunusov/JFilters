#pragma once

#define VST_PROGRAMS_COUNT (1)
#define VST_PARAMS_COUNT (2)

#define VST_INDEX_SLOPE (0)
#define VST_INDEX_CUTOFF (1)

#define FILTER_SLOPE_MAX (5)
#define FILTER_RIPPLE (0.0001)
#define FILTER_CHEBYSHEV_ORDER (4)

#define CHANNELS_COUNT (2)

#include <math.h>
#include <mutex>
#include <thread>
#include <string>
#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "DspFilters/Dsp.h"

using std::recursive_mutex;
using std::lock_guard;
using std::string;

class Plugin : public AudioEffectX {
private:
	typedef std::lock_guard<std::recursive_mutex> guard;
	typedef struct {
		string name;
		string label;
		float value;
		float raw_value;
	} PluginParams;
	AFilter *currentFilter;
	PluginParams params[VST_PARAMS_COUNT];
	string programName = "Default";
	recursive_mutex recursiveMutex;
	//TODO: rewrite it
	inline void updateCutoffValue(void) {
		guard lock(recursiveMutex);
		const float freq(getSampleRate() * 0.5);
		const float minFreqHZ = 20;
		const float maxFreqHZ = freq - minFreqHZ;
		float calcFreq = pow(params[VST_INDEX_CUTOFF].raw_value, params[VST_INDEX_SLOPE].value + 1) * freq + minFreqHZ;
		if (calcFreq < minFreqHZ) {
			 calcFreq = minFreqHZ;
		}
		if (calcFreq > maxFreqHZ) {
			 calcFreq = maxFreqHZ;
		}
		params[VST_INDEX_CUTOFF].value = calcFreq;
	}
	inline void updateSlopeValue(void) {
		params[VST_INDEX_SLOPE].value = params[VST_INDEX_SLOPE].raw_value * FILTER_SLOPE_MAX;
	}
public:
	Plugin(audioMasterCallback audioMaster, AFilter *filter) :
		AudioEffectX(audioMaster, VST_PROGRAMS_COUNT, VST_PARAMS_COUNT) {
		currentFilter = filter;
		params[VST_INDEX_SLOPE].name = "Slope";
		params[VST_INDEX_SLOPE].label = "";
		params[VST_INDEX_SLOPE].value = 0;
		params[VST_INDEX_SLOPE].raw_value = 0;
		params[VST_INDEX_CUTOFF].name = "Cutoff";
		params[VST_INDEX_CUTOFF].label = "Hz";
		params[VST_INDEX_CUTOFF].raw_value = 0.5;
		updateCutoffValue();
		setNumInputs(CHANNELS_COUNT);
		setNumOutputs(CHANNELS_COUNT);
		isSynth(false);
		setUniqueID(CCONST(UID[0], UID[1], UID[2], UID[3]));
		canProcessReplacing();
		canDoubleReplacing();
	}
	virtual ~Plugin() {
		delete currentFilter;
	}

	virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {
		guard lock(recursiveMutex);
		currentFilter->process(inputs, outputs, sampleFrames);
	}
	virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) {
		guard lock(recursiveMutex);
		currentFilter->process(inputs, outputs, sampleFrames);
	}

	virtual void setParameter(VstInt32 index, float value) {
		guard lock(recursiveMutex);
		params[index].raw_value = value;
		if (index == VST_INDEX_SLOPE) {
			updateSlopeValue();
		}
		if (index == VST_INDEX_CUTOFF) {
			updateCutoffValue();
		}
		currentFilter->setup(getSampleRate(), FILTER_CHEBYSHEV_ORDER, params[VST_INDEX_CUTOFF].value, FILTER_RIPPLE);
	}
	virtual float getParameter(VstInt32 index) {
		return params[index].raw_value;
	}
	virtual void getParameterLabel(VstInt32 index, char* label) {
		vst_strncpy(label, params[index].label.c_str(), kVstMaxParamStrLen);
	}
	virtual void getParameterDisplay(VstInt32 index, char* text) {
		float2string(params[index].value, text, kVstMaxParamStrLen);
	}
	virtual void getParameterName(VstInt32 index, char* label) {
		vst_strncpy(label, params[index].name.c_str(), kVstMaxParamStrLen);
	}

	virtual bool getEffectName(char* name) {
		vst_strncpy(name, EFFECT_NAME, kVstMaxEffectNameLen);
		return true;
	}
	virtual bool getVendorString(char* text) {
		vst_strncpy(text, VENDOR_STRING, kVstMaxVendorStrLen);
		return true;
	}
	virtual bool getProductString(char* text) {
		vst_strncpy(text, PRODUCT_NAME, kVstMaxProductStrLen);
		return true;
	}
	virtual VstInt32 getVendorVersion() {
		return VENDOR_VERSION;
	}

	virtual void setProgramName(char* name) {
		programName = name;
	}

	virtual void getProgramName(char* name) {
		vst_strncpy(name, programName.c_str(), kVstMaxProgNameLen);
	}
};
