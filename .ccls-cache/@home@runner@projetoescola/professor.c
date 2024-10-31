#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "professor.h"
#define TAM 20
#define ERRO 0
#define SUCESSO 1


int listarProfessor(struct Professor *atual) {
    printf("\nLista de Professores:");

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

void menuProfessor(struct Professor **listaProfessor){

    int sairProfessor = 1;
    int opcao = 1;

    while(sairProfessor){

        printf("\n\n Menu professor \n\n");
        printf("0 - Voltar\n");
        printf("1 - Cadastrar professor\n");
        printf("2 - Atualizar professor\n");
        printf("3 - Excluir professor\n");
        printf("4 - Listar professores\n");
        printf("5 - Listar professores por categoria\n");
        printf("\nInsira uma opcao: ");
        scanf("%d", &opcao);
        system("clear");

        switch(opcao){
            case 0:
                sairProfessor = 0;
                printf("Voltando...\n");
                break;
            case 1:
                if(inserirProfessor(listaProfessor)) printf("Professor adicionado com sucesso\n");
                break;
            case 2:
                atualizarProfessor(listaProfessor);
                break;
            case 3:
                removerProfessor(listaProfessor);
                break;
            case 4:
                listarProfessor(*listaProfessor);
                break;
            case 5:
                relatorioProfessor(*listaProfessor);
                break;
            default:
                printf("\nOpcao invalida!");
                break;
        }
    }

}



int relatorioProfessor(struct Professor *temp){

    int cont = 0;

    struct Professor *aux = temp;


    int opcao;

    printf("\n\n Relatorios \n\n");
    printf("0 - Voltar\n");
    printf("1 - Listar professores por sexo\n");
    printf("2 - Listar professores por nome (ordem alfabetica)\n");
    printf("3 - Listar professores por data de nascimento\n");
    printf("4 - Listar professores detalhadamente\n");
    
    printf("\nInsira uma opcao: ");
    scanf("%d", &opcao);
    system("clear");

    switch(opcao){
        case 0:
            printf("\nVoltando...");
            break;
        case 1:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }
            printf("\n1 - Masculino");
            printf("\n2 - Feminino");
            printf("\nQual sexo deseja filtrar: ");
            scanf("%d", &opcao);
            if(opcao == 1){
                printf("Professores do sexo masculino: ");
                while(temp != NULL){
                    if(temp->sexo == 'M' || temp->sexo == 'm') printf("\n%s", temp->nome);
                    temp = temp->prox; 
                }
            }else if(opcao == 2){
                printf("Professores do sexo feminino: ");
                while(temp != NULL){
                    if(temp->sexo == 'F' || temp->sexo == 'f') printf("\n%s", temp->nome);
                    temp = temp->prox; 
                }
            }else{
                printf("\nInsira uma opcao valida!");
                return ERRO;
            }
            break;
        case 2:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }

            while (temp != NULL) { //verifica a quantidade de professores cadastrados
                cont++;
                temp = temp->prox;
            }

            char **professor = (char**) malloc(cont * sizeof(char*)); // alocando matriz de strings
            for(int i = 0; i < cont; i++){
                professor[i] = (char*) malloc(TAM * sizeof(char));
            }

            for(int i = 0; i < cont; i++){
                strcpy(professor[i], aux->nome);
                aux = aux->prox;
            }

            char saux[TAM];

            for(int i = 0; i < cont; i++){
                for(int j = i + 1; j < cont; j++){
                    if(strcmp(professor[i], professor[j]) > 0){
                        strcpy(saux, professor[i]);
                        strcpy(professor[i], professor[j]);
                        strcpy(professor[j], saux);
                    }
                }
            }

            for(int i = 0; i < cont; i++){
                printf("\n%s", professor[i]);
            }

            for (int i = 0; i < cont; i++) {
                free(professor[i]); // libera cada string individualmente
            }
            free(professor);
            break;
        case 3:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }

            while (temp != NULL) { //verifica a quantidade de professores cadastrados e calcula a idade em dias
                temp->diasIdade = temp->anoNascimento * 365.3 + temp->mesNascimento * 30 + temp->diaNascimento;
                cont++;
                temp = temp->prox;
            }
            
            int *idade = (int*) malloc(cont * sizeof(int));
            char **professores = (char**) malloc(cont * sizeof(char*)); // alocando matriz de strings

            for (int i = 0; i < cont; i++) {
                professores[i] = (char*) malloc(TAM * sizeof(char));
            }
            
            for(int i = 0; i < cont; i++){
                idade[i] = aux->diasIdade;
                strcpy(professores[i], aux->nome);
                aux = aux->prox;
            }

            int iaux;
            char naux[TAM];

            for(int i = 0; i < cont; i++){
                for(int j = i + 1; j < cont; j++){
                    if(idade[j] > idade[i]){
                        iaux = idade[j];
                        idade[j] = idade[i];
                        idade[i] = iaux;
                        strcpy(naux, professores[j]);
                        strcpy(professores[j], professores[i]);
                        strcpy(professores[i], naux);
                    }
                }
                printf("\nProfessor: %s", professores[i]);
            }
            for (int i = 0; i < cont; i++) {
                free(professores[i]); // libera cada string individualmente
            }
            free(professores);
            free(idade);
            break;
        case 4:
            if(temp == NULL){
                printf("\nLista Vazia!");
                return ERRO;
            }

            while (temp != NULL) { // Corrige a condição de parada
                printf("\n Nome: %s", temp->nome);
                printf(" | Matricula: %d", temp->matricula);
                printf(" | Sexo: %c", temp->sexo);
                printf(" | CPF: %s", temp->cpf);
                printf(" | Data de nascimento: %d/%d/%d", temp->diaNascimento, temp->mesNascimento, temp->anoNascimento);
                temp = temp->prox;
            }
            break;
        default:
            break;
    }


    return SUCESSO;
}




int inserirProfessor(struct Professor **listaProfessor){
    struct Professor *novo;
    novo = malloc(sizeof(struct Professor));

    //verifica se o malloc retornou NULL
    if(novo == NULL){
        printf("ERRO AO ALOCAR MEMORIA");
        exit(ERRO);
    }

    novo->prox = NULL;
    printf("\nDigite o nome do professor: ");

    fflush(stdin);
    fgets(novo->nome, TAM, stdin);
    printf("\nDigite o sexo do professor ('m' ou 'f'): ");
    scanf("%c", &novo->sexo);
    printf("\nDigite a data de nascimento do professor no formato (ddmmaaaa): ");
    int data, dia, mes, ano;
    scanf("%d", &data);
    ano = data % 10000;
    data /= 10000;
    mes = data % 100;
    data /= 100;
    dia = data;

    novo->matricula = rand() * dia % 10000;
    printf("\nMatricula gerada: %d", novo->matricula);

    if(validar_data_nascimento(dia, mes, ano) == SUCESSO){
        novo->anoNascimento = ano;
        novo->mesNascimento = mes;
        novo->diaNascimento = dia;
    }else{
        printf("\nData invalida!");
        free(novo);
        return ERRO;
    }

    printf("\nAno nascimento: %d", novo->anoNascimento);
    printf("\nMes nascimento: %d", novo->mesNascimento);
    printf("\nDia nascimento: %d", novo->diaNascimento);

    printf("\nDigite o CPF do Professor: ");
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

    if (*listaProfessor == NULL) { // se a lista estiver vazia
        *listaProfessor = novo; 
    } else {
        struct Professor *temp = *listaProfessor;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = novo;
    }

    return SUCESSO;
}

int removerProfessor(struct Professor **listaProfessor){
    struct Professor *temp = *listaProfessor;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do professor a ser removido: ");
    fgets(string, TAM, stdin);

    //remoção do \n deixado no final da string pelo fgets
    size_t ln = strlen(string);
    if(string[ln-1] == '\n') string[ln-1] = '\0';

    if(!strcmp(temp->nome, string)){ //caso o Professor a ser removido seja o primeiro da lista
        *listaProfessor = temp->prox;
        free(temp);
        return SUCESSO;
    }

    while(temp != NULL){
        struct Professor *tempprox = temp->prox; // celula posterior a temp
        if(!strcmp(tempprox->nome, string)){
            temp->prox = tempprox->prox;
            free(tempprox);
            return SUCESSO;
        }
        temp = temp->prox;
    }
    return ERRO;
}


int atualizarProfessor(struct Professor **listaProfessor){

    struct Professor *temp = *listaProfessor;
    char string[TAM];
    fflush(stdin);
    printf("\nDigite o nome do professor para atualizar: ");
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

                system("clear");

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
                printf("\nDigite a data de nascimento do professor no formato (ddmmaaaa): ");
                int data, dia, mes, ano;
                scanf("%d", &data);
                ano = data % 10000;
                data /= 10000;
                mes = data % 100;
                data /= 100;
                dia = data;

                if(validar_data_nascimento(dia, mes, ano) == SUCESSO){
                    temp->anoNascimento = ano;
                    temp->mesNascimento = mes;
                    temp->diaNascimento = dia;
                }else{
                    printf("\nData invalida!");
                    return ERRO;
                }

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

    printf("\nProfessor nao encontrado");
    
    return ERRO;

}