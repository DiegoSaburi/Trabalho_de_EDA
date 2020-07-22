#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "guiche.h"
#include "cliente.h"
//ALUNO: Diego Conceição Bianchi Saburi
//MATRÍCULA: 217115857

void probabilidade_panico (ListaGuiche* guiches) {
	/* Determina a probabilidade do 
		botão de panico ser ativado*/

	tguiche* current = guiches->inicio;
	int n;
	while(current->prox != NULL){

		n = (rand()*rand())%100;

		if (n > 85 && n <= 99)// 15% de chance
			current->panico = 1;
		else
			current->panico = 0;
		
		current = current->prox;
	}

	n = (rand()*rand())%100;

	if (n > 85 && n <= 99)
		current->panico = 1;
	else
		current->panico = 0;
	
}

int probabilidade_preferencia () {
	/* Determina a probabilidade do
		cliente ser prioridade ou não*/
	int n = (rand()*rand())%100;

		if (n > 70 && n <= 99)//30% de chance
			return 1;
		else
			return 0;
}

void calcula_tempo_atendimento (ListaGuiche* guiches){
	/*Quando um novo cliente é adicionado,
	  essa função certifica que o tempo de
	  atendimento do guiche será atualizado.

	  ->É ativada se somente se o guiche
	  não atendeu ninguem ainda ou voltou do
	  tempo de descanso.*/

	tguiche * current_guiche = guiches->inicio;
	tcliente * current_cliente = current_guiche->cliente_atual.inicio;

	while (current_guiche->prox != NULL){
		if(current_guiche->tempo_atendimento==0&&current_cliente!=NULL&&current_guiche->clientes_atendidos%5==0){
			//-> Não atendeu ninguem ou voltou do descanso
			printf("\nSenha %d dirija-se ao guiche de numero %d\n\n", current_cliente->senha,current_guiche->index);//chama o cliente
			current_guiche->tempo_atendimento = current_cliente->tempo_atendimento;//atualiza o tempo de atendimento do guiche
			current_guiche->clientes_atendidos++;//conta o numero de clientes atendidos
		}
		else if(current_cliente != NULL){
			if(current_guiche->tempo_atendimento != current_cliente->tempo_atendimento ){
				//->Caso algum cliente seja realocado para algum guiche que ja tenha atendido alguem(evita bugs do programa)
				printf("\nSenha %d dirija-se ao guiche de numero %d\n\n", current_cliente->senha,current_guiche->index);//chama o cliente
				current_guiche->tempo_atendimento = current_cliente->tempo_atendimento;//atualiza o tempo de atendimento do guiche
				current_guiche->clientes_atendidos++;//conta o numero de clientes atendidos
			}
		}
		current_guiche = current_guiche->prox;
		current_cliente = current_guiche->cliente_atual.inicio;
	}
		if(current_guiche->tempo_atendimento==0&&current_cliente!=NULL&&current_guiche->clientes_atendidos%5==0){
			//-> Não atendeu ninguem ou voltou do descanso
			printf("\nSenha %d dirija-se ao guiche de numero %d\n\n", current_cliente->senha,current_guiche->index);//chama o cliente
			current_guiche->tempo_atendimento = current_cliente->tempo_atendimento;//atualiza o tempo de atendimento do guiche
			current_guiche->clientes_atendidos++;//conta o numero de clientes atendidos
		}

		else if(current_cliente != NULL){
			if(current_guiche->tempo_atendimento != current_cliente->tempo_atendimento){
				//->Caso algum cliente seja realocado para algum guiche que ja tenha atendido alguem(evita bugs do programa)
				printf("\nSenha %d dirija-se ao guiche de numero %d\n\n", current_cliente->senha,current_guiche->index);//chama o cliente
				current_guiche->tempo_atendimento = current_cliente->tempo_atendimento;//atualiza o tempo de atendimento do guiche
				current_guiche->clientes_atendidos++;//conta o numero de clientes atendidos
			}
		}
}

