#ifndef RUNTIME_H
#define RUNTIME_H

#include <quickjs.h>


typedef struct LogFunction {
    const char *name;
    void* func;
    int length;
} LogFunction;


void runtime_add_log(JSContext *ctx);

void runtime_add_args(JSContext *ctx);

#endif