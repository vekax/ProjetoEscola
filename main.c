#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "aluno.h"


int exibirMenu(){
    int opcao;
    printf("\n\n Menu Escola \n\n");
    printf("0 - Sair\n");
    printf("1 - Menu Aluno\n");
    printf("2 - Menu Professor\n");
    printf("3 - Menu Disciplina\n");
    printf("\nInsira uma opcao: ");
    scanf("%d", &opcao);
    
    return opcao;
}

void menu(int opcao, struct Aluno **inicioAluno){
    switch(opcao){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            system("cls");
            menuAluno(inicioAluno);
            break;
        case 2:
            printf("Menu Professor selecionado\n");
            break;
        case 3:
            printf("Menu Materia selecionado\n");
            break;
        default:
            system("cls");
            printf("Digite uma opcao valida!\n");
            break;
    }
}

int main(){

    srand(time(NULL));

    struct Aluno *inicioAluno = NULL;
    int opcao = 1;
    int qtdAluno = 0;

    while(opcao){
        opcao = exibirMenu();
        menu(opcao, &inicioAluno);
    }
    
    return 0;
}