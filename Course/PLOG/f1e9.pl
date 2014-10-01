use_module(library(lists)).

aluno(joao, paradigmas).
aluno(maria, paradigmas).
aluno(joel, lab2).
aluno(joel, estruturas).
frequenta(joao, feup).
frequenta(maria, feup).
frequenta(joel, ist).
professor(carlos, paradigmas).
professor(ana_paula, estruturas).
professor(pedro, lab2).
funcionario(pedro, ist).
funcionario(ana_paula, feup).
funcionario(carlos, feup).

% a) Quem são os alunos do professor X?
alunosDe(X,Lista):- aluno(Aluno,Aula),
                    professor(Professor,Aula), 
                    non_member(Aluno,Lista).

% b) Quem são as pessoas da universidade X? (alunos ou docentes)
% c) Quem é colega de quem? Se aluno: é colega se for colega de disciplina ou colega de curso ou colega de universidade. Se professor: se for professor da mesma universidade.
