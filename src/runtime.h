#ifndef RUNTIME_H
#define RUNTIME_H

#include <quickjs.h>


typedef struct LogFunction {
    const char *name;
    void* func;
    int length;
} LogFunction;


void runtime_add_log(JSValue *global, JSContext *ctx);

void runtime_add_args(JSValue *global, JSContext *ctx, int args, char *argv[]);

void runtime_add_run(JSValue *global, JSContext *ctx);

#endif