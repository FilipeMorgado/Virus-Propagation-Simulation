/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}


// Função main () com alguns exemplos simples de utilizacao das funcoes
