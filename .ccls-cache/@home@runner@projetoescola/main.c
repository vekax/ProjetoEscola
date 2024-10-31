#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "main.h"
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"


#define TAM 20
#define ERRO 0
#define SUCESSO 1


int relatoriosGerais(struct Aluno **listaAluno, struct Professor **listaProfessor, struct Disciplina **listaDisciplina){

    struct Aluno *tempAluno = *listaAluno;
    struct Professor *tempProfessor = *listaProfessor;
    struct Disciplina *tempDisciplina = *listaDisciplina;

    int opcao;
    time_t agora = time(NULL);
    struct tm *dataAtual = localtime(&agora);
    int mesAtual = dataAtual->tm_mon + 1; // + 1 pois vai de janeiro 0 a dezembro 11



    printf("\n\n Outros relatorios \n\n");
    printf("0 - Sair\n");
    printf("1 - Aniversariante do mes\n");
    printf("2 - Lista de pessoas a partir de uma string de busca (minimo 3 letras)\n");
    printf("3 - Lista de Disciplinas, com nome do professor, que extrapolam 40 vagas\n");
    printf("\nInsira uma opcao: ");
    scanf("%d", &opcao);
    system("clear");

    switch(opcao){
        case 1:
            printf("\nAniversariantes do mes (%d): ", mesAtual);
            while(tempAluno != NULL){
                if(tempAluno->mesNascimento == mesAtual) printf("\nAluno | Nome: %s", tempAluno->nome);
                tempAluno = tempAluno->prox;
            }

            while(tempProfessor != NULL){
                if(tempProfessor->mesNascimento == mesAtual) printf("\nProfessor | Nome: %s", tempProfessor->nome);
                tempProfessor = tempProfessor->prox;
            }
            break;
        case 2:{

            char string[TAM];

            printf("\nInsira a string de busca(minimo 3 letras): ");
            fflush(stdin);
            fgets(string, TAM, stdin);
            size_t ln = strlen(string);
            if(string[ln-1] ==  '\n') string[ln-1] = '\0';

            if(strlen(string) < 3){
                printf("\nString muito pequena!");
                return ERRO;
            }

            int n;
            int j;

            int achou = 0;

            while(tempAluno != NULL){
                for(int i = 0; i < strlen(tempAluno->nome); i++){
                    j = 0;
                    int aux = i;
                    while(tempAluno->nome[aux] == string[j]){
                        aux++;
                        j++;
                        if(j == strlen(string)) achou = 1;
                    }
                }
                if(achou) printf("\nAluno: %s", tempAluno->nome);
                tempAluno = tempAluno->prox;
            }

            achou = 0;

            while(tempProfessor != NULL){
                for(int i = 0; i < strlen(tempProfessor->nome); i++){
                    j = 0;
                    int aux = i;
                    while(tempProfessor->nome[aux] == string[j]){
                        aux++;
                        j++;
                        if(j == strlen(string)) achou = 1;
                    }
                }
                if(achou) printf("\nProfessor: %s", tempProfessor->nome);
                tempProfessor = tempProfessor->prox;
            }
            break;}
        case 3:{

            if(tempDisciplina == NULL) printf("\nLista vazia!");

            while(tempDisciplina != NULL){
                printf("\nInsira o nome do professor: ");
                char string[TAM];
                fflush(stdin);
                fgets(string, TAM, stdin); 
                size_t ln = strlen(string);
                if(string[ln-1] ==  '\n') string[ln-1] = '\0';

                if(!strcmp(tempDisciplina->professor, string)){
                    if(tempDisciplina->vagas > 40) printf("\nDisciplina do professor %s que extrapola 40 vagas: %s", tempDisciplina->professor, tempDisciplina->nome);
                }
                tempDisciplina = tempDisciplina->prox;
            }
            break;}
        default:
            break;
    }

    return SUCESSO;

}

int exibirMenu(){
    int opcao;
    printf("\n\n Menu Escola \n\n");
    printf("0 - Sair\n");
    printf("1 - Menu Aluno\n");
    printf("2 - Menu Professor\n");
    printf("3 - Menu Disciplina\n");
    printf("4 - Outras opcoes\n");
    printf("\nInsira uma opcao: ");
    scanf("%d", &opcao);
    system("clear");
    
    return opcao;
}

void menu(int opcao, struct Aluno **inicioAluno, struct Professor **inicioProfessor, struct Disciplina **inicioDisciplina){
    switch(opcao){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            system("clear");
            menuAluno(inicioAluno);
            break;
        case 2:
            system("clear");
            menuProfessor(inicioProfessor);
            break;
        case 3:
            menuDisciplina(inicioDisciplina, inicioAluno, inicioProfessor);
            break;
        case 4:
            relatoriosGerais(inicioAluno, inicioProfessor, inicioDisciplina);
            break;
        default:
            system("clear");
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