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

typedef struct Efila {
    Registro* dados;
    struct Efila* proximo;
} Efila;

typedef struct {
    Efila* head;
    Efila* tail;
    int qtde;
} Fila;

typedef struct {
    Registro* dados[20];
    int qtde;
} Heap;

typedef enum {
    ENFILEIRAMENTO,
    DESENFILEIRAMENTO
} Tipo_Operacao;

typedef struct {
    Registro* paciente;
    Tipo_Operacao Tipo_Operacao;
} Operacao;


typedef struct Epilha {
    struct Epilha* anterior;
    Operacao* dados;
    struct Epilha* proximo;
} Epilha;

typedef struct {
    Epilha* topo;
    int qtde;
} Pilha;

typedef struct Eabb {
    Registro* dados;
    struct Eabb* filho_esq;
    struct Eabb* filho_dir;
} Eabb;

typedef struct {
    Eabb* raiz;
    int qtde;
} Abb;

void push(Pilha *pilha, Operacao *operacao);

Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtde = 0;
    return lista;
}

Fila *criar_fila(){
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtde = 0;
    return fila;
}

Heap *criar_heap(){
    Heap *heap = malloc(sizeof(Heap));
    heap->dados[0] = NULL;
    heap->qtde = 0;
    return heap;
}

Pilha *criar_pilha(){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    pilha->qtde = 0;
    return pilha;
}

Abb *criar_arvore(){
	Abb* arvore = malloc(sizeof(Abb));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	return arvore;
}

// Cadastro

void cadastrar(Lista *lista) {
    Elista *nova_celula = malloc(sizeof(Elista));
    Registro *novo_registro = malloc(sizeof(Registro));
    Data *nova_data = malloc(sizeof(Data));

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

void mostrar_lista(Lista *lista){
    if (lista->inicio == NULL) {
        printf("\nNao ha paciente cadastrado.\n");
        return;
    }
    
    Elista *atual = lista->inicio;
    
    while(atual != NULL){
        printf("\nNome: %s\t", atual->dados->nome);
        printf("Idade: %d\t", atual->dados->idade);
        printf("RG: %c%c.%c%c%c.%c%c%c-%c\t", atual->dados->rg[0], atual->dados->rg[1], 
        atual->dados->rg[2], atual->dados->rg[3], atual->dados->rg[4],
        atual->dados->rg[5], atual->dados->rg[6], atual->dados->rg[7],
        atual->dados->rg[8]);
        printf("Data de entrada: %d/%d/%d", atual->dados->entrada->dia, atual->dados->entrada->mes, 
        atual->dados->entrada->ano);

        atual = atual->proximo;
    }
    printf("\n");
}

void atualizar_paciente(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nNao ha paciente cadastrado.\n");
        return;
    }

    Elista *paciente = encontrar_celula(lista);

    char novo_nome[100];
    int nova_idade;
    char novo_rg[15];
    int novo_dia;
    int novo_mes;
    int novo_ano;

    if (paciente == NULL) {
      return;  
    }
    
    printf("Digite o novo nome: ");
    fgets(novo_nome, sizeof(novo_nome), stdin);
    novo_nome[strcspn(novo_nome, "\n")] = '\0';
    printf("Digite a nova idade: ");
    scanf("%d", &nova_idade);
    clearBuffer();
    do {
        printf("Digite o novo RG (apenas numeros): ");
        fgets(novo_rg, sizeof(novo_rg), stdin);
        novo_rg[strcspn(novo_rg, "\n")] = '\0';
        if (strlen(novo_rg) != 9)
          printf("RG invalido.\n");
      } while (strlen(novo_rg) != 9);
    printf("Digite o novo dia de entrada: ");
    scanf("%d", &novo_dia);
    clearBuffer();
    printf("Digite o novo mes de entrada: ");
    scanf("%d", &novo_mes);
    clearBuffer();
    printf("Digite o novo ano de entrada: ");
    scanf("%d", &novo_ano);
    clearBuffer();

    
    strcpy(paciente->dados->nome, novo_nome);
    paciente->dados->idade = nova_idade;
    strcpy(paciente->dados->rg, novo_rg);
    paciente->dados->entrada->dia = novo_dia;
    paciente->dados->entrada->mes = novo_mes;
    paciente->dados->entrada->ano = novo_ano;

    printf("Paciente atualizado com sucesso!\n");
}

