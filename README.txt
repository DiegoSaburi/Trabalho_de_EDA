====================== READ ME ======================
-> TAD's utilizados:

Para formar os guiches foi utilizado uma fila simples-
mente encadeada, sendo cada guiche um n�. Cada um des-
ses n�s tem uma fila cujos n�s s�o os clientes.
Com essa "lista de filas" podemos fazer um simula��o
em ciclos, simulando o tempo real. Enquanto novos cli-
entes s�o alocados, os guiches realizam o atendimento.

->Funcionamento:

O programa simula o atendimento de 7 clientes numa
lista de 3 guiches, sendo o ultimo deles preferencial.

Os clientes s�o gerados aleat�riamente for fun��es
rand() e por multiplica��es da mesma(para aumentar
a aleatoriedade).

Os tempo de atendimento de cada tipo depende do n�-
mero de guiches. Dessa forma podemos garantir que sem-
pre haver� algum cliente em espera numa fila de um
guiche (Isso caso todos os clientes escolham a op��o
com menor tempo de atendimento).

Os limites de tempo total de atendimento, para que
o guiche entre em descanso, tamb�m dependem do numero
de guiches. Dessa forma fazemos com que as pausas sejam
proporcionais ao numero de guiches minimizando situa��es
adversas.

->Execu��o:

Para executar, basta compilar e executar no proprio terminal.
Por exemplo podemos usar o seguinte comando:
gcc -o executar main.c cliente.c guiche.c (para compilar)
executar(para executar)
============================================================