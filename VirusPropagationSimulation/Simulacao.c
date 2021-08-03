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
#include <string.h>
#include <ctype.h>

#include "structs.h"
#include "utils.h"
#include "struct_Sim.h"
#define tam 100

void apresenta_estatistica(ppessoa listaPN,local espaco[], int totEsp,int totPessoas,int verificador,int contIT,int contADC){
    int i,j,k,estado[3]={}, idsala[tam]={},distr[tam]={};
    float taxa_saudavel=0,taxa_imune=0,taxa_infetado=0;
    ppessoa aux = listaPN;
    
    //Criacao de array com id's dos espacos
    for(i=0; i<totEsp;i++){
       idsala[i]=espaco[i].id;
    }
    //Contagem do numero de S/I/D
    while(listaPN != NULL){
     if(listaPN->estado=='S')
         estado[0]+=1;
     if(listaPN->estado=='I')
         estado[1]+=1;
     if(listaPN->estado=='D')
         estado[2]+=1;
     //Ciclo para preencher array com quantas vezes cada espaco aparece
     for(j=0; j<totEsp;j++){
     if(listaPN->espaco == idsala[j]){
         distr[j]++;          //soma +1 ao espaco que aparece de cada pessoa 
     }
     }
     idsala[j+1]='\0';
     distr[j+1]='\0';
     listaPN=listaPN->prox;
    }
    
    //Calculo das taxas em % dos S/I/D
    taxa_saudavel=(estado[0]/(float)totPessoas)*100;
    taxa_imune=(estado[1]/(float)totPessoas)*100;
    taxa_infetado=(estado[2]/(float)totPessoas)*100;
    
    //Verificador usado para evitar criação de uma função extra com os mesmos calculos, filtrando assim 
    // a informacao mostrada no ecra dependendo da situação e do pedido do utilizador
    if(verificador == 0){
    printf("\n\nNumero de pessoas: %d\n\n",totPessoas);
    printf("Existem %d pessoas saudaveis, a sua taxa e de: %.2f %%\n",estado[0],taxa_saudavel);
    printf("Existem %d pessoas Imunes, a sua taxa e de: %.2f %%\n",estado[1],taxa_imune);
    printf("Existem %d pessoas Infetadas, a sua taxa e de: %.2f %%\n",estado[2],taxa_infetado);
    
    for(k=0;k<totEsp;k++){
            printf("\nExistem %d pessoas na sala: %d",distr[k],idsala[k]);       
    }
    }
    //Se verificador = 1, entao grava um relatorio final em relatorio.txt
    if(verificador == 1){
        gravaRelatorio(aux,espaco,totPessoas,totEsp,estado,idsala,distr,contIT,contADC,taxa_saudavel,taxa_imune,taxa_infetado);
    }
}

