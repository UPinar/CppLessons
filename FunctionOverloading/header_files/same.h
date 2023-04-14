#pragma once

/*
	predefined symbolic constants (predefined macro)
	------------------------------------------------
	__LINE__
	__FILE__
	__DATE__
	__TIME__
*/

#ifdef __cplusplus
extern "C" {
#endif
	int func_same(int, int);
	int f1(int, int);
	int f2(int, int);
	int f3(int, int);

#ifdef __cplusplus
}
#endif

// If the Compiler is C++ compiler it will add extern "C" block to the code.
// If the Compiler is C compiler it will not add extern "C" block and only use functions.

// This module can be used with C and C++ now.
