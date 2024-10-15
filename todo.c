#include <stdio.h>
#include <stdbool.h>

struct ToDo
{
    char titulo[25];
    char descricao[100];
    int prioridade;
    bool status;
};

void adicionar(struct ToDo tarefas[100], int *numTarefas);
void exibir();
void excluir();
void editar();
int ordenar();
int buscar();
void concluida();

int main(void)
{
    struct ToDo tarefas[100];
    int numTarefas = 0;

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