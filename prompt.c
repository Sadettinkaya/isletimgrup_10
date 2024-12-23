#include <stdio.h>
#include <string.h> // strcspn fonksiyonu için eklendi
#include "prompt.h"

// Komut istemini yazdırır
void print_prompt() { //girilen komutu ekrana yazdırır
    printf("> "); //kullanıcıdan komut almak için 
    fflush(stdout); //alınan komutu cıkış ekranına yansıtır
}

// Kullanıcıdan komut alır
int read_command(char *command, int max_length) {
    if (fgets(command, max_length, stdin) == NULL) {
        return -1; // Kullanıcıdan veri alınamazsa hata döner
    }
    // Yeni satır karakterini temizle
    command[strcspn(command, "\n")] = '\0';
    return 0; // Başarıyla komut alındı
}