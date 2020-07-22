#ifndef __GUICHE__
#define __GUICHE__
#include <stdbool.h>
#include "cliente.h"

typedef struct guiche{
	int index;//numero do guiche
	int panico;//botao de panico(1-ativado 0-desativado)
	int tempo_atendimento;//tempo em atendimento
	int clientes_atendidos;//total de clientes atendidos
	int tempo_total;//total de tempo atendido
	int flag_prioridade;//prioridade (1-sim 0-não)
	FilaCliente cliente_atual;//Fila de clientes
	int tempo_descanso;//tempo de descanso
	struct guiche *prox;//proximo guiche
} tguiche;

typedef struct {
	int flag_pausa;//aux para dizer se existe algum guiche em panico ou pausa
	tguiche* inicio;//primeiro guiche
	int total_guiche;//total de guiches
} ListaGuiche;

tguiche* alocaguiche(int i, int panico, int tempo,int flag_prioridade);

void imprimeguiche(ListaGuiche* L);

void limpaLista(ListaGuiche L);

void initLista(ListaGuiche* L);

int tamLista(ListaGuiche L);

void insereFinalLista(ListaGuiche* L, int panico, int tempo, int flag_prioridade);

bool insereInicioLista(ListaGuiche* L, int panico, int tempo, int flag_prioridade);

bool removeElemento(ListaGuiche* L, int valor);

#endif
