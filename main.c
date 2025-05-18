// Importa bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Limpa buffer de entrada
void clearBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Estrutura da data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data; 

// Estrutura do registro de dados do paciente
typedef struct {
    char nome[100];
    int idade;
    char rg[15];
    Data* entrada;
} Registro;

// Célula da lista
typedef struct Elista {
    Registro* dados;
    struct Elista* proximo;
} Elista;

// LDDE
typedef struct {
    Elista* inicio;
    int qtde;
} Lista;

// Célula  da fila
typedef struct Efila {
    Registro* dados;
    struct Efila* proximo;
} Efila;

// Fila
typedef struct {
    Efila* head;
    Efila* tail;
    int qtde;
} Fila;

// Heap
typedef struct {
    Registro* dados[20];
    int qtde;
} Heap;

// Tipos de operações enumerados
typedef enum {
    ENFILEIRAMENTO,
    DESENFILEIRAMENTO
} Tipo_Operacao;

// Estrutura da operação
typedef struct {
    Registro* paciente;
    Tipo_Operacao Tipo_Operacao;
} Operacao;

// Célula da pilha
typedef struct Epilha {
    struct Epilha* anterior;
    Operacao* dados;
    struct Epilha* proximo;
} Epilha;

// Pilha
typedef struct {
    Epilha* topo;
    int qtde;
} Pilha;

// Célula da árvore
typedef struct Eabb {
    Registro* dados;
    struct Eabb* filho_esq;
    struct Eabb* filho_dir;
} Eabb;

// Árvore binária 
typedef struct {
    Eabb* raiz;
    int qtde;
} Abb;

void push(Pilha *pilha, Operacao *operacao);

// Funções para criar estrutura
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

    // Pede os dados
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
      } while (strlen(novo_registro->rg) != 9); // Checa se RG é válido
    printf("Digite o dia de entrada: ");
    scanf("%d", &nova_data->dia);
    clearBuffer();
    printf("Digite o mes de entrada: ");
    scanf("%d", &nova_data->mes);
    clearBuffer();
    printf("Digite o ano de entrada: ");
    scanf("%d", &nova_data->ano);
    clearBuffer();

    // Guarda os dados na LDDE
    novo_registro->entrada = nova_data;
    nova_celula->dados = novo_registro;
    nova_celula->proximo = lista->inicio;
    lista->inicio = nova_celula;
    lista->qtde++;
    printf("\nPaciente cadastrado com sucesso!\n");
}

