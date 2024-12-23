#include <stdio.h>
#include <string.h>
#include "prompt.h"
#include "command_handler.h"
#include "background_handler.h"

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Tamamlanan işlemleri kontrol et
        check_completed_processes();
        
        // Prompt göster,
        print_prompt();
        // Kullanıcıdan komut al
        if (read_command(command, MAX_COMMAND_LENGTH) < 0) {
            printf("\nÇıkış yapılıyor...\n");
            break;
        }
        // "quit" kontrolü
        if (strcmp(command, "quit") == 0) {
            printf("Shell sonlandırılıyor...\n");
            break;
        }
        
        //komutu calıstır
        execute_command(command);
        
    }
    return 0;
}