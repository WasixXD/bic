
log.info("This is a", "info log")


log.warn("This is a", "warn log")


for(let i = 0; i < args.length; i++) {
    log.info(args[i])
}


run("gcc", [])
