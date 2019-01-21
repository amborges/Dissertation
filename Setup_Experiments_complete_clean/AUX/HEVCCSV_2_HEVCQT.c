#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int blk2nll(char* str){
	//Corrige o final das strings lidas
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	if(strlen(str) > 1) return 1;
	return 0;
}

void print(const char M[16][16]){
	int i, j;
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++)
			printf("%c ", M[i][j]);
		printf("\n");
	}
	printf("\n\n");
}


void fillMB(char MB[16][16], char* chr, int* pos, 
						int* wid, int* hei, int* dep){
	if(chr[*pos] == '0'){
		//Caso mais fácil. 64x64
		int i, j;
		for(i = 0; i < 16; i++)
			for(j = 0; j < 16; j++)
				MB[i][j] = '1';
		//testar memset
	}
	else if(*dep == 0){
		//Não é 64x64 e está no primeiro nível, dividir
		*dep+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=8;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=8;
		*hei+=8;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=8;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=8;
		*hei-=8;
		*dep-=1;
		return;
	}
	else if(chr[*pos] == '1'){
		//Segundo caso mais fácil. 32x32
		int i, j;
		for(i = 0; i < 8; i++)
			for(j = 0; j < 8; j++)
				MB[*hei + i][*wid + j] = '2';
		//testar memset
	}
	else if(*dep == 1){
		//Não é 32x32 e está no segundo nível, dividir
		*dep+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=4;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=4;
		*hei+=4;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=4;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=4;
		*hei-=4;
		*dep-=1;
		return;
	}
	else if(chr[*pos] == '2'){
		//Terceiro caso mais fácil. 16x16
		int i, j;
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				MB[*hei + i][*wid + j] = '3';
		//testar memset
	}
	else if(*dep == 2){
		//Não é 16x16 e está no segundo nível, dividir
		*dep+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=2;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=2;
		*hei+=2;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=2;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=2;
		*hei-=2;
		*dep-=1;
		return;
	}
	else if(chr[*pos] == '3'){
		//Terceiro caso mais fácil. 8x8
		int i, j;
		for(i = 0; i < 2; i++)
			for(j = 0; j < 2; j++)
				MB[*hei + i][*wid + j] = '4';
		//testar memset
	}
	else if(*dep == 3){
		//Não é 16x16 e está no segundo nível, dividir
		*dep+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=1;
		*hei+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=1;
		*hei-=1;
		*dep-=1;
		return;
	}
	else if(chr[*pos] == '4'){
		//Não tem CU 4x4. Nunca deverá entrar nesse caso
		int i, j;
		for(i = 0; i < 1; i++)
			for(j = 0; j < 1; j++)
				MB[*hei + i][*wid + j] = '5';
		//testar memset
	}
	
	//Após tratar cada char, passar para o próximo
	//printf("%d -> %c\n", *pos, chr[*pos]);
	*pos+=1;
}

void write2file(const char M1[16][16], const char M2[16][16], FILE* f){
	int i, j;
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			//printf("%c", M1[i][j]);
			fputc(M1[j][i], f);
		}
		for(j = 0; j < 16; j++){
			//printf("%c", M2[i][j]);
			fputc(M2[j][i], f);
		}
	}
	//printf("\n\n");
}

