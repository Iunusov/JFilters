#pragma once

#define VST_PROGRAMS_COUNT			(1)
#define VST_PARAMS_COUNT			(2)
#define CHANNELS_COUNT				(2)
#define VST_INDEX_SLOPE				(0)
#define VST_INDEX_CUTOFF			(1)
#define FILTER_SLOPE_MAX			(5)
#define FILTER_RIPPLE				(0.0001)
#define FILTER_CHEBYSHEV_ORDER		(4)

#include <mutex>
#include <string>
#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "AFilter.h"

using std::recursive_mutex;
using std::lock_guard;
using std::string;

class Plugin: public AudioEffectX {
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
	inline void updateCutoffValue(void);
	inline void updateSlopeValue(void);
	volatile bool isEnabled = false;
	void setupFilter(void);
public:
	virtual void open();
	virtual void close();
	virtual void suspend();
	virtual void resume();
	Plugin(audioMasterCallback audioMaster, AFilter *filter);
	virtual ~Plugin();
	virtual void processReplacing(float** inputs, float** outputs,
			VstInt32 sampleFrames);
	virtual void processDoubleReplacing(double** inputs, double** outputs,
			VstInt32 sampleFrames);
	virtual void setParameter(VstInt32 index, float value);
	virtual float getParameter(VstInt32 index);
	virtual void getParameterLabel(VstInt32 index, char* label);
	virtual void getParameterDisplay(VstInt32 index, char* text);
	virtual void getParameterName(VstInt32 index, char* label);
	virtual bool getEffectName(char* name);
	virtual bool getVendorString(char* text);
	virtual bool getProductString(char* text);
	virtual VstInt32 getVendorVersion();
	virtual void setProgramName(char* name);
	virtual void getProgramName(char* name);
};
