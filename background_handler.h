#ifndef BACKGROUND_HANDLER_H
#define BACKGROUND_HANDLER_H

#include <unistd.h>
#include <sys/types.h>

// Arka plan işlemini başlatır
void handle_background_process(pid_t pid);

// Tamamlanan işlemleri kontrol eder
void check_completed_processes();

#endif