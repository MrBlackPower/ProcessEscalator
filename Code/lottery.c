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
int slotLott;


//=====Funcoes Auxiliares=====
int drawRandomTicket(int ticketNumber){
    return 1 + (rand() % ticketNumber);
}

int getTotalTickets(Process* plist){
    int total = 0;
    Process* p = plist;
    LotterySchedParams *lotteryProcess;
    while(p != NULL){
        lotteryProcess = processGetSchedParams(p);
        if(processGetStatus(p) == PROC_READY)
            total = total + lotteryProcess->num_tickets;
        p = processGetNext(p);
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
	SchedInfo *si = malloc(sizeof(SchedInfo));
    strcpy(si->name,lottName);
    si->initParamsFn = lottInitSchedParams;
    si->scheduleFn = lottSchedule;
    si->releaseParamsFn = lottReleaseParams;
    slotLott = schedRegisterScheduler(si);

}

//Inicializa os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' associado ao slot de Lottery
void lottInitSchedParams(Process *p, void *params) {
	//...
	processSetSchedParams(p,params);
	processSetSchedSlot(p,slotLott);

}

//Retorna o proximo processo a obter a CPU, conforme o algortimo Lottery
Process* lottSchedule(Process *plist) {
	//...
	Process* nextProcess = plist;
    int randomTicket = drawRandomTicket(getTotalTickets(plist));// retorna um numero aleatorio variando de 1 até o numero total de tickets
    LotterySchedParams *lotteryProcess;
    int processTickets = 0;
    while(nextProcess != NULL){
        if(processGetStatus(nextProcess) == PROC_READY){// apenas processos prontos
            lotteryProcess = processGetSchedParams(nextProcess);
            processTickets = processTickets + lotteryProcess->num_tickets;
            if(processTickets >= randomTicket){
                break;
            }
        }
        nextProcess = processGetNext(nextProcess);
    }
	return nextProcess;
}

//Libera os parametros de escalonamento de um processo p, chamada
//normalmente quando o processo e' desassociado do slot de Lottery
//Retorna o numero do slot ao qual o processo estava associado
int lottReleaseParams(Process *p) {
	//...
	int slot = processGetSchedSlot(p);

	processSetSchedParams(p,NULL);
	processSetSchedSlot(p,-1);
	return slot;
}

//Transfere certo numero de tickets do processo src para o processo dst.
//Retorna o numero de tickets efetivamente transfeirdos (pode ser menos)
int lottTransferTickets(Process *src, Process *dst, int tickets) {
	//...
	LotterySchedParams *srcLsp,*dstLsp;
	srcLsp = processGetSchedParams(src);
	dstLsp = processGetSchedParams(dst);

	if(srcLsp->num_tickets == 1)//caso possua apenas um ticket
        return 0;
    else if(srcLsp->num_tickets < tickets){//caso o numero de tickets pedidos seja maior que o numero de tickets de src
        tickets = srcLsp->num_tickets - 1;
    }

    srcLsp->num_tickets = srcLsp->num_tickets - tickets;
    dstLsp->num_tickets = dstLsp->num_tickets + tickets;

    processSetSchedParams(src,srcLsp);
    processSetSchedParams(dst,dstLsp);

    return tickets;
}

