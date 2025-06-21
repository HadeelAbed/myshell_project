myshell: myshell.c utility.c myshell.h
	gcc -Wall myshell.c utility.c -lreadline -o myshell
