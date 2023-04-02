/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

void file_handling(int* matrix) {
	char namafile[255];
    char line[255];
	char* token;
    FILE *matriks; //pointer of type file

    printf("Masukkan nama file matriks: ");
    scanf("%s", &namafile);

    matriks = fopen(namafile, "r"); //buka file mode read only

    if (matriks == NULL){ //jika file tidak ditemukan
        printf("Error : file invalid\n");
        fclose(matriks);
    }

	int i = 0;
	int j = 0;
    while(fgets(line, 255, matriks)){
		j = 0;
        token = strtok(line, ",");
        while (token != NULL)
        {
            *((matrix+i*COL) + j) = atoi(token);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
	}
}

int main()
{
	int temp = 0;
	int M[ROW][COL] = {};
	file_handling((int*)M);
	//matriks sebelum diubah blok jalannya
	for (int i=0; i<ROW; i++){
		for (int j=0; j<COL; j++){
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
    //..............................................
	printf("Matriks hasil blok jalan yang tidak terpakai:\n");
	//matriks setelah diubah blok jalannya
	for (int i=0; i<ROW; i++){
		for (int j=0; j<COL; j++){
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
