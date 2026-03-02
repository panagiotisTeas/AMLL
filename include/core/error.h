#ifndef AMLL_ERROR_H
#define AMLL_ERROR_H

// --------------------------
// --- Programming errors ---
// --------------------------

#include <assert.h>

#define AMLL_ASSERT(expression)                         assert((expression))
#define AMLL_ASSERT_WITH_MESSAGE(expression, message)   assert((expression) && (message))

// ----------------------------------
// --- Recoverable Runtime Errors ---
// ----------------------------------

#include <stdarg.h>

typedef enum AMLLErrorCode
{
    AMLL_OK = 0,
} AMLLErrorCode;

typedef struct AMLLError
{
    AMLLErrorCode   code;
    char*           message;
} AMLLError;

void amll_set_error(AMLLError** error, AMLLErrorCode code, const char* message, ...);
void amll_clear_error(AMLLError** error);


#endif // AMLL_ERROR_H