//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4       $Date: 2006/02/13 12:04:56 $
//
// Category     : VST 2.x Classes
// Filename     : vstplugmain.cpp
// Created by   : Steinberg Media Technologies
// Description  : VST Plug-In Main Entry
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "public.sdk/source/vst2.x/audioeffect.h"
#define VST_EXPORT
HINSTANCE hInstance(NULL);
//------------------------------------------------------------------------
/** Must be implemented externally. */
extern AudioEffect* createEffectInstance (audioMasterCallback audioMaster);

extern "C" {
//------------------------------------------------------------------------
/** Prototype of the export function main */
//------------------------------------------------------------------------
VST_EXPORT __declspec(dllexport) int main(audioMasterCallback audioMaster)
{
	// Get VST Version
	if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
		return 0;  // old version

	// Create the AudioEffect
	AudioEffect* effect = createEffectInstance (audioMaster);
	if (!effect)
		return 0;

	return (int)effect->getAeffect ();
}
} // extern "C"

//------------------------------------------------------------------------
BOOL WINAPI DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	hInstance = hInst;
	return 1;
}