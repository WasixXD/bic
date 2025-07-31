# BIC
_Building QuIC_

# Example

```js
const build_folder = "./build/"

const compiler = "gcc"

const sources = ["main.c", "header.h", "header.c"]

const flags = [
    "-Wall",
    `-I${HOME}/dev/quickjs/`,  // HOME is a macro that expands to /home/your_user
    "-o", "build/main", 
    ...sources
]

function main() {

    if(args[1] == "test") {
        run(compiler, "test")
        return
    }

    if(!fs.folderExists(build_folder)) {
        log.info(`${build_folder} created`)
        fs.folderCreate(build_folder)
    }
    
    run(compiler, flags)
    log.info("Build completed")

    if(args[1] == "run") {
        run("./main")
    }
}

main()
```


# Why reivent the wheel?
I don´t like using Make, ninja or anything like that. And I find scripting with JS incredible pleasant so I glued them both together
