# Proje Bilgisi
# Grup Üyeleri:
# - sadettin
# - zeynep
# - reyhan
# - yaren
# - ferhat
# Ders Kodu: Oişletim sistemleri 2024 Güz
# Ödev: Kabuk Projesi
# Derleyici ve bayraklar



# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -g
OBJS = main.o command_handler.o io_handler.o prompt.o

all: shell

shell: $(OBJS)
	$(CC) $(CFLAGS) -o shell $(OBJS)

main.o: main.c command_handler.h prompt.h
	$(CC) $(CFLAGS) -c main.c

command_handler.o: command_handler.c command_handler.h io_handler.h
	$(CC) $(CFLAGS) -c command_handler.c

io_handler.o: io_handler.c io_handler.h
	$(CC) $(CFLAGS) -c io_handler.c

prompt.o: prompt.c prompt.h
	$(CC) $(CFLAGS) -c prompt.c

clean:
	rm -f shell *.o

help:
	@echo "Kullanılabilir Makefile Komutları:"
	@echo "  make          Shell uygulamasını derler."
	@echo "  make clean    Geçici dosyaları temizler."
	@echo "  make help     Bu yardım mesajını gösterir."