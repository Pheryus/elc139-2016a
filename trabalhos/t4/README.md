[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2016a) > Trabalhos

# T4: Floyd-Warshall Paralelo em Multicore

## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t4`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do aluno;
 - Link para o programa desenvolvido;
 - com explicações sobre as etapas de particionamento, comunicação, aglomeração e mapeamento;
 - Tabelas e gráficos com tempos, speedup e eficiência;
 - Referências.
 
## Objetivo

O [algoritmo de Floyd](https://en.wikipedia.org/wiki/Floyd-Warshall_algorithm) é uma solução clássica para encontrar os caminhos de menor custo entre todos os pares de vértices de um grafo (problema conhecido como APSP - All Pairs Shortest Path). Para um grafo com N nós, o tempo computacional deste algoritmo é proporcional a N^3, de modo que sua execução seqüencial pode ser inviável para grandes valores de N. Nestes casos, a implementação paralela do algoritmo de Floyd é uma alternativa para reduzir o tempo para solução do problema. 

Seus objetivos neste trabalho serão desenvolver e avaliar um programa paralelo que implemente o algoritmo de Floyd para uma arquitetura multicore. 

## Desenvolvimento

- Você pode partir de uma implementação seqüencial do algoritmo de Floyd, disponível em [floyd_seq](floyd_seq). Este programa gera aleatoriamente um grafo de tamanho estipulado, facilitando a experimentação com diferentes dados de entrada para o mesmo algoritmo. Se preferir, você pode reescrever este programa em outra linguagem, mas deve manter a funcionalidade de geração dos grafos, para facilitar a avaliação do programa paralelo com diferentes dados de entrada.

- Na paralelização, você deverá utilizar OpenMP ou outra ferramenta que permita dividir o trabalho entre múltiplas threads. 

- A fim de avaliar o desempenho da implementação paralela, deve-se medir os tempos de execução para diferentes números de threads e diferentes tamanhos de grafos. Depois disso, você deverá calcular speedup e eficiência do seu programa para cada caso considerado.


## Material de apoio


- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP. 


- [Case Study: Shortest-Path Algorithms](http://www.mcs.anl.gov/~itf/dbpp/text/node35.html#SECTION02490000000000000000)  
  Capítulo do livro *Designing and Building Parallel Programs* com explicações sobre a paralelização do algoritmo de Floyd.

