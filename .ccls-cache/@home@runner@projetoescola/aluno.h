
#pragma once
#define TAM 20

struct Aluno{
    int matricula;
    char nome[TAM];
    char sexo;
    int anoNascimento;
    int mesNascimento;
    int diaNascimento;
    int diasIdade;
    char cpf[13];
    int disciplinasCadastradas;
    struct Aluno *prox;
};

//prototipos

void menuAluno();
int inserirAluno();
int listarAluno();
int removerAluno();
int atualizarAluno();
int relatorioAluno();

int validar_data_nascimento();
int validar_cpf();