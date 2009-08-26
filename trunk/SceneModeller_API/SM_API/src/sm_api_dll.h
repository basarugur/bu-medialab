#ifndef SM_API_DLL_H
#define SM_API_DLL_H


#ifndef SM_API_EXPORT
#define SM_API_EXPORT  __declspec(dllexport)
#else
#define SM_API_EXPORT  __declspec(dllimport)
#endif

#endif