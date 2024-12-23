#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command_handler.h"

void execute_command(const char *command)
{
    pid_t pid=fork();
    if(pid==0)
    {
        char *args[]={"/bin/sh", "-c", (char*)command, NULL};
        execv("/bin/sh",args);
        perror("execv başarısız oldu");
        exit(1);
    }
    else if(pid>0)
    {
        int status;
        waitpid(pid, &status, 0);
    }
    else {perror("fork başarısız oldu");}
}