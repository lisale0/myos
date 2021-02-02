# myos
This is a toy OS based on https://wiki.osdev.org/Expanded_Main_Page


# Installation
`make`

# Run
`make qemumulti`

# Debug
`make qemudebug`
`~ gdb`
```
(gdb) set architecture i8086
(gdb) target remote localhost:26000
```

# TODO
- update the README to include how to install dev tools
- Reference resources used in this project
