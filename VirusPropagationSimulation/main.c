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
#include <ctype.h>
#include "utils.h"
#include "structs.h"
#include "struct_recuar.h"
#include "struct_Sim.h"
#include "struct_Propaga.h"

int main (int argc, char** argv){
    local *espaco = NULL;
    int totEsp=0, op=0,totPessoas=0,contIT=0,contADC=0,verificador=0;
    char op1,fichPess[30]={};
    ppessoa listaP = NULL, listaPN = NULL; 
    precua listaREC = NULL;
    
    initRandom();  
    printf("--------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tFASE DE PREPARACAO\n");
    printf("--------------------------------------------------------------------------------------\n\n");
    
    //Carrega ficheiro dos espacos
    espaco = carregaEspaco(espaco,&totEsp);
    //Caso exista algum erro na abertura ou verificações, programa termina como indicado no enunciado
    if(espaco == NULL)
        return 0;
    if(verificaLigacao(espaco,totEsp) == 0)
        return 0;
    if(verificaID(espaco,totEsp) == 0)
              return 0; 
    
    //Mostra ficheiro de espacos aberto
    printf("_____________________________________________________________________________________________\n");
    printf("\t\t\t\t    --->ESPACOS<---\n\n");
    imprime_espaco(espaco,totEsp);
    printf("\n_____________________________________________________________________________________________\n");
    
    int arrEsp[totEsp];
    for(int i = 0; i < totEsp; i++){
        arrEsp[i]=espaco[i].capacidade;
    } 
        
    printf("\nIndique o ficheiro de pessoas a Utilizar: ");
    scanf("%s",fichPess);
    //Carrega ficheiro das pessoas
    listaP = carregaPessoas(fichPess);
    //Caso exista algum erro na abertura ou verificações, programa termina como indicado no enunciado
    if(listaP == NULL){
        return 0;
    }
    if(verificaDadosPessoas(listaP) == 0){
        printf("\nOs dados das pessoas estao incorretos, programa vai terminar..\n");
        return 0;
    }
    //Mostra ficheiro das pessoas aberto
    printf("______________________________________________________________________________________________\n");
    printf("\t\t\t\tPESSOAS\n");
    imprime_pessoas(listaP);
    printf("\n______________________________________________________________________________________________\n");
    
    //Distribui pessoas pelos locais
    listaPN = distribui_Pessoas(listaP,espaco,totEsp,&totPessoas);
    if(listaPN == NULL){
        printf("\nErro na distribuicao das pessoas...\n");
        return 0;
    }
    ControlaCapacidade(listaPN,espaco,totEsp,arrEsp);
    //Fase de simulacao
    do {

            printf("\n\n\n\n--------------------------------------------------------------------------------------\n");
            printf("\t\t\t\tFASE DE SIMULACAO\n");
            printf("--------------------------------------------------------------------------------------\n\n");

            printf("1 - Avancar 1 iteracao na simulacao\n");
            printf("2 - Apresentar estatistica\n");
            printf("3 - Adicionar Doente\n");
            printf("4 - Transferir pessoas\n");
            printf("5 - Mostrar distribuicao atual das pessoas\n");
            printf("6 - Voltar atras entre 1 a 3 iteracoes: \n");
            printf("7 - Terminar simulacao\n");
            printf("8 - Sair do programa sem terminar simulacao...\n\n");
            do {
            printf("Insira uma das opcoes apresentadas: ");
            scanf("%d", &op); 
        }while (op < 1 || op > 8);
    switch(op)
    {   case 1: //Guarda iterações e certifica-se que guarda as últimas 3
                listaREC = carregaIteracao(listaREC,listaPN,&totPessoas);
                listaREC = Mantem3itera(listaREC);
                //Propagação do Vírus
                dissemina(listaPN,totEsp,espaco);
                prob_recup(listaPN); 
                dura_max_infe(listaPN);
                contIT++;//Contador para gerar dados para relatorio final
                break;
                
        case 2: //Apresentar estatistica
                apresenta_estatistica(listaPN,espaco,totEsp,totPessoas,verificador,contIT,contADC);
                break;
                
        case 3: //Insere doente no final
                listaPN = insere_doente_Final(listaPN,espaco,totEsp,&totPessoas);
                contADC++;
                break;
                
        case 4: //Transferir pessoas
                listaPN = tranfere_pessoas(listaPN,espaco,totEsp);
                break;
                
        case 5: //Mostrar distribuição das pessoas por espaços
                mostra_pessas_orde_esp(listaPN,espaco,totEsp);
                break;
                
        case 6: //Voltar atrás entre 1 a 3 iterações
                if(listaREC == NULL){
                printf("\nDe momento nao foi avancada ainda nenhuma iteracao...");
                break;
                }
                op1=0;
                while (toupper(op1) != 'S' && toupper(op1) != 'N'){
                    printf("\nPretende ver a lista atual das iteracoes recuperadas (S/N) ?  ");
                    scanf("%s", &op1);
                }
                if (toupper(op1) == 'S' )
                imprimeListaRecuperacao(listaREC,espaco,totEsp,arrEsp);
                
                listaPN = recuperaListaREC(listaREC, listaPN,&totPessoas,espaco,totEsp,arrEsp);
                
                break;
                
        case 7: //Terminar simulação
                verificador=1;
                apresenta_estatistica(listaPN,espaco,totEsp,totPessoas,verificador,contIT,contADC);
                gravaPessoas(listaPN,totPessoas);
                printf("\n\nSimulacao terminada !\n\n");
                return 0;
        case 8: //termina programa sem terminar simulação
                printf("\n\nSimulacao terminada !\n\n");
                return 0;
           
                
    }
    }while(op>=1 && op<8);
    
        free(espaco);
        liberta_lista(listaPN);
        liberta_lista(listaP);
        apagaListaInterna(listaREC);

    return (EXIT_SUCCESS);
}

