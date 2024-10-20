#include <stdio.h>
#include "aluno.h"
#define TAM 10

struct Aluno{
    int matricula;
    char nome[TAM];
    char sexo;
    int anoNascimento;
    int mesNascimento;
    int diaNascimento;
    char cpf[12];
};


