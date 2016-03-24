
Nome: Pedro Langbecker Lima

Sessão 1: Aplicação dot_product

Foi testado a aplicação dot_product com a primeira entrada variando de 3000 ate 30000000 no primeiro valor, e de 10 ate 90 no segundo valor.
Perguntas: 
  - (a) O perfil é afetado pelas opções de configuração?
  - (b) Pelo perfil de execução, há alguma função que poderia ser candidata a paralelização? Por quê?

(a)
Sim, com uma entrada muito pequena como 3000 e 10, o tempo acumulativo e a porcentagem do tempo usada em cada função do programa se aproximam o suficiente de 0 para que o gprof assuma que esse é o seu valor (ou seja, porcentagem e tempo em milessegundos com pouca precisão). Já com entradas maiores, o resultado do tempo de cada função, bem como o gráfico de chamada das funções,  é representado de forma mais significativa, demonstrando o impacto do aumento da entrada. Dentre as funções chamadas, a funcao dot_product gasta uma porcentagem de aproximadamente 98.8% do tempo de execução do programa, enquanto a função init_vectors gasta uma porcentagem inferior a 2%. Testando entradas como 3000000 e 60, obteve-se um resultado semelhante na porcentagem de tempo com outros valores de entrada em uma escala maior, como 30000000 e 90, bem como no tempo medio de milissegundos gasto em cada chamada de função. No geral, o perfil gerado demonstra pouca variação da porcentagem da função dot_product, revelando que exclusivamente ela domina o programa em tempo de execução.
![](http://www-usr.inf.ufsm.br/~plima/images/1a.jpg)
![](http://www-usr.inf.ufsm.br/~plima/images/1b.jpg)

(b)
Naturalmente, toda funcao dot_product deve ser o foco da possivel paralelização, pelo seu custo maior de processamento. Conseguindo uma paralelização que reduzisse o tempo da função dot_product em 50% acarretaria em uma redução de praticamente 50% do tempo de execução do programa. Por outro lado, paralelizando a função init_vectors e conseguindo uma redução de 100 vezes do tempo daquela função, acarretaria em uma variação ínfima demais no tempo total do programa. 

Sessao2: Caça-Palavras na linguagem C

Foram testadas várias entradas com dimensões da matriz do caça-palavras diferentes. O programa entao preenche toda matriz com caracteres aleatórios. Em seguida, o usuário informa uma sequencia de caracteres que são procuradas por toda matriz, em qualquer ordem, como um caça-palavras comum. 
As duas primeiras imagens contém informações referentes a execução do programa com uma matriz de tamanho 10.000 x 10.000, chamada como A.
![](http://www-usr.inf.ufsm.br/~plima/images/2a.jpg)
![](http://www-usr.inf.ufsm.br/~plima/images/2b.jpg)
Já as duas próximas imagens são referentes a execução do programa com uma matriz de tamanho 5.000 x 5.000, denotada como B.
![](http://www-usr.inf.ufsm.br/~plima/images/2d.jpg)
![](http://www-usr.inf.ufsm.br/~plima/images/2c.jpg)
(a)
Pode-se perceber uma variação no custo da função gera_matriz entre as duas entradas, com um custo de tempo maior para a matriz A, bem como uma repetição de chamadas das funções muito maior do que a matriz B. Isso se deve ao fato de uma sequencia de passos que se repete iteração por iteração dentro de toda matriz. 
(b)A função gera_matriz, que possue um custo grande em ambas matrizes, bem como a função busca_p, sao funções que ocorrem uma única vez, mas consomem boa parte do tempo de execução do programa. A busca_p no entanto, tem sua porcentagem elevada por conta de sua chamada a outras funções repetidas vezes, sendo provavelmente a mais indicada para uma possivel paralelização.
