#ifndef DLL_EXPORT_H
#define DLL_EXPORT_H

#ifdef _WIN32
  #ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
  #else
    #define DLL_EXPORT
  #endif
#else
  #define DLL_EXPORT
#endif

#endif // DLL_EXPORT_H
