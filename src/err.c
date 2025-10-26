/* err.c - error handling */

#include "err.h"
#include "type.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

Void init_err(Err *err) {
    err->code               = ERR_OK;
    err->ln                 = 0;
    err->msg[0]             = '\0';
    err->file[0]            = '\0';
    return;
}

Void throw(Err *err, U8 code, U32 ln, Ch *file, Ch *msg, ...) {

    if (err == NULL) {
        return;
    }
    
    // Set trivial fields:
    err->code = code;
    err->ln = ln;

    // Write to character buffers:
    strncpy(err->file, file, ERR_FILE_BUF_SZ - 1);
    va_list args;
    va_start(args, msg);
    vsnprintf(err->msg, ERR_MSG_BUF_SZ - 1, msg, args);
    va_end(args);
    return;
}

Bool is_err(Err *err) {
    return err->code != ERR_OK;
}

Void warn(Err *err) {
    fprintf(stderr, "======\n");
    fprintf(stderr, "ERROR!\n");
    fprintf(stderr, "======\n");
    fprintf(stderr, "File:      %s\n", err->file);
    fprintf(stderr, "Line:      %ld\n", err->ln);
    fprintf(stderr, "Code:      %d\n", err->code);
    fprintf(stderr, "Message:   %s\n", err->msg);
}
