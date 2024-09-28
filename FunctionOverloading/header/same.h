#ifndef SAME_H
#define SAME_H

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
  #ifdef __cplusplus
  }
  #endif

#endif // SAME_H

// If compiler is a C++ compiler it will 
// add extern "C" block to the code.

// if compiler is a C compiler it will not add 
// extern "C" block and only use functions.

// This module can be used with both C and C++ compiler.
