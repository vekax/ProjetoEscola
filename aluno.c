#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

bool valida_data_nascimento(int dia, int mes, int ano) {
  // Verifica se o ano é válido (entre 1900 e o ano atual)
  if (ano < 1900 || ano > 2023) {
    return false;
  }

  // Verifica se o mês é válido (entre 1 e 12)
  if (mes < 1 || mes > 12) {
    return false;
  }

  // Verifica se o dia é válido com base no mês
  int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Ano bissexto
    diasNoMes[1] = 29;
  }
  if (dia < 1 || dia > diasNoMes[mes - 1]) {
    return false;
  }

  return true;
}

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
    printf("\nDigite a data de nascimento do aluno no formato (ddmmaaaa): ");
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

    if(validar_cpf(novo->cpf) == SUCESSO){
        printf("\nCPF validado com sucesso!\n");
    }else{
        printf("\nCPF invalido!\nErro ao cadastrar CPF\n");
        free(novo);
        return ERRO;
    }
    
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
        if(!strcmp(temp->nome, string)){

            int opcao = 1;
            while(opcao){

                printf("\nQual informacao deseja atualizar: ");
                printf("\n0 - Voltar\n");
                printf("1 - Nome\n");
                printf("2 - Sexo\n");
                printf("3 - Data Nascimento\n");
                printf("4 - CPF\n");
                printf("\nInsira uma opcao: ");
                scanf("%d", &opcao);

                system("cls");

                if(opcao >= 0 && opcao <= 4) break;
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
                printf("\nDigite um novo sexo para modificar: ");
                char tsexo;
                fflush(stdin);
                scanf("%c", &tsexo);
                if(tsexo == 'm' || tsexo == 'M' || tsexo == 'f' || tsexo == 'F'){
                    temp->sexo = tsexo;
                    return SUCESSO;
                }
                else{
                    printf("\nDigite um sexo valido ('m' ou 'f')");
                    return ERRO;
                }
                break;
            }
            case 3:{
                printf("\nDigite a data de nascimento do aluno no formato (ddmmaaaa): ");
                int data;
                scanf("%d", &data);
                temp->anoNascimento = data % 10000;
                data /= 10000;
                temp->mesNascimento = data % 100;
                data /= 100;
                temp->diaNascimento = data;

                printf("\nAno nascimento: %d", temp->anoNascimento);
                printf("\nMes nascimento: %d", temp->mesNascimento);
                printf("\nDia nascimento: %d", temp->diaNascimento);
                return SUCESSO;
                break;
            }
            case 4:{
                printf("\nDigite o novo CPF: ");
                fflush(stdin);
                char tcpf[13];
                fgets(tcpf, 12, stdin);
                if(tcpf[12] ==  '\n') tcpf[12] = '\0';

                if(validar_cpf(tcpf) == SUCESSO){
                    printf("\nCPF validado com sucesso!\n");
                    strcpy(temp->cpf, tcpf);
                    return SUCESSO;
                }else{
                    printf("\nCPF invalido!\nErro ao cadastrar CPF\n");
                    return ERRO;
                }
                break;
            }

        }
            break;
        }
        temp = temp->prox;
    }

    printf("\nAluno nao encontrado");
    
    return ERRO;

}

int validar_cpf(char cpf[]){

    //verifica se o cpf informado tem menos de 11 digitos
    for(int i = 0; i < 11; i++){
        if(cpf[i] == '\0') return ERRO;
    }

    int icpf[11];
    int soma = 0;
    int resto1, resto2;
    int digito1, digito2;

    //conversao de tipos
    for(int i = 0; i < 11; i++){
        icpf[i] = cpf[i] - 48;
    }

    //calculo primeiro digito verificador
    for(int i = 0; i < 9; i++){
        soma += icpf[i] * (10 - i);
    }

    resto1 = soma % 11;

    if(resto1 < 2) digito1 = 0;
    else digito1 = 11 - resto1;

    //calculo segundo digito verificador
    soma = 0;
    for(int i = 0; i < 10; i++){
        soma += icpf[i] * (11 - i);
    }

    resto2 = soma % 11;
    if(resto2 < 2) digito1 = 0;
    else digito2 = 11 - resto2;

    if(icpf[9] == digito1 && icpf[10] == digito2) return SUCESSO;

    return ERRO;
}
