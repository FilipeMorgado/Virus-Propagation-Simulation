/*
    // Trabalho Pratico Programacao - LEI
   // DEIS-ISEC 2019-2020
 * 
 -> Criado por: Filipe Daniel Ramos Morgado
 -> Número de aluno: a2019137625
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "utils.h"
#include "struct_Propaga.h"

ppessoa prob_recup(ppessoa p){

    float prob,result,prob_imune=0.2;
    
    while(p!= NULL){
        if(p->estado == 'D'){   //Se tiver doente é feito o calculo abaixo referenciado pelo enunciado
            prob=(float)1/p->idade;
            result = probEvento(prob);  //Caso a prob == 1, ou seja, acertou na chance de ficar recuperado, doente fica imune
            if(result == 1){
                p->estado = 'S';
                p->dias_inf=0;
               if(probEvento(prob_imune) == 1) //Como referenciado pelo enunciado, sempre que passa de doente a saudavel, tem a chance de ficar imune
                   p->estado = 'I';
            }
        }
        p=p->prox;
    }
}

ppessoa dura_max_infe(ppessoa p){
    int prob;
    float prob_imune=0.2;
   while(p!= NULL){
        if(p->estado == 'D'){   
            prob=5+(0.1*p->idade);
            if(p->dias_inf >= prob){        //Se tiver doente e a probabilidade for > dias infetados, doente fica saudavel, e novamente tem a chance de ficar imune
                p->estado = 'S';
                p->dias_inf=0;
                if(probEvento(prob_imune) == 1)
                   p->estado = 'I';
            }
        }
        p=p->prox;
    }   
}

ppessoa dissemina(ppessoa p,int totEsp, local espaco[]){
    ppessoa aux = p;
    int contaEsp = 0, result = 0, j = 0, rand = 0, cnt=0;
    float probinf = 0.05;
    
    for (int i = 0; i < totEsp; i++) {
        int soma=0;
        contaEsp = 0;
        j = 0;
        int arr[200] = {};
        //cria array com os locais em que tem o espaço id
        aux = p;
        while (aux != NULL) {
            soma++;
            if (aux->espaco == espaco[i].id) {
                arr[j] = soma;
                j++;
                contaEsp++;
            }   
            aux=aux->prox;
        }
        //Verifica quantos vai infetar
        result = contaEsp * (float)probinf;

        aux = p;        
        //Se infetar pelo menos 1
        while(result > 0) {
            cnt = 0;
            for(int i=0; i<contaEsp;i++){  //Verifica se ainda tem pessoas para infetar nesse espaço
                if(arr[i] == -1)
                    cnt++;
            }
            if(cnt == contaEsp)    //Se nao houver mais pessoas a infetar, sai do ciclo
                break;
            //Escolha aleatoria de uma pessoa a infetar
            do {
                rand = intUniformRnd(0, contaEsp - 1);
            }while(arr[rand] == -1);
            
            int soma1=0;
            //Percorre ate encontrar a pessoa escolhida pelo rand e muda o seu estado para 'D'
            while (aux != NULL) {
                soma1++;
                if (soma1 == arr[rand] && aux->estado == 'S') { 
                                    arr[rand] = -1;
                                    aux->estado = 'D';
                                    aux->dias_inf = 1;
                }
                aux=aux->prox;
            }
            //Decrementa o numero de doentes que infetou
            result--;
        }
    }
}

//Outra possibilidade de dessiminação, tendo em conta a prob de infetar ser 5%

/*
ppessoa prob_disse(ppessoa p){

    ppessoa aux=p;
    int guardaEsp;
    
    
    while(aux!= NULL){
        if(aux->estado == 'D'){
            guardaEsp = aux->espaco;
            aux->dias_inf++;
            //chama func verifica espaco
            dissemina_local(aux,guardaEsp);
        }
        aux=aux->prox;
       
    } 
}

ppessoa dissemina_local(ppessoa p,int guardaEsp){
    int result;
    
    while (p != NULL) {
        if (p->espaco == guardaEsp && p->estado == 'S') {
            result = probEvento(0.05);
            if (result == 1) {
                p->estado = 'D';
                p->dias_inf = 1;
            }
        }
        p = p->prox;
    }
    return p;
}
*/
