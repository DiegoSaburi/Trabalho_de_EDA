#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "guiche.h"

tguiche* alocaguiche(int i, int panico, int tempo, int flag_prioridade){

	tguiche* novo = (tguiche *)malloc(sizeof(tguiche));
		novo->index = i;
		novo->panico = panico;
		novo->tempo_atendimento = tempo;
		novo->clientes_atendidos = 0;
		novo->prox = NULL;
		novo->tempo_descanso = 0;
		novo->tempo_total = 0;
		novo->flag_prioridade = flag_prioridade;
		initFila(&novo->cliente_atual);

	return novo;
	
}

void initLista(ListaGuiche* L) {
	L->inicio = NULL;
	L->total_guiche = 0;
	L->flag_pausa = 0;
	
}

void limpaLista(ListaGuiche L) {

	tguiche *current = L.inicio;
	tguiche *anterior;
	
	while (current != NULL){
		anterior = current;
		current = current->prox;
		free(anterior);
	}
	free(current);
}

int tamLista(ListaGuiche L) {
    return L.total_guiche;
}

bool insereInicioLista(ListaGuiche* L,int panico, int tempo,int flag_prioridade) {

	tguiche* new_inicio = alocaguiche(0,panico,tempo,flag_prioridade);
	tguiche* current;
	new_inicio->prox = L->inicio;
	L->inicio = new_inicio;

	L->total_guiche++;
	current = L->inicio;

	while (current != NULL){
		current->index++;
		current = current->prox;
	}
	return true;
}

void insereFinalLista(ListaGuiche* L, int panico, int tempo, int flag_prioridade) {

	tguiche* current = L->inicio;
	if (current == NULL){
		current = alocaguiche(1 ,panico, tempo,flag_prioridade);
	}
	while(current->prox != NULL ){
		current = current->prox;
	}
	current->prox = alocaguiche(L->total_guiche,panico,tempo, flag_prioridade);
	L->total_guiche++;
}

void imprimeguiche (ListaGuiche* L){
	tguiche* current = L->inicio;
	printf("===================================================================\n");
	printf("========================= relatorio ===============================\n");
	printf("===================================================================\n\n");
	while (current != NULL)	{
		printf("\t================ Guiche %d ================\n", current->index);
		printf("\tTempo total de atendimento:%d\n",current->tempo_total);
		printf("\tPrioridade:%d\n", current->flag_prioridade);
		printf("\tClientes atendidos:%d\n",current->clientes_atendidos);
		printf("\tTempo para acabar atendimento:%d\n",current->tempo_atendimento);
		printf("\tTempo percorrido em descanso:%d\n",current->tempo_descanso);
		printf("\t\t--- Fila de clientes ---\n");
		imprimefila(&current->cliente_atual);
		current = current->prox;
	}
	
}

bool removeGuiche(ListaGuiche* L, int i) {
	tguiche* current;
	bool flag = false;
	while (flag == false && current != NULL){
		if (current->prox->index == i){
			current->prox = current->prox->prox;
			flag = true;
		}
		current = current->prox;
	}
	while(current != NULL && flag == true){
		current->index--;
		current = current->prox;
	}

	return flag;

}
