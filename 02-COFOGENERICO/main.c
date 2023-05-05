/*------------------------------------------------
main.c
Arquivo com o menu de acesso as funcionalidades do cofo
---------------------------------------------------
Autor: Anderson Lopes Silva
May/2023
-------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "gcofo.h"

#define TRUE 1
#define FALSE 0

typedef struct _livro_
{
    int id;
    char nome[30];
    float preco;
} Livro;

gCofo *chamaGCofCreate();
int chamaGCofDestroy(gCofo *meuCofo);
void chamaGCofInsert(gCofo *meuCofo);
void chamaGCofQuery(gCofo *meuCofo);
void chamaGCofRemove(gCofo *meuCofo);
void chamaGCofItems(gCofo *meuCofo);
void gCofEmpty(gCofo *meuCofo);
int cmpId(void *a, void *b);
int cmpNome(void *a, void *b);

int main(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    gCofo *meuCofo;
    int opcao = 0, cofoCriado = FALSE;

    do
    {
        printf("\n\n|------------------------------------------------|\n");
        printf("|                      MENU                      |\n");
        printf("|------------------------------------------------|\n");
        printf("|| 1. Criar o cofo\n");
        printf("|| 2. Inserir um livro no cofo\n");
        printf("|| 3. Verificar se um livro est� no cofo\n");
        printf("|| 4. Mostrar itens no cofo\n");
        printf("|| 5. Remover um livro do cofo\n");
        printf("|| 6. Esvaziar o cofo\n");
        printf("|| 7. Destruir o cofo\n");
        printf("|| 8. Sair\n");
        printf("||- Sua escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (cofoCriado == FALSE)
            {
                meuCofo = chamaGCofCreate();
                if (meuCofo != FALSE)
                {
                    cofoCriado = TRUE;
                }
            }
            else
            {
                printf("\nVoc� j� possui um cofo criado. Divirta-se com as opera��es do seu cofo!");
            }
            break;

        case 2:
            if (cofoCriado)
            {
                chamaGCofInsert(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;
        case 3:
            if (cofoCriado)
            {
                chamaGCofQuery(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;
        case 4:
            if (cofoCriado)
            {
                chamaGCofItems(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 5:
            if (cofoCriado)
            {
                chamaGCofRemove(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 6:
            if (cofoCriado)
            {
                gCofEmpty(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;
        case 7:
            if (cofoCriado)
            {
                cofoCriado = chamaGCofDestroy(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 8:
            printf("\n\nObrigado por utilizar meu programa :) !!\n\n");
            break;

        default:
            printf("\n\nAten��o: digite um d�gito v�lido!\n\n");
        }

    } while (opcao != 8);
}

gCofo *chamaGCofCreate()
{
    int tamanhoCofo;
    gCofo *c;

    printf("\nVAMOS CRIAR SEU COFO!");
    printf("\nDigite o tamanho do cofo: ");
    scanf("%d", &tamanhoCofo);
    c = gcofCreate(tamanhoCofo);

    if (c != NULL)
    {
        printf("Cofo criado com SUCESSO!");
        return c;
    }
    else
    {
        printf("\nN�o foi poss�vel criar seu cofo, tente novamente mais tarde :( !");
        return FALSE;
    }
}

int chamaGCofDestroy(gCofo *meuCofo)
{
    int sucesso;
    sucesso = gcofDestroy(meuCofo);
    if (sucesso)
    {
        printf("\nCofo Destru�do!");
        return FALSE;
    }
    else
    {
        printf("\nN�o foi poss�vel destruir o cofo!");
        return TRUE;
    }
}

void chamaGCofInsert(gCofo *meuCofo)
{
    int sucesso;
    Livro *l = (Livro *)malloc(sizeof(Livro));
    if (l != NULL)
    {
        printf("\nDigite o nome do livro: ");
        scanf("%s", &(l->nome));
        printf("Digite o ID do livro: ");
        scanf("%d", &(l->id));
        printf("Digite o valor do livro: ");
        scanf("%f", &(l->preco));
        sucesso = gcofInsert(meuCofo, (void *)l);
    }
    if (sucesso)
    {
        printf("\nOs dados do livro foram inseridos com sucesso!");
    }
    else
    {
        printf("\nN�o foi poss�vel adicionar o livro no cofo");
    }
}

void chamaGCofQuery(gCofo *meuCofo)
{
    if (meuCofo->numItens)
    {
        int cod;
        char nome[30];
        Livro *livro;

        printf("\nDigite o ID que voc� deseja saber se est� no cofo: ");
        scanf("%d", &cod);
        livro = (Livro *)gcofQuery(meuCofo, (void *)&cod, cmpId);

        if (livro != NULL)
        {
            printf("\nO seguinte livro foi encontrado: \nLivro: %s \nID: %d \nValor: %.2f", livro->nome, livro->id, livro->preco);
        }
        else
        {
            printf("\nN�o foi poss�vel encontrar o livro pedido");
        }
    }
    else
    {
        printf("\nN�o h� livros no cofo para serem removidos!");
    }
}

void chamaGCofRemove(gCofo *meuCofo)
{
    int chave;
    Livro *livro;

    if (meuCofo->numItens)
    {
        printf("\nDigite o ID do livro que voc� deseja remover do cofo: ");

        scanf("%d", &chave);

        livro = (Livro *)gcofRemove(meuCofo, (void *)(&chave), cmpId);
        if (livro != NULL)
        {
            printf("\nO seguinte livro foi removido: \nLivro: %s \nID: %d \nValor: %.2f", livro->nome, livro->id, livro->preco);
        }
        else
        {
            printf("\nN�o foi poss�vel remover o livro do cofo!");
        }
    }
    else
    {
        printf("\nN�o h� livros no cofo para serem removidos!");
    }
}

void chamaGCofItems(gCofo *meuCofo)
{
    Livro *livro;
    if (meuCofo->numItens > 0)
    {
        livro = gcofGetFirst(meuCofo);
        printf("\nNome do Livro: %s \nID: %d \nValor: %.2f\n", livro->nome, livro->id, livro->preco);
        for (int i = 1; i < meuCofo->numItens; i++)
        {
            livro = gcofGetNext(meuCofo);
            printf("\nNome do Livro: %s \nID: %d \nValor: %.2f\n", livro->nome, livro->id, livro->preco);
        }
    }
    else
    {
        printf("\nN�o h� livros no cofo para mostrar!");
    }
}

void gCofEmpty(gCofo *meuCofo)
{
    Livro *livro;
    if (meuCofo != NULL)
    {
        if (meuCofo->numItens)
        {
            while (meuCofo->numItens > 0)
            {
                livro = (Livro *)gcofGetFirst(meuCofo);
                gcofRemove(meuCofo, (void *)&(livro->id), cmpId);
            }
            printf("\nCofo esvaziado!");
        }
        else
        {
            printf("\nO cofo j� est� vazio!");
        }
    }
}

int cmpId(void *a, void *b)
{
    int *id = (int *)a;
    Livro *livro = (Livro *)b;

    if (livro->id == *id)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}