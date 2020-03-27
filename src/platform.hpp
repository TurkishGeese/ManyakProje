#if defined(MANYAK_WIN32)
	#define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
#elif defined(MANYAK_MAC)
	#define EXPORT extern "C"
	#define IMPORT
#endif