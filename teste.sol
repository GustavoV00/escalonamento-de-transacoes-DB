0 -> 1 1 
1 -> 2 3 
2 -> 3 2 
3 -> 4 2 
4 -> 5 1 
5 -> 6 3 
6 -> 7 1 
7 -> 8 3 
8 -> 9 1 
9 -> 10 2 
10 -> 11 3 

0 -> R X 
1 -> R Z 
2 -> R X 
3 -> W X 
4 -> R Y 
5 -> R Y 
6 -> R Z 
7 -> W Z 
8 -> C - 
9 -> C - 
10 -> C - 
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
quantidade: 11
teste: 3
0 0 0 
0 0 0 
0 0 0 

Conflito2: 1 1 R X e 4 2 W X
Conflito2: 7 1 R Z e 8 3 W Z
2
inicio:0 e Fim:7
1 3 2 0 0 0 0 
X Z Y 0 0 0 0 





1 3 2 
1 2 3 
2 1 3 
2 3 1 
3 2 1 
3 1 2 

Test:1 

Test:3 

Test:2 
HereZ:1 e 1 = 1 | X
HereZ:3 e 1 = 0 | Z
HereZ:1 e 1 = 1 | Y

HereX:-1 e -1 = 1 | X
HereX:-1 e -1 = 1 | Z
HereX:-1 e -1 = 1 | Y

HereC:2 e 2 = 1 | X
HereC:3 e 3 = 1 | Z
HereC:-1 e -1 = 1 | Y

z = 1, x = 1, c = 1 | 1

0 -> 1 1 
1 -> 5 1 
2 -> 7 1 
3 -> 2 3 
4 -> 6 3 
5 -> 8 3 
6 -> 3 2 
7 -> 4 2 

0 -> R X 
1 -> R Y 
2 -> R Z 
3 -> R Z 
4 -> R Y 
5 -> W Z 
6 -> R X 
7 -> W X 

----------------------------------------

Flags: 1 
----------------------------------------
test:1 e 0
Vertices:3
1 1,2,3 SS SV

inicio:10 e Fim:8
0 0 0 
1 0 0 
1 0 0 
