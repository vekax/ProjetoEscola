#include <stdio.h>
#define TAM 3

// O menuAluno e o struct n tava rodando antes do menu ent tive que trazer eles pra ca, dps ce muda onde ele fica dps se quiser

typedef struct Aluno{
    int matricula;
    char nome[51];
    char sexo;
    char data[11];
    char cpf[12];
}Aluno;


int exibirMenu(){
    int opcao;
    printf("\nMenu Escola\n");
    printf("0 - Sair\n");
    printf("1 - Menu Aluno\n");
    printf("2 - Menu Professor\n");
    printf("3 - Menu Disciplina\n");
    scanf("%d", &opcao);

    return opcao;
}

void cadastroAluno(struct Aluno *listaAluno, int qtdAluno){
    printf("Digite a matricula: ");
    scanf("%d", &listaAluno[qtdAluno].matricula);
    printf("Digite o nome do aluno: ");fflush(stdin);
    gets(listaAluno[qtdAluno].nome);
    printf("Digite o sexo do aluno: ");fflush(stdin);
    scanf("%c", &listaAluno[qtdAluno].sexo);
    printf("Digite a data de nascimento do aluno: ");fflush(stdin);
    gets(listaAluno[qtdAluno].data);
    printf("Digite o CPF do aluno: ");fflush(stdin);
    gets(&listaAluno[qtdAluno].cpf);

    qtdAluno++;
}

void menuAluno(int opcao, struct Aluno *listaAluno, int qtdAluno){
    int sairAluno = 1;

    while(sairAluno){
        printf("Menu aluno!\n");
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
                cadastroAluno(listaAluno, qtdAluno);
                break;
            case 2:
                printf("Teste2");
                break;
            case 3:
                printf("Teste3");
                break;
            case 4:
                printf("Teste4");
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    }

}

void menu(int opcao, struct Aluno *listaAluno, int qtdAluno){
    switch(opcao){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            printf("Menu Aluno selecionado\n");
            menuAluno(opcao, listaAluno, qtdAluno);
            break;
        case 2:
            printf("Menu Professor selecionado\n");
            break;
        case 3:
            printf("Menu Disciplina selecionado\n");
            break;
        default:
            printf("Digite uma opcao valida!\n");
            break;
    }
}

int main(){

    int opcao = 1, qtdAluno = 0;
    struct Aluno listaAluno[TAM];

    while(opcao){
        opcao = exibirMenu();
        menu(opcao, listaAluno, qtdAluno);

    }

    return 0;
}
