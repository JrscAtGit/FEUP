pilot('Lamb').
pilot('Besenyei').
pilot('Chambliss').
pilot('MacLean').
pilot('Mangold').
pilot('Jones').
pilot('Bonhomme').

team('Breitling','Lamb').
team('Red Bull','Besenyei').
team('Red Bull','Chambliss').
team('Mediterranean Racing Team','MacLean').
team('Cobra','Mangold').
team('Matador','Jones').
team('Matador','Bonhomme').

plane('MX2','Lamb').
plane('Edge540','Besenyei').
plane('Edge540','Chambliss').
plane('Edge540','MacLean').
plane('Edge540','Mangold').
plane('Edge540','Jones').
place('Edge540','Bonhomme').

circuits('Istanbul').
circuits('Budapest').
circuits('Porto').

won('Porto','Jones').
won('Budapest','Mangold').
won('Istanbul','Mangold').

gates('Istanbul',9).
gates('Budapest',6).
gates('Porto',5).

won(X,Z) :- won(X,Z),won(Y,Z),X\=Y.

% a) Quem venceu a corrida no Porto?
% won('Porto',X).

% b) Qual a equipa que ganhou no Porto?
% won('Porto',X),team(Y,X).

% c) Quais os pilotos que venceram mais de um circuito?
% won(X,Z),won(Y,Z),X\=Y,X<Y.

% d) Que circuitos têm mais de 8 gates
% gates(X,Y),Y>8.

% e) Que pilotos não pilotam um Edge540?
