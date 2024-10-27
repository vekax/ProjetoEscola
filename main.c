#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"


int exibirMenu(){
    int opcao;
    printf("\n\n Menu Escola \n\n");
    printf("0 - Sair\n");
    printf("1 - Menu Aluno\n");
    printf("2 - Menu Professor\n");
    printf("3 - Menu Disciplina\n");
    printf("\nInsira uma opcao: ");
    scanf("%d", &opcao);
    system("cls");
    
    return opcao;
}

void menu(int opcao, struct Aluno **inicioAluno, struct Professor **inicioProfessor, struct Disciplina **inicioDisciplina){
    switch(opcao){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            system("cls");
            menuAluno(inicioAluno);
            break;
        case 2:
            system("cls");
            menuProfessor(inicioProfessor);
            break;
        case 3:
            menuDisciplina(inicioDisciplina, inicioAluno);
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
    struct Professor *inicioProfessor = NULL;
    struct Disciplina *inicioDisciplina = NULL;
    int opcao = 1;

    while(opcao){
        opcao = exibirMenu();
        menu(opcao, &inicioAluno, &inicioProfessor, &inicioDisciplina);
    }
    
    return 0;
}