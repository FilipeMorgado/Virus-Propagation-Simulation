/*
    // Trabalho Pratico Programacao - LEI
   // DEIS-ISEC 2019-2020
 * 
 -> Criado por: Filipe Daniel Ramos Morgado
 -> Número de aluno: a2019137625
 
 */
#ifndef STRUCT_SIM_H
#define STRUCT_SIM_H

//Funções usadas no proceso de simulação
void apresenta_estatistica(ppessoa listaPN,local espaco[], int totEsp,int totPessoas,int verificador,int contIT,int contADC);

//Inserir Doente
ppessoa insere_doente_Final(ppessoa p,local espaco[],int totEsp,int* totPessoas);
void adiciona_doente(ppessoa novo,local espaco[],int totEsp,ppessoa aux);
int verifica_existe_nome(ppessoa p,char*nome);
int VerificaSemEspaco(local espaco[],int totEsp);

//Transferencia de pessoas
ppessoa verifica_espaco(ppessoa p,int totEsp,local espaco[]);
ppessoa tranfere_pessoas(ppessoa p,local espaco[],int totEsp);
int verifica_orig_destino(int origem,int destino,local espaco[],int totEsp);
void atualizaEspacoTranfere(plocal espaco,int totEsp,int origem,int destino,int npess);

void verifica_dados_transf(int* origem,int* destino,int* npess,int totEsp,local espaco[],int flag);
void atualiza_espacos(ppessoa p,int npess,int ArrDosAleatori[],int destino);

//Gravação em ficheiros .txt 
void gravaPessoas(ppessoa p,int totPessoas);
void gravaRelatorio(ppessoa p,local espaco[],int totPessoas,int totEsp,int estado[],int idsala[],int distr[],int contIT,int contADC,float taxa_saudavel,float taxa_imune,float taxa_infetado);


#endif /* STRUCT_SIM_H */

