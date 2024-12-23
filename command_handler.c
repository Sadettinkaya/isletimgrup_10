#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command_handler.h"
#include "io_handler.h"
#include "prompt.h"
#include "background_handler.h"

void execute_command(const char *command) //komutun çalıştırılmasını sağlayan fonksiyon 
 {
    char *cmd_copy = strdup(command); //strdup ile kopyası oluşturulur ve pointera atanır
    char *input_file = NULL; //komutun giriş dosyasını tutar
    char *output_file =NULL;
    char *actual_command = NULL; //komutu tutar
    int background =0;

    //arka plan islemi kontrolu
    if(cmd_copy[strlen(cmd_copy)-1]=='&')
    {
        background = 1;
        cmd_copy[strlen(cmd_copy)-1] = '\0'; // & isaretini kaldir
    }


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

    // Çıkıs yönlendirme kontrolü
    char *output_redirect = strrchr(cmd_copy, '>');     
    if (output_redirect) // '<'  bulununca:
    {
        *output_redirect = '\0'; // Komutu giriş kısmından ayır
        output_redirect++; //işaretçi '< işaretinden bir sonraki yere kaydırılır'
        while (*output_redirect == ' ') output_redirect++; //boşluk işaretleri atlanır
        char *end = strpbrk(output_redirect, " \n"); //giriş dosyasının sonuna gitmek için 
        if (end) *end = '\0';
        output_file = output_redirect;
    }

    // Komut çalıştırılacak kısmını belirle
    actual_command = cmd_copy;
    while (*actual_command == ' ') actual_command++; //komutun başındaki boşlukları temizleme

    pid_t pid=fork(); //yeni bir proses oluşturma 
    if(pid==0) // eğer if sıfırsa çocuk proses sürecindeyiz demektir 
    {
        if (input_file) {
            int input_fd = open(input_file, O_RDONLY);
            if (input_fd < 0) {
                perror("Giriş dosyası açılamadı");
                exit(1);
            }
            if (dup2(input_fd, STDIN_FILENO) < 0) {
                perror("stdin yönlendirme hatası");
                close(input_fd);
                exit(1);
            }
            close(input_fd);
        }

        // Çıkış yönlendirme
        if (output_file) {
            int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0) {
                perror("Çıkış dosyası açılamadı");
                exit(1);
            }
            if (dup2(output_fd, STDOUT_FILENO) < 0) {
                perror("stdout yönlendirme hatası");
                close(output_fd);
                exit(1);
            }
            close(output_fd);
        }
         char *args[] = {"/bin/bash", "-c", actual_command, NULL};
        execvp(args[0], args);
        perror("exec failed");
        exit(1);

    } 
    else if(pid>0) //sıfırdan büyükse ana prosesteyiz
    {
        if(!background){
           int status;
            waitpid(pid, &status, 0); /*ana proses çocuk prosesin tamamlanmasını bekler tamamlanınca statuste
                                    cocuk değişkenin başarılı olup olmadığı yazar*/
        }
        else{
            handle_background_process(pid); // arka plan işlemlerini bildir
        }
        
    }
    else
    {
        perror("fork failed ");//hata olursa döner
    }
    
    free(cmd_copy);

}