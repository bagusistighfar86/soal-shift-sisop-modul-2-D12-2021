# soal-shift-sisop-modul-2-D12-2021
## Anggota Kelompok
| Nama | NRP |
|------|-----|
|Muhammad Bagus Istighfar|05111940000049|
|Rizqi Rifaldi|05111940000068|
|Afdhal Ma'ruf Lukman|05111940007001|

## Soal No 1

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang
disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing
sesuai extensi. (a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama
folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg (b) untuk
musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link
dibawah juga :). (c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu
meng-extract-nya setelah didownload serta (d) memindahkannya ke dalam folder yang telah
dibuat (hanya file yang dimasukkan).
(e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum
waktu ulang tahun Stevany). (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder
akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya
menyisakan .zip)

Source Code :

```C
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <wait.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

void move(char *basepath,char *destination){
	char path[1000];
	pid_t child_id;
	int status;
	struct dirent *dp;
	DIR *dir = opendir(basepath);
	if(!dir){
		return;
	}
	while((dp = readdir(dir)) != NULL){
		if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") !=0){
			strcpy(path,basepath);
			strcat(path,"/");
			strcat(path,dp->d_name);
			child_id = fork();
			if(child_id < 0){
				exit(EXIT_FAILURE);
			}
			if(child_id == 0){
				char *argv[]= {"mv",path,destination,NULL};
				execv("/bin/mv",argv);
			}
		}
	}
	closedir(dir);
}


int main(){
	pid_t pid,sid;
	pid = fork();
	if(pid < 0){
		exit(EXIT_FAILURE);
	}
	if(pid > 0){
		exit(EXIT_SUCCESS);
	}
	umask(0);
	sid = setsid();
	if(sid < 0){
		exit(EXIT_FAILURE);
	}
	if((chdir("/home/rizqi/modul2")) < 0){
		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1){
		time_t t = time (NULL);
		struct tm *tmp = localtime(&t);
		if(tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 16 && tmp->tm_min == 22 && tmp->tm_sec == 0){
			pid_t child_id1,child_id2,child_id3,child_id4,child_id5;
			pid_t child_id2a,child_id3a,child_id4a,child_id5a;
			pid_t child_id5b;
			int status;
			child_id1 = fork();
			if(child_id1 < 0){
				exit(EXIT_FAILURE);
			}
			if(child_id1 == 0){
				char *argv[] = {"mkdir","/home/rizqi/modul2/Musyik","/home/rizqi/modul2/Fylm","/home/rizqi/modul2/Pyoto",NULL};
				execv("/bin/mkdir",argv);
			}
			else{
				while ((wait(&status)) > 0);
				child_id2 = fork();
				if(child_id2 < 0){
					exit(EXIT_FAILURE);
				}
				if(child_id2 == 0){
					child_id2a = fork();
					if(child_id2a < 0){
						exit(EXIT_FAILURE);
					}
					if(child_id2a == 0){
						//download musik
						char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O","/home/rizqi/modul2/Musik_For_Stevany.zip",NULL};
						execv("/bin/wget",argv);
					}
					else{
						while((wait(&status)) > 0);
						//unzip musik
						char *argv[] = {"unzip","-q","/home/rizqi/modul2/Musik_For_Stevany.zip","-d","/home/rizqi/modul2",NULL};
						execv("/bin/unzip",argv);
					}
				}
				else{
					while((wait(&status)) > 0);
					child_id3 = fork();
					if(child_id3 < 0){
						exit(EXIT_FAILURE);
					}
					if(child_id3 == 0){
						child_id3a = fork();
						if(child_id3a < 0){
							exit(EXIT_FAILURE);
						}
						if(child_id3a == 0){
							//download foto
							char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O","/home/rizqi/modul2/Foto_For_Stevany.zip",NULL};
							execv("/bin/wget",argv);
						}
						else{
							while ((wait(&status)) > 0);
							//unzip foto
							char *argv[] = {"unzip","-q","/home/rizqi/modul2/Foto_For_Stevany.zip","-d","/home/rizqi/modul2",NULL};
							execv("/bin/unzip",argv);
						}
					}
					else{
						while ((wait(&status)) > 0);
						child_id4 = fork();
						if(child_id4 < 0){
							exit(EXIT_FAILURE);
						}
						if(child_id4 == 0){
							child_id4a = fork();
							if(child_id4a < 0){
								exit(EXIT_FAILURE);
							}
							if(child_id4a == 0){
								//download film
								char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","/home/rizqi/modul2/Film_For_Stevany.zip",NULL};
								execv("/bin/wget",argv);
							}
							else{
								while((wait(&status)) > 0);
								//unzip film
								char *argv[] = {"unzip","-q","/home/rizqi/modul2/Film_For_Stevany.zip","-d","/home/rizqi/modul2",NULL};
								execv("/bin/unzip",argv);
							}
						}
						else{
							while((wait(&status)) > 0);
							child_id5 = fork();
							if(child_id5 < 0){
								exit(EXIT_FAILURE);
							}
							if(child_id5 == 0){
								child_id5a = fork();
								if(child_id5a < 0){
									exit(EXIT_FAILURE);
								}
								if(child_id5a == 0){
									//pindah MUSIK ke Musyik
									//char *argv[] = {"mv","/home/rizqi/modul2/MUSIK/*","/home/rizqi/modul2/Musyik",NULL};
									//execv("/bin/mv",argv);
									move("/home/rizqi/modul2/MUSIK","/home/rizqi/modul2/Musyik");
									_exit(1);
								}
								else{
									while((wait(&status)) > 0);
									child_id5b = fork();
									if(child_id5b < 0){
										exit(EXIT_FAILURE);
									}
									if(child_id5b == 0){
										//pindah FOTO ke Pyoto
										//char *argv[] = {"mv","/home/rizqi/modul2/FOTO/*","/home/rizqi/modul2/Pyoto",NULL};
										//execv("/bin/mv",argv);
										move("/home/rizqi/modul2/FOTO","/home/rizqi/modul2/Pyoto");
										_exit(1);
									}
									else{
										while((wait(&status)) > 0);
										//pindah FILM ke Fylm
										//char *argv[] = {"mv","/home/rizqi/modul2/FILM/*","/home/rizqi/modul2/Fylm",NULL};
										//execv("/bin/mv",argv);
										move("/home/rizqi/modul2/FILM","/home/rizqi/modul2/Fylm");
										_exit(1);
									}
								}
							}
						}
					}
				}
			}
		}
		else if (tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 22 && tmp->tm_min == 22 && tmp->tm_sec == 0){
			pid_t child_id6;
			int status2;
			child_id6 = fork();
			if(child_id6 < 0){
				exit(EXIT_FAILURE);
			}
			if(child_id6 == 0){
				char *argv[] = {"zip","-rmq","Lopyu_Stevany","Musyik","Pyoto","Fylm",NULL};
				execv("/bin/zip",argv);
			}
			else{
				while((wait(&status2)) > 0);
				char *argv[] = {"rm","-r","/home/rizqi/modul2/MUSIK","/home/rizqi/modul2/FOTO","/home/rizqi/modul2/FILM",NULL};
				execv("/bin/rm",argv);
			}
		}
		sleep(1);
	}
}
```
Karena script atau program harus bisa dijalankan secara otomatis, maka proses yang dibuat harus merupakan daemon, yaitu program yang dapat berjalan pada background. Untuk template dari pembuatan proses daemon yaitu :
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini

    sleep(30);
  }
}
```
Didalam while, kita bisa menuliskan program yang akan dijalankan.

Dan selain menggunakan header pada template membuat daemon, saya juga menggunakan beberapa header lain yaitu ```dirent.h``` untuk mengakses file dan ```time.h``` untuk mengakses waktu.

### Soal 1a
Pada bagian a, program yang dibuat harus bisa membuat direktori atau folder yang bernama : Musyik untuk mp3, Pyoto untuk jpg, dan Fylm untuk menyimpan file mp4.
Maka dari itu kita harus melakukan ```fork()``` pada ```child_id1``` untuk membuat proses baru, yang isinya adalah untuk membuat 3 direktori atau folder yang dibutuhkan yaitu Musyik, Pyoto, dan Fylm.
```C
child_id1 = fork();
if(child_id1 < 0){
	exit(EXIT_FAILURE);
}
if(child_id1 == 0){
	char *argv[] = {"mkdir","/home/rizqi/modul2/Musyik","/home/rizqi/modul2/Fylm","/home/rizqi/modul2/Pyoto",NULL};
	execv("/bin/mkdir",argv);
}
```
Pertama-tama kita harus melakukan ```fork()``` untuk membuat proses baru. Jika ```child_id1 == 0``` yang berarti merupakan child, program akan membuat direktori atau folder baru dengan menggunakan ```argv[]``` dan ```exec```.
Dan else setelah if pada source code berikut adalah untuk fork child_id2.

### Soal 1b dan 1c
Pada bagian b, program atau script harus dapat mendownload file berupa zip yang bernama ```Musik_For_Stevany```, ```Foto_For_Stevany```, dan ```Film_For_Stevany```, dan pada bagian b ini langsung dilanjutkan dengan bagian c yaitu melakukan ```extract``` atau ```unzip``` tepat setelah selesai mendownload masing-masing file.
Source Code :
```C
child_id2 = fork();
if(child_id2 < 0){
	exit(EXIT_FAILURE);
}
if(child_id2 == 0){
	child_id2a = fork();
	if(child_id2a < 0){
		exit(EXIT_FAILURE);
	}
	if(child_id2a == 0){
		//download musik
		char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O","/home/rizqi/modul2/Musik_For_Stevany.zip",NULL};
		execv("/bin/wget",argv);
	}
	else{
		while((wait(&status)) > 0);
		//unzip musik
		char *argv[] = {"unzip","-q","/home/rizqi/modul2/Musik_For_Stevany.zip","-d","/home/rizqi/modul2",NULL};
		execv("/bin/unzip",argv);
	}
}	
```
Setelah melakukan ```fork()``` pada ```child_id2```, saat ```child_id2 == 0``` saya melakukan ```fork()``` lagi pada ```child_id2a``` yang pada ```child_id2a``` ini nantinya akan melakukan download dari file zip Musik_For_Stevany dan setelah selesai mendownload, selanjutnya file zip tersebut akan langsung diextract atau di unzip ke direktori ```/home/rizqi/modul2```.

Setelah melakukan unzip Musik_For_Stevany, selanjutnya pada else dari ```child_id2``` atau saat ```child_id2 > 0```, saya melakukan ```fork()``` pada ```child_id3```
dan saat ```child_id3 == 0``` saya melakukan ```fork()``` lagi pada ```child_id3a``` yang pada ```child_id3a``` ini nantinya untuk mendownload file zip Foto_For_Stevany dan melakukan unzip dari file tersebut. Source Code :
```C
child_id3 = fork();
if(child_id3 < 0){
	exit(EXIT_FAILURE);
}
if(child_id3 == 0){
	child_id3a = fork();
	if(child_id3a < 0){
		exit(EXIT_FAILURE);
	}
	if(child_id3a == 0){
		//download foto
		char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O","/home/rizqi/modul2/Foto_For_Stevany.zip",NULL};
		execv("/bin/wget",argv);
	}
	else{
		while ((wait(&status)) > 0);
		//unzip foto
		char *argv[] = {"unzip","-q","/home/rizqi/modul2/Foto_For_Stevany.zip","-d","/home/rizqi/modul2",NULL};
		execv("/bin/unzip",argv);
	}
}
```
Dan setelah selesai melakukan download dan unzip dari file Foto_For_Stevany, selanjutnya pada else dari ```child_id3``` atau saat ```child_id3 > 0```, saya melakukan ```fork()``` pada ```child_id4``` dan saat ```child_id4 == 0``` saya melakukan ```fork()``` lagi pada ```child_id4a``` yang pada ```child_id4a``` ini nantinya untuk mendownload file zip Foto_For_Stevany dan melakukan unzip dari file tersebut. Source Code :
```C
child_id4 = fork();
if(child_id4 < 0){
	exit(EXIT_FAILURE);
}
if(child_id4 == 0){
	child_id4a = fork();
	if(child_id4a < 0){
		exit(EXIT_FAILURE);
	}
	if(child_id4a == 0){
		//download film
		char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","/home/rizqi/modul2/Film_For_Stevany.zip",NULL};
		execv("/bin/wget",argv);
	}
	else{
		while((wait(&status)) > 0);
		//unzip film
		char *argv[] = {"unzip","-q","/home/rizqi/modul2/Film_For_Stevany.zip","-d","/home/rizqi/modul2",NULL};
		execv("/bin/unzip",argv);
	}
}
```
### Soal 1d
Pada bagian d, program diharuskan bisa memindahkan semua isi dari folder - folder hasil unzip dari file yang sudah didownload ke dalam folder - folder yang sudah dibuat pada soal bagian a, yaitu semua isi folder MUSIK harus dipindahkan ke dalam folder Musyik, semua isi folder FOTO harus dipindahkan ke dalam folder Pyoto, dan semua isi folder FILM harus dipindahkan ke dalam folder Fylm. Pertama - tama saya membuat fungsi baru yang berfungsi untuk memindahkan semua isi folder ke folder yang lain. Fungsi ini memiliki 2 parameter, yaitu path isi folder yang akan dipindahkan (basepath) dan path tujuan kemana akan dipindahkan (destination). Fungsi ini hampir sama seperti untuk listing file yang dicontohkan pada modul 2, bedanya adalah bukannya melakukan print, fungsi ini akan melakukan ```fork()``` yang prosesnya untuk melakukan ```move``` dari file-file tersebut. Source Code:
```C
void move(char *basepath,char *destination){
	char path[1000];
	pid_t child_id;
	int status;
	struct dirent *dp;
	DIR *dir = opendir(basepath);
	if(!dir){
		return;
	}
	while((dp = readdir(dir)) != NULL){
		if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") !=0){
			strcpy(path,basepath);
			strcat(path,"/");
			strcat(path,dp->d_name);
			child_id = fork();
			if(child_id < 0){
				exit(EXIT_FAILURE);
			}
			if(child_id == 0){
				char *argv[]= {"mv",path,destination,NULL};
				execv("/bin/mv",argv);
			}
		}
	}
	closedir(dir);
}
```
Pada fungsi ini, karena berurusan dengan file, maka memerlukan header ```dirent.h```. Setelah proses dari ```child_id4``` selesai, maka pada else dari ```child_id4``` atau jika ```child_id4 > 0```, saya kembali melakukan ```fork()``` pada child_id5 untuk membuat proses baru, yang jika ```child_id5 == 0``` saya kembali melakukan ```fork()``` lagi untuk membuat proses baru pada ```child_id5a```. Pada proses di ```child_id5a``` ini, pada saat child proccess atau ```child_id5a == 0```, akan menjalankan fungsi move yang sudah dijelaskan tadi, untuk memindahkan semua isi folder MUSIK ke dalam folder Musyik. Source Code :
```C
child_id5 = fork();
if(child_id5 < 0){
	exit(EXIT_FAILURE);
}
if(child_id5 == 0){
	child_id5a = fork();
	if(child_id5a < 0){
		exit(EXIT_FAILURE);
	}
	if(child_id5a == 0){
		//pindah MUSIK ke Musyik
		//char *argv[] = {"mv","/home/rizqi/modul2/MUSIK/*","/home/rizqi/modul2/Musyik",NULL};
		//execv("/bin/mv",argv);
		move("/home/rizqi/modul2/MUSIK","/home/rizqi/modul2/Musyik");
		_exit(1);
	}
}
```
Setelah melakukan child proses pada ```child_id5a```, pada parent proses nya atau ```child_id5a > 0```, saya sekali lagi melakukan ```fork()``` untuk membuat proses baru pada ```child_id5b```, yang pada child proses dari ```child_id5b``` atau jika ```child_id == 0```, maka akan melakukan proses untuk memindahkan semua isi folder FOTO ke dalam folder Pyoto menggunakan fungsi move yang telah dibuat. Selanjutnya setelah child proses dari ```child_id5b``` selesai, pada parent proses nya atau ```child_id5b > 0``` dilakukan proses untuk memindahkan semmua isi pada folder FILM ke folder Fylm. Source Code :
```C
child_id5b = fork();
if(child_id5b < 0){
	exit(EXIT_FAILURE);
}
if(child_id5b == 0){
	//pindah FOTO ke Pyoto
	//char *argv[] = {"mv","/home/rizqi/modul2/FOTO/*","/home/rizqi/modul2/Pyoto",NULL};
	//execv("/bin/mv",argv);
	move("/home/rizqi/modul2/FOTO","/home/rizqi/modul2/Pyoto");
	_exit(1);
}
else{
	while((wait(&status)) > 0);
	//pindah FILM ke Fylm
	//char *argv[] = {"mv","/home/rizqi/modul2/FILM/*","/home/rizqi/modul2/Fylm",NULL};
	//execv("/bin/mv",argv);
	move("/home/rizqi/modul2/FILM","/home/rizqi/modul2/Fylm");
	_exit(1);
}
```

### Soal 1e
Pada soal e, program diminta untuk dapat melakukan semua proses pada soal 1a sampai 1d secara otomatis pada saat 6 jam sebelum ulang tahun dari Stevany, yaitu tepatnya pada 9 April Pukul 16:22. Seperti dijelaskan diawal, untuk melakukan semua proses secara otomatis, maka proses tersebut harus berupa daemon atau proses yang berjalan pada background. Maka semua proses yang ada pada soal 1a sampai 1d harus dimasukkan pada ```while (1)``` pada template daemon yang tersedia di atas.
Kemudian untuk masalah berjalan pada tanggal 9 April pada jam 16:22, pertama tama kita harus tau waktu sekarang, yaitu menggunakan kode sebagai berikut :
```C
time_t t = time (NULL);
struct tm *tmp = localtime(&t);
```
Potongan kode tersebut berfungsi untuk mengambil waktu lokal yang ada pada komputer kita. Dikarenakan berhubungan dengan waktu, maka diperlukan header ```time.h```. Kemudian untuk mencocokkan waktu lokal dan tanggal 9 April jam 16:22 agar semua proses soal 1a sampai 1d berjalan pada tanggal dan jam tersebut,maka kita menggunakan percabangan seperti berikut :
```C
if(tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 16 && tmp->tm_min == 22 && tmp->tm_sec == 0)
```
Penjelasan :
* tm_mon = Bulan, karena dimulai dari 0 maka ditambah 1 dan sama dengan 4 untuk bulan april
* tm_mday = Hari, karena diminta pada tanggal 9 maka sama dengan 9
* tm_hour = Jam, karena diminta pada jam 16 maka sama dengan 16
* tm_min = menit, karena diminta pada menit ke 22 maka sama dengan 22
* tm_sec = detik, karena diminta tepat pukul 16:22, maka detiknya adalah 0

Pada potongan kode tersebut dimaksudkan jika waktu lokal di komputer kita adalah 9 April jam 16:22, maka semua proses pada soal 1a sampai 1d baru akan berjalan.

### Soal 1f
Pada soal f, program diminta untuk membuat zip dari folder Musyik, Pyoto dan Fylm dengan nama Lopyu_Stevany dan menghapus folder kosong MUSIK, FOTO, dan FILM. Semuanya dilakukan pada hari ulang tahun Stevany yaitu pada tanggal 9 April jam 22:22. Pertama - tama, pada else dari percabangan pada soal 1e, kita akan mencocokkan waktu lokal komputer kita dengan tanggal 9 April Jam 22:22 :
```C
else if (tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 22 && tmp->tm_min == 22 && tmp->tm_sec == 0)
```
Penjelasan :
* tm_mon = Bulan, karena dimulai dari 0 maka ditambah 1 dan sama dengan 4 untuk bulan april
* tm_mday = Hari, karena diminta pada tanggal 9 maka sama dengan 9
* tm_hour = Jam, karena diminta pada jam 22 maka sama dengan 22
* tm_min = menit, karena diminta pada menit ke 22 maka sama dengan 22
* tm_sec = detik, karena diminta tepat pukul 16:22, maka detiknya adalah 0

Pada potongan kode tersebut dimaksudkan jika waktu lokal di komputer kita adalah 9 April jam 22:22, maka semua proses untuk melakukan zip dan menghapus folder kosong baru akan berjalan.
Kemudian didalamnya ```else if``` tersebut, saya mendeklarasikan ```child_id6``` dan saya  melakukan ```fork()``` untuk membuat proses baru pada ```child_id6``` dan pada child proses dari ```child_id6``` atau jika ```child_id6 == 0```, akan melakukan zip dari folder Musyik, Pyoto, dan Fylm menjadi file zip bernama ```Lopyu_Stevany.zip``` dan pada parent proses nya atau ```child_id6 > 0```, terjadi proses untuk menghapus folder kosong MUSIK, FOTO dan FILM.
Source Code :
```C
pid_t child_id6;
int status2;
child_id6 = fork();
if(child_id6 < 0){
	exit(EXIT_FAILURE);
}
if(child_id6 == 0){
	char *argv[] = {"zip","-rmq","Lopyu_Stevany","Musyik","Pyoto","Fylm",NULL};
	execv("/bin/zip",argv);
}
else{
	while((wait(&status2)) > 0);
	char *argv[] = {"rm","-r","/home/rizqi/modul2/MUSIK","/home/rizqi/modul2/FOTO","/home/rizqi/modul2/FILM",NULL};
	execv("/bin/rm",argv);
}

```
## Soal No 2
## Soal No 3
### Main Soal No 3
Berikut adalah main source code dari soal no3. Tahapan proses soal no.3 :
1. Membuat daemon proses melalui fungsi daemonize
2. Membuat killer_script untuk mematikan daemon proses melalui bash script sesuai dengan argumen yang ditentukan
3. 
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
