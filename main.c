#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"


int exibirMenu(){
    int opcao;
    printf("\n\nMenu Escola\n");
    printf("0 - Sair\n");
    printf("1 - Menu Aluno\n");
    printf("2 - Menu Professor\n");
    printf("3 - Menu Disciplina\n");
    scanf("%d", &opcao);
    
    return opcao;
}

void menu(int opcao, struct Aluno **inicioAluno){
    switch(opcao){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            printf("Menu Aluno selecionado\n");
            menuAluno(inicioAluno);
            break;
        case 2:
            printf("Menu Professor selecionado\n");
            break;
        case 3:
            printf("Menu Materia selecionado\n");
            break;
        default:
            printf("Digite uma opcao valida!\n");
            break;
    }
}

int main(){

    struct Aluno *inicioAluno = NULL;
    int opcao = 1;
    int qtdAluno = 0;

    while(opcao){
        opcao = exibirMenu();
        menu(opcao, &inicioAluno);
    }
    
    return 0;
}