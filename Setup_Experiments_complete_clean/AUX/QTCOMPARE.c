#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getDepth(char c){
	int depth;
	switch(c){
		case '0': depth = 0; break;
		case '1': depth = 1; break;
		case '2': depth = 2; break;
		case '3': depth = 3; break;
		case '4': depth = 4; break;
		case '5': depth = 5; break;
		default:
			printf("ERROR: profundidade invalida. Encontrado (%d) '%c'\n", (int)c, c);
			depth = -1;
	}
	return depth;
}

int main(int argc, char** argv){
	
	int lim, tframes, tojump;
	char *in1name, *in2name;
	
	//Essas linhas servem para excluir da contagem
	//a borda inferior do mapa de calor.
	//A logica da operacao é: o tamanho da largura do vídeo
	//divididos por 4 (cada char vale um bloco 4x4) e a altura do
	//vídeo tb divididos por 4. Reduz em 1 a altura (pra
	//remover a borda inferior). Multiplica pela quantidade
	//de char que há num MB de 128x128, que é 1024.
	
	if(argc == 5){
		if(strcmp(argv[1],"432") == 0){
			lim = 18432; // 6*3*1024
			tojump = 6144; // 6*1024
		}
		else if(strcmp(argv[1],"720") == 0){
			lim = 51200; // 10*5*1024
			tojump = 10240; // 10*1024
		}
		else if(strcmp(argv[1],"1080") == 0){
			lim = 122880; // 15*8*1024
			tojump = 15360; // 15*1024
		}
		else if(strcmp(argv[1],"2k") == 0){
			lim = 191488; // 17*11*1024
			tojump = 17408; // 17*1024
		}
		else{// if(strcmp(argv[1],"4k") == 0){
			lim = 524288; // 32*16*1024
			tojump = 32768; // 32*1024
		}
		tframes = atoi(argv[2]);
		in1name = malloc(strlen(argv[3])+1);
		in2name = malloc(strlen(argv[4])+1);
		if(in1name != NULL && in2name != NULL){
    	strcpy(in1name, argv[3]);
    	strcpy(in2name, argv[4]);
    }
    else{
    	printf("ERROR: problem to allocate memory\n");
    }
	}
	else{
		printf("Please, use: '%s <hsize> <num_of_frames> <filename1> <filename2>'\n", argv[0]);
		printf("<hsize> accepted: 432, 720, 1080, 2k, 4k\n");
		return 1;
	}

	FILE *hevc, *av1;
	char dhevc, dav1;
	int i, j, depthhevc, depthav1, frame, auxlim;
	const int MAXDEPTH = 6;
	
	unsigned long int CNT[MAXDEPTH][MAXDEPTH], totalCNT = 0, totallinha[MAXDEPTH];
	
	hevc = fopen(in1name, "r");
	av1 = fopen(in2name, "r");
	auxlim = lim;
	frame = 0;
	
	while(frame < tframes){
		frame++;
		lim = auxlim;
		
		for(i = 0; i < MAXDEPTH; i++){
			totallinha[i] = 0;
			for(j = 0; j < MAXDEPTH; j++){
				CNT[i][j] = 0;
			}
		}
	
	
		if(hevc == NULL || av1 == NULL){
			printf("FAIL TO OPEN qt FILES\n");
			return 1;
		}
	
		do{
			dhevc = getc(hevc);
			dav1 = getc(av1);
			if(dhevc != EOF && dav1 != EOF){
			
				depthhevc = getDepth(dhevc);
				depthav1  = getDepth(dav1);
			
				if(depthhevc != -1 && depthav1 != -1){
					CNT[depthhevc][depthav1]++;
					totallinha[depthhevc]++;
					totalCNT++;
				}
			}
			lim--;	
		}while(dhevc != EOF && dav1 != EOF && lim > 0);
		
		printf("Tabela Comparativa das Profundidades - Valores Absolutos (FRAME %2d)\n", frame);
		printf("\tAV1\n");
		printf("HEVC\tDL0\tDL1\tDL2\tDL3\tDL4\tDL5\n");
		for(i = 1; i < MAXDEPTH; i++){
			printf("DL%d\t", i);
			printf("%lu\t%lu\t%lu\t%lu\t%lu\t%lu\n", CNT[i][0], CNT[i][1], CNT[i][2], CNT[i][3], CNT[i][4], CNT[i][5]);
		}
	
		printf("Tabela Comparativa das Profundidades - Porcentagens (FRAME %2d)\n", frame);
		printf("\tAV1\n");
		printf("HEVC\tDL0\tDL1\tDL2\tDL3\tDL4\tDL5\n");
		for(i = 1; i < MAXDEPTH; i++){
			printf("DL%d\t", i);
			printf("%.2f%%\t%.2f%%\t%.2f%%\t%.2f%%\t%.2f%%\t%.2f%%\n", 100.*((float)CNT[i][0]/(float)totallinha[i]), 
																																	 100.*((float)CNT[i][1]/(float)totallinha[i]), 
																																	 100.*((float)CNT[i][2]/(float)totallinha[i]), 
																																	 100.*((float)CNT[i][3]/(float)totallinha[i]), 
																																	 100.*((float)CNT[i][4]/(float)totallinha[i]),  
																																	 100.*((float)CNT[i][5]/(float)totallinha[i]));
		}
		
		printf("\n\n");
		
		//pulando a linha inferior;
		for(i = 0; i < tojump; i++){
			depthhevc = getDepth(dhevc);
			depthav1  = getDepth(dav1);
		}
	}
	
	fclose(av1);
	fclose(hevc);
	
	return 0;
}