// Encontra célula pelo RG
Elista *encontrar_celula(Lista *lista) {
    if (lista->inicio == NULL) { // Checa se tem alguém na lista
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

    while (atual != NULL) { // Percorre a lista até encontrar o RG informado
        if (strcmp(atual->dados->rg, rg) == 0) {
            return atual;
        }
        atual = atual->proximo; 
    }
    printf("\nPaciente nao encontrado.\n");
    return NULL;
}

// Consulta e mostra dados do paciente informado
void consultar(Lista *lista) { 
    Elista *paciente = encontrar_celula(lista); 

    if (paciente == NULL) { // Paciente não encontrado
        return;
    }

    // Mostra dados
    printf("\nNome: %s\n", paciente->dados->nome);
    printf("Idade: %d\n", paciente->dados->idade);
    printf("RG: %c%c.%c%c%c.%c%c%c-%c\n", paciente->dados->rg[0], paciente->dados->rg[1], 
        paciente->dados->rg[2], paciente->dados->rg[3], paciente->dados->rg[4],
        paciente->dados->rg[5], paciente->dados->rg[6], paciente->dados->rg[7],
        paciente->dados->rg[8]);
    printf("Data de entrada: %d/%d/%d\n", paciente->dados->entrada->dia, paciente->dados->entrada->mes, 
        paciente->dados->entrada->ano);
}

// Lista todos os pacientes
void mostrar_lista(Lista *lista){
    if (lista->inicio == NULL) {
        printf("\nNao ha paciente cadastrado.\n");
        return;
    }
    
    Elista *atual = lista->inicio;
    
    while(atual != NULL){ // Percorre a lista mostrando todos os dados
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

// Atualiza dados do paciente informado
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

    // Substitui os dados da célula pelos novos
    strcpy(paciente->dados->nome, novo_nome);
    paciente->dados->idade = nova_idade;
    strcpy(paciente->dados->rg, novo_rg);
    paciente->dados->entrada->dia = novo_dia;
    paciente->dados->entrada->mes = novo_mes;
    paciente->dados->entrada->ano = novo_ano;

    printf("Paciente atualizado com sucesso!\n");
}

// Remove um registro da lista
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
            if (anterior == NULL) { // Exclusão no início
                lista->inicio = atual->proximo; // Início passa a ser a segunda  célula
                break;
            } else { 
                anterior->proximo = atual->proximo; // "Pula" a célula excluida 
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

    free(atual); // Libera a célula desejada da memória
    lista->qtde--; // Diminui a quantidade de células na lista
    printf("Paciente removido com sucesso!\n");
    return;
}

// Menu das funções da lista
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

// Enfileira paciente na fila normal
void enfileirar(Fila *fila, Lista *lista, Pilha *pilha) {
    if (lista->inicio == NULL) { // Checa se há registro para ser enfileirado
        printf("Nao ha paciente cadastrado.\n");
        return;
    }

    Efila *nova = malloc(sizeof(Efila));
    Elista *paciente = encontrar_celula(lista);
    if (paciente == NULL) {
        return;
    }
    
    nova->dados = paciente->dados; // Coloca os dados do paciente informado na nova célula
    nova->proximo = NULL;

    if (fila->qtde == 0) { // Enfileira no início da fila
        fila->head = nova;
    } else {
        fila->tail->proximo = nova; // Enfileira após tail em caso de inserção no início ou fim
    }
    fila->tail = nova;
    fila->qtde++;

    // Guarda tipo de operação e dados do paciente 
    Operacao *op = malloc(sizeof(Operacao));
    op->paciente = nova->dados;
    op->Tipo_Operacao = ENFILEIRAMENTO;
    push(pilha, op); // Empilha operação

    printf("Paciente enfileirado com sucesso!");
}

// Desenfileira paciente da fila normal
void desinfileirar(Fila *fila, Pilha *pilha) {
    if (fila->qtde == 0) { // Checa se há paciente na fila
        printf("Fila vazia.\n");
        return;
    }
    Efila *removido = fila->head;
    if (fila->qtde == 1) { // Desenfileiramento no início
        // Anula ponteiros
        fila->tail = NULL;
        fila->head = NULL;
    } else {     
        fila->head = fila->head->proximo; // Início da fila passa a ser a segunda célula
    }

    // Guarda tipo de operação e dados do paciente removido
    Operacao *op = malloc(sizeof(Operacao));
    op->paciente = removido->dados;
    op->Tipo_Operacao = DESENFILEIRAMENTO;
    push(pilha, op); // Empilha operação

    fila->qtde--;
    free(removido);

    printf("Paciente desifileirado!");
}

// Mostra todos os pacientes da enfileirados
void mostrar_fila(Fila *fila) {
    if (fila->qtde == 0) {
        printf("Fila vazia.\n");
        return;
    }

    Efila *atual = fila->head;
    int cont = 1; // Contagem para indicar a posição do paciente
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

        // Percorre a fila e incrementa a posição
        atual = atual->proximo;
        cont++;
    }
    printf("\n");
}

// Menu das funções de fila
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

// Funções para a manipulação da Heap
// Encontra filho esquerdo
int filho_esq(int pai) { 
    return 2 * pai + 1;
    }
// Encontra filho direito
int filho_dir(int pai) { 
    return 2 * pai + 2;
    }
// Encontra pai
int pai(int filho) { 
    return (filho - 1) / 2;
    }
// encontra o pai mais a direita (último)
int ultimo_pai(Heap *h) { 
    return (h->qtde / 2) - 1;
}

// Mantém a propriedade da heap na remoção
void peneirar_baixo(Heap *h, int pai) {
    int esq = filho_esq(pai);
    int dir = filho_dir(pai);
    int maior = pai;

    // Checa se a idade do filho esquerdo é maior que a do pai
    if (esq < h->qtde && h->dados[esq]->idade > h->dados[maior]->idade) {
        maior = esq;
    }

    // Checa se a idade do filho direito é maior que a do pai
    if (dir < h->qtde && h->dados[dir]->idade > h->dados[maior]->idade) {
        maior = dir;
    }

    // Faz a troca se o ponteiro se o pai não for o maior
    if (pai != maior) {
        Registro *temp = h->dados[pai];
        h->dados[pai] = h->dados[maior];
        h->dados[maior] = temp;
        peneirar_baixo(h, maior); // Chama peneirar recursivamente
    }
}

// Mantém a propriedade da heap na inserção 
void peneirar_cima(Heap *h, int i) {
    // Troca de dados entre pai e filho até o pai ter a maior idade da comparação
    while (i > 0 && h->dados[pai(i)]->idade < h->dados[i]->idade) { 
        Registro *temp = h->dados[pai(i)];
        h->dados[pai(i)] = h->dados[i];
        h->dados[i] = temp; 
        i = pai(i);
    }
}

/* void construir(Heap *h) {
    int n = ultimo_pai(h);
    for (int i = n; i >= 0; i--) {
        peneirar_baixo(h, i);
    }
} */

// Enfileira paciente na lista prioritária
void enfileirar_prioritario(Lista *lista, Heap *h) {
    if (h->qtde == 20) { // Capacidade de 20 pacientes
        printf("Capacidade maxima atingida!\n");
        return;
    }
    
    h->dados[h->qtde] = encontrar_celula(lista)->dados; // Pede paciente e registra-o no array
    h->qtde++; // Incrementa quantidade
    peneirar_cima(h, h->qtde - 1); // Peneira para cima a partir do elemento inserido
    printf("Paciente enfileirado com sucesso!\n");
}

// Desenfileira o paciente mais velho
void desenfileirar_prioritario(Heap *h) {
    if (h->qtde == 0) { 
        printf("Fila vazia.\n");
        return;
    }
    
    h->dados[0] = h->dados[h->qtde - 1]; // Último paciente passa a ser a raíz
    h->qtde--;
    peneirar_baixo(h, 0); // Peneira para baixo a partir da raíz para manter propriedade da heap
    printf("Paciente desenfileirado com sucesso!\n");
}

// Mostra todos os pacientes na lista prioritária
void mostrar_prioritario(Heap *h) {
    if (h->qtde == 0) {
        printf("Fila vazia.\n");
        return;
    }

    // Mostra todos os dados do array
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

// Menu para funções de heap
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

// Percorre a árvore na ordem esquerda-raiz-direita
void in_ordem(Eabb *raiz) {
    if (raiz != NULL) {
        in_ordem(raiz->filho_esq);
        printf("\nNome: %s\t", raiz->dados->nome);
        printf("Idade: %d\t", raiz->dados->idade);
        printf("RG: %c%c.%c%c%c.%c%c%c-%c\t", raiz->dados->rg[0], raiz->dados->rg[1], 
        raiz->dados->rg[2], raiz->dados->rg[3], raiz->dados->rg[4],
        raiz->dados->rg[5], raiz->dados->rg[6], raiz->dados->rg[7],
        raiz->dados->rg[8]);
        printf("Data de entrada: %d/%d/%d", raiz->dados->entrada->dia, raiz->dados->entrada->mes, 
        raiz->dados->entrada->ano);
        in_ordem(raiz->filho_dir);
    }
}

// Insere paciente na árvore ordenada por ano
void inserir_ano(Abb *arvore, Registro *paciente) {
    Eabb* novo = malloc(sizeof(Eabb));
    novo->dados = paciente;
    novo->filho_dir = NULL;
    novo->filho_esq = NULL;

	Eabb* anterior = NULL;
	Eabb* atual = arvore->raiz;

	while(atual != NULL){ // Percorre a árvore
		anterior = atual;
		if(paciente->entrada->ano <= anterior->dados->entrada->ano){
			atual = atual->filho_esq;
		}else{
			atual = atual->filho_dir;
		}
	}

	if(anterior != NULL){ 
		if(paciente->entrada->ano <= anterior->dados->entrada->ano){
			anterior->filho_esq = novo; // Inserção na esquerda
		}else{
			anterior->filho_dir = novo; // inserção na direita
		}
	}else{
		arvore->raiz = novo; // Inserção na raíz
	}
	arvore->qtde++;
}

// Insere paciente na árvore ordenada por mes
void inserir_mes(Abb *arvore, Registro *paciente) {
    Eabb* novo = malloc(sizeof(Eabb));
    novo->dados = paciente;
    novo->filho_dir = NULL;
    novo->filho_esq = NULL;

	Eabb* anterior = NULL;
	Eabb* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(paciente->entrada->mes <= anterior->dados->entrada->mes){
			atual = atual->filho_esq;
		}else{
			atual = atual->filho_dir;
		}
	}

	if(anterior != NULL){
		if(paciente->entrada->mes <= anterior->dados->entrada->mes){
			anterior->filho_esq = novo;
		}else{
			anterior->filho_dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;
}

// Insere paciente na árvore ordenada por dia
void inserir_dia(Abb *arvore, Registro *paciente) {
    Eabb* novo = malloc(sizeof(Eabb));
    novo->dados = paciente;
    novo->filho_dir = NULL;
    novo->filho_esq = NULL;

	Eabb* anterior = NULL;
	Eabb* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(paciente->entrada->dia <= anterior->dados->entrada->dia){
			atual = atual->filho_esq;
		}else{
			atual = atual->filho_dir;
		}
	}

	if(anterior != NULL){
		if(paciente->entrada->dia <= anterior->dados->entrada->dia){
			anterior->filho_esq = novo;
		}else{
			anterior->filho_dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;
}

// Insere paciente na árvore ordenada por idade
void inserir_idade(Abb *arvore, Registro *paciente) {
    Eabb* novo = malloc(sizeof(Eabb));
    novo->dados = paciente;
    novo->filho_dir = NULL;
    novo->filho_esq = NULL;

	Eabb* anterior = NULL;
	Eabb* atual = arvore->raiz;
	while(atual != NULL){
		anterior = atual;
		if(paciente->idade <= anterior->dados->idade){
			atual = atual->filho_esq;
		}else{
			atual = atual->filho_dir;
		}
	}

	if(anterior != NULL){
		if(paciente->idade <= anterior->dados->idade){
			anterior->filho_esq = novo;
		}else{
			anterior->filho_dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;
}

// Menu para funções de árvore binária
void menu_pesquisa(Lista *lista) {
    if (lista->qtde == 0) {
        printf("Nenhum registro encontrado.\n");
        return;
    } 
     Abb* arvore_ano = NULL;
     Abb* arvore_mes = NULL;
     Abb* arvore_dia = NULL;
     Abb* arvore_idade = NULL;

    // Cria árvores uma vez para cada menu_pesquisa aberto
    if (arvore_ano == NULL) {
        arvore_ano = criar_arvore();
        arvore_mes = criar_arvore();
        arvore_dia = criar_arvore();
        arvore_idade = criar_arvore();

        Elista* atual = lista->inicio;
        // Insere todos os dados da lista nas diferentes árvores
        while (atual != NULL) {
            inserir_ano(arvore_ano, atual->dados);
            inserir_mes(arvore_mes, atual->dados);
            inserir_dia(arvore_dia, atual->dados);
            inserir_idade(arvore_idade, atual->dados);
            atual = atual->proximo;
        }
        
    }
    
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
                in_ordem(arvore_ano->raiz);
                break;
            case 2:
                in_ordem(arvore_mes->raiz);
                break;
            case 3:
                in_ordem(arvore_dia->raiz);
                break;
            case 4:
                in_ordem(arvore_idade->raiz);
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

// Empilha operação
void push(Pilha *pilha, Operacao *operacao) {
    Epilha *nova = malloc(sizeof(Epilha));
    nova->dados = operacao;
    nova->anterior = NULL;
    nova->proximo = NULL;
    if (pilha->qtde > 0) { // Primeira célula
        pilha->topo->proximo = nova;
        nova->anterior = pilha->topo;
    }
    pilha->topo = nova; // Coloca nova operação no topo da pilha
    pilha->qtde++;
}

// Desempilha operação
Operacao *pop(Pilha *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }
    
    Epilha *removida = pilha->topo; // Operação no topo a ser removida
    Operacao *op = removida->dados; // Guarda os dados da operação

    if (pilha->qtde == 1) { // Remoção em pilha unitária
        pilha->topo = NULL; // Nada no topo da pilha
    } else {
        pilha->topo->anterior->proximo = NULL; // Ponteiro proximo da penúltima célula anulado
        pilha->topo = pilha->topo->anterior; // Topo passa a ser penúltima célula
    }
    free(removida); // Libera célula 
    pilha->qtde--;

    return op; // Retorna os dados da operação desempilhadada
}

// Mostra historico de operações    
void mostrar_pilha(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Nenhuma operacao encontrada.\n");
        return;
    }

    // Mostra as operações da mais recente à mais antiga
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
        if (atual->dados->Tipo_Operacao == ENFILEIRAMENTO) { // Checa o tipo de operação
            printf("Tipo de operacao: Enfileiramento\n");
        } else {
            printf("Tipo de operacao: Desenfileiramento\n");
        }

        atual = atual->anterior;  
}  
    printf("\n");
}

// Desfaz a operação no topo da pilha
void desfazer(Pilha *pilha, Fila *fila) {
    Operacao *op = pop(pilha); // Guarda os dados da última operação e a desempilha
    if (op == NULL) {
        printf("Nenhuma operacao armazenada.\n");
        return;
    }

    char resp;
    // Mostra a última operação
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
    // Pede confirmação
    printf("Deseja desfazer a operacao acima? (S/N) ");
    scanf(" %c", &resp);
    clearBuffer();

    if (resp == 'S' || resp == 's') {
        if (op->Tipo_Operacao == ENFILEIRAMENTO) {
            Efila *anterior = NULL;
            Efila *atual = fila->head;
        
            while (atual->proximo != NULL) { // Percorre a fila até o último paciente
                anterior = atual;
                atual = atual->proximo;
            }
        
            if (anterior == NULL) { // Fila unitária
                fila->head = NULL;
                fila->tail = NULL;
            } else { 
                anterior->proximo = NULL;
                fila->tail = anterior; // Último paciente passa a ser o penúltimo
            }
        
            free(atual); // Libera o último paciente da memória
            fila->qtde--;
        } else {
            // Recria o paciente desenfileirado
            Efila *nova = malloc(sizeof(Efila));
            nova->dados = op->paciente;
            // Coloca o paciente no início da fila
            nova->proximo = fila->head; 
            fila->head = nova; 
            
            if (fila->qtde == 0) { // Fila vazia 
                fila->tail = nova;
            } 
            
            fila->qtde++;
        }
        free(op); //  Libera operação da memória
        printf("Operacao desfeita com sucesso!\n");
    } else {
        push(pilha, op); // Empilha operação novamente
        printf("Cancelando...\n");
    }
}

// Menu para operações de pilha
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

// C/S
// Função para salvar pacientes
void salvar (Lista *lista) {
    if (lista->qtde == 0) {
        printf("Nao ha pacientes para salvar.\n");
        return;
    }

    // Abre arquivo em mode de escrita
    FILE *f = fopen("pacientes.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Percorre a lista, escrevendo todos os pacientes em ordem
    Elista *atual = lista->inicio;
    while (atual != NULL) {
        fprintf(f, "%s\n", atual->dados->nome);
        fprintf(f, "%d\n", atual->dados->idade);
        fprintf(f, "%s\n", atual->dados->rg);
        fprintf(f, "%d\n", atual->dados->entrada->dia);
        fprintf(f, "%d\n", atual->dados->entrada->mes);
        fprintf(f, "%d\n", atual->dados->entrada->ano);
        
        atual = atual->proximo;
    }

    fclose(f); // Fecha arquivo
    printf("Dados salvos com sucesso!\n");
} 

// Carrega pacientes do arquivo de texto
void carregar (Lista *lista) {
    FILE *f = fopen("pacientes.txt", "r"); // Abre arquivo em modo leitura
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Apaga todos os itens se a lista não estiver vazia
    while (lista->inicio != NULL) {
        Elista *temp = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
        lista->qtde--;
    }


    Registro* registros[1000];  // Array temporário para pegar os dados do arquivo
    Data* datas[1000];
    int total = 0; 
    char linha[500];

    while (fgets(linha, sizeof(linha), f) != NULL) {
        registros[total] = malloc(sizeof(Registro));
        datas[total] = malloc(sizeof(Data));
        
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(registros[total]->nome, linha);
        
        fgets(linha, sizeof(linha), f);
        registros[total]->idade = atoi(linha);
        
        fgets(linha, sizeof(linha), f);
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(registros[total]->rg, linha);
        
        fgets(linha, sizeof(linha), f);
        datas[total]->dia = atoi(linha);
        
        fgets(linha, sizeof(linha), f);
        datas[total]->mes = atoi(linha);
        
        fgets(linha, sizeof(linha), f);
        datas[total]->ano = atoi(linha);
        
        registros[total]->entrada = datas[total];
        total++;
    }
    
    fclose(f);

    // Insere na lista na ordem correta
    for (int i = total - 1; i >= 0; i--) {
        Elista *nova_celula = malloc(sizeof(Elista));
        nova_celula->dados = registros[i];
        nova_celula->proximo = lista->inicio;
        lista->inicio = nova_celula;
        lista->qtde++;
    }

    printf("Dados carregados com sucesso!\n");
} 

// Menu para opções de armazenamento
void menu_cs(Lista *lista) {
    
    int opcao = 0;

    do {
        printf("\n");
        printf("Carregar / Salvar\n");
        printf("\n");
        printf("1 - Carregar\n");
        printf("2 - Salvar\n");
        printf("0 - Voltar\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                carregar(lista);
                break;
            case 2:
                salvar(lista);
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

// Menu principal
int main() {
    // Criação de estruturas
    Lista *lista = criar_lista();
    Fila *fila = criar_fila();
    Heap *heap = criar_heap();
    Pilha *pilha = criar_pilha();
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

        // Sub-menus
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
                menu_pesquisa(lista);
                break;
            case 5:
                menu_desfazer(fila, pilha);
                break;
            case 6:
                menu_cs(lista);
                break;
            case 7:
                printf("\n");
                printf("Nome: Kayna de Deus\n");
                printf("Ciclo: 4\n");
                printf("Curso: Ciencia da Computacao\n");
                printf("Data: 19/05/2025\n");
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