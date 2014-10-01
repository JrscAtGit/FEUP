homem(ricardo).
homem(toze).

mulher(goreti).
mulher(daniela).
mulher(gabriela).

pais(ricardo,toze,goreti).
pais(daniela,toze,goreti).
pais(gabriela,toze,goreti).

pai(X,Y) :- pais(Y,X,_), homem(X).
mae(X,Y) :- pais(Y,_,X), mulher(X).
irmao(X,Y):- pais(Y,Pai,Mae), pais(X,Pai,Mae), homem(X), X\=Y.
irma(X,Y):- pais(Y,Pai,Mae), pais(X,Pai,Mae), mulher(X), X\=Y.
avopaterno(X,Z) :- pai(X,Y), pai(Y,Z).
