/*
*  lottery.c - Implementacao do algoritmo Lottery Scheduling e sua API
*
*  Autores: SUPER_PROGRAMADORES_C
*  Projeto: Trabalho Pratico I - Sistemas Operacionais
*  Organizacao: Universidade Federal de Juiz de Fora
*  Departamento: Dep. Ciencia da Computacao
*
*
*/

#include "lottery.h"
#include <stdio.h>
#include <string.h>

//Nome unico do algoritmo. Deve ter 4 caracteres.
const char lottName[]="LOTT";

//=====Funcoes Auxiliares=====
int drawRandomTicket(int ticketNumber){
    return 1 + rand() % ticketNumber;
}

int generateRandomTicket(){
    return 1 + rand();
}

int getTotalTickets(Process* plist){
    int total = 0;
    while(plist != NULL){
        //total += ;

    }
    return total;
}


//=====Funcoes da API=====

//Funcao chamada pela inicializacao do S.O. para a incializacao do escalonador
//conforme o algoritmo Lottery Scheduling
//Deve envolver a inicializacao de possiveis parametros gerais
//Deve envolver o registro do algoritmo junto ao escalonador
void lottInitSchedInfo() {
	//...
	SchedInfo* si;
    strcpy(si->name,lottName);
}

//Inicializa os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' associado ao slot de Lottery
void lottInitSchedParams(Process *p, void *params) {
	//...
    SchedInfo* si;
    si->initParamsFn(p,params);
}

//Retorna o proximo processo a obter a CPU, conforme o algortimo Lottery
Process* lottSchedule(Process *plist) {
	//...
	SchedInfo* p;

	Process* nextProcess = plist;
    int randomTicket = drawRandomTicket(10);
    int loop = 1;
    while(loop){
        //randomTicket = randomTicket - plist;
        if(randomTicket <= 0){
            //nextProcess = plist;
            loop = 0;
        }
    }
	return nextProcess;
}

//Libera os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' desassociado do slot de Lottery
//Retorna o numero do slot ao qual o processo estava associado
int lottReleaseParams(Process *p) {
	//...
	return 0;
}

//Transfere certo numero de tickets do processo src para o processo dst.
//Retorna o numero de tickets efetivamente transfeirdos (pode ser menos)
int lottTransferTickets(Process *src, Process *dst, int tickets) {
	//...
	return 0;
}
