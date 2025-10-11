/* debug.h - various debug tools */

#ifndef DEBUG_H
#define DEBUG_H

#include "err.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef FEATURE_DEBUG_MODE
    #define ASSERT_TRUE(expr, msg, ...) \
        if (!expr) { \
            fprintf(stderr, "=================\n"); \
            fprintf(stderr, "ASSERTION FAILED!\n"); \
            fprintf(stderr, "=================\n"); \
            fprintf(stderr, "File:      %s\n", __FILE__); \
            fprintf(stderr, "Line:      %d\n", __LINE__); \
            fprintf(stderr, "Message:   ", msg); \
            fprintf(stderr, msg, ##__VA_ARGS__); \
			exit(ERR_ASSERT); \
		}
#else
    #define ASSERT_TRUE(expr, msg, ...) do {} while(0);

#endif		                                                // FEATURE_DEBUG_MODE

#ifdef FEATURE_DEBUG_MODE
    #define DEBUG_LOG(msg, ...) \
        printf("DEBUG (%s:%d) - ", __FILE__, __LINE__); \
        printf(msg, ##__VA_ARGS__);
#else
    #define DEBUG_LOG(msg, ...) do {} while(0);
#endif


#endif		                                                // !ERR_H
