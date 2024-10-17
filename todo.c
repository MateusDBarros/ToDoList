#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Estrutura para armazenar as informações das tarefas
struct ToDo
{
    char titulo[25];
    char descricao[100];
    int prioridade;
    bool status;// true se concluida, false se nao concluida
};

//Declaracoes de funcoes
void adicionar(struct ToDo tarefas[100], int *numTarefas);
void exibir(struct ToDo tarefas[100], int *numTarefas);
int excluir(struct ToDo tarefas[100], int *numTarefas);
int editar(struct ToDo tarefas[100], int *numTarefas);
int ordenar(struct ToDo tarefas[100], int *numTarefas);
int buscar(int l, int r, char* alvo, struct ToDo tarefas[]);
void status(struct ToDo tarefas[100], int *numTarefas);

int main(void)
{
    struct ToDo tarefas[100]; //Array para armazenar ate 100 tarefas
    int numTarefas = 0; // Contador de tarefas
    int escolha; //Variavel para armazenar escolha do usuario
    char alvo[25]; //Variavel para buscar tarefas 

    //Loop do menu principal
    do {
        printf("\n\t Menu Principal \t\n");
        printf("\n");
        printf("1. Adicionar Tarefa.\n");
        printf("2. Exibir Tarefas.\n");
        printf("3. Excluir Tarefa.\n");
        printf("4. Editar Tarefa.\n");
        printf("5. Buscar Tarefa.\n");
        printf("6. Alterar Status.\n");
        printf("7. Sair\n");
        scanf("%d", &escolha);
        printf("\n");

        switch (escolha)
        {
        case 1:
            adicionar(tarefas, &numTarefas); //Chama função adicionar
            break;
        case 2:
            ordenar(tarefas, &numTarefas);
            exibir(tarefas, &numTarefas); //Chama função exibir
            break;
        case 3:
            excluir(tarefas, &numTarefas); //Chama função excluir
            break;
        case 4:
            editar(tarefas, &numTarefas); //Chama função editar
            break;
        case 5:
            printf("Digite qual tarefa deseja buscar: ");
            scanf("%s", alvo);
            ordenar(tarefas, &numTarefas);
            int index = buscar(0, numTarefas - 1, alvo, tarefas); //Chama função buscar e coloca seu resultado em uma variavel
            if (index != -1) {
                //Exibe a terefa encontrada
                printf("%s | Prioridade: %d | ", tarefas[index].titulo, tarefas[index].prioridade);
                if (tarefas[index].status == false)
                    printf("Status: Ativo\n");
                else
                    printf("Status: Concluido\n");
                printf("%s\n", tarefas[index].descricao);
                printf("---------------------------------\n");
                printf("\n");
            }
            else
                printf("Tarefa nao encontrada!\n");
            break;
        case 6:
            status(tarefas, &numTarefas); //Chama função para alterar o status
            break;
        case 7:
            printf("Encerrando programa...\n");
            return 0; //Encerra o programa
            break;
        
        default:
            printf("Opcao invalida, Tente novamente!\n");
            break;
        }

    } while (escolha != 7);

}

// Função para adicionar uma nova tarefa
void adicionar(struct ToDo tarefas[100], int *numTarefas) {
    printf("Digite o titulo da tarefa: ");
    scanf("%s", tarefas[*numTarefas].titulo);
    printf("Entre a descricao da tarefa: ");
    scanf(" %[^\n]", tarefas[*numTarefas].descricao);
    printf("Qual o nivel de prioridade? (de 5 a 1) ");
    scanf("%d", &tarefas[*numTarefas].prioridade);
    printf("Tarefa adicionada com sucesso!\n");
    tarefas[*numTarefas].status = false;  // Inicializa o status como não concluída
    (*numTarefas)++;  // Incrementa o contador de tarefas
}

// Função para exibir todas as tarefas
void exibir(struct ToDo tarefas[100], int *numTarefas) {
    for (int i = 0; i < *numTarefas; i++) {
        printf("%s | Prioridade: %d | ", tarefas[i].titulo, tarefas[i].prioridade);
        if (tarefas[i].status == false)
            printf("Status: Ativo\n");
        else
            printf("Status: Concluido\n");
        printf("%s\n", tarefas[i].descricao);
        printf("---------------------------------\n");
    }
}

// Função para excluir uma tarefa
int excluir(struct ToDo tarefas[100], int *numTarefas) {
    char nome[25];
    printf("Escolha qual tarefa quer excluir: ");
    scanf("%s", nome);
    for (int i = 0; i < *numTarefas; i++) {
        if (strcmp(nome, tarefas[i].titulo) == 0) {
            for (int j = i; j < *numTarefas - 1; j++) {
                tarefas[j] = tarefas[j + 1];
            }
            (*numTarefas)--;  // Decrementa o contador de tarefas
            return 0;
        }
    }
    printf("Tarefa nao encontrada\n");
    return -1;
}

// Função para editar uma tarefa
int editar(struct ToDo tarefas[100], int *numTarefas) {
    char nome[25];
    printf("Escolha qual tarefa deseja editar: ");
    scanf("%s", nome);
    for (int i = 0; i < *numTarefas; i++) {
        if (strcmp(nome, tarefas[i].titulo) == 0) {
            printf("Digite o novo titulo da tarefa: ");
            scanf("%s", tarefas[i].titulo);
            printf("Entre a nova descricao da tarefa: ");
            scanf(" %[^\n]", tarefas[i].descricao);
            printf("Qual o novo nivel de prioridade? (de 5 a 1) ");
            scanf("%d", &tarefas[i].prioridade);
            printf("Tarefa editada com sucesso!\n");
            return 0;
        }
    }
    printf("Tarefa nao encontrada, por favor verifique o titulo da tarefa selecionada\n");
    return -1;
}

// Função para ordenar as tarefas por prioridade usando Bubble Sort
int ordenar(struct ToDo tarefas[100], int *numTarefas) {
    struct ToDo temp;
    for (int i = 0; i < *numTarefas - 1; i++) {
        for (int j = 0; j < *numTarefas - i - 1; j++) {
            if (tarefas[j].prioridade > tarefas[j + 1].prioridade) {
                temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }
    return 0;  // Ordenação realizada com sucesso
}

// Função para buscar uma tarefa pelo título usando busca binária
int buscar(int l, int r, char* alvo, struct ToDo tarefas[]) {
    int meio = l + (r - l) / 2;
    if (l > r)
        return -1;
    if (strcmp(tarefas[meio].titulo, alvo) == 0)
        return meio;
    if (strcmp(tarefas[meio].titulo, alvo) > 0)
        return buscar(l, meio - 1, alvo, tarefas);
    else
        return buscar(meio + 1, r, alvo, tarefas);
}

// Função para alterar o status de uma tarefa
void status(struct ToDo tarefas[100], int *numTarefas) {
    char nome[25];
    printf("Digite qual tarefa deseja alterar o status: ");
    scanf("%s", nome);
    for (int i = 0; i < *numTarefas; i++) {
        if (strcmp(nome, tarefas[i].titulo) == 0) {
            if (tarefas[i].status == false)
                tarefas[i].status = true;
            else
                tarefas[i].status = false;
            printf("Status da tarefa alterado com sucesso!\n");
            return;
        }
    }
    
}