int main(int argc, char** argv){
	FILE* theCSV = fopen("HEVC.csv", "r");
	FILE* qtfile = fopen("HEVC.qt", "w");
	
	char* positions = malloc(sizeof(char)*25);
	char* tree = malloc(sizeof(char)*512);
	char* auxc;
	int pares, htpares, hpares, tframes, ctu_limit;
	
	if(argc > 1){
		if(strcmp(argv[1],"432") == 0){
			//printf("LOADING 720\n");
			pares = 12; //768/64
			htpares = 7; //432/64
			ctu_limit = 83;
			tframes = atoi(argv[2]);
		}
		else if(strcmp(argv[1],"720") == 0){
			//printf("LOADING 720\n");
			pares = 20; //1280/64
			htpares = 12; //720/64
			ctu_limit = 239;
			tframes = atoi(argv[2]);
		}
		else if(strcmp(argv[1],"1080") == 0){
			//printf("LOADING 1080\n");
			pares = 30; //1920/64
			htpares = 17; //1080/64
			ctu_limit = 509;
			tframes = atoi(argv[2]);
		}
		else if(strcmp(argv[1],"2k") == 0){
			//printf("LOADING 2K\n");
			pares = 34; //2160/64
			htpares = 23; //1440/64
			ctu_limit = 781;
			tframes = atoi(argv[2]);
		}
		else{// if(strcmp(argv[1],"4k") == 0){
			//printf("LOADING 4K\n");
			pares = 64; //4096/64
			htpares = 34; //2160/64
			ctu_limit = 2175;
			tframes = atoi(argv[2]);
		}
	}
	else{
		//printf("LOADING DEFAULT\n");
		pares = 20;
		htpares = 12;
		tframes = 3;
	}
	
	char M[3][pares][512];
	int x_pos, y_pos, ctu_count;
	int linha = 0, coluna = 0, chr = 0;
	int frames = 0;
	int i = 0;
	int pos = 0, wid = 0, hei = 0, dep = 0;
	static char MB1[16][16], MB2[16][16], MB3[16][16], MB4[16][16];
	
	int myh = 0, myw = 0;
	int senoid = 1, first = 1;
	
	do{
		//printf("\nFRAME %d\n\n", frames);
		frames++;
		hpares = htpares;
		do{
			//limpando matrizes
			memset(&M[0][coluna][0], '\0', 512);
			memset(&M[0][coluna + 1][0], '\0', 512);
			memset(&M[1][coluna][0], '\0', 512);
			memset(&M[1][coluna + 1][0], '\0', 512);
			
			hpares -= 2;
			linha = 0;
			coluna = 0;
			
			while(linha < 2 && (fgets(positions, 25, theCSV)) != NULL){
				if(blk2nll(positions)){
					auxc = strtok(positions, ","); //CTU num
					ctu_count = atoi(auxc);
					auxc = strtok(NULL, ","); // pega o X
					x_pos = atoi(auxc);
					auxc = strtok(NULL, ","); // pega o Y
					y_pos = atoi(auxc);
					//printf("POS[%d,%d]\n", x_pos, y_pos);
					
					fgets(tree, 512, theCSV);
					blk2nll(tree);
					auxc = strtok(tree, ","); //Sempre vai ter um primeiro elemento
					chr = 0;
					M[linha][coluna][chr++] = auxc[0];
					
					while((auxc = strtok(NULL, ",")) != NULL){
						//Pega os demais e adiciona na matriz, se houver
						M[linha][coluna][chr++] = auxc[0];
					}
					M[linha][coluna][chr] = '\0'; //caractere nulo ao final
					
					coluna++;
			
					if(coluna >= pares){
						linha++;
						coluna = 0;
					}
					
					if(ctu_count == ctu_limit) linha = 2;
				}
			}
			
			
			//Imprime na ordem de blocos 128x128
			if(linha == 2){
				for(coluna = 0; coluna < pares; coluna = coluna + 2){
								
					pos = 0, wid = 0, hei = 0, dep = 0;
					fillMB(MB1, M[0][coluna], &pos, &wid, &hei, &dep);
				
					pos = 0, wid = 0, hei = 0, dep = 0;
					fillMB(MB2, M[1][coluna], &pos, &wid, &hei, &dep);
				
					write2file(MB1, MB2, qtfile);
				
					pos = 0, wid = 0, hei = 0, dep = 0;
					fillMB(MB1, M[0][coluna + 1], &pos, &wid, &hei, &dep);
								
					pos = 0, wid = 0, hei = 0, dep = 0;
					fillMB(MB2, M[1][coluna + 1], &pos, &wid, &hei, &dep);
				
					write2file(MB1, MB2, qtfile);
				
					//fputc('\n', qtfile);
				}
			}
		}while(hpares >= 0);
	}while(frames < tframes);
	
	fclose(theCSV);
	return 0;
}