void remover_paciente(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("Nao ha paciente cadastrado.\n");
        return;
    }

    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    char rg[15];

    do {
        printf("Digite o RG (apenas numeros): ");
        fgets(rg, sizeof(rg), stdin);
        rg[strcspn(rg, "\n")] = '\0';
        if (strlen(rg) != 9)
          printf("RG invalido.\n");
      } while (strlen(rg) != 9);

    while (atual != NULL) {
        if (strcmp(atual->dados->rg, rg) == 0) {
            if (anterior == NULL) {
                lista->inicio = atual->proximo;
                break;
            } else {
                anterior->proximo = atual->proximo;
                break;
            }
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    free(atual);
    lista->qtde--;
    printf("Paciente removido com sucesso!\n");
    return;
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
                mostrar_lista(lista);
                break;
            case 4:
                atualizar_paciente(lista);
                break;
            case 5:
                remover_paciente(lista);
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

// Atendimento
void enfileirar(Fila *fila, Lista *lista, Pilha *pilha) {
    if (lista->inicio == NULL) {
        printf("Nao ha paciente cadastrado.\n");
        return;
    }

    Efila *nova = malloc(sizeof(Efila));
    Elista *paciente = encontrar_celula(lista);
    if (paciente == NULL) {
        return;
    }
    
    nova->dados = paciente->dados;
    nova->proximo = NULL;

    if (fila->qtde == 0) {
        fila->head = nova;
    } else {
        fila->tail->proximo = nova;
        //nova->anterior = Queue->tail;
    }
    fila->tail = nova;
    fila->qtde++;

    Operacao *op = malloc(sizeof(Operacao));
    op->paciente = nova->dados;
    op->Tipo_Operacao = ENFILEIRAMENTO;
    push(pilha, op);

    printf("Paciente enfileirado com sucesso!");
}

void desinfileirar(Fila *fila, Pilha *pilha) {
    if (fila->qtde == 0) {
        printf("Fila vazia.\n");
        return;
    }
    Efila *removido = fila->head;
    if (fila->qtde == 1) {
        fila->tail = NULL;
        fila->head = NULL;
    } else {
        //fila->head->proximo->anterior = NULL;      
        fila->head = fila->head->proximo;
    }

    Operacao *op = malloc(sizeof(Operacao));
    op->paciente = removido->dados;
    op->Tipo_Operacao = DESENFILEIRAMENTO;
    push(pilha, op);

    fila->qtde--;
    free(removido);

    printf("Paciente desifileirado!");
}

void mostrar_fila(Fila *fila) {
    if (fila->qtde == 0) {
        printf("Fila vazia.\n");
        return;
    }

    Efila *atual = fila->head;
    int cont = 1;
    while (atual != NULL)
    {
        printf("\n%d: Nome: %s\t", cont, atual->dados->nome);
        printf("Idade: %d\t", atual->dados->idade);
        printf("RG: %c%c.%c%c%c.%c%c%c-%c\t", atual->dados->rg[0], atual->dados->rg[1], 
        atual->dados->rg[2], atual->dados->rg[3], atual->dados->rg[4],
        atual->dados->rg[5], atual->dados->rg[6], atual->dados->rg[7],
        atual->dados->rg[8]);
        printf("Data de entrada: %d/%d/%d", atual->dados->entrada->dia, atual->dados->entrada->mes, 
        atual->dados->entrada->ano);

        atual = atual->proximo;
        cont++;
    }
    printf("\n");
}

void menu_atendimento(Lista *lista, Fila *fila, Pilha *pilha) {
    int opcao = 0;

    do {
        printf("\n");
        printf("Atendimento\n");
        printf("\n");
        printf("1 - Enfileirar paciente\n");
        printf("2 - Desenfileirar paciente\n");
        printf("3 - Mostrar Fila\n");
        printf("0 - Voltar\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                enfileirar(fila, lista, pilha);
                break;
            case 2:
                desinfileirar(fila, pilha);
                break;
            case 3:
                mostrar_fila(fila);
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

// Atendimento prioritário
int filho_esq(int pai) { 
    return 2 * pai + 1;
    }

int filho_dir(int pai) { 
    return 2 * pai + 2;
    }

int pai(int filho) { 
    return (filho - 1) / 2;
    }

int ultimo_pai(Heap *h) { 
    return (h->qtde / 2) - 1;
}

void peneirar_baixo(Heap *h, int pai) {
    int esq = filho_esq(pai);
    int dir = filho_dir(pai);
    int maior = pai;

    if (esq < h->qtde && h->dados[esq]->idade > h->dados[maior]->idade)
    {
        maior = esq;
    }

    if (dir < h->qtde && h->dados[dir]->idade > h->dados[maior]->idade)
    {
        maior = dir;
    }

    if (pai != maior) {
        Registro *temp = h->dados[pai];
        h->dados[pai] = h->dados[maior];
        h->dados[maior] = temp;
        peneirar_baixo(h, maior);
    }
}

void peneirar_cima(Heap *h, int i) {
    while (i > 0 && h->dados[pai(i)]->idade < h->dados[i]->idade) {
        Registro *temp = h->dados[pai(i)];
        h->dados[pai(i)] = h->dados[i];
        h->dados[i] = temp; 
        i = pai(i);
    }
}

void construir(Heap *h) {
    int n = ultimo_pai(h);
    for (int i = n; i >= 0; i--) {
        peneirar_baixo(h, i);
    }
}

void enfileirar_prioritario(Lista *lista, Heap *h) {
    if (h->qtde == 20) {
        printf("Capacidade maxima atingida!\n");
        return;
    }
    
    h->dados[h->qtde] = encontrar_celula(lista)->dados;
    h->qtde++;
    peneirar_cima(h, h->qtde - 1);
    printf("Paciente enfileirado com sucesso!\n");
}

void desenfileirar_prioritario(Heap *h) {
    if (h->qtde == 0) {
        printf("Fila vazia.\n");
        return;
    }
    
    h->dados[0] = h->dados[h->qtde - 1];
    h->qtde--;
    peneirar_baixo(h, 0);
    printf("Paciente desenfileirado com sucesso!\n");
}

void mostrar_prioritario(Heap *h) {
    if (h->qtde == 0) {
        printf("Fila vazia.\n");
        return;
    }

    for (int i = 0; i < h->qtde; i++) {
        printf("\n%d: Nome: %s\t", i + 1, h->dados[i]->nome);
        printf("Idade: %d\t", h->dados[i]->idade);
        printf("RG: %c%c.%c%c%c.%c%c%c-%c\t", h->dados[i]->rg[0], h->dados[i]->rg[1], 
        h->dados[i]->rg[2], h->dados[i]->rg[3], h->dados[i]->rg[4],
        h->dados[i]->rg[5], h->dados[i]->rg[6], h->dados[i]->rg[7],
        h->dados[i]->rg[8]);
        printf("Data de entrada: %d/%d/%d", h->dados[i]->entrada->dia, h->dados[i]->entrada->mes, 
        h->dados[i]->entrada->ano);
    }
    printf("\n");
}

void menu_prioritario(Lista *lista, Heap *heap) {
    int opcao = 0;

    do {
        printf("\n");
        printf("Atendimento Prioritario\n");
        printf("\n");
        printf("1 - Enfileirar paciente\n");
        printf("2 - Desenfileirar paciente\n");
        printf("3 - Mostrar Fila\n");
        printf("0 - Voltar\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                enfileirar_prioritario(lista, heap);
                break;
            case 2:
                desenfileirar_prioritario(heap);
                break;
            case 3:
                mostrar_prioritario(heap);
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

// Pesquisa
void menu_pesquisa(Lista *lista, Abb *arvore) {
    int opcao = 0;

    do {
        printf("\n");
        printf("Pesquisa\n");
        printf("\n");
        printf("1 - Filtrar por ano\n");
        printf("2 - Filtrar por mes\n");
        printf("3 - Filtrar por dia\n");
        printf("4 - Filtrar por idade\n");
        printf("0 - Voltar\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                printf("ano");
                break;
            case 2:
                printf("mes");
                break;
            case 3:
                printf("dia");
                break;
            case 4:
                printf("idade");
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

// Desfazer
void push(Pilha *pilha, Operacao *operacao) {
    Epilha *nova = malloc(sizeof(Epilha));
    Operacao *nova_op = malloc(sizeof(Operacao));
    *nova_op = *operacao;
    nova->dados = nova_op;
    if (pilha->qtde != 0) {
        nova->proximo = pilha->topo;
        pilha->topo->anterior = nova;
    }
    pilha->topo = nova;
    pilha->qtde++;
}

Operacao *pop(Pilha *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }
    
    Epilha *removida = pilha->topo;
    if (pilha->qtde == 1) {
        pilha->topo = NULL;
    } else {
        pilha->topo->anterior->proximo = NULL;
        pilha->topo = pilha->topo->anterior;
    }
    Operacao *op = removida->dados;
    free(removida);
    pilha->qtde--;

    return op;
}

void mostrar_pilha(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Nenhuma operacao encontrada.\n");
        return;
    }

    Epilha *atual = pilha->topo;
    printf("Mais recente:\n");
    while (atual != NULL) {

        printf("Paciente: %s\t", atual->dados->paciente->nome);
        printf("RG: %c%c.%c%c%c.%c%c%c-%c\t", atual->dados->paciente->rg[0], 
            atual->dados->paciente->rg[1], 
            atual->dados->paciente->rg[2], 
            atual->dados->paciente->rg[3], 
            atual->dados->paciente->rg[4],
            atual->dados->paciente->rg[5], 
            atual->dados->paciente->rg[6], 
            atual->dados->paciente->rg[7],
            atual->dados->paciente->rg[8]);
        if (atual->dados->Tipo_Operacao == ENFILEIRAMENTO) {
            printf("Tipo de operacao: Enfileiramento\n");
        } else {
            printf("Tipo de operacao: Desenfileiramento\n");
        }

        atual = atual->proximo;  
}  
    printf("\n");
}

void desfazer(Pilha *pilha, Fila *fila) {
    Operacao *op = pop(pilha);
    if (op == NULL) {
        printf("Nenhuma operacao armazenada.\n");
        return;
    }

    char resp;
    printf("\nPaciente: %s\t", op->paciente->nome);
    printf("RG: %c%c.%c%c%c.%c%c%c-%c\t", op->paciente->rg[0], 
        op->paciente->rg[1], 
        op->paciente->rg[2], 
        op->paciente->rg[3], 
        op->paciente->rg[4],
        op->paciente->rg[5], 
        op->paciente->rg[6], 
        op->paciente->rg[7],
        op->paciente->rg[8]);
    if (op->Tipo_Operacao == ENFILEIRAMENTO) {
        printf("Tipo de operacao: Enfileiramento\n");
    } else {
        printf("Tipo de operacao: Desenfileiramento\n");
    }
    printf("Deseja desfazer a operacao acima? (S/N) ");
    scanf(" %c", &resp);
    clearBuffer();

    if (resp == 'S' || resp == 's') {
        if (op->Tipo_Operacao == ENFILEIRAMENTO) {
            Efila *anterior = NULL;
            Efila *atual = fila->head;
        
            while (atual->proximo != NULL) {
                anterior = atual;
                atual = atual->proximo;
            }
        
            if (anterior == NULL) {
                fila->head = NULL;
                fila->tail = NULL;
            } else {
                anterior->proximo = NULL;
                fila->tail = anterior;
            }
        
            free(atual);
            fila->qtde--;
        } else {
            Efila *nova = malloc(sizeof(Efila));
            nova->dados = op->paciente;
            nova->proximo = fila->head;
            fila->head = nova;
            
            if (fila->qtde == 0) {
                fila->tail = nova;
            } 
            
            fila->qtde++;
        }
        free(op);
        printf("Operacao desfeita com sucesso!\n");
    } else {
        push(pilha, op);
        printf("Cancelando...\n");
    }
}

void menu_desfazer(Fila *fila, Pilha *pilha) {
    int opcao = 0;

    do {
        printf("\n");
        printf("Desfazer Operacao\n");
        printf("\n");
        printf("1 - Mostrar operacoes\n");
        printf("2 - Desfazer operacao\n");
        printf("0 - Voltar\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                mostrar_pilha(pilha);
                break;
            case 2:
                desfazer(pilha, fila);
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
    Fila *fila = criar_fila();
    Heap *heap = criar_heap();
    Pilha *pilha = criar_pilha();
    Abb *arvore = criar_arvore();
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
                menu_atendimento(lista, fila, pilha);
                break;
            case 3:
                menu_prioritario(lista, heap);
                break;
            case 4:
                menu_pesquisa(lista, arvore);
                break;
            case 5:
                menu_desfazer(fila, pilha);
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