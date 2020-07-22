#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "guiche.h"

FilaCliente* initFila(FilaCliente* fila){

	fila->total_Cliente = 0;
	fila->tempo_espera = 0;
	fila->inicio = NULL;
	fila->fim = NULL;

	return fila;
}

void imprimefila (FilaCliente* fila ){
	tcliente* current = fila->inicio;
	printf("\t\tTempo de espera:%d\n", fila->tempo_espera);
	printf("\t\tTotal de clientes:%d\n", fila->total_Cliente);
	printf("\t\t-----------------------\n");
	while (current != NULL){
		printf("\t\tSenha:%d\n",current->senha);
		printf("\t\ttempo de atendimento: %d\n",current->tempo_atendimento);
		printf("\t\tPrioridade:%d\n", current->flag_prioridade);
		printf("\n");
		current = current->prox;
	}
	

}

tcliente* alocacliente(int tempo,int senha,int flag_prioridade) {
	tcliente* novo = (tcliente *)malloc(sizeof(tcliente));

	novo->tempo_atendimento = tempo;
	novo->senha = senha;
	novo->flag_prioridade = flag_prioridade;
	novo->prox = NULL;

	return novo;
}

void enfileirar(FilaCliente *fila, int tempo,int senha,int flag_prioridade){

	tcliente* novo = alocacliente(tempo,senha,flag_prioridade);
	
	if (fila->total_Cliente == 0){
		fila->inicio = novo;
		fila->fim = novo;
		fila->total_Cliente++;
		fila->tempo_espera += tempo;

	}
	else {
		fila->fim->prox = novo;
		fila->fim = novo;
		fila->total_Cliente++;
		fila->tempo_espera += tempo;
	}

}

bool eVazia(FilaCliente* fila){
	return fila->total_Cliente == 0;
}

void desenfileirar(FilaCliente *fila){

	if(eVazia(fila) == false){

		if(fila->inicio->prox == NULL){
			fila->inicio = NULL;
			fila->fim = NULL;
			fila->total_Cliente--;
		}
		else{
			fila->inicio = fila->inicio->prox;
			fila->total_Cliente--;
		}
	}

}

void limpar_fila(FilaCliente *fila){

	tcliente *current = fila->inicio;
	tcliente *anterior;
	
	while (current->prox != NULL){
		anterior = current;
		current = current->prox;
		free(anterior);
	}
	free(current);
}