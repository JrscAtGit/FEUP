tipo('romance').
tipo('ficção').
book('Os Maias','Eça de Queiroz','romance').
author('Eça de Queiroz','português').

% a) Quem escreveu “Os Maias”?
% book('Os Maias',Author,_).

% b) Que autores portugueses escrevem romances?
% book(_,Author,'romance').

% c) Quais os autores de livros de ficção que escreveram livros de outro tipo também?
% author(_,Author), book(_,_,'ficção'), book(_,_,Tipo), Tipo\='ficção'.
