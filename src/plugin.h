#ifndef __plugin__
#define __plugin__

#define LABEL_MAX_LENGTH 32

#define VST_PROGRAMS_COUNT 1
#define VST_PARAMS_COUNT 2

#define VST_INDEX_CUTOFF 1
#define VST_INDEX_SLOPE 0

#define FILTER_SLOPE_MAX 5
#define FILTER_RIPPLE 0.0001
#define FILTER_CHEBYSHEV_ORDER 4

#include <math.h>
#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "DspFilters/Dsp.h"

typedef struct {
	char name[LABEL_MAX_LENGTH];
	char label[LABEL_MAX_LENGTH];
	double value;
	double raw_value;
} plugin_params;
template<class TFILTER>
class Plugin: public AudioEffectX {
public:
	Plugin(audioMasterCallback audioMaster) :
			AudioEffectX(audioMaster, VST_PROGRAMS_COUNT, VST_PARAMS_COUNT) {
		vst_strncpy(params[VST_INDEX_CUTOFF].name, "Cutoff", LABEL_MAX_LENGTH);
		vst_strncpy(params[VST_INDEX_CUTOFF].label, "Hz", LABEL_MAX_LENGTH);
		vst_strncpy(params[VST_INDEX_SLOPE].name, "Slope", LABEL_MAX_LENGTH);
		setNumInputs(2);		// stereo in
		setNumOutputs(2);		// stereo out
		setUniqueID (UID);	// identify
		canProcessReplacing();	// supports replacing output
		canDoubleReplacing();	// supports double precision processing
		params[VST_INDEX_CUTOFF].raw_value = 0.5;
		params[VST_INDEX_SLOPE].value = 0;
		params[VST_INDEX_SLOPE].raw_value = 0;
		vst_strncpy(programName, "Default", kVstMaxProgNameLen);// default program name
	}
	~Plugin() {
	}

	// Processing
	virtual void processReplacing(float** inputs, float** outputs,
			VstInt32 sampleFrames) {
		float* in1 = inputs[0];
		float* in2 = inputs[1];
		float* out1 = outputs[0];
		float* out2 = outputs[1];
		Filter.setup(getSampleRate(), FILTER_CHEBYSHEV_ORDER,
				params[VST_INDEX_CUTOFF].value, FILTER_RIPPLE);
		Filter.process(sampleFrames, inputs);
		while (--sampleFrames >= 0) {
			(*out1++) = (*in1++);
			(*out2++) = (*in2++);
		}
	}
	virtual void processDoubleReplacing(double** inputs, double** outputs,
			VstInt32 sampleFrames) {
		double* in1 = inputs[0];
		double* in2 = inputs[1];
		double* out1 = outputs[0];
		double* out2 = outputs[1];
		Filter.setup(getSampleRate(), FILTER_CHEBYSHEV_ORDER,
				params[VST_INDEX_CUTOFF].value, FILTER_RIPPLE);
		Filter.process(sampleFrames, inputs);
		while (--sampleFrames >= 0) {
			(*out1++) = (*in1++);
			(*out2++) = (*in2++);
		}
	}

	// Program
	virtual void setProgramName(char* name) {
		vst_strncpy(programName, name, kVstMaxProgNameLen);
	}
	virtual void getProgramName(char* name) {
		vst_strncpy(name, programName, kVstMaxProgNameLen);
		params[VST_INDEX_CUTOFF].value = calc_cutoff(
				params[VST_INDEX_CUTOFF].raw_value);
	}

	// Parameters
	virtual void setParameter(VstInt32 index, float value) {
		params[index].raw_value = value;
		if (index == VST_INDEX_SLOPE) {
			params[index].value = value * FILTER_SLOPE_MAX;
			// setParameter(VST_INDEX_CUTOFF, params[VST_INDEX_CUTOFF].raw_value);
		}
		if (index == VST_INDEX_CUTOFF) {
			params[VST_INDEX_CUTOFF].value = calc_cutoff(
					params[VST_INDEX_CUTOFF].raw_value);
		}
	}
	virtual float getParameter(VstInt32 index) {
		return (float) params[index].raw_value;
	}
	virtual void getParameterLabel(VstInt32 index, char* label) {
		vst_strncpy(label, params[index].label, kVstMaxParamStrLen);
	}
	virtual void getParameterDisplay(VstInt32 index, char* text) {
		float2string((float) params[index].value, text, kVstMaxParamStrLen);
	}
	virtual void getParameterName(VstInt32 index, char* label) {
		vst_strncpy(label, params[index].name, kVstMaxParamStrLen);
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

protected:
	Dsp::Params filter_params;
	TFILTER Filter;
	plugin_params params[VST_PARAMS_COUNT];
	char programName[kVstMaxProgNameLen + 1];
	double calc_cutoff(double value) {
		return std::min(
				0.5 * pow(value, params[VST_INDEX_SLOPE].value + 1)
						* getSampleRate() + 20, 0.5 * getSampleRate());
	}
};
#endif
