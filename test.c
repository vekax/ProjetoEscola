#include <stdio.h>
#include <stdlib.h>

struct Aluno{
    int idade;
    struct Aluno *prox;
};

void inserir(struct Aluno **aluno){
    struct Aluno *novo;
    novo = malloc(sizeof(struct Aluno));
    scanf("%d", &novo->idade);
    novo->prox = NULL;

    if(*aluno == NULL){
        *aluno = novo;
    }else{
        while(*aluno->prox != NULL) *aluno = *aluno->prox;
        *aluno->prox = novo;
    }
}

void imprimir(struct Aluno *atual){
    while(atual->prox != NULL){
        printf("\nIdade atual: %d", atual->idade);
        atual = atual->prox;
    }
}

int main(){

    struct Aluno *primeiro = NULL;

    inserir(primeiro);
    inserir(primeiro);
    inserir(primeiro);


    imprimir(primeiro);

    return 0;
}
