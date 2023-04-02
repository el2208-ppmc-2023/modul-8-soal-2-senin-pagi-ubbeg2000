/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

//algoritma DFS rekursif
void DFS(int *M, int row, int col, bool* visited) {

	static int rowNbr[] = { 0, -1, 0, 1 };
	static int colNbr[] = { -1, 0, 1, 0 };

	*((visited+row*COL) + col) = true; //tandai bahwa index row col matriks sudah dicek

	int jalan = 0; //variabel untuk simpan node ini terhubung oleh berapa jalan (nilai matriks =1) 
	int baris = 0;
	int kolom = 0;
	for (int k = 0; k < 4; ++k){
		baris = row + rowNbr[k];
		kolom = col + colNbr[k];
		if ((baris >= 0) && (baris < ROW) && (kolom >= 0) && (kolom < COL) && (*((M+baris*COL) + kolom))){
			jalan++;
			if(!*((visited+baris*COL) + kolom)){
				DFS(M, baris, kolom, visited);
				if((*((M+baris*COL) + kolom))==0){
					jalan--;
				}
			}
		}
	}
	if ( jalan<2 && (row!=4 || col!=4) && (row!=0 || col!=0)){
		*((M+row*COL) + col) = 0;
	}
}
void blok_jalan(int *M){
	bool visited[ROW][COL];
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < ROW; ++i){
		for (int j = 0; j < COL; ++j){
			if (*((M+i*COL) + j) && !visited[i][j]){ 
				DFS(M, i, j, (bool*)visited); 
			}
		}
	}
}

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

	blok_jalan((int *)M);
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
