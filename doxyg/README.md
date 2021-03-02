# README.md
Escalonamento de Transações - Dois algoritmos de detecção de conflitos de escalonamento de transações concorrentes.

Notas: Não consegui formatar 100% o README.md na main page do doxygen. Talvez seja melhor ler direto do README.md.

    Estrutura do diretório:
    Includes: 
        Contem todos os arquivos do tipo *.h

    src:
        Contem todos os arquivos do tipo *.c

    doxyg:
        Contem o arquivo de configuração do doxygen e o README.md que gera a main page do doxygen e dentro dele está a pasta html que contem o index.html

    Como usar o doxygen: 
        gerar os arquivos: make all

        Depois de gerado, basta entrar na psta doxyg/html e abrir o index.
        html. 

    Formas de uso: 
        Compilar: make all 
        executar: ./escalona < input.txt > output.txt    
        Limpar os .o: make clean 
        Limpar os .o, escalona e os arquivos do doxygen: make purge 
        
    Explicando o código: 
        1° - Como o arquivo de entrada possui dois tipos diferentes de
        dados, sendo eles inteiros e chars. Os dados foram separados em
        duas matrizes diferentes, separados respectivamente para cada
        tipo. As funções que cuidam desse processo são respectivamente:
        alocaDadosDeEntradaInt(); e alocaDadosDeEntradaChar(); que estão 
        localizados na função main(); do código.
        Exemplo: No arquivo, cada linha tem algo do tipo, 1 1 R X, sendo 
        assim a matriz do tipo inteiro vai receber o 1,1 e a matriz do 
        tipo char vai receber o R,X.

        2° - Para o algoritimo de teste de seriabilidade quanto ao
        conflito, foi utilizado uma struct grafo: 

            struct Grafo{
                int vertices; // Quantidade de vértices do grafo
                int arcos; // Quantidade de arcos de um grafo
                int **matriz; // Matriz adjacência "Grafo"
            }; 
        
            Primeiro é iniciado a struct grafo, o vertíce recebe o
            maior valor da transação da matriz de entrada, indicando 
            quantas vezes cada vértice pode se ligar a outro nodo. Após, 
            é iniciado o arco com valor igual a 0, e para cada vez que 
            acontece um conflito é somado 1 ao valor. E por último é 
            iniciado a matriz com os valores zerados.

            O Grafo utiliza uma Matriz de adjacência, para cada vez que
            acontece algum conflito, acontece uma ligação, essa ligação é
            indicada pela modificação do valor 0 padrão na matriz do
            grafo, pelo valor 1. Caso o valor da matriz nos indíces i,j
            sejam iguais a j,i, pode se dizer que aconteceu um ciclo. Com
            isso é identificável que o Escalonamento não é serial. 

            Caso contrário, podemos afirmar que o Escalonamento é serial.
            Esse processo comentado acima, é feito pelas funções 
            iniciaGrafo(); e pela função seriabilidade();. A primeira tem 
            como objetivo iniciar o grafo e a segunda tem como objetivo
            testar o algoritimo de teste de seriabilidade quanto ao 
            conflito. Ambas as funções estão localizadas na função main();

        3° - Para o algoritimo de visão equivalente foi utilizado
        as matrizes que foram criado no processo 1° e submatrizes a 
        partir dessa matriz maior para realizar os testes das 
        propriedades do algoritimo de visão equivalente. Esse processo
        é realizado pela função visaoEquivalente();

            Após entrar nesta função, o código cálcula quantas 
            subMatrizes existem, após conseguir essa informação, o 
            algoritimo entra em um while, que vai percorrer cada 
            subMatriz, para cada subMatriz equivale a um Escalonamento. 
            Sendo assim, esse while serve para percorrer cada 
            Escalonamento do arquivo de entrada. A matriz que cuida desse
            processo é a calculaQuantidadeDeSubMatrizes();

            Após isso, o código entra em um while e para cada indíce do 
            while, equivale para um Escalonamento diferente, que é 
            indicado por uma subMatriz. Dentro desse while é calculado 
            quantas transações diferentes estão acontecendo no mesmo 
            Escalonamento e quantos atributos diferentes existem. As 
            funções que cuidam desse processo são 
            calculaQuantosTTExistemNaMatriz(); e 
            calculaQuantosAtributosExistemNaMatriz (); respectivamente.

            Depois que os dados estão prontos, o código entra na função
            testaAlgoritimoNaSubMatriz();, onde realmente vai acontecer
            os testes das três prorpeidades do algoritimo de visão 
            equivalente. 

            Para realizar a permutação da visão equivalente, foi 
            utilizando um algoritimo chamado Johnson and Trotter. Foi 
            utilizado um algoritimo iterativo ao invés de um algoritimo 
            recursivo, pois foi necessário salvar os resultados da 
            permutação em uma matriz das permutaçõs. Para cada linha da 
            matriz permutação, indicava uma permutação diferente 
            possível. A função que cuida desse processo é chamda de 
            printPermutation();

            Agora que a matriz de permutações possíveis para cada 
            Escalonamento foi gerada, o código entra em um while, que 
            vai percorrer todas essas possíveis permutações, procurando 
            uma visão equivalente. Caso encontre uma, o fluxo do código 
            para e retorna uma flag dizendo que foi encontrado. Para cada 
            propriedade existe uma função diferente, elas foram criadas 
            de acordo com o que foi fornecido pelo Professor. Essas 
            funções são chamadas de verificaCondicaoUm();, 
            verificaCondicaoDois(); e verificaCondicaoTres(); 

            Se essas três funções retornarem uma flag de valor um, então 
            a visão equivalente existe.

            Depois que esse processo termina, o código imprime em um 
            arquivo stdout o resultado dos dois algoritimos.