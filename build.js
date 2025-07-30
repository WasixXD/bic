

const GCC = "gcc"
const flags = [
    "-I/usr/local/include/quickjs/",
    "-Wall",
    "-L/usr/local/lib/quickjs/",
    "-o", "bic",  "src/runtime.h", "src/runtime.c", "src/main.c",
    "-lquickjs", "-lm"
]


function main() {

    log.info("Bootstraping the project!")

    run(GCC, flags)

    // run("./main")
}



main()