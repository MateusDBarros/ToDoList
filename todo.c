#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct ToDo
{
    char titulo[25];
    char descricao[100];
    int prioridade;
    bool status;
};

void adicionar(struct ToDo tarefas[100], int *numTarefas);
void exibir(struct ToDo tarefas[100], int *numTarefas);
int excluir(struct ToDo tarefas[100], int *numTarefas);
int editar(struct ToDo tarefas[100], int *numTarefas);
int ordenar(struct ToDo tarefas[100], int *numTarefas);
int buscar(int l, int r, char* alvo, struct ToDo tarefas[]);
int status(struct ToDo tarefas[100], int *numTarefas);

int main(void)
{
    struct ToDo tarefas[100];
    int numTarefas = 0;
    int escolha;
    char alvo[25];

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
            adicionar(tarefas, &numTarefas);
            break;
        case 2:
            exibir(tarefas, &numTarefas);
            break;
        case 3:
            excluir(tarefas, &numTarefas);
            break;
        case 4:
            editar(tarefas, &numTarefas);
            break;
        case 5:
            printf("Digite qual tarefa deseja buscar: ");
            scanf("%s", alvo);
            int index = buscar(0, numTarefas - 1, alvo, tarefas);
            if (index != -1) {
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
            status(tarefas, &numTarefas);
            break;
        case 7:
            printf("Encerrando programa...\n");
            return 0;
            break;
        
        default:
            printf("Opcao invalida, Tente novamente!\n");
            break;
        }

    } while (escolha != 7);

}

void adicionar(struct ToDo tarefas[100], int *numTarefas) {

    printf("Digite o titulo da tarefa: ");
    scanf("%s", tarefas[*numTarefas].titulo);
    printf("Entre a descricao da tarefa: ");
    scanf(" %[^\n]", tarefas[*numTarefas].descricao);
    printf("Qual o nivel de prioridade?(de 5 a 1) ");
    scanf("%d", &tarefas[*numTarefas].prioridade);
    printf("Tarefa adicionada com sucesso!\n");
    tarefas[*numTarefas].status = false;
    (*numTarefas)++;
}

void exibir(struct ToDo tarefas[100], int *numTarefas) {
    for (int i = 0; i < *numTarefas; i++) {
        printf("%s | Prioridade: %d | ", tarefas[i].titulo, tarefas[i].prioridade);
        if (tarefas[i].status == false)
            printf("Status: Ativo\n");
        else
            printf("Status: Concluido\n");
        printf("%s\n", tarefas[i].descricao);
        printf("---------------------------------");
    }
}

int excluir(struct ToDo tarefas[100], int *numTarefas) {
    char nome[25];
    printf("Escolha qual tarefa quer excluir: ");
    scanf("%s", nome);
    for (int i = 0; i < *numTarefas; i++) {
        if (strcmp(nome, tarefas[i].titulo) == 0) {
            for (int j = i; j < *numTarefas - 1; j++) {
                tarefas[j] = tarefas[j + 1];
            }
            (*numTarefas)--;
            return 0;
        }
    }
    printf("Tarefa nao encontrada\n");
    return -1;
}

int editar(struct ToDo tarefas[100], int *numTarefas) {
    char nome[25];
    printf("Escolha qual tarefa deseja editar: ");
    scanf("%s", nome);
    for (int i = 0; i < *numTarefas; i++) {
        if (strcmp(nome, tarefas[i].titulo) == 0) {
            printf("Digite o titulo da tarefa: ");
            scanf("%s", tarefas[i].titulo);
            printf("Entre a descricao da tarefa: ");
            scanf(" %[^\n]", tarefas[i].descricao);
            printf("Qual o nivel de prioridade?(de 5 a 1) ");
            scanf("%d", &tarefas[i].prioridade);
            printf("Tarefa editada com sucesso!\n");
            return 0;
        }
    }
    printf("Tarefa nao encotrada, por favor verifique o titulo da tarefa selecionada\n");
    return -1;
}

int ordenar(struct ToDo tarefas[100], int *numTarefas) {
    struct ToDo temp;
    for (int i = 0; i < *numTarefas - 1; i++) {
        for (int j = 0; j < *numTarefas - i - 1; j++) {
            if (tarefas[j].prioridade > tarefas[j + 1].prioridade){
                temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }
    return 0;
}
//int l = primeiro numero da esquerda
//int r = ultimo numero da array
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

int status(struct ToDo tarefas[100], int *numTarefas) {
    char nome[25];
    printf("Digite qual tarefa deseja alterar status: ");
    scanf("%s", nome);

    for (int i = 0; i < *numTarefas; i++) {
        if (strcmp(nome, tarefas[i].titulo) == 0) {
            if (tarefas[i].status == false) {
                tarefas[i].status = true;
                printf("Status atualizadp\n");
                return 0;
            }
                
            else {
                tarefas[i].status = false;
                printf("Status atualizadp\n");
                return 0;
            }
                
        }
    }
    printf("Tarefa nao encontrada!\n");
    return -1;
}
