Programação Paralela

# T3: Programação Paralela Multithread 
Pedro Langbecker Lima

Configurações básicas do computador: Processador dual core, i5 1.7 Ghz com 4 Gb RAM.

Pthreads

1 - Particionamento:

   		int wsize = dotdata.wsize;
   		int start = offset*wsize;
   		int end = start + wsize;

Consiste nas divisões do vetor onde as threads podem trabalhar. Cada thread possui um start e um end diferente para previnir conflitos entre os dados.

Comunicação:

   		pthread_mutex_lock (&mutexsum);
   		pthread_mutex_unlock (&mutexsum);

Satisfaz as dependências de atualizações nas variáveis em nível multithread. No caso dot_prod, os mutex geram exclusões mútuas para que somente uma thread por vez possa alterar o valor da variável dotdata.c.

Aglomeração:

	dotdata.c += mysum;

Junção das somas para realizar as somas parciais. No código, cada thread acrescenta sua variável a dotdata.c.


Mapeamento: 
	
	for (i = 0; i < nthreads; i++) {
      pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);}
	for (i = 0; i < nthreads; i++) {
      pthread_join(threads[i], NULL);   }

Etapa de criação das threads, bem como sua junção posteriormente. 



2 - No primeiro caso, com uma única thread com um vetor de 1.000.000 elementos, obteve-se um tempo de 38,67 segundos. Com duas threads, cada uma trabalhando com um vetor de 500.0000 elementos, obteve-se um tempo de 1,329 segundos, totalizando em um speedup de aproximadamente 1,926. 

3 - Foram realizados testes com 2000, 4000 e 6000 repetições, com o número de threads variando entre 1 e 4. Cada teste foi realizado 5 vezes, obtendo-se uma média do tempo de execução. Além disso, o número de elementos do vetor manteve-se o mesmo, independente do número de threads, para todo conjunto de aplicações computar o mesmo número de dados para cada thread. Foi escolhido um vetor de 100.000 elementos para cada possível thread. 
Como pode ser avaliado na Figura 1, a mudança de threads com vetores de mesmo tamanho aumentou o tempo de execução. Entretanto, sabe-se que resultados com 2000 repetições com 2 threads, por exemplo, geram resultados com 4000 repetições com uma única thread. Relacionando a diferença de tempo de execução desses dois exemplos dados, percebe-se um speedup tendendo a 2 da versão com 2 threads para a versão monothread.
Outro exemplo para ficar mais visível: 3 threads executando com 2000 repetições chegam ao mesmo resultado que 1 uma única thread de 6000 repetições. A aceleração obtida pelo método das três threads é muito próxima de 2 (lembrando que o número de processadores do computador utilizado é 2).

5 - Ele não está correto, mas às vezes pode acabar tendo saídas válidas. Como todas as threads estarão na função dotprod_worker e ambas acessarão a mesma variável do dotdata.c, é necessário exclusão mútua, para que o conteúdo que é incrementado não torne-se inválido em algumas situações específicas (como por exemplo, na adição de valores na variável pelas threads praticamente ao mesmo tempo, onde apenas a última thread a atualizar a variável será computada).

![](http://www-usr.inf.ufsm.br/~plima/images/image.png)

OpenMP

Aqui segue uma imagem com a média de tempo de execução usando openmp (cada teste foi realizado 5 vezes, de onde se obteve a média).
A aplicação paralela segue na pasta openmp.

![](http://www-usr.inf.ufsm.br/~plima/images/image1.png)