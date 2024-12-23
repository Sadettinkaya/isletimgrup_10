#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command_handler.h"
#include "io_handler.h"
#include "prompt.h"

void execute_command(const char *command) //komutun çalıştırılmasını sağlayan fonksiyon 
 {
    char *cmd_copy = strdup(command); //strdup ile kopyası oluşturulur ve pointera atanır
    char *input_file = NULL; //komutun giriş dosyasını tutar
    char *actual_command = NULL; //komutu tutar

    // Giriş yönlendirme kontrolü
    char *input_redirect = strrchr(cmd_copy, '<'); //'<' aranır bulununca işaretçisini döndürür
    if (input_redirect) // '<'  bulununca:
    {
        *input_redirect = '\0'; // Komutu giriş kısmından ayır
        input_redirect++; //işaretçi '< işaretinden bir sonraki yere kaydırılır'
        while (*input_redirect == ' ') input_redirect++; //boşluk işaretleri atlanır
        char *end = strpbrk(input_redirect, " \n"); //giriş dosyasının sonuna gitmek için 
        if (end) *end = '\0';
        input_file = input_redirect;
    }

    // Komut çalıştırılacak kısmını belirle
    actual_command = cmd_copy;
    while (*actual_command == ' ') actual_command++; //komutun başındaki boşlukları temizleme

    pid_t pid=fork(); //yeni bir proses oluşturma 
    if(pid==0) // eğer if sıfırsa çocuk proses sürecindeyiz demektir 
    {
        char *args[]={"/bin/sh", "-c", (char*)command, NULL}; //kullanıcın verdiği komutu kabukta çalıştırmak için bir dizi 
        execv("/bin/sh",args); // sh kabuğu çalıştırılır ve komut gönderilir
        perror("execv başarısız oldu");
        exit(1); // başarısız olursa süreç sonlandırılır

    } 
    else if(pid>0) //sıfırdan büyükse ana prosesteyiz
    {
        int status;
        waitpid(pid, &status, 0); /*ana proses çocuk prosesin tamamlanmasını bekler tamamlanınca statuste
                                    cocuk değişkenin başarılı olup olmadığı yazar*/
    }
    else
    {
        perror("fork başarısız oldu");//hata olursa döner
    }

}