ppessoa insere_doente_Final(ppessoa p,local espaco[],int totEsp,int* totPessoas){
    ppessoa novo, aux=p;
     if(VerificaSemEspaco(espaco,totEsp) == 0)
         return p;
    // Aloca espaço
    novo = malloc(sizeof(pessoa));
    if(novo == NULL)
        return p;   
    
    // Preenche dados do doente
    adiciona_doente(novo,espaco,totEsp,aux);
    (*totPessoas)++;
    
    // Insere na Lista
    if(p == NULL)       // Lista vazia
        p = novo;
    else{
        aux = p;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return p;
}

void adiciona_doente(ppessoa novo,local espaco[],int totEsp,ppessoa aux){
    
        printf("\n\nInsira um doente novo a um espaco:\n");
	do{
            printf("Nome: ");
            scanf(" %s", novo->id);
        }while(verifica_existe_nome(aux,novo->id) == 0);
        do{
	printf("Idade (0-122): ");
	scanf("%d", &novo->idade);
        }while(novo->idade<1 || novo->idade>122);//Pessoa mais velha do mundo até a data tinha 122 anos; Jeanne Calment
	novo->estado='D';
        do{
        printf("Numero de dias Infetados (0-17): "); //17 é o numero maximo de dias infetado para uma pessoa com 122 anos, se sobreviver 17 dias 
	scanf("%d", &novo->dias_inf);
        }while(novo->dias_inf<1 || novo->dias_inf>17 || novo->dias_inf>=5+(0.1*novo->idade)); //Sem dados especificos para limitar ainda tempo máximo de infeção
        verifica_espaco(novo,totEsp,espaco);
	novo->prox = NULL;
}

int verifica_existe_nome(ppessoa p,char*nome){
    while(p!=NULL){
        if(!strcmp(p->id,nome)){
            printf("\nEssa pessoa ja existe, insira outra!\n");
            return 0;
        }
        p=p->prox;
    }
    return 1;
}

//Simples verificador de espaços
int VerificaSemEspaco(local espaco[],int totEsp){
    int cont=0;
    
    for (int i = 0; i < totEsp; i++) {
            if (espaco[i].capacidade == 0) {
                cont++;
            }
            if(cont==totEsp){
                printf("\nNao existe espaco disponivel para adicionar ou transferir pessoas!");
                return 0;
            }
        }
    return 1;
}
ppessoa verifica_espaco(ppessoa novo,int totEsp,local espaco[]){
    int flag = 0, cont = 0;
    do {
        printf("Local a inserir: ");
        scanf("%d", &novo->espaco);
        //
        for (int i = 0; i < totEsp; i++) {
            cont++;
            if (novo->espaco == espaco[i].id) {
                //Se o espaco ainda tiver lotacao, fica com menos 1 espaco de lotacao
                if (espaco[i].capacidade > 0) {
                    espaco[i].capacidade--;
                    flag = 1;
                }
                //Se chegar ao fim dos espacos e nao houver espaco, devolve nova pessoa sem adicionar
                if (cont == totEsp && flag == 0) {
                    printf("\nNao existe espaco para adicionar uma pessoa");
                    return novo;
                }
            }
        }
        if (flag == 0)
            printf("\nInsira um local correto e com capacidade\n");
    } while (flag == 0);
    return novo;
}

//Simples atualização de capacidade 
void atualizaEspacoTranfere(plocal espaco,int totEsp,int origem,int destino,int npess){
    
    for(int i=0;i<totEsp;i++){
            if(espaco[i].id==origem)
                espaco[i].capacidade+=npess;
            if(espaco[i].id==destino)
                espaco[i].capacidade-=npess;
        }
}

ppessoa tranfere_pessoas(ppessoa p, local espaco[], int totEsp) {
    ppessoa aux = p;
    int npess = 0, flag = 0, flag1 = 0, cont1 = 0, origem = 0, destino = 0, OrigTotPess = 0, i = 0, valorAleat = 0, PosListOrig[tam] = {};
    if (VerificaSemEspaco(espaco, totEsp) == 0)
        return p;
    do {
        //Faz a validacao completa da origem,destino
        verifica_dados_transf(&origem, &destino, &npess, totEsp, espaco, flag);
        for (int i = 0; i < totEsp; i++) {
            if (espaco[i].id == destino && espaco[i].capacidade - npess < 0) {
                printf("\nNao existe capacidade no destino para a transferencia de pessoas !\n");
                return p;
            }
        }
        atualizaEspacoTranfere(espaco, totEsp, origem, destino, npess);
        flag = 0;
        while (aux != NULL) {
            ++cont1; //codigo para contagem das vezes em que origem aparece na lista de pessoas
            if (aux->espaco == origem) {
                OrigTotPess++;
                PosListOrig[i] = cont1;
                i++;
            }
            aux = aux->prox;
        }
        PosListOrig[i + 1] = '\0';
        //Caso o numero de pessoas inserido pelo utilizador for > que as que existem na lista, repete transferencia
        if (npess > OrigTotPess) {
            printf("\n\nPor favor, indique numero de pessoas valido!\n\n");
            flag = 1;
        }
    } while (flag == 1);
    //Criacao aqui do Array apos obter o NPESS
    int ArrDosAleatori[npess];
    //Codigo para escolher aleatoriamente o Numero de pessoas que o utilizador quer transferir das existentes
    for (int j = 0; j < npess; j++) {
        do {
            flag1 = 0;

            valorAleat = intUniformRnd(0, OrigTotPess - 1);
            ArrDosAleatori[j] = PosListOrig[valorAleat];
            for (int k = 0; k < npess; k++) {
                if (ArrDosAleatori[k] == ArrDosAleatori[j] && k != j) {
                    flag1 = 1;
                }
            }
        } while (flag1 == 1);
    }
    //Apos recolha completa dos dados necessarios para a transferencia, e feita a atualizacao dos espacos das
    //pessoas da origem para o destino
    atualiza_espacos(p, npess, ArrDosAleatori, destino);
    return p;
}

void atualiza_espacos(ppessoa p, int npess, int ArrDosAleatori[], int destino) { //Altera os valores escolhidos aleatoriamente do espaco de origem para o destino
    int cont = 0;
    // Codigo para sempre que encontra a posicao em que a pessoa foi transferida da origem, 
    //altera espaco para destino
    while (p != NULL) {
        ++cont;
        for (int i = 0; i < npess; i++) {
            if (cont == ArrDosAleatori[i]) {
                
                p->espaco = destino;
            }
        }
        p = p->prox;
    }
}

void verifica_dados_transf(int* origem, int* destino, int* npess, int totEsp, local espaco[], int flag) {
    int flag2 = 0, flag3 = 0;

    if (flag == 0) {
        do {
            do {
                printf("\nIndique o id do local de origem:");
                scanf("%d", &(*origem));
                for (int i = 0; i < totEsp; i++) {
                    if (*origem == espaco[i].id) { //Confirma existencia da origem 
                        flag2 = 1;
                        break;
                    }
                }
                if (flag2 == 0)
                    printf("Indique um local de origem Valido!\n");

            } while (flag2 == 0);

            do {
                printf("\nIndique o id do local de destino e diferente da origem:");
                scanf("%d", &(*destino));
                for (int i = 0; i < totEsp; i++) {
                    if (*destino == espaco[i].id && *destino != *origem) { //Confirma existencia do destino e que e diferente da origem
                        flag3 = 1;
                        break;
                    }
                }
            } while (flag3 == 0);
            
            printf("\nIndique o numero de pessoas que pretende mover de local: ");
            scanf("%d", &(*npess));
            
            verifica_orig_destino(*origem, *destino, espaco, totEsp);
            
        } while (verifica_orig_destino == 0);
    } else {
        printf("\nIndique o numero de pessoas que pretende mover de local: ");
        scanf("%d", &(*npess));
    }

}
//verifica conexao entre origem destino
int verifica_orig_destino(int origem,int destino,local espaco[],int totEsp){
    
    int flag4=0;
        for (int i = 0; i < totEsp; i++) {
            if (espaco[i].id == origem) { //Entra no espaco da origem
                for (int j = 0; j < totEsp; j++) {
                    if (espaco[j].id == destino) {//Entra no espaco do destino
                        for (int k = 0; k < 3; k++) {
                            for (int h = 0; h < 3; h++) {
                                if (espaco[i].id == espaco[j].liga[h]) { //Compara ligacoes do destino com id da origem
                                    flag4 = 1;
                                }
                            }
                            if (flag4 == 1)
                                break;
                        }
                    }
                }
            }
        }
        if (flag4 == 0){
            printf("\n\nNao existe conexao entre os dois locais\n\n");
            return 0;
        }else
            return 1; 
}

void gravaPessoas(ppessoa p,int totPessoas){
    FILE *f;
    char novofich[]={};
    
    printf("\nIndique o nome do ficheiro para guardar as Pessoas: ");
    scanf("%s",&novofich);
    f = fopen(novofich,"wt");
    if (!f) {
        fclose(f);
        fprintf(stderr,"Erro a criar o ficheiro: %s\n",novofich);
        return;
    } 
    fprintf(f, "Total de pessoas: %d\n", totPessoas);
    while(p!=NULL){
        if(p->estado == 'D'){
        fprintf(f, "Nome: %s\t Idade: %d\t Estado: %c\t Dias Infetado: %d\t Espaco:%d \n", 
                p->id,p->idade,p->estado,p->dias_inf,p->espaco);
        }else{
             fprintf(f, "Nome: %s\t Idade: %d\t Estado: %c\t Espaco:%d \n", p->id,p->idade,
                p->estado,p->espaco);
        }
        p=p->prox;
        }
    fclose(f);  
}

void gravaRelatorio(ppessoa p,local espaco[],int totPessoas,int totEsp,int estado[],int idsala[],int distr[],int contIT,int contADC,float taxa_saudavel,float taxa_imune,float taxa_infetado){
    FILE *f;
    ppessoa aux = NULL;
    f = fopen("Report.txt","wt");
    if (!f) {
        fclose(f);
        fprintf(stderr,"Erro a criar o ficheiro: Report.txt\n");
        return;
    }
    fprintf(f,"\t\t------------------------------------Relatorio Final da Simulacao------------------------------------");
    fprintf(f,"\n\n\t\tApos %d iteracoes, a distribuicao das pessoas foi a seguinte: \n\n",contIT);
    fprintf(f,"\n\nTotal de espacos: %d",totEsp);
    fprintf(f,"\nTotal de pessoas: %d",totPessoas);
    fprintf(f,"\nForam adicionadas %d pessoas",contADC);
    
    for (int i = 0; i < totEsp; i++) {
        fprintf(f,"\n____________________________________________________________________________________________________\n");
            fprintf(f,"ID: %d\t", espaco[i].id);
            fprintf(f,"Capacidade: %d\t\t", espaco[i].capacidade);
            fprintf(f,"1->Ligacao: %d  || \t", espaco[i].liga[0]);
            fprintf(f,"2->Ligacao: %d  || \t", espaco[i].liga[1]);
            fprintf(f,"3->Ligacao: %d  ||\n",  espaco[i].liga[2]);
            fprintf(f,"----------------------------------------------------------------------------------------------------\n");
        aux = p;
        while (aux != NULL) {
            if (aux->espaco == espaco[i].id) {
                if (aux->estado == 'D') {
                    fprintf(f,"\n\t Nome: %s\t Idade: %d\t Estado: %c\t Dias Infetado: %d",aux->id, aux->idade, aux->estado, aux->dias_inf);
                } else {
                    fprintf(f,"\n\t Nome: %s\t Idade: %d\t Estado: %c", aux->id, aux->idade, aux->estado);
                }
            }
            aux = aux->prox;
        }
    }        
    fprintf(f,"\n\n\t\t------------------------------------Estatistica final------------------------------------\n\n");
        fprintf(f,"Existem %d pessoas saudaveis, a sua taxa e de: %.2f %%\n",estado[0],taxa_saudavel);
        fprintf(f,"Existem %d pessoas Imunes, a sua taxa e de: %.2f %%\n",estado[1],taxa_imune);
        fprintf(f,"Existem %d pessoas Infetadas, a sua taxa e de: %.2f %%\n",estado[2],taxa_infetado);
        
        for(int k=0;k<totEsp;k++){
            fprintf(f,"\nExistem %d pessoas na sala: %d",distr[k],idsala[k]);       
    }
    fclose(f);  
}