#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <unistd.h>

// Giriş yönlendirmesi için fonksiyon
int redirect_input(const char *input_file);

// Çıkış yönlendirmesi için fonksiyon
int redirect_output(const char *output_file);

#endif