void proximocliente (ListaGuiche* guiches){
	/* Essa função chama o proximo cliente
	   quando o guiche termina de atender
	   o cliente atual.

	   ->Considera-se o primeiro cliente da
	   fila como sendo o cliente atualmente
	   atendido.
	   ->Só faz a chamada da senha quando
	   o atendimento atual acabar.
	   -> Se não tiver mais niguem na fila,
	   o guiche estará livre.*/

	tguiche* current_guiche = guiches->inicio;
	tcliente* current_cliente = current_guiche->cliente_atual.inicio;

	while(current_guiche->prox != NULL){
		if(current_guiche->tempo_atendimento == 0 && eVazia(&current_guiche->cliente_atual) == false && current_cliente->prox != NULL){
			current_cliente = current_cliente->prox;
			//-> Caso tenha um proximo cliente na fila
			printf("\nSenha %d dirija-se ao guiche de numero %d\n\n", current_cliente->senha,current_guiche->index);//chama o cliente
			desenfileirar(&current_guiche->cliente_atual);//retira o primeiro da fila (que é o que estava sendo atendido)
			current_guiche->clientes_atendidos++;//aumenta o numero de clientes atendidos
			current_guiche->tempo_atendimento = current_cliente->tempo_atendimento;//atualiza o tempo de atendimento do guiche
			}
		else if (current_guiche->tempo_atendimento == 0 && eVazia(&current_guiche->cliente_atual) == false){
			//-> Caso não tenha um proximo cliente na fila
			desenfileirar(&current_guiche->cliente_atual);//retira o primeiro da fila (que é o que estava sendo atendido)
			printf("\nGuiche %d livre.\n\n", current_guiche->index);//Diz que o guiche está sem fila
		}
		current_guiche = current_guiche->prox;
		current_cliente = current_guiche->cliente_atual.inicio;
	}
	
	if(current_guiche->tempo_atendimento == 0 && current_guiche->cliente_atual.inicio != NULL && current_cliente->prox != NULL){
			current_cliente = current_cliente->prox;
			//-> Caso tenha um proximo cliente na fila
			printf("\nSenha %d dirija-se ao guiche de numero %d\n\n", current_cliente->senha,current_guiche->index);//chama o cliente
			desenfileirar(&current_guiche->cliente_atual);//retira o primeiro da fila (que é o que estava sendo atendido)
			current_guiche->clientes_atendidos++;//aumenta o numero de clientes atendidos
			current_guiche->tempo_atendimento = current_cliente->tempo_atendimento;//Diz que o guiche está sem fila
			}
	else if (current_guiche->tempo_atendimento == 0 && current_guiche->cliente_atual.inicio != NULL){
		//-> Caso não tenha um proximo cliente na fila
		desenfileirar(&current_guiche->cliente_atual);//retira o primeiro da fila (que é o que estava sendo atendido)
		printf("\nGuiche %d livre.\n\n", current_guiche->index);
	}
}

bool falsoclock (ListaGuiche* guiches){
	/*Essa função "dita" o tempo do
	  programa, funcionando como um
	  guiche em "tempo real". Cada
	  Loop de execução de um while
	  (ou for) é considerado como
	  um ciclo.
	  
	  -> Ela retorna true caso todos
	  os guiches estejam vazios, depois
	  o programa pode ser encerrado.*/

	bool flag = false;
	tguiche* current_guiche = guiches->inicio;
	tcliente* current_cliente;

	while(current_guiche->prox != NULL){
		if(current_guiche->tempo_descanso > 0){
			current_guiche->tempo_descanso--;//Decrementa o tempo de descanso
			if(current_guiche->tempo_descanso == 0)
				guiches->flag_pausa = 0;//se decrementar e dar zero, reseta flag_pausa
		}

		if(current_guiche->cliente_atual.inicio != NULL){
			current_cliente = current_guiche->cliente_atual.inicio;
			if(current_cliente->tempo_atendimento > 0){
				current_cliente->tempo_atendimento--;//decrementa o tempo de atendimento do cliente atual
			}
		}

		if(current_guiche->tempo_atendimento > 0){
			current_guiche->tempo_atendimento--;//Decrementa o tempo de atendimento do guiche
			current_guiche->tempo_total++;//aumenta tempo total
			flag = true;
		}
		if(current_guiche->cliente_atual.tempo_espera > 0){
			current_guiche->cliente_atual.tempo_espera--;//Decrementa o tempo de espera da fila
			flag = true;
		}

		current_guiche = current_guiche->prox;
	}

	if(current_guiche->tempo_descanso > 0){
		current_guiche->tempo_descanso--;//Decrementa o tempo de descanso
		if (current_guiche->tempo_descanso == 0)
			guiches->flag_pausa = 0;//se decrementar e dar zero, reseta flag_pausa
		}
		
	if(current_guiche->cliente_atual.inicio != NULL){
		current_cliente = current_guiche->cliente_atual.inicio;
		if(current_cliente->tempo_atendimento > 0){
			current_cliente->tempo_atendimento--;//decrementa o tempo de atendimento do cliente atual
		}
	}

	if(current_guiche->tempo_atendimento > 0){
			current_guiche->tempo_atendimento--;//Decrementa o tempo de atendimento do guiche
			current_guiche->tempo_total++;//aumenta tempo total
			flag = true;
		}
	if(current_guiche->cliente_atual.tempo_espera > 0){
		current_guiche->cliente_atual.tempo_espera--;//Decrementa o tempo de espera da fila
		flag = true;
	}

	return flag;
}

tguiche* menortempo_com_p (ListaGuiche* Guiche, int prioridade){
	/*Essa função retorna o guiche
	  com menor tempo de espera para
	  o novo cliente ser alocado.

	  ->se o guiche prioritario
	  estiver vazio, clientes sem
	  prioridade poderão entrar.

	  ->Cliente prioritário sempre 
	  entrará no guiche de menor
	  tempo de espera.*/

	tguiche* current = Guiche->inicio;
	tguiche* menor = current;

	while (current->prox != NULL ){

		if (menor->tempo_descanso > 0)
			menor = current->prox;
			/*->Garante que, caso o guiche esteja em
			   descanso, ele n será o de menor tempo.*/
		if (current->flag_prioridade == 0){
			if (current->cliente_atual.tempo_espera <= menor->cliente_atual.tempo_espera && current->tempo_descanso == 0)
				menor = current;
		}
		else{
			if (prioridade == 1){
				if (current->cliente_atual.tempo_espera <= menor->cliente_atual.tempo_espera && current->tempo_descanso == 0){
					menor = current;
				}
			}
			else if (current->cliente_atual.total_Cliente == 0 && current->tempo_descanso == 0 && current->cliente_atual.tempo_espera < menor->cliente_atual.tempo_espera)
				menor = current;//Caso o guiche prioridade esteja vazio
		}
		current = current->prox;
	}
		
	if (current->flag_prioridade == 0){
		if (current->cliente_atual.tempo_espera <= menor->cliente_atual.tempo_espera && current->tempo_descanso == 0)
			menor = current;
	}
	else{
		if (prioridade == 1){
			if (current->cliente_atual.tempo_espera <= menor->cliente_atual.tempo_espera && current->tempo_descanso == 0){
				menor = current;
			}
		}
		else if (current->cliente_atual.total_Cliente == 0 && current->tempo_descanso == 0 && current->cliente_atual.tempo_espera < menor->cliente_atual.tempo_espera)
			menor = current;
		}

	return menor;
}

tguiche* menortempo(ListaGuiche* Guiche){
	/*Essa função retorna o guiche
	  com menor tempo de espera
	  independente da prioridade
	  (funciona como um bubble sort).
	  
	  -> Só é ativada no caso de
	  panico ativado ou tempo de
	  espera requerido.*/
	
	tguiche* current = Guiche->inicio;
	tguiche* menor = current;

	while (current->prox != NULL){
		if (current->cliente_atual.tempo_espera <= menor->cliente_atual.tempo_espera && current->tempo_descanso == 0)
			menor = current;
		current = current->prox;
	}
		
	if (current->cliente_atual.tempo_espera <= menor->cliente_atual.tempo_espera && current->tempo_descanso == 0)
		menor = current;
	
	return menor;
}

void panico_limite(ListaGuiche* guiches){
	/*Essa função verifica a ativação
	  do botão de panico ou a necessidade
	  de pausa por parte dos guiches. Se
	  a condição for satisfeita, ela já 
	  faz a alocação dos clientes da fila
	  do guiche para os outros guiches.
	  
	  ->O tempo total atendido necessário
	  para se requerir descanso depende do
	  numero de guiches.
	  ->O tempo de descanso (caso panico seja
	  ativado ou descanso seja requerido),
	é de 3 ciclos.
	  ->Caso o guiche atenda 5 clientes ou
	  tenha um tempo total atendido de 
	  10*totl_guiches cilos,ele entra em 
	  dencanso.*/

	tguiche* current_guiche = guiches->inicio;
	tcliente* current_cliente;

	while(current_guiche->prox != NULL){
		if (guiches->flag_pausa == 1)
			return;// Garante que apenas um guiche esteja em pausa ou em panico

		if(current_guiche->panico == 1 && current_guiche->clientes_atendidos > 1 && current_guiche->tempo_descanso == 0 && current_guiche->cliente_atual.total_Cliente != 0){

			printf("======================= Botao de panico ativado =======================\n");
			printf("\tO guiche de numero %d ativou o botao de panico\n",current_guiche->index);
			//Atualizamos os dados do guiche
			current_guiche->tempo_descanso = 3;
			current_guiche->panico = 0;
			guiches->flag_pausa = 1;
			current_guiche->tempo_atendimento = 0;

			//Consideramos que o atendimento do cliente atual já acabou
			desenfileirar(&current_guiche->cliente_atual);

			//================================================ realocação dos clientes =================================================
			if (eVazia(&current_guiche->cliente_atual) == false){
				current_cliente = current_guiche->cliente_atual.inicio;

				while (current_cliente->prox != NULL){
					//-> Enfileiramos e passamos para o proximo cliente antes de desenfileirar para evitar erros
					enfileirar(&menortempo(guiches)->cliente_atual,current_cliente->tempo_atendimento,current_cliente->senha,current_cliente->flag_prioridade);
					current_cliente = current_cliente->prox;
					desenfileirar(&current_guiche->cliente_atual);
				}
				enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento,current_cliente->senha,current_cliente->flag_prioridade);
				desenfileirar(&current_guiche->cliente_atual);
			}
			current_guiche->cliente_atual.tempo_espera = 0;
			//============================================================================================================================
		}

		else if((current_guiche->clientes_atendidos%5 == 0 || current_guiche->tempo_total%(guiches->total_guiche*10) == 0) && current_guiche->clientes_atendidos > 1 && current_guiche->cliente_atual.total_Cliente != 0){

			printf("======================= Tempo de descanso requerido =======================\n");
			printf("\tO guiche de numero %d entrou em descanso\n",current_guiche->index);
			//Atualizamos os dados do guiche
			current_guiche->tempo_descanso = 3;
			current_guiche->tempo_atendimento = 0;
			guiches->flag_pausa = 1;

			//Consideramos que o atendimento do cliente atual já acabou
			desenfileirar(&current_guiche->cliente_atual);

			//================================================ realocação dos clientes =================================================
			if (eVazia(&current_guiche->cliente_atual) == false){
				current_cliente = current_guiche->cliente_atual.inicio;

				while (current_cliente->prox != NULL){
					//-> Enfileiramos e passamos para o proximo cliente antes de desenfileirar para evitar erros
					enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento, current_cliente->senha,current_cliente->flag_prioridade);
					current_cliente = current_cliente->prox;
					desenfileirar(&current_guiche->cliente_atual);
				}
				enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento, current_cliente->senha,current_cliente->flag_prioridade);
				desenfileirar(&current_guiche->cliente_atual);
			}
			current_guiche->cliente_atual.tempo_espera = 0;
			//============================================================================================================================
		}
		current_guiche = current_guiche->prox;
		current_cliente = current_guiche->cliente_atual.inicio;
	}


	if (guiches->flag_pausa == 1)
		return;// Garante que apenas um guiche esteja em pausa ou em panico

	if(current_guiche->panico == 1 && current_guiche->clientes_atendidos > 1 && current_guiche->tempo_descanso == 0 && current_guiche->cliente_atual.total_Cliente != 0){
		printf("======================= Botao de panico ativado =======================\n");
		printf("\tO guiche de numero %d ativou o botao de panico\n",current_guiche->index);
		//Atualizamos os dados do guiche
		current_guiche->tempo_descanso = 3;
		current_guiche->panico = 0;
		current_guiche->tempo_atendimento = 0;
		guiches->flag_pausa = 1;

		//Consideramos que o atendimento do cliente atual já acabou		
		desenfileirar(&current_guiche->cliente_atual);

		//================================================ realocação dos clientes =================================================
		if (eVazia(&current_guiche->cliente_atual) == false){
			current_cliente = current_guiche->cliente_atual.inicio;

			while (current_cliente->prox != NULL){
				//-> Enfileiramos e passamos para o proximo cliente antes de desenfileirar para evitar erros
				enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento,current_cliente->senha,current_cliente->flag_prioridade);
				current_cliente = current_cliente->prox;
				desenfileirar(&current_guiche->cliente_atual);
			}
			enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento,current_cliente->senha,current_cliente->flag_prioridade);
			desenfileirar(&current_guiche->cliente_atual);
		}
		current_guiche->cliente_atual.tempo_espera = 0;
		//============================================================================================================================
	}
	
	else if((current_guiche->clientes_atendidos%5 == 0 || current_guiche->tempo_total%(guiches->total_guiche*10) == 0)	&& current_guiche->clientes_atendidos > 1 && current_guiche->cliente_atual.total_Cliente != 0){

		printf("======================= Tempo de descanso requerido =======================\n");
		printf("\tO guiche de numero %d entrou em descanso\n",current_guiche->index);
		//Atualizamos os dados do guiche
		current_guiche->tempo_descanso = 3;
		current_guiche->tempo_atendimento = 0;
		guiches->flag_pausa = 1;

		//Consideramos que o atendimento do cliente atual já acabou
		desenfileirar(&current_guiche->cliente_atual);

		//================================================ realocação dos clientes =================================================
		if (eVazia(&current_guiche->cliente_atual) == false){
			current_cliente = current_guiche->cliente_atual.inicio;

			while (current_cliente->prox != NULL){
				//-> Enfileiramos e passamos para o proximo cliente antes de desenfileirar para evitar erros
				enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento, current_cliente->senha,current_cliente->flag_prioridade);
				current_cliente = current_cliente->prox;
				desenfileirar(&current_guiche->cliente_atual);
			}
			enfileirar(&menortempo(guiches)->cliente_atual, current_cliente->tempo_atendimento, current_cliente->senha,current_cliente->flag_prioridade);
			desenfileirar(&current_guiche->cliente_atual);
		}
		current_guiche->cliente_atual.tempo_espera = 0;
		//============================================================================================================================
	}

}

int main (){

	int i,senha,flag_prioridade, tipo_atendiento;

	int total_guiches = 3, total_clientes = 7;

	ListaGuiche Guiche;//lista de guiches
	bool guiches_livres = true;//Flag para verificar o momento do programa terminar
	tguiche* menor_tempo_guiche;//Flag para saber o guiche de menor tempo de espera

	//================================= alocação dos guiches ======================================
	initLista(&Guiche);
	insereInicioLista(&Guiche,1,0,1);

	for (i = 1; i < total_guiches ; i++){
		insereInicioLista(&Guiche, 0, 0,0);
	}
	//=============================================================================================
	srand(time(0));

	for (i = 0; i < total_clientes ; i++){
		tipo_atendiento = 1 + abs((((rand()*rand())%100)*rand()))%3;//tipo de atendimento randomizado
		//o tempo de atendimento é baseado na seguinte foruma: tipo_atendimento*total_guiches
		flag_prioridade = probabilidade_preferencia();//probabilidade de ser prioriade sendo 30%
		senha = abs((((rand()*rand())%100)*rand()))%1000;//senha randomizada

		printf("\n=========================== novo cliente ==================================\n");
		printf("\t\tSenha do cliente numero %d: %d\n", i+1, senha);
		printf("============================================================================\n");
		
		menor_tempo_guiche = menortempo_com_p(&Guiche,flag_prioridade);//retorna o guiche com a fila de menor tempo de espera
		enfileirar(&menor_tempo_guiche->cliente_atual, total_guiches*tipo_atendiento,senha,flag_prioridade);/*enfileira o cliente na fila
																											  do respectivo guichê*/
		calcula_tempo_atendimento(&Guiche);// atualiza os guiches inicialmente sem clientes

		proximocliente(&Guiche);// aloca os proximos clientes quando o atendimento atual terminar
		imprimeguiche(&Guiche);//imprime um relatorio com as informaçoes de todos os guiches, de suas respectivas filas e clientes

		guiches_livres = falsoclock(&Guiche);//atualiza todas as variáveis que ditam o "tempo" (tempo de espera do guiche e de atendimento)
		probabilidade_panico(&Guiche);//Atualiza a probabilidade de panico de cada guiche (15% de chance)
		panico_limite(&Guiche);//Verifica se o botão de panico foi ativado ou a necessedidade de pausa
	}

	while (guiches_livres == true){
		//Certifica que todos os clientes foram atendidos

		calcula_tempo_atendimento(&Guiche);

		proximocliente(&Guiche);
		imprimeguiche(&Guiche);
		guiches_livres = falsoclock(&Guiche);
		probabilidade_panico(&Guiche);
		panico_limite(&Guiche);
	}


}