#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

//fungsi fork
void forkchild(char command[],char *argv[]){
    int status;
    pid_t child_id;
    child_id = fork();
    if(child_id == 0){
        printf("%s",command);
        execv(command,argv);
    }
    else{
        ((wait(&status)) > 0);
    }
}


int main() {
    pid_t child_id1;
    int status;
    char path[100] = "/home/rizqi/modul2/petshop";
    char filepath[100] = "/home/rizqi/modul2/petshop/";
    child_id1 = fork();

    if(child_id1 < 0){
        exit(EXIT_FAILURE);
    }
        
    if(child_id1 == 0){
        //membuat folder petshop
        char *argv_mkdir[] = {"mkdir","-p",path,NULL};
        forkchild("/bin/mkdir",argv_mkdir);
        //unzip pets.zip ke folder petshop
        char *argv_unzip[] = {"unzip","-q","/home/rizqi/Downloads/pets.zip","-d",path,NULL};
        execv("/usr/bin/unzip",argv_unzip);
    }
    while((wait(NULL)) > 0);
    DIR *dir = opendir(path);
    struct dirent *item;
    if(dir != NULL){
        while((item = readdir(dir)) != NULL){
            if(strcmp(item->d_name,".") == 0 || strcmp(item->d_name,"..") == 0) continue;
            if(fork() == 0)  continue;
            else if(item->d_type == DT_DIR){
                strcat(filepath,item->d_name);
                //Menghapus folder dalam petshop
                char *argv[] = {"rm","-rf",filepath,NULL};
                forkchild("/bin/rm",argv);
                exit(EXIT_SUCCESS);
            }
            //menghilangkan format .jpg pada string
            char *noformat;
            int a,n;
            for(a=0; item->d_name[a] != '\0'; a++);
                n = a-4+1;
            noformat = (char*)malloc(n*sizeof(char));
            for(a=0; a<n-1; a++)
                noformat[a] = item->d_name[a];
            noformat[a] = '\0';
                	
            char *undersplit;
            //Split string dengn token "_"
            while(undersplit = strtok_r(noformat,"_",&noformat)){
                int i = 0;
                char jenis[50];
                char nama[50];
                char umur[50];
                char *semcolsplit;
                //Split string dengan token ";"
                while(semcolsplit = strtok_r(undersplit,";",&undersplit)){
                    if(i == 0){
                        //membuat folder jenis hewan 
                        char files[80] = "/home/rizqi/modul2/petshop/";
                        strcat(files,semcolsplit);
                        char *argv[] = {"mkdir","-p",files,NULL};
                        forkchild("/bin/mkdir",argv);
                        strcpy(jenis,semcolsplit);
                    }
                    if(i == 1){
                        strcpy(nama,semcolsplit);
                    }
                    if(i == 2){
                        strcpy(umur,semcolsplit);
                    }
                    i++;
                }
                while((wait(NULL)) > 0);
                char fullpath[500];
                sprintf(fullpath,"%s%s",filepath,item->d_name);
                
                //copy file ke folder jenis hewan masing-masing
                char dest[300];
                sprintf(dest,"%s%s/%s.jpg",filepath,jenis,nama);
                char *argv_cp[] = {"cp",fullpath,dest,NULL};
                forkchild("/bin/cp",argv_cp);

                //membuat keterangan.txt
                char keterangan[300];
                sprintf(keterangan,"%s%s/keteragan.txt",filepath,jenis);
                //mengisi nama dan umur hewan di keterangan.txt
                FILE *fp;
                fp = fopen(keterangan,"a");
                fprintf(fp,"nama : %s\numur : %s tahun\n\n",nama,umur);
                fclose(fp);
            }
            //remove foto di folder petshop
            strcat(filepath,item->d_name);
            char *argv_rm[] = {"rm",filepath,NULL};
            execv("/bin/rm",argv_rm);
		}
        closedir(dir);
    }
    return 0;
}
