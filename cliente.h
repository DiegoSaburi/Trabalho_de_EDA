#ifndef __CLIENTE__
#define __CLIENTE__
#include <stdbool.h>
typedef struct cliente{
	int senha;
	int tempo_atendimento;
	int flag_prioridade;
	struct cliente* prox;
} tcliente;

typedef struct {
	tcliente* inicio;
	tcliente* fim;
	int total_Cliente;
	int tempo_espera;
} FilaCliente;

FilaCliente* initFila(FilaCliente* fila);

void senha(int tipo_atendimento, tcliente* novo);

void enfileirar(FilaCliente *fila, int tempo, int senha,int flag_prioridade);

void desenfileirar(FilaCliente *fila);

bool eVazia(FilaCliente* f);

void limpar_fila(FilaCliente *f);

void imprimefila(FilaCliente* fila);

tcliente* alocacliente(int tempo,int senha,int flag_prioridade);

#endif