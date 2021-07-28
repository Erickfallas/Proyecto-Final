igato : Main.c
	gcc `pkg-config gtk+-3.0 --cflags` Main.c -o gato `pkg-config --libs gtk+-3.0`
