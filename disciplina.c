#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "disciplina.h"
#define TAM 20
#define MAX 3
#define ERRO 0
#define SUCESSO 1

struct Disciplina{
    int codigo;
    char nome[TAM];
    char professor[TAM];
    int semestre;
    char alunos[TAM][MAX];
    struct Disciplina *prox;
};
struct Aluno{
    int matricula;
    char nome[TAM];
    char sexo;
    int anoNascimento;
    int mesNascimento;
    int diaNascimento;
    char cpf[13];
    struct Aluno *prox;
};

int listarDisciplina(struct Disciplina *atual) {
    printf("\nLista de Disciplina:");

    if(atual == NULL){
        printf("\nLista Vazia!");
        return ERRO;
    }

    while (atual != NULL) { // Corrige a condição de parada
        printf("\n Nome: %s", atual->nome);
        printf(" | Codigo: %d", atual->codigo);
        printf("\n Semestre: %d", atual->semestre);
        printf(" | Professor: %s", atual->professor);
        atual = atual->prox;
    }
    return SUCESSO;
}

int listarDetalhadamente(struct Disciplina **listaDisciplina){ //NAO TESTEI AINDA
    struct Disciplina *temp = *listaDisciplina;
    printf("Digite o nome da disciplina: ");
    char string[TAM];
    fgets(string, TAM, stdin);

    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    while(temp != NULL){
        if(!strcmp(string, temp->nome)){
            printf("\n Nome: %s", temp->nome);
            printf(" | Codigo: %d", temp->codigo);
            printf("\n Semestre: %d", temp->semestre);
            printf(" | Professor: %s", temp->professor);
            printf("\nAlunos matriculados:\n");

            for(int i=0; temp->alunos[i] != NULL; i++) printf("%s\n", temp->alunos[i]);

            return SUCESSO;
        }
    }

    printf("Disciplina nao encontrada");

    return ERRO;
}

int matricularAluno(struct Disciplina **listaDisciplina, struct Aluno **listaAluno) { //NAO TA RODANDO, ACHO QUE EU SOU BURRO, TENTA CONSERTAR AI PLS
    struct Disciplina *tempDisciplina = *listaDisciplina;
    struct Aluno *tempAluno = *listaAluno;
    char stringDisciplina[TAM];

    printf("\nDigite o nome do Disciplina que o aluno sera matriculado: ");
    fgets(stringDisciplina, TAM, stdin);
    stringDisciplina[strcspn(stringDisciplina, "\n")] = 0; // remove \n

    while (tempDisciplina != NULL) {
        if (!strcmp(tempDisciplina->nome, stringDisciplina)) {
            char stringAluno[TAM];
            printf("\nDigite o nome do aluno: ");
            fgets(stringAluno, TAM, stdin);
            stringAluno[strcspn(stringAluno, "\n")] = 0; // remove \n

            while (tempAluno != NULL) {
                if (!strcmp(tempAluno->nome, stringAluno)) {
                    // Aloque espaço para o nome do aluno
                    strcpy(tempDisciplina->alunos[0], tempAluno->nome);
                    return SUCESSO;
                }
                tempAluno = tempAluno->prox;
            }
            printf("Aluno nao encontrado");
            return ERRO;
        }
        tempDisciplina = tempDisciplina->prox;
    }
    printf("\nDisciplina nao encontrada");
    return ERRO;
}

void menuDisciplina(struct Disciplina **listaDisciplina, struct Aluno **listaAluno){

    int sairDisciplina = 1;
    int opcao = 1;

    while(sairDisciplina){

        printf("\n\n Menu Disciplina \n\n");
        printf("0 - Voltar\n");
        printf("1 - Cadastrar Disciplina\n");
        printf("2 - Atualizar Disciplina\n");
        printf("3 - Excluir Disciplina\n");
        printf("4 - Listar Disciplinas\n");
        printf("5 - Listar Disciplina detalhadamente\n");
        printf("6 - Cadastrar Aluno na Disciplina\n");
        printf("\nInsira uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
            case 0:
                sairDisciplina = 0;
                printf("Voltando...\n");
                break;
            case 1:
                if(inserirDisciplina(listaDisciplina)) printf("Disciplina adicionado com sucesso\n");
                break;
            case 2:
                atualizarDisciplina(listaDisciplina);
                break;
            case 3:
                removerDisciplina(listaDisciplina);
                break;
            case 4:
                listarDisciplina(*listaDisciplina);
                break;
            case 5:
                listarDetalhadamente(*listaDisciplina);
                break;
            case 6:
                matricularAluno(*listaDisciplina, *listaAluno);
                break;
            default:
                printf("\nOpcao invalida!");
                break;
        }
    }

}

int inserirDisciplina(struct Disciplina **listaDisciplina){
    struct Disciplina *novo;
    novo = malloc(sizeof(struct Disciplina));

    //verifica se o malloc retornou NULL
    if(novo == NULL){
        printf("ERRO AO ALOCAR MEMORIA");
        exit(ERRO);
    }

    novo->codigo = rand();
    novo->prox = NULL;
    printf("\nCodigo gerada: %d", novo->codigo);
    printf("\nDigite o nome do Disciplina: ");

    fflush(stdin);
    fgets(novo->nome, TAM, stdin);

    printf("\nDigite o semestre da Disciplina: ");
    scanf("%d", &novo->semestre);

    printf("\nDigite o professor da Disciplina: ");
    fflush(stdin);
    fgets(novo->professor, TAM, stdin);
    
    size_t ln = strlen(novo->nome);
    if(novo->nome[ln-1] ==  '\n') novo->nome[ln-1] = '\0';

    if (*listaDisciplina == NULL) { // se a lista estiver vazia
        *listaDisciplina = novo; 
    } else {
        struct Disciplina *temp = *listaDisciplina;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = novo;
    }

    return SUCESSO;
}

int removerDisciplina(struct Disciplina **listaDisciplina){
    struct Disciplina *temp = *listaDisciplina;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do Disciplina a ser removido: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    if(!strcmp(temp->nome, string)){ //caso o Disciplina a ser removido seja o primeiro da lista
        *listaDisciplina = temp->prox;
        free(temp);
        return SUCESSO;
    }

    while(temp != NULL){
        struct Disciplina *tempprox = temp->prox; // celula posterior a temp
        if(!strcmp(tempprox->nome, string)){
            temp->prox = tempprox->prox;
            free(tempprox);
            return SUCESSO;
        }
        temp = temp->prox;
    }
    return ERRO;
}


int atualizarDisciplina(struct Disciplina **listaDisciplina){

    struct Disciplina *temp = *listaDisciplina;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do Disciplina para atualizar: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    

    while(temp != NULL){
        if(!strcmp(temp->nome, string)){

            int opcao = 1;
            while(opcao){

                printf("\nQual informacao deseja atualizar: ");
                printf("\n0 - Voltar\n");
                printf("1 - Nome\n");
                printf("2 - Semestre\n");
                printf("3 - Professor\n");
                printf("\nInsira uma opcao: ");
                scanf("%d", &opcao);

                system("cls");

                if(opcao >= 0 && opcao <= 3) break;
                else printf("\nDigite uma opcao valida!");
            }

            switch(opcao){
            case 1:{
                printf("\nDigite o novo nome para modificar: ");
                fflush(stdin); // limpa o buffer
                fgets(temp->nome, TAM, stdin);
                ln = strlen(temp->nome);
                if(temp->nome[ln-1] == '\n') temp->nome[ln-1] = '\0';
                printf("\nNome atualizado com sucesso");
                return SUCESSO;
                break;
            }
            case 2:{
                printf("\nDigite o novo semestre da disciplina: ");
                int tsemestre;
                fflush(stdin);
                scanf("%d", &tsemestre);
                if(tsemestre>0 || tsemestre<7){
                    temp->semestre = tsemestre;
                    return SUCESSO;
                }
                else{
                    printf("\nDigite um semestre valido (1-6)");
                    return ERRO;
                }
                break;
            }
            case 3:{
                printf("\nDigite o novo professor: ");
                fflush(stdin);
                fgets(temp->professor, TAM, stdin);
                ln = strlen(temp->professor);
                if(temp->professor[ln-1] == '\n') temp->professor[ln-1] = '\0';
                printf("\nProfessor atualizado com sucesso");
                
                return SUCESSO;
                break;
            }

        }
            break;
        }
        temp = temp->prox;
    }

    printf("\nDisciplina nao encontrada");
    
    return ERRO;

}