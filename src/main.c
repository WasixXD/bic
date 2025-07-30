#include <stdio.h>
#include <quickjs.h>
#include <unistd.h>
#include <malloc.h>
#include "runtime.h"

#define BUILD_SRC "build.js"
#define BUILD_PATH_SIZE FILENAME_MAX + sizeof(BUILD_SRC)


int read_build_js(char **content) {
    char current_dir[FILENAME_MAX];
    if(getcwd(current_dir, FILENAME_MAX) == NULL) {
        printf("ERROR: getcwd()\n");
        return -1;
    }

    char build_path[BUILD_PATH_SIZE];
    sprintf(build_path, "%s/%s", current_dir, BUILD_SRC);

    FILE *build_js = fopen(build_path, "r");

    if(build_js == NULL) {
        printf("ERROR: `build.js` not found\n");
        return -1;
    }

    fseek(build_js, 0, SEEK_END);
    long file_size = ftell(build_js);
    rewind(build_js);

    *content = (char *)malloc(file_size + 1);
    if(*content == NULL) {
        printf("ERROR: malloc()\n");
        fclose(build_js);
        return -1;
    }

    if(fread(*content, 1, file_size, build_js) != file_size) {
        printf("ERROR: On reading the content of build.js file\n");
        free(*content);
        return -1;
    }

    (*content)[file_size] = '\0';
    fclose(build_js);
    return 0;
}



int main() {

    char *content;
    if(read_build_js(&content) < 0) {
        return -1;
    }

    free(content);
    return 0;
}
