/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Dissertacao.h"

void chr2BLK(char* chr, int line){
    int i;
    if(!(sizeof(chr)/sizeof(char) > 0)){
    	printf("END OF FILE AND STILL LOADING SB\n");
    }
    for(i = 0; i < 32; i++){
        switch(chr[i]){
		        case '5': MBTD[line][i] = BLOCK_4X4; break; // [DONT]
            case '4': MBTD[line][i] = BLOCK_8X8; break; // 
            case '3': MBTD[line][i] = BLOCK_16X16; break; // 
            case '2': MBTD[line][i] = BLOCK_32X32; break; // 
            case '1': MBTD[line][i] = BLOCK_64X64; break; // 
            case '0': MBTD[line][i] = BLOCK_128X128; break; // [DONT]
            default: MBTD[line][i] = -1; break; //ERROR
        }
    }
    
}

void loadMBTreeDepth(unsigned int frame, int mi_row, int mi_col, int hvideo){
    
    //Para cada nova rd_sb, atualiza
    //printf("F%d[%d,%d]\n", frame, mi_row, mi_col);
    static unsigned int lastFrame;
    if(!WASLOADCSV){
    	  lastFrame = -1;
        TREELOG = fopen("HEVC.qt", "r");
        if(TREELOG == NULL)
            printf("\nFAIL TO OPEN HEVC.qt\n");
        else
            WASLOADCSV = 1;
    }
    
    //printf("\nAV1[%d,%d]", mi_row, mi_col);
    
    if(mi_row == 0 && mi_col == 0 && frame == lastFrame){
    	//ha casos em que o frame eh processado novamente
    	//para esses, "rebobinar" o arquivo para o inicio do frame
    	long int offset;
    	if(hvideo == 432) offset = -24576;
    	else if(hvideo == 720) offset = -61440;
    	else if(hvideo == 1080) offset = -138240;
    	else if(hvideo == 1440) offset = -208896;
    	
    	fseek(TREELOG, offset, SEEK_CUR);
    } 
    
    int row, col;
    char chrrd[32];
    for(row = 0; row < 32; row++){
        fread(chrrd, 1, 32, TREELOG);
        chr2BLK(chrrd, row);
    }
    
    if(mi_row == 0 && mi_col == 0){
    		lastFrame = frame;
        //printMBTD(frame);
    }
    
} 
int canISlip(int mi_row, int mi_col, BLOCK_SIZE depth){
    //TRUE se pode descer na árvore de particionamento, FALSE se não
    if(!WASLOADCSV){
    	printf("CSV doesnt load\n");
    }
    //else if (depth > MBTD[mi_col % 32][mi_col % 32]) return 1; //EQUAL
    else if (depth >= MBTD[mi_col % 32][mi_col % 32]) return 1; //DL+1
    return 0;
    
    //return 1; //Quase original
}

void exportTree(int mi_row, int mi_col, PARTITION_TYPE pt, BLOCK_SIZE bs, int videoheight, int videowidth){
    int wlimit = (videowidth / 4) - 32;
    int hlimit = (videoheight / 4) - 32;
    
    if((mi_row % 32 == 0) && (mi_col % 32 == 0)){
    	printf("10 10\n");
    	//if((mi_row >= hlimit) || (mi_col >= wlimit)){
    	if((mi_row >= hlimit)){
    		//printf("20 20 [%d, %d]\n", mi_row, mi_col);
    		printf("20 20\n");
    	}
    }
    
    printf("%d %d\n", (int)pt, (int)bs);
}
