#ifndef DEBUG_HELPER_H
#define DEBUG_HELPER_H

#ifdef DEBUG
#include <iostream>
#include <assert.h>


#define LOG(x)	std::cout << "Function:" << __FUNCTION__ << "\tLine:" << __LINE__ \
	<< "Info: " << x << std::endl;
#define ASSERT(x)	assert(x)

#else // it is not defined DEBUG

#define LOG(x)
#define ASSERT(x)


#endif


#endif
