#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Elista {
    Registro* dados;
    struct Elista* proximo;
} Elista;

typedef struct {
    Elista* inicio;
    int qtde;
} Lista;


Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtde = 0;
    return lista;
}

// Cadastro

void cadastrar(Lista *lista) {
    Elista *nova_celula = malloc(sizeof(Elista));
    Registro *novo_registro = malloc(sizeof(Registro));
    Data *nova_data = malloc(sizeof(Data));

    printf("\nCadastro de Novo Paciente\n");

    printf("Digite o nome: ");
    fgets(novo_registro->nome, sizeof(novo_registro->nome), stdin);
    novo_registro->nome[strcspn(novo_registro->nome, "\n")] = '\0';
    printf("Digite a idade: ");
    scanf("%d", &novo_registro->idade);
    clearBuffer();
    do {
        printf("Digite o RG (apenas numeros): ");
        fgets(novo_registro->rg, sizeof(novo_registro->rg), stdin);
        novo_registro->rg[strcspn(novo_registro->rg, "\n")] = '\0';
        if (strlen(novo_registro->rg) != 9)
          printf("RG invalido.\n");
      } while (strlen(novo_registro->rg) != 9);
    printf("Digite o dia de entrada: ");
    scanf("%d", &nova_data->dia);
    clearBuffer();
    printf("Digite o mes de entrada: ");
    scanf("%d", &nova_data->mes);
    clearBuffer();
    printf("Digite o ano de entrada: ");
    scanf("%d", &nova_data->ano);
    clearBuffer();

    novo_registro->entrada = nova_data;
    nova_celula->dados = novo_registro;
    nova_celula->proximo = lista->inicio;
    lista->inicio = nova_celula;
    lista->qtde++;
    printf("\nPaciente cadastrado com sucesso!\n");
}

Elista *encontrar_celula(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nNao ha paciente cadastrado.\n");
        return NULL;
    }
    char rg[15];
    Elista *atual = lista->inicio;

    do {
        printf("Digite o RG (apenas numeros): ");
        fgets(rg, sizeof(rg), stdin);
        rg[strcspn(rg, "\n")] = '\0';
        if (strlen(rg) != 9)
          printf("RG invalido.\n");
      } while (strlen(rg) != 9);

    while (atual != NULL) {
        if (strcmp(atual->dados->rg, rg) == 0) {
            return atual;
        }
        atual = atual->proximo; 
    }
    printf("\nPaciente nao encontrado.\n");
    return NULL;
}

void consultar(Lista *lista) {
    Elista *paciente = encontrar_celula(lista);

    if (paciente == NULL) {
        return;
    }

    printf("\nNome: %s\n", paciente->dados->nome);
    printf("Idade: %d\n", paciente->dados->idade);
    printf("RG: %c%c.%c%c%c.%c%c%c-%c\n", paciente->dados->rg[0], paciente->dados->rg[1], 
        paciente->dados->rg[2], paciente->dados->rg[3], paciente->dados->rg[4],
        paciente->dados->rg[5], paciente->dados->rg[6], paciente->dados->rg[7],
        paciente->dados->rg[8]);
    printf("Data de entrada: %d/%d/%d\n", paciente->dados->entrada->dia, paciente->dados->entrada->mes, 
        paciente->dados->entrada->ano);
}

void menu_cadastro(Lista *lista) {
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
                cadastrar(lista);
                break;
            case 2:
                consultar(lista);
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
    Lista *lista = criar_lista();
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
                menu_cadastro(lista);
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