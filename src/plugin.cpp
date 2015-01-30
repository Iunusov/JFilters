#include "plugin.h"
#include "define.h"
//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new Plugin (audioMaster);
}
//-------------------------------------------------------------------------------------------------------
Plugin::Plugin (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, VST_PROGRAMS_COUNT, VST_PARAMS_COUNT)	
{
	vst_strncpy(params[VST_INDEX_CUTOFF].name,"Cutoff",LABEL_MAX_LENGTH);
	vst_strncpy(params[VST_INDEX_CUTOFF].label,"Hz",LABEL_MAX_LENGTH);
	vst_strncpy(params[VST_INDEX_SLOPE].name,"Slope",LABEL_MAX_LENGTH);
	setNumInputs (2);		// stereo in
	setNumOutputs (2);		// stereo out
	setUniqueID (UID);	// identify
	canProcessReplacing ();	// supports replacing output
	canDoubleReplacing ();	// supports double precision processing
	params[VST_INDEX_CUTOFF].raw_value = 0.5;
	params[VST_INDEX_SLOPE].value = 0;
	params[VST_INDEX_SLOPE].raw_value = 0;
	vst_strncpy (programName, "Default", kVstMaxProgNameLen);	// default program name
}
//-------------------------------------------------------------------------------------------------------
double Plugin::calc_cutoff(double value){
	return std::min(0.5*pow(value, params[VST_INDEX_SLOPE].value+1)*getSampleRate()+20,0.5*getSampleRate());
}

Plugin::~Plugin ()
{

}

//-------------------------------------------------------------------------------------------------------
void Plugin::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Plugin::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
	params[VST_INDEX_CUTOFF].value = calc_cutoff(params[VST_INDEX_CUTOFF].raw_value);
}

//-----------------------------------------------------------------------------------------
void Plugin::setParameter (VstInt32 index, float value)
{
	params[index].raw_value = value;
	if(index == VST_INDEX_SLOPE){
	    params[index].value = value*FILTER_SLOPE_MAX;
	   // setParameter(VST_INDEX_CUTOFF, params[VST_INDEX_CUTOFF].raw_value);
	}
	if(index == VST_INDEX_CUTOFF){
	  params[VST_INDEX_CUTOFF].value = calc_cutoff(params[VST_INDEX_CUTOFF].raw_value);
	}
}

//-----------------------------------------------------------------------------------------
float Plugin::getParameter (VstInt32 index)
{
	return (float)params[index].raw_value;
}

//-----------------------------------------------------------------------------------------
void Plugin::getParameterName (VstInt32 index, char* label)
{
	vst_strncpy (label, params[index].name, kVstMaxParamStrLen);
}

//-----------------------------------------------------------------------------------------
void Plugin::getParameterDisplay (VstInt32 index, char* text)
{
	float2string ((float)params[index].value, text, kVstMaxParamStrLen);
}

//-----------------------------------------------------------------------------------------
void Plugin::getParameterLabel (VstInt32 index, char* label)
{
	vst_strncpy (label, params[index].label, kVstMaxParamStrLen);
}

//------------------------------------------------------------------------
bool Plugin::getEffectName (char* name)
{
	vst_strncpy (name, EFFECT_NAME, kVstMaxEffectNameLen);
	return true;
}

//------------------------------------------------------------------------
bool Plugin::getProductString (char* text)
{
	vst_strncpy (text, PRODUCT_NAME, kVstMaxProductStrLen);
	return true;
}

//------------------------------------------------------------------------
bool Plugin::getVendorString (char* text)
{
	vst_strncpy (text, VENDOR_STRING, kVstMaxVendorStrLen);
	return true;
}


//-----------------------------------------------------------------------------------------
VstInt32 Plugin::getVendorVersion ()
{ 
	return VENDOR_VERSION; 
}
//-----------------------------------------------------------------------------------------
void Plugin::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];
	Filter.setup(getSampleRate(), FILTER_CHEBYSHEV_ORDER,params[VST_INDEX_CUTOFF].value,FILTER_RIPPLE);
	Filter.process(sampleFrames,inputs);
	while (--sampleFrames >= 0)
    {
        (*out1++) = (*in1++);
        (*out2++) = (*in2++);
    }
}
//-----------------------------------------------------------------------------------------
void Plugin::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames){
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];
	Filter.setup(getSampleRate(), FILTER_CHEBYSHEV_ORDER,params[VST_INDEX_CUTOFF].value,FILTER_RIPPLE);
	Filter.process(sampleFrames,inputs);
	while (--sampleFrames >= 0)
    {
        (*out1++) = (*in1++);
        (*out2++) = (*in2++);
    }
}
//-----------------------------------------------------------------------------------------