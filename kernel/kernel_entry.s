global kernel_entry
extern kernel_main

kernel_entry:
    cli
    call kernel_main
    hlt
