/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dissertacao.h
 * Author: alex
 *
 * Created on 18 de Abril de 2018, 15:21
 */

#ifndef DISSERTACAO_H
#define DISSERTACAO_H

#include <stdio.h>
#include <time.h>
#include "../common/enums.h"
#include "../common/onyxc_int.h"
#include "ratectrl.h"
//#include "encoder.h"

BLOCK_SIZE MBTD[32][32]; //Representa o MacroBloco local
static char WASLOADCSV = 0; //variável que controla se pode abrir o arquivo CSV ou não
static FILE *TREELOG; //O arquivo csv do HEVC
unsigned char isPickPartition;
BLOCK_SIZE ACTUALDEPTHBLOCK;
unsigned short int stopLoop;

#define MYBLOCKLIMIT BLOCK_4X4

void loadMBTreeDepth(unsigned int frame, int mi_row, int mi_col, int hvideo); //Para cada nova rd_sb, atualiza
int canISlip(int mi_row, int mi_col, BLOCK_SIZE depth, int original); //TRUE se pode descer na árvore de particionamento, FALSE se não
void exportTree(int mi_row, int mi_col, PARTITION_TYPE pt, BLOCK_SIZE bs, int videoheight, int videowidth); //imprime num arquivo a arvore de profundidade
int fullsearch(BLOCK_SIZE);

#endif /* DISSERTACAO_H */

