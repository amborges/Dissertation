#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(const char M[32][32]){
	int i, j;
	for(i = 0; i < 32; i++){
		for(j = 0; j < 32; j++)
			printf("%c ", M[i][j]);
		printf("\n");
	}
	printf("\n\n");
}


void fillMB(char MB[32][32], char chr[1024], int* pos, 
						int* wid, int* hei, int* dep){
	if(chr[*pos] == '0'){
		//printf("eh 128x128\n");
		int i, j;
		for(i = 0; i < 32; i++)
			for(j = 0; j < 32; j++)
				MB[i][j] = '0';
	}
	else if(*dep == 0){
		//Não é 128x128 e está no primeiro nível, dividir
		*dep+=1;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=16;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=16;
		*hei+=16;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid+=16;
		fillMB(MB, chr, pos, wid, hei, dep);
		*wid-=16;
		*hei-=16;
		*dep-=1;
		return;
	}
	else if(chr[*pos] == '1'){
		//printf("eh 64x64\n");
		int i, j;
		for(i = 0; i < 16; i++)
			for(j = 0; j < 16; j++)
				MB[*hei + i][*wid + j] = '1';
	}
	else if(*dep == 1){
		//Não é 64x64 e está no segundo nível, dividir
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
	else if(chr[*pos] == '2'){
		//printf("eh 32x32\n");
		int i, j;
		for(i = 0; i < 8; i++)
			for(j = 0; j < 8; j++)
				MB[*hei + i][*wid + j] = '2';
	}
	else if(*dep == 2){
		//Não é 32x32 e está no terceiro nível, dividir
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
	else if(chr[*pos] == '3'){
		//printf("eh 16x16\n");
		int i, j;
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				MB[*hei + i][*wid + j] = '3';
		//testar memset
	}
	else if(*dep == 3){
		//Não é 16x16 e está no terceiro nível, dividir
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
	else if(chr[*pos] == '4'){
		//printf("eh 8x8\n");
		int i, j;
		for(i = 0; i < 2; i++)
			for(j = 0; j < 2; j++)
				MB[*hei + i][*wid + j] = '4';
	}
	else if(*dep == 4){
		//Não é 8x8 e está no quarto nível, dividir
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
	else if(chr[*pos] == '5'){
		//printf("eh 4x4\n");
		int i, j;
		for(i = 0; i < 1; i++)
			for(j = 0; j < 1; j++)
				MB[*hei + i][*wid + j] = '5';
	}
	
	//Após tratar cada char, passar para o próximo
	//printf("%d -> %c\n", *pos, chr[*pos]);
	*pos+=1;
}

void write2file(const char M[32][32], FILE* f){
	int i, j;
	for(i = 0; i < 32; i++){
		for(j = 0; j < 32; j++){
			//printf("%c", M1[i][j]);
			fputc(M[j][i], f);
		}
	}
}

void jumpLines(FILE* f, int howMany){
	int i;
	static char pt[5], bs[5]; //to doesnt overload memory time
	
	for(i = 0; i < howMany; i++){
		fscanf(f, "%s %s\n", pt, bs);
	}
}

int main(int argc, char** argv){
	char *in1name, *in2name;
	
	if(argc == 1){
		printf("ERROR use: %s <filename.dpt>", argv[0]);
		return 1;
	}
	
	in1name = malloc(strlen(argv[1])+1);
	in2name = malloc(strlen(argv[1])+1);
	strcpy(in1name, argv[1]);
  strcpy(in2name, argv[1]);
  in2name[strlen(argv[1])-1] = '\0';
  in2name[strlen(argv[1])-2] = 't';
  in2name[strlen(argv[1])-3] = 'q';
	
	FILE* theDPT = fopen(in1name, "r");
	FILE* qtfile = fopen(in2name, "w");
	
	char dhevc, space, ptav1[5], bsav1[5];
	int pos, wid, hei, dep, sum;
	char MB[32][32], strdpth[1024];
	int depthav1, ptnum, bsnum;
	int strpos, couldItContinue, isANewMB, isABorderMB, isFirstMB, borderPTJump, MBcount;
	
	memset(&strdpth[0], '\0', 1024);
	
	strpos = 0;	
	isANewMB = 0;
	isABorderMB = 0;
	isFirstMB = 1;
	borderPTJump = 0;
	MBcount = 0;
	
	do{
		memset(&ptav1[0], '\0', 5);
		memset(&bsav1[0], '\0', 5);
		couldItContinue = (int)fscanf(theDPT, "%s %s\n", ptav1, bsav1);
		
		if(couldItContinue != -1){
			
			ptnum = atoi(ptav1);
			bsnum = atoi(bsav1);
				
			switch(bsnum){
				case 0:  depthav1 = 5; break; // BLOCK_4X4,
				case 1:  depthav1 = 4; break; // BLOCK_4X8,
				case 2:  depthav1 = 4; break; // BLOCK_8X4,
				case 3:  depthav1 = 4; break; // BLOCK_8X8,
				case 4:  depthav1 = 3; break; // BLOCK_8X16,
				case 5:  depthav1 = 3; break; // BLOCK_16X8,
				case 6:  depthav1 = 3; break; // BLOCK_16X16,
				case 7:  depthav1 = 2; break; // BLOCK_16X32,
				case 8:  depthav1 = 2; break; // BLOCK_32X16,
				case 9:  depthav1 = 2; break; // BLOCK_32X32,
				case 10: depthav1 = 1; break; // BLOCK_32X64,
				case 11: depthav1 = 1; break; // BLOCK_64X32,
				case 12: depthav1 = 1; break; // BLOCK_64X64,
				case 13: depthav1 = 0; break; // BLOCK_64X128,
				case 14: depthav1 = 0; break; // BLOCK_128X64,
				case 15: depthav1 = 0; break; // BLOCK_128X128,
				case 16: depthav1 = 3; break; // BLOCK_4X16,
				case 17: depthav1 = 3; break; // BLOCK_16X4,
				case 18: depthav1 = 2; break; // BLOCK_8X32,
				case 19: depthav1 = 2; break; // BLOCK_32X8,
				case 20: depthav1 = 1; break; // BLOCK_16X64,
				case 21: depthav1 = 1; break; // BLOCK_64X16,
				default: 
					depthav1 = -1;
					printf("ERROR: it was found the BLOCK %d\n", bsnum);
					break; // ERRO
			}
			
			switch(ptnum){
				case 0: break; // PARTITION_NONE, não faz nada, segue o resultado acima do bs
				
				case 1: // PARTITION_HORZ,
				case 2: // PARTITION_VERT, tanto o caso 1 como o caso 2, pega o atual BS e ignora o seguinte
					if(!isABorderMB)
						jumpLines(theDPT, 1);
					break;
					
				//case 3: // PARTITION_SPLIT, Nunca vai ocorrer na decodificação
				
				case 4: // PARTITION_HORZ_A,
				case 6: // PARTITION_VERT_A, esses dois dividem em 3, o primeiro bloco é
								//de um tamanho menor, assim sendo, a depth tá maior que deveria,
								//aumenta a depth e ignora os dois BS seguintes
					depthav1--;
					if(!isABorderMB)
						jumpLines(theDPT, 2);
					break;
					
				case 5: // PARTITION_HORZ_B,
				case 7: // PARTITION_VERT_B, esses dois dividem o MB em 3, o primeiro deles
								// já está na profundidade correta, apenas ignorar os próximos dois BS
					if(!isABorderMB)
						jumpLines(theDPT, 2);
					break;
					
				case 8: // PARTITION_HORZ_4,
				case 9: // PARTITION_VERT_4, esses dois dividem o MB em quatro, o depth esta certo, so ignorar os outros tres BS
					if(!isABorderMB)
						jumpLines(theDPT, 3);
					break;
					
				case 10:
					//printf("IT WAS START A NEW NORMAL MB\n");
					isANewMB = 1;
					depthav1 = 10;
					MBcount++;
					break;
				
				case 20:
					//printf("IT WAS START A NEW BORDER MB\n");
					isABorderMB = 1;
					depthav1 = 10;
					break;
				
				default:
					printf("ERROR: it was found the PARTITION %d\n", ptnum);
					break; //ERRO
			}
			
			
			switch(depthav1){
				case 0: strdpth[strpos++] = '0'; break;
				case 1: strdpth[strpos++] = '1'; break;
				case 2: strdpth[strpos++] = '2'; break;
				case 3: strdpth[strpos++] = '3'; break;
				case 4: strdpth[strpos++] = '4'; break;
				case 5: strdpth[strpos++] = '5'; break;
				case 10: /*DO NOTHING IS A NEW MB*/ break;
				default:
					printf("ERROR: profundidade nao prevista: %d\n", depthav1);
					break; //ERRO
			}

			
			if(isFirstMB){
				//O primeiro comando do DPT é um sinal de novo MB
				isANewMB = 0;
				isFirstMB = 0;
			}
			else if(isANewMB){			
				//formou um MB 128, escreve direto
				pos = 0; wid = 0; hei = 0; dep = 0;
				fillMB(MB, strdpth, &pos, &wid, &hei, &dep);
				write2file(MB, qtfile);

				printf("DEPTHs: %s\n", strdpth);
				//printf("\n\n");
				//print(MB);
				
				if(MBcount == 60){ //só vale para HD720
					MBcount = 0;
					//fputc('\n', qtfile);
					printf("\nnew frame\n");
				}
				
				isANewMB = 0;
				isABorderMB = 0;
				borderPTJump = 0;
				strpos = 0;
				memset(&strdpth[0], '\0', 1024);
			}
			else if(isABorderMB){
				//Bordas precisam de um tratamento especial, 
				//podem haver MB de borda que foram divididas
				//e a divisão que fica fora dos limites do
				//video, é simplesmente ignorado e não é 
				//enviado nenhuma informação sobre isso.
				//Deve ser subentendido pelo decoder, assim
				//sendo, precisamos cuidar esses casos.
				//A ideia é ler informação por informação
				//e decidir se vamos usar ela ou ignorar ela.
				
				if(depthav1 == 10) continue; //só identificou a borda
				
				//printf("pt = %d, bs = %d\n", ptnum, bsnum);
				
				if(ptnum == 0){// PARTITION_NONE
					//nao pula ninguem
				}
				else if(ptnum == 1 || ptnum == 2){
					// PARTITION_HORZ or PARTITION_VERT
					//pode pular 1
					if(borderPTJump == 0) borderPTJump = 1;
					else if(borderPTJump > 0){
						borderPTJump--;
						if(strdpth[strpos - 1] == depthav1){
							strdpth[strpos - 1] = '\0';
							strpos--;
						}
					}
				}
				else if(ptnum == 4){
					// PARTITION_HORZ_A
					//pode pular 2
					if(borderPTJump == 0) borderPTJump = 2;
					else if(borderPTJump > 0){
						borderPTJump--;
						if(strdpth[strpos - 1] == depthav1){
							strdpth[strpos - 1] = '\0';
							strpos--;
						}
					}

				}
				else if(ptnum == 5){// PARTITION_VERT_A
					//pode pular 2
					if(borderPTJump == 0) borderPTJump = 2;
					else if(borderPTJump > 0){
						borderPTJump--;
						if(strdpth[strpos - 1] == depthav1){
							strdpth[strpos - 1] = '\0';
							strpos--;
						}
					}
				}
				else if(ptnum == 6){// PARTITION_HORZ_B
					//pode pular 2
					if(borderPTJump == 0) borderPTJump = 2;
					else if(borderPTJump > 0){
						borderPTJump--;
						if(strdpth[strpos - 1] == depthav1){
							strdpth[strpos - 1] = '\0';
							strpos--;
						}
					}
				}
				else if(ptnum == 7){// PARTITION_VERT_B
					//pode pular 2
					if(borderPTJump == 0) borderPTJump = 2;
					else if(borderPTJump > 0){
						borderPTJump--;
						if(strdpth[strpos - 1] == depthav1){
							strdpth[strpos - 1] = '\0';
							strpos--;
						}
					}
				}
				else if(ptnum == 8 || ptnum == 9){
					// PARTITION_HORZ_4 or PARTITION_VERT_4
					//pode pular 3
					if(borderPTJump == 0) borderPTJump = 3;
					else if(borderPTJump > 0){
						borderPTJump--;
						if(strdpth[strpos - 1] == depthav1){
							strdpth[strpos - 1] = '\0';
							strpos--;
						}
					}
				}
			}
		}
		
	}while(couldItContinue != -1);
	
	pos = 0; wid = 0; hei = 0; dep = 0;
	fillMB(MB, strdpth, &pos, &wid, &hei, &dep);
	write2file(MB, qtfile);
	printf("\nDEPTHs: %s\n", strdpth);
	
	fclose(theDPT);
	fclose(qtfile);
	
	return 0;
}

