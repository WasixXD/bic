#include "runtime.h"
#include <quickjs.h>
#include <unistd.h>
#include <string.h>

// TODO: Better Error Handling 

// **********************************************************

// TODO: Print objects
static int dummy_print(JSContext *ctx, int argc, JSValue *argv) {
    for(int i = 0; i < argc; i++) {
        if(i != 0) {
            printf(" ");
        }
        
        const char *str = JS_ToCString(ctx, argv[i]);
        if(!str) {
            return -1;
        }

        printf("%s", str);
        JS_FreeCString(ctx, str);
    }
    printf("\n");
    return 0;
}

static JSValue js_log_info(JSContext *ctx, JSValue this_val, int argc, JSValue *argv) {

    printf("[INFO] ");

    if(dummy_print(ctx, argc, argv) < 0) {
        return JS_EXCEPTION;
    }

    return JS_UNDEFINED;
}


static JSValue js_log_warn(JSContext *ctx, JSValue this_val, int argc, JSValue *argv) {

    printf("[WARN] ");

    if(dummy_print(ctx, argc, argv) < 0) {
        return JS_EXCEPTION;
    }

    return JS_UNDEFINED;
}

static LogFunction log_functions[] = {
    (LogFunction){.name = "info", .func = js_log_info, .length = 1},
    (LogFunction){.name = "warn", .func = js_log_warn, .length = 1},
};

void runtime_add_log(JSValue *global, JSContext *ctx) {
    JSValue log = JS_NewObject(ctx);

    size_t size_log = sizeof(log_functions) / sizeof(log_functions[0]);

    for(size_t i = 0 ; i < size_log; i++) {

        LogFunction f = log_functions[i];
        JS_SetPropertyStr(ctx, log, f.name, JS_NewCFunction(ctx, f.func, f.name, f.length));
    }


    JS_SetPropertyStr(ctx, *global, "log", log);
    return;
}


// **********************************************************

void runtime_add_args(JSValue *global, JSContext *ctx, int _args, char *argv[]) {
    JSValue args = JS_NewArray(ctx);

    for(int i = 0; i < _args; i++) {
        JSValue str = JS_NewString(ctx, argv[i]);
        JS_DefinePropertyValueUint32(ctx, args, i, str, JS_PROP_C_W_E);
    }


    JS_SetPropertyStr(ctx, *global, "args", args);
    return;
}


// **********************************************************

static JSValue js_internal_run(JSContext *ctx, JSValue this_val, int argc, JSValue *argv) {
    const char *command = JS_ToCString(ctx, argv[0]);
    if(!command) {
        return JS_EXCEPTION;
    }
    

    JSValue arr = argv[1];
    uint32_t len;
    JSValue val = JS_GetPropertyStr(ctx, arr, "length");
    JS_ToUint32(ctx, &len, val);

    char *flags[len + 2];

    flags[0] = command;
    for(uint32_t i = 0; i < len; i++) {
        val = JS_GetPropertyUint32(ctx, arr, i);
        const char *str = JS_ToCString(ctx, val);

        flags[i + 1] = strdup(str);
        JS_FreeCString(ctx, str);
    }

    flags[len + 1] = NULL;


    execvp(command, flags);

    JS_FreeCString(ctx, command);
    return JS_UNDEFINED;
}

void runtime_add_run(JSValue *global, JSContext *ctx) {

    JSValue run = JS_NewCFunction(ctx, js_internal_run, "run", 1);

    JS_SetPropertyStr(ctx, *global, "run", run);
    return;
}