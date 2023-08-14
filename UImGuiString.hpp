#pragma once
#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
    #ifdef UIMGUI_TEXT_UTILS_CUSTOM_STRING
    	#ifdef UIMGUI_TEXT_UTILS_CUSTOM_STRING_INCLUDE
    		#include UIMGUI_TEXT_UTILS_CUSTOM_STRING_INCLUDE
            namespace UImGui
            {
                typedef UIMGUI_TEXT_UTILS_CUSTOM_STRING TString;
            }
    	#else
    		#error UIMGUI_TEXT_UTILS_CUSTOM_STRING defined but UEXEC_CUSTOM_STRING_INCLUDE not defined, it is needed to include the necessary headers for the string, and should contain the name of the header wrapped in ""
    	#endif
    #else
    	#include <string>
        namespace UImGui
        {
            typedef std::string TString;
        }
    #endif
#endif
