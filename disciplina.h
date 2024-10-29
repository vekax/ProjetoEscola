
#pragma once
#define TAM 20

struct Disciplina{
    int codigo;
    char nome[TAM];
    char professor[TAM];
    int semestre;
    int vagas;
    struct Aluno *alunos[30];
    struct Disciplina *prox;
};

//prototipos

void menuDisciplina();
int inserirDisciplina();
int listarDisciplina();
int listarDetalhadamente();
int removerDisciplina();
int atualizarDisciplina();
int matricularAluno();