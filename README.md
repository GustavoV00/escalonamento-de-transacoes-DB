# README.md
Escalonamento de Transações - Dois algoritmos de detecção de conflitos de escalonamento de transações concorrentes.

Notas: 

    Estrutura do diretório:
    Includes:
    Contem todos os arquivos do tipo *.h

    src:
    Contem todos os arquivos do tipo *.c

    doxyg:
    Contem o arquivo de configuração do doxygen e dentro dele está a pasta html que contem o index.html

    Como usar o doxygen: 
    gerar os arquivos: make all 

    Depois de gerado, basta entrar na psta doxyg/html e abrir o index.html. 

Formas de uso: 
    Compilar: make all 
    executar: make run < input.txt > output.txt 
                           ou 
              ./escalona < input.txt > output.txt  
    Limpar os .o: make clean 
    Limpar os .o, escalona e os arquivos do doxygen: make purge \n
    

           

Explicando o código: 
    -> Como o arquivo de entrada possui dois tipos diferentes de dados, sendo eles inteiros e chars. Os dados foram separados em duas matrizes diferentes, separados respectivamente para cada tipo. 

    -> Para o algoritimo de teste de seriabilidade quanto ao conflito, foi utilizado uma struct grafo: 

        struct Grafo{
            int vertices; // Quantidade de vértices do grafo
            int arcos; // Quantidade de arcos de um grafo
            int **matriz; // Matriz adjacência "Grafo"
        }; \n

        Essa struct é uma Matriz de adjacência, para cada vez que acontece algum conflito, acontece uma ligação, essa ligação é indicada pela modificação do valor 0 padrão na matriz do grafo, pelo valor 1. Caso o valor da matriz nos indíces i,j sejam iguais a j,i, pode se dizer que aconteceu um ciclo. Com isso é identificável que o Escalonamento não é serial. 

    -> Para o algoritimo de visão equivalente foi utilizado matrizes e submatrizes para realizar os testes de propriedades. 

        Para realizar a permutação da visão equivalente, foi utilizando um algoritimo chamado Johnson and Trotter. Foi utilizado um algoritimo iterativo ao invéz de um algoritimo recursivo, pois foi necessário salvar os resultados da permutação em uma matriz das permutaçõs. Para cada linha da matriz permutação, indicava uma permutação diferente possível. 

        Como a entrada do código é um arquivo "input.txt", toda essa entrada foi salva em uma matriz. E como essa matriz pode ter mais de um escalonamento acontecendo, então para cada escalonamento foi separado como uma submatriz, da matriz principal, que no caso seria o "input.txt". 

        Para cada submatriz, ele testa as três propriedades da visão equivalente, todas as três prorpeidades retornam um flag de valor 1, caso a propriedade for aceita com sucesso. Se isso acontece, então o escalonamento S' é aceito, indicando que existe visão equivalente.  

    -> Fluxo de execução do código:
        Primeiro ele lê o arquivo de entrada, separando em duas matrizes diferentes. Sendo elas, uma matriz que recebe os dados do tipo inteiro e uma matriz que recebe os dados do tipo char. Exemplo: \n
            No arquivo, cada linha tem algo do tipo, 1 1 R X, sendo assim a matriz do tipo inteiro vai receber o 1,1 e a matriz do tipo char vai receber o R,X. 
        
        Depois que arrumar as matrizes do jeito certo, o código vai inicializar o grafo com valor padrão 0, que vai cuidar do teste de seriabilidade quando ao conflito. Seguindo o fluxo do código, vai rodar a função que vai testar o algoritimo, para cada vez que acontecer algum conflito, o valor na matriz do grafo vai mudar de 0 para 1. E caso o valor da matriz com os índices de i,j sejam igauis a j,i, então existe um ciclo, o que pode ser considerado como escalonamento não serial. 

        Depois do algoritimo de teste de seriabilidade quanto ao conflito terminar, o teste de visão equivalente vai iniciar. Aqui, ele vai pegar as matrizes principais, que seriam as matrizes do arquivo de entrada e vai criar submatrizes, de acordo com a quantidade de escalonamentos que podem existir na entrada dos dados. Para cada submatriz, vai acontecer o teste de visão equivalente. Dependendo da quantidade de transações que existir, vai acontecer uma permutação para identificar quantas possíveis visões essa submatriz pode ter. 

        Depois que ambos os algoritimos estiverem pronto, o código vai imprimir o resultado final e vai liberar a memória das matrizes. 
