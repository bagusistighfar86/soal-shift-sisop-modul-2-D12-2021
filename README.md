# soal-shift-sisop-modul-2-D12-2021
## Anggota Kelompok
| Nama | NRP |
|------|-----|
|Muhammad Bagus Istighfar|05111940000049|
|Rizqi Rifaldi|05111940000068|
|Afdhal Ma'ruf Lukman|05111940007001| 

Keterangan : Afdhal Ma'ruf Lukman ==> tidak ada kontribusi dan komunikasi sama sekali (hilang tanpa kabar)

## Soal No 3
### Main Soal No 3
Berikut adalah main source code dari soal no3. Tahapan proses soal no.3 :
1. Membuat daemon proses melalui fungsi daemonize
2. Membuat killer_script untuk mematikan daemon proses melalui bash script sesuai dengan argumen yang ditentukan
3. Parent proses untuk mengingatkan child1 berjalan setiap 40 detik
4. Fork child2 proses untuk menjalankan fungsi pembuatan direktori
5. Setelah itu fork child3 proses untuk menjalankan wget atau proses download gambarnya. Proses ini tidak dijalnkan bersamaan dengan poin no.4, melainkan bergantian.
6. Dalam fork child3 setelah wget akan dilanjutkan ke proses pembuatan "status.txt", lalu ke proses pembuatan zip hingga delete direktori aslinya
```c
int main(int argc, char const *argv[]) {
    daemonize();
    
    killer_script(argv,(int)getpid());

    int i, size;
    char nama_folder[100], path_gambar[250], url[100], time_temp[100];
    time_t rawtime;

    while (1) {
        int status1;
        time (&rawtime);
        struct tm *tmp = localtime(&rawtime);
        strftime(nama_folder,sizeof(nama_folder),"%Y-%m-%d_%X",tmp);
        pid_t child1 = fork();

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

                // 3c. Membuat zip dan menghapus directory aslinya
                char nama_zip[150];
                sprintf(nama_zip,"%s.zip",nama_folder);
                char *arg_zip[] = {"zip", "-rm", "-q", nama_zip, nama_folder, NULL};
                execv("/usr/bin/zip", arg_zip);
            }
        }
        sleep(40);
    }
}
```
### Proses Daemon Proses (Daemonize)
```c
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
```
path background proses yang akan dijalankan menuju ke/home/bagus/Documents/Modul2/soal3
### Proses Membuat Killer_Script
```c
void killer_script(char const *argv[], int pid){
    FILE *file_killer = fopen("killer.sh","w");
    // 3e. Membuat dua mode kill bash
    if(strcmp(argv[1],"-z") == 0){ 
        fprintf(file_killer,"#!/bin/bash\n killall -9 %s\n", argv[0]);
    }
    else if(strcmp(argv[1],"-x") == 0){
        fprintf(file_killer,"#!/bin/bash\n kill -15 %d\n", pid);
    }
    fprintf(file_killer,"rm killer.sh\n");
    fclose(file_killer);
}
```
Pada function ini dibuat suatu bash script killer berdasarkan kondisi dimana saat argv[1] bernilai "-x" atau "-z".
* Kondisi argv[1] == -z
  Semua proses akan di kill saat itu juga tanpa menunggu proses selesai
* Kondisi argv[1] == -x
  Parent proses akan di kill saat itu juga, tetapi background proses dari child masih tetap berjalan sampai proses delete directory aslinya selesai
Setelah kill, maka file_killer tersebut akan otomatis terhapus.

### Proses mkdir
```c
// 3a.Membuat folder berdasarkan timestamp
char *arg_mkdir[] = {"mkdir",nama_folder,NULL};
execv("/bin/mkdir",arg_mkdir);
```
Proses tersebut akan menjalankan arg_mkdir yang isinya perintah bash script mkdir pada child

### Proses download
```c
while (wait(&status1) > 0);
for (i=1; i<=10; i++){
pid_t child3 = fork();
if(child3 < 0){
    exit(EXIT_FAILURE);
}
if(child3  == 0){
while (wait(&status1) > 0);
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
    // fprintf(process_log,"Gambar %s berhasil diunduh\n",path_gambar);
    // fflush(process_log);
    sleep(5); 
    }
}
```
Di proses download ini file akan didownload berdasarkan waktu real time saat ini yang didaptkan dari epoch unix second. Proses download ini disendirikan dengan proses mkdir agar tidak menghambat proses mkdir. Selama for 1-10,  
