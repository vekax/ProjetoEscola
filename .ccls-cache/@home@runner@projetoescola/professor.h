
#pragma once
#define TAM 20


struct Professor{
    int matricula;
    char nome[TAM];
    char sexo;
    int anoNascimento;
    int mesNascimento;
    int diaNascimento;
    int diasIdade;
    char cpf[13];
    struct Professor *prox;
};

//prototipos

void menuProfessor();
int inserirProfessor();
int listarProfessor();
int removerProfessor();
int atualizarProfessor();
int relatorioProfessor();

int validar_data_nascimento();
int validar_cpf();