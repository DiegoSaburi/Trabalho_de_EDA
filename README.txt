====================== READ ME ======================
-> TAD's utilizados:

Para formar os guiches foi utilizado uma fila simples-
mente encadeada, sendo cada guiche um nó. Cada um des-
ses nós tem uma fila cujos nós são os clientes.
Com essa "lista de filas" podemos fazer um simulação
em ciclos, simulando o tempo real. Enquanto novos cli-
entes são alocados, os guiches realizam o atendimento.

->Funcionamento:

O programa simula o atendimento de 7 clientes numa
lista de 3 guiches, sendo o ultimo deles preferencial.

Os clientes são gerados aleatóriamente for funções
rand() e por multiplicações da mesma(para aumentar
a aleatoriedade).

Os tempo de atendimento de cada tipo depende do nú-
mero de guiches. Dessa forma podemos garantir que sem-
pre haverá algum cliente em espera numa fila de um
guiche (Isso caso todos os clientes escolham a opção
com menor tempo de atendimento).

Os limites de tempo total de atendimento, para que
o guiche entre em descanso, também dependem do numero
de guiches. Dessa forma fazemos com que as pausas sejam
proporcionais ao numero de guiches minimizando situações
adversas.

->Execução:

Para executar, basta compilar e executar no proprio terminal.
Por exemplo podemos usar o seguinte comando:
gcc -o executar main.c cliente.c guiche.c (para compilar)
executar(para executar)
============================================================