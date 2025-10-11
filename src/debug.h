/* debug.h - various debug tools */

#ifndef DEBUG_H
#define DEBUG_H

#include "err.h"

#include <stdlib.h>

#ifdef FEATURE_DEBUG_MODE
    #define ASSERT_TRUE(expr, msg) \
        if (!expr) { \
            fprintf(stderr, "=================\n"); \
            fprintf(stderr, "ASSERTION FAILED!\n"); \
            fprintf(stderr, "=================\n"); \
            fprintf(stderr, "File:      %s\n", __FILE__); \
            fprintf(stderr, "Line:      %d\n", __LINE__); \
            fprintf(stderr, "Message:   %s\n", msg); \
			exit(ERR_ASSERT); \
		}
#else
    #define ASSERT_TRUE(expr, msg) do {} while(0);

#endif		// FEATURE_DEBUG_MODE
#endif		// !ERR_H
