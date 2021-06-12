#include "ucmd.h"
#include "stdlib.h"

//if cmds stop working copy this to main.c and delete "&" in ucmd_parse()

Command my_cmd_list[] = {
    {
        "led",
        "LED || on\r",
        (Command_cb) led_on_cb,
    },	
    {
        "",
        "null list terminator",
        NULL,
    },
};
