#ifndef SM_API_DLL_H
#define SM_API_DLL_H

#if defined (__GNUC__) && defined(__unix__)
    #define SM_API_EXPORT __attribute__ ((__visibility__("default")))
#elif defined (WIN32)
    #ifndef SM_API_EXPORT
        #define SM_API_EXPORT  __declspec(dllexport)
    #else
        #define SM_API_EXPORT  __declspec(dllimport)
    #endif
#endif

#endif
