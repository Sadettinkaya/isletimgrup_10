#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "io_handler.h"

// Giriş yönlendirme
int redirect_input(const char *input_file) {
    int input_fd = open(input_file, O_RDONLY);
    if (input_fd < 0) {
        perror("Giriş dosyası açılamadı");
        return -1;
    }
    if (dup2(input_fd, STDIN_FILENO) < 0) {
        perror("stdin yönlendirme hatası");
        close(input_fd);
        return -1;
    }
    close(input_fd);
    return 0;
}

// Çıkış yönlendirme
int redirect_output(const char *output_file) {
    int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Çıkış dosyası açılamadı");
        return -1;
    }
    if (dup2(output_fd, STDOUT_FILENO) < 0) {
        perror("stdout yönlendirme hatası");
        close(output_fd);
        return -1;
    }
    close(output_fd);
    return 0;
}