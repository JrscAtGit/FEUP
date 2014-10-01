male('Aldo').
male('Lincoln').
male('LJ').
male('Michael').

female('Christina').
female('Lisa').
female('Sara').
female('Ella').

parent('Aldo','Lincoln').
parent('Aldo','Michael').
parent('Christina','Lincoln').
parent('Christina','Michael').
parent('Lisa','LJ').
parent('Lincoln','LJ').
parent('Michael','Ella').
parent('Sara','Ella').

% a) Quem são os pais de Michael?
% parent(X,'Michael').

% b) Quem são os filhos de Aldo?
% parent('Aldo',X).
