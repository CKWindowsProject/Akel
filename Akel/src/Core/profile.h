// This file is a part of Akel
// CREATED : 26/06/2021
// UPDATED : 18/09/2021

#ifndef __AK_PROFILE_CORE__
#define __AK_PROFILE_CORE__

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define AK_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define AK_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
	#define AK_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define AK_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define AK_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define AK_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define AK_FUNC_SIG __func__
#else
	#define AK_FUNC_SIG "Unknown function"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define AK_PLATFORM_WINDOWS
	#define forceinline __forceinline
	#if _WIN64
		#define AK_64BITS
	#else
		#define AK_32BITS
	#endif
#elif __GNUC__
	#if __x86_64__ || __ppc64__
		#define AK_64BITS
	#else
		#define AK_32BITS
	#endif
#else
	#error Akel can only run on 32bit or 64bit architectures
#endif

#ifdef __linux__
	#define AK_PLATFORM_LINUX
	#define forceinline __attribute__((always_inline))
#elif defined(__APPLE__) || defined(__MACH__)
	#define AK_PLATFORM_OSX
	#define forceinline __attribute__((always_inline))
#endif

#endif // __AK_PROFILE_CORE__
