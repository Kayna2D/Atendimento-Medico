#include <stdio.h>
#include <stdlib.h>

void clearBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
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
                printf("Cadastro\n");
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

            default:
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (opcao != 0);

    return 0;
    
}