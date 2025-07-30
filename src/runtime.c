#include "runtime.h"
#include <quickjs.h>

// **********************************************************

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

    if(dummy_print(ctx, argc, argv) < 0 ) {
        return JS_EXCEPTION;
    }

    return JS_UNDEFINED;
}


static JSValue js_log_warn(JSContext *ctx, JSValue this_val, int argc, JSValue *argv) {

    printf("[WARN] ");

    if(dummy_print(ctx, argc, argv) < 0 ) {
        return JS_EXCEPTION;
    }

    return JS_UNDEFINED;
}

static LogFunction log_functions[] = {
    (LogFunction){.name = "info", .func = js_log_info, .length = 1},
    (LogFunction){.name = "warn", .func = js_log_warn, .length = 1},
};

void runtime_add_log(JSContext *ctx) {
    JSValue global, log;

    global = JS_GetGlobalObject(ctx);
    log = JS_NewObject(ctx);

    size_t size_log = sizeof(log_functions) / sizeof(log_functions[0]);

    for(size_t i = 0 ; i < size_log; i++) {

        LogFunction f = log_functions[i];
        JS_SetPropertyStr(ctx, log, f.name, JS_NewCFunction(ctx, f.func, f.name, f.length));
    }


    JS_SetPropertyStr(ctx, global, "log", log);

    JS_FreeValue(ctx, global);
    return;
}


// **********************************************************