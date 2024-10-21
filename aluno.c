#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#define TAM 20

struct Aluno{
    int matricula;
    char nome[TAM];
    char sexo;
    int anoNascimento;
    int mesNascimento;
    int diaNascimento;
    char cpf[12];
    struct Aluno *prox;
};

void listarAluno(struct Aluno *atual) {
    printf("\nLista de alunos:");
    while (atual != NULL) { // Corrige a condição de parada
        printf("\n Nome: %s", atual->nome);
        printf(" | Matricula: %d", atual->matricula);
        atual = atual->prox;
    }
}

void menuAluno(struct Aluno **listaAluno){

    int sairAluno = 1;
    int opcao = 1;

    while(sairAluno){
        printf("\n\nMenu aluno!\n");
        printf("0 - Voltar\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Atualizar aluno\n");
        printf("3 - Excluir aluno\n");
        printf("4 - Listar alunos\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                sairAluno = 0;
                printf("Voltando...\n");
                break;
            case 1:
                inserirAluno(listaAluno);              
                printf("Aluno adicionado com sucesso");
                break;
            case 2:
                atualizarAluno(listaAluno);
                break;
            case 3:
                removerAluno(listaAluno);
                break;
            case 4:
                listarAluno(*listaAluno);
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    }

}

void inserirAluno(struct Aluno **listaAluno){
    struct Aluno *novo;
    novo = malloc(sizeof(struct Aluno));

    //verifica se o malloc retornou NULL
    if(novo == NULL){
        printf("ERRO AO ALOCAR MEMORIA");
        exit(1);
    }

    novo->matricula = rand();
    novo->prox = NULL;
    printf("\nMatricula gerada: %d", novo->matricula);
    printf("\nDigite o nome do aluno: ");

    fflush(stdin);
    fgets(novo->nome, TAM, stdin);
    
    size_t ln = strlen(novo->nome);
    if(novo->nome[ln-1] ==  '\n') novo->nome[ln-1] = '\0';

    if (*listaAluno == NULL) { // se a lista estiver vazia
        *listaAluno = novo; 
    } else {
        struct Aluno *temp = *listaAluno;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = novo;
    }
}

int removerAluno(struct Aluno **listaAluno){
    struct Aluno *temp = *listaAluno;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do aluno a ser removido: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    if(!strcmp(temp->nome, string)){ //caso o aluno a ser removido seja o primeiro da lista
        *listaAluno = temp->prox;
        free(temp);
        return 1;
    }

    while(temp != NULL){
        struct Aluno *tempprox = temp->prox; // celula posterior a temp
        if(!strcmp(tempprox->nome, string)){
            temp->prox = tempprox->prox;
            free(tempprox);
            return 1;
        }
        temp = temp->prox;
    }
    return 0;
}


int atualizarAluno(struct Aluno **listaAluno){

    struct Aluno *temp = *listaAluno;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do aluno para atualizar: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    while(temp != NULL){
            if(!strcmp(temp->nome, string)){ //caso o aluno a ser removido seja o primeiro da lista
            printf("\nDigite o novo nome para modificar: ");
            fgets(temp->nome, TAM, stdin);
            ln = strlen(temp->nome);
            if(temp->nome[ln-1] == '\n') temp->nome[ln-1] = '\0';
            printf("\nNome atualizado com sucesso");
            return 1;
        }
        temp = temp->prox;
    }

    
    return 0;

}