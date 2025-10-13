/* err.h - error handling */

#ifndef ERR_H
#define ERR_H

#include "type.h"

#include <stdarg.h>

/* ----- ERROR CODES ----- */

#define ERR_OK          0                   // No error
#define ERR_RUN         1                   // Generic runtime error
#define ERR_ARGV        2                   // Bad command-line option
#define ERR_MEM         3                   // Out-of-memory
#define ERR_IO          4                   // IO failure
#define ERR_DATA        5                   // Corrupt/malformed data
#define ERR_INIT		6                   // Subsystem initialization
#define ERR_GRAPH		7                   // Graphics failure
#define ERR_ASSERT      240                 // Assertion failure

/* ----- OTHER CONSTANTS ----- */

#define ERR_MSG_BUF_SZ 128
#define ERR_FILE_BUF_SZ 64

/* ----- MACROS ----- */

/* Throw an error. Supports 'printf' style formatting. At least one format variable must be given. */
#define THROW(err, code, msg, ...) throw(err, code, __LINE__, __FILE__, msg, ##__VA_ARGS__);

/* ----- STRUCTS ----- */

/* Holds an error state. */
typedef struct STRUCT_ERR {
    U8      code;
    U32     ln;
    Ch      msg[ERR_MSG_BUF_SZ];
    Ch      file[ERR_FILE_BUF_SZ];
} Err;

/* ----- FUNCTIONS ----- */

/* Use this function to reset an 'Err' to default state as well. */
Void init_err(Err *err);

/* Supports printf-style formatting. This function shouldn't be used directly--use the 'THROW' macro instead. */
Void throw(Err *err, U8 code, U32 ln, Ch *file, Ch *msg, ...);

Bool is_err(Err *err);

Void warn(Err *err);

#endif
