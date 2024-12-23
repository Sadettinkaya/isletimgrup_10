#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "background_handler.h"

#define MAX_PROCESSES 100
static pid_t background_pids[MAX_PROCESSES];
static int pid_count = 0;

// Arka plan işlemini bildirir
void handle_background_process(pid_t pid) {
    if (pid_count < MAX_PROCESSES) {
        background_pids[pid_count++] = pid; // PID'yi listeye ekle
    }
    printf("[Arka planda çalışan işlem PID: %d]\n", pid);
}
// Tamamlanan arka plan işlemlerini kontrol eder
void check_completed_processes() {
    pid_t completed_pid;
    int status;
    for (int i = 0; i < pid_count; i++) {
        completed_pid = waitpid(background_pids[i], &status, WNOHANG);
        if (completed_pid > 0) {
            printf("[İşlem %d tamamlandı]\n", completed_pid);
            // Listeyi güncelle
            for (int j = i; j < pid_count - 1; j++) {
                background_pids[j] = background_pids[j + 1];
            }
            pid_count--;
            i--; // Aynı indeksi tekrar kontrol et
        }
    }
}