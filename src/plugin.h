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

#include "math.h" 
#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "DspFilters/Dsp.h"
#include "define.h"

class AFilter{
protected:
	Dsp::Filter *Filter;
	Dsp::Params filter_params;
public:
	void process(int numSamples, double **arr){
		Filter->process(numSamples, arr);
	}
	void process(int numSamples, float **arr){
		Filter->process(numSamples, arr);
	}
	~AFilter(){delete Filter;}
};

class LPFilter: public AFilter{
public:
	LPFilter(){
		Filter = new Dsp::SmoothedFilterDesign
      <Dsp::ChebyshevI::Design::LowPass <FILTER_CHEBYSHEV_ORDER>, 2>(2048);
	}
	void setup(double sRate, int order, double cutoff, double ripple){
		filter_params[0] = sRate; // sample rate
        filter_params[1] = order;
        filter_params[2] = cutoff; // corner frequency
        filter_params[3] = ripple; // passband ripple
	    Filter->setParams(filter_params); 
	}
};

class HPFilter: public AFilter{
public:
	HPFilter(){
		Filter = new Dsp::SmoothedFilterDesign
      <Dsp::ChebyshevI::Design::HighPass <FILTER_CHEBYSHEV_ORDER>, 2>(2048);
	}
	void setup(double sRate, int order, double cutoff, double ripple){
		filter_params[0] = sRate; // sample rate
        filter_params[1] = order;
        filter_params[2] = cutoff; // corner frequency
        filter_params[3] = ripple; // passband ripple
	    Filter->setParams(filter_params); 
	}
};

class BPFilter: public AFilter{
public:
	BPFilter(){
		Filter = new Dsp::SmoothedFilterDesign
      <Dsp::RBJ::Design::BandPass1, 2>(2048);
	}
	void setup(double sRate, int order, double cutoff, double ripple){
		filter_params[0] = sRate; // sample rate
        filter_params[1] = cutoff; // corner frequency
		filter_params[2] = 2; //bandwidth
	    Filter->setParams(filter_params); 
	}
};
//-----------------------------------------------------------------------------------------------------------
typedef struct{
	  char name[LABEL_MAX_LENGTH];
	  char label[LABEL_MAX_LENGTH];
	  double value;
	  double raw_value;
    } plugin_params;
class Plugin : public AudioEffectX
{
public:
	Plugin (audioMasterCallback audioMaster);
	~Plugin ();

	// Processing
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual void processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames);


	// Program
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);


	// Parameters
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();

protected:
	Dsp::Params filter_params;
	FILTER_NAME Filter;
	plugin_params params[VST_PARAMS_COUNT];
	char programName[kVstMaxProgNameLen+1];
	double calc_cutoff(double value);
};
#endif
