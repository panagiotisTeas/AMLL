#include "core/error.h"

#include "core/types.h"
#include <stdlib.h>
#include <stdio.h>

#define AMLL_ERROR_MESSAGE_BUFFER_SIZE 1024

void 
amll_set_error(AMLLError** error, AMLLErrorCode code, const char* message, ...)
{
    if (error == NULL) return;

    if (*error != NULL) amll_clear_error(error);

    *error = (AMLLError*)malloc(sizeof(AMLLError));
    if (*error == NULL) exit(EXIT_FAILURE);

    (*error)->code = code;
    (*error)->message = (char*)malloc(sizeof(char) * AMLL_ERROR_MESSAGE_BUFFER_SIZE);
    if ((*error)->message == NULL) { free(*error); exit(EXIT_FAILURE); }
    u32 message_buffer_offset = 0;

    va_list args;
    va_start(args, message);

    message_buffer_offset += vsnprintf(
        (*error)->message + message_buffer_offset, 
        AMLL_ERROR_MESSAGE_BUFFER_SIZE - message_buffer_offset, 
        message, 
        args);
        
    va_end(args);
}

void 
amll_clear_error(AMLLError** error)
{
    if (error == NULL || *error == NULL) return;

    free((*error)->message);
    free(*error);
    *error = NULL;
}