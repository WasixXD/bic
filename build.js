

const GCC = "gcc"
const sources = ["src/runtime.h", "src/runtime.c", "src/main.c"]
const flags = [
    "-I/usr/local/include/quickjs/",
    "-Wall",
    "-L/usr/local/lib/quickjs/",
    "-o", "bic",  ...sources,
    "-lquickjs", "-lm"
]


function main() {
    
    log.info("Bootstraping the project")

    run(GCC, flags)
    if(args[1] == "run") {
        log.info("Running")
        run("./main", [...args])
    }
}



main()