#include <stdio.h>
#include <stdlib.h>

void clearBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct {
    int dia;
    int mes;
    int ano;
} Data; 

typedef struct {
    char nome[100];
    int idade;
    char rg[15];
    Data* entrada;
} Registro;

typedef struct {
    Registro* dados;
    struct Elista* proximo;
} Elista;

typedef struct {
    Elista* inicio;
    int qtde;
} Lista;

void menu_cadastro() {
    int opcao = 0;

    do {
        printf("\n");
        printf("Cadastro\n");
        printf("\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar paciente\n");
        printf("3 - Listar pacientes\n");
        printf("4 - Atualizar dados\n");
        printf("5 - Remover paciente\n");
        printf("0 - Voltar\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                printf("Cadastro\n");
                break;
            case 2:
                printf("Consulta\n");
                break;
            case 3:
                printf("Listar\n");
                break;
            case 4:
                printf("Atualizar\n");
                break;
            case 5:
                printf("Remover\n");
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (opcao != 0);
    return;
}


int main() {
    int opcao = 0;

    do {
        printf("\n");
        printf("Bem vindo a Clinica Quem Cuida Ajuda\n");
        printf("\n");
        printf("1 - Cadastro\n");
        printf("2 - Atendimento\n");
        printf("3 - Atendimento prioritario\n");
        printf("4 - Pesquisa\n");
        printf("5 - Desfazer\n");
        printf("6 - Carregar / Salvar\n");
        printf("7 - Sobre\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                menu_cadastro();
                break;
            case 2:
                printf("Atendimento\n");
                break;
            case 3:
                printf("Prioritario\n");
                break;
            case 4:
                printf("Pesquisa\n");
                break;
            case 5:
                printf("Desfazer\n");
                break;
            case 6:
                printf("C/S\n");
                break;
            case 7:
                printf("Sobre\n");
                break;
            case 0:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (opcao != 0);

    return 0;
    
}