#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#define TAM 20
#define ERRO 0
#define SUCESSO 1

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

int listarAluno(struct Aluno *atual) {
    printf("\nLista de alunos:");

    if(atual == NULL){
        printf("\nLista Vazia!");
        return ERRO;
    }

    while (atual != NULL) { // Corrige a condição de parada
        printf("\n Nome: %s", atual->nome);
        printf(" | Matricula: %d", atual->matricula);
        atual = atual->prox;
    }
    return SUCESSO;
}

void menuAluno(struct Aluno **listaAluno){

    int sairAluno = 1;
    int opcao = 1;

    while(sairAluno){

        printf("\n\n Menu aluno \n\n");
        printf("0 - Voltar\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Atualizar aluno\n");
        printf("3 - Excluir aluno\n");
        printf("4 - Listar alunos\n");
        printf("\nInsira uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
            case 0:
                sairAluno = 0;
                printf("Voltando...\n");
                break;
            case 1:
                if(inserirAluno(listaAluno)) printf("Aluno adicionado com sucesso\n");
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
                printf("\nOpcao invalida!");
                break;
        }
    }

}

int inserirAluno(struct Aluno **listaAluno){
    struct Aluno *novo;
    novo = malloc(sizeof(struct Aluno));

    //verifica se o malloc retornou NULL
    if(novo == NULL){
        printf("ERRO AO ALOCAR MEMORIA");
        exit(ERRO);
    }

    novo->matricula = rand();
    novo->prox = NULL;
    printf("\nMatricula gerada: %d", novo->matricula);
    printf("\nDigite o nome do aluno: ");

    fflush(stdin);
    fgets(novo->nome, TAM, stdin);
    printf("\nDigite o sexo do aluno ('m' ou 'f'): ");
    scanf("%c", &novo->sexo);
    printf("\nDigite a data de nascimento do aluno no formato (ddmmaaaa)");
    int data;
    scanf("%d", &data);
    novo->anoNascimento = data % 10000;
    data /= 10000;
    novo->mesNascimento = data % 100;
    data /= 100;
    novo->diaNascimento = data;

    printf("\nAno nascimento: %d", novo->anoNascimento);
    printf("\nMes nascimento: %d", novo->mesNascimento);
    printf("\nDia nascimento: %d", novo->diaNascimento);

    printf("\nDigite o CPF do aluno: ");
    fflush(stdin);
    fgets(novo->cpf, 12, stdin);

    if(novo->cpf[12] ==  '\n') novo->cpf[12] = '\0';
    
    size_t ln = strlen(novo->nome);
    if(novo->nome[ln-1] ==  '\n') novo->nome[ln-1] = '\0';

    if (*listaAluno == NULL) { // se a lista estiver vazia
        *listaAluno = novo; 
    } else {
        struct Aluno *temp = *listaAluno;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = novo;
    }

    return SUCESSO;
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
        return SUCESSO;
    }

    while(temp != NULL){
        struct Aluno *tempprox = temp->prox; // celula posterior a temp
        if(!strcmp(tempprox->nome, string)){
            temp->prox = tempprox->prox;
            free(tempprox);
            return SUCESSO;
        }
        temp = temp->prox;
    }
    return ERRO;
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
            return SUCESSO;
        }
        temp = temp->prox;
    }

    
    return ERRO;

}