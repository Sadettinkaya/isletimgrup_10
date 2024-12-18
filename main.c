#include <studio.h>
#include <string.h>
#include "prompt.h"

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Tamamlanan işlemleri kontrol et
        // Prompt göster
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
        
    }
    return 0;
}