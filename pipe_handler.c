#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe_handler.h"

void handle_pipe(const char *command, int background) {
    char *commands[2];
    int fd[2];
    pid_t pid1, pid2;
    char *cmd_copy = strdup(command);
    char *pipe_position = strchr(cmd_copy, '|');
    if (!pipe_position) {
        free(cmd_copy);
        return;
    }
    *pipe_position = '\0';
    commands[0] = cmd_copy;
    commands[1] = pipe_position + 1;
    if (pipe(fd) < 0) {
        perror("pipe oluşturulamadı");
        free(cmd_copy);
        return;
    }
    if ((pid1 = fork()) == 0) { // İlk süreç
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("sh", "sh", "-c", commands[0], NULL);
        perror("exec failed");
        exit(1);
    }
    if ((pid2 = fork()) == 0) { // İkinci süreç
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execlp("sh", "sh", "-c", commands[1], NULL);
        perror("exec failed");
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    if (!background) {
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    } else {
        printf("[Arka planda çalışan işlem PID: %d]\n", pid1); // İlk işlemin PID'sini yazdır
        printf("[Arka planda çalışan işlem PID: %d]\n", pid2); // İkinci işlemin PID'sini yazdır
    }
    free(cmd_copy);
}