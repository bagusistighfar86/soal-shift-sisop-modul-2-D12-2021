#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

void daemonize(){
    pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/bagus/Documents/Modul2/soal3")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

char *caesarchiper(char *message, int key){
    int i;
    char ch;
    for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
    return message;
}

// 3d. Membuat kill bash script
void killer_script(char const *argv[], int pid){
    FILE *file_killer = fopen("killer.sh","w");
    // 3e. Membuat dua mode kill bash
    if(strcmp(argv[1],"-z") == 0){ 
        fprintf(file_killer,"#!/bin/bash\n killall -9 %s\n", argv[0]);
    }
    else if(strcmp(argv[1],"-x") == 0){
        fprintf(file_killer,"#!/bin/bash\n kill -15 %d\n", pid);
    }
    fprintf(file_killer, "rm killer.sh\n");
    fclose(file_killer);
}

int main(int argc, char const *argv[]) {
    daemonize();
    // FILE *folderlog;
    
    killer_script(argv,(int)getpid());

    int i, size;
    // folderlog = fopen("folderlog.txt", "w+");
    char nama_folder[100], path_gambar[250], url[100], time_temp[100];
    time_t rawtime;

    while (1) {
        int status1;
        time (&rawtime);
        struct tm *tmp = localtime(&rawtime);
        strftime(nama_folder,sizeof(nama_folder),"%Y-%m-%d_%X",tmp);
        pid_t child1 = fork();
        // fprintf(folderlog,"%s",nama_folder);
        // fflush(folderlog);

        if(child1 < 0){
            exit(EXIT_FAILURE);
        }
        else if(child1 == 0){
            pid_t child2 = fork();
            int status2;
            if (child2 < 0){
                exit(EXIT_FAILURE);
            }
            if (child2 == 0){
                // 3a.Membuat folder berdasarkan timestamp
                char *arg_mkdir[] = {"mkdir",nama_folder,NULL};
                execv("/bin/mkdir",arg_mkdir);
                // fprintf(folderlog,"Folder %s berhasil dibuat\n",nama_folder);
                // fflush(folderlog);
            }
            else {
                while (wait(&status2) > 0);
                for (i=1; i<=10; i++){
                    pid_t child3 = fork();
                    if(child3 < 0){
                        exit(EXIT_FAILURE);
                    }
                    if(child3  == 0){
                        time (&rawtime);
                        tmp = localtime(&rawtime);
                        strftime(time_temp,sizeof(time_temp),"%Y-%m-%d_%X",tmp);
                        sprintf(path_gambar, "%s/%s.jpg", nama_folder, time_temp);
                        size = (int)time(NULL);
                        sprintf(url, "https://picsum.photos/%d", (size%1000)+50);
                        char *arg_wget[] = {"wget", "-bq", "-O", path_gambar, url, NULL};
                        execv("/bin/wget",arg_wget); 
                    }
                    // fprintf(folderlog,"Gambar %s berhasil diunduh\n",path_gambar);
                    // fflush(folderlog);
                    sleep(5); 
                }

                // 3c. Membuat status.txt dan diisi dengan hasil enkripsi dari pesan menggunakan algoritma caesarchiper 
                char pesan[100] = "Download Succes";
                caesarchiper(pesan, 5);
                char path_status[150];
                sprintf(path_status,"%s/status.txt", nama_folder);
                FILE *file_status; 
                file_status = fopen(path_status,"w");
                fprintf(file_status,"%s",pesan);
                fclose(file_status);
                // fprintf(folderlog,"Status pesan : status.txt berhasil dibuat\n");
                // fflush(folderlog);

                // 3c. Membuat zip dan menghapus directory aslinya
                char nama_zip[150];
                sprintf(nama_zip,"%s.zip",nama_folder);
                char *arg_zip[] = {"zip", "-rm", "-q", nama_zip, nama_folder, NULL};
                execv("/usr/bin/zip", arg_zip);
                // fprintf(folderlog,"Status Zip : File zip %s sudah berhasil dibuat\n", nama_zip);
                // fflush(folderlog); 
            }
        }
        sleep(40);
    }
    // fclose(folderlog);
}
