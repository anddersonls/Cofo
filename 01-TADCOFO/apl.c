/*------------------------------------------------
apl.c
Arquivo com o menu de acesso �s fun��es do cofo
---------------------------------------------------
Autor: Anderson Lopes Silva
April/2023
-------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cofo.h"

#define TRUE 1
#define FALSE 0

// cd 01-TADCOFO
// gcc apl.c cofo.c -o apl
// ./apl

// DECLARA��O DAS FUN��ES AUXILIARES
Cofo *chamaCofCreate();
int chamaCofDestroy(Cofo *meuCofo);
void chamaCofInsert(Cofo *meuCofo);
void chamaCofQuery(Cofo *meuCofo);
void chamaCofRemove(Cofo *meuCofo);
void chamaCofItems(Cofo *meuCofo);

int main(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    Cofo *meuCofo;
    int opcao = 0, cofoCriado = FALSE;

    do
    {
        printf("\n\n|------------------------------------------------|\n");
        printf("|                      MENU                      |\n");
        printf("|------------------------------------------------|\n");
        printf("|| 1. Criar o cofo\n");
        printf("|| 2. Destruir o cofo\n");
        printf("|| 3. Inserir um elemento no cofo\n");
        printf("|| 4. Verificar se um elemento est� no cofo\n");
        printf("|| 5. Remover um elemento do cofo\n");
        printf("|| 6. Mostrar itens no cofo\n");
        printf("|| 7. Sair\n");
        printf("||- Sua escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (cofoCriado == FALSE)
            {
                meuCofo = chamaCofCreate();
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
                cofoCriado = chamaCofDestroy(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 3:
            if (cofoCriado)
            {
                chamaCofInsert(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 4:
            if (cofoCriado)
            {
                chamaCofQuery(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 5:
            if (cofoCriado)
            {
                chamaCofRemove(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;

        case 6:
            if (cofoCriado)
            {
                chamaCofItems(meuCofo);
            }
            else
            {
                printf("\nATEN��O: antes de utilizar as opera��es voc� deve primeireiramente criar um cofo!");
            }
            break;
        case 7:
            printf("\n\nObrigado por utilizar meu programa :) !!\n\n");
            break;
        default:
            printf("\n\nAten��o: digite um d�gito v�lido!\n\n");
        }

    } while (opcao != 7);
}

// FUN��ES AUXILIARES
Cofo *chamaCofCreate()
{
    int tamanhoCofo;
    Cofo *c;

    printf("\nVAMOS CRIAR SEU COFO!");
    printf("\nDigite o tamanho do cofo: ");
    scanf("%d", &tamanhoCofo);
    c = cofCreate(tamanhoCofo);

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

int chamaCofDestroy(Cofo *meuCofo)
{
    int sucesso;
    sucesso = cofDestroy(meuCofo);
    if (sucesso)
    {
        printf("\nCofo Destru�do!");
        return FALSE;
    }
    else
    {
        printf("\nN�o foi poss�vel destruir o cofo, tente novamente!");
        return TRUE;
    }
}

void chamaCofInsert(Cofo *meuCofo)
{
    int sucesso, elemento;
    printf("\nDigite o elemento que voc� deseja inserir no cofo: ");
    scanf("%d", &elemento);

    sucesso = cofInsert(meuCofo, elemento);
    if (sucesso)
    {
        printf("\nO elemento %d foi inserido com sucesso!", elemento);
    }
    else
    {
        printf("\nN�o foi poss�vel inserir o elemento %d no cofo!", elemento);
    }
}

void chamaCofQuery(Cofo *meuCofo)
{
    int elemento, sucesso;

    printf("\nDigite o elemento que voc� deseja saber se est� no cofo: ");
    scanf("%d", &elemento);

    sucesso = cofQuery(meuCofo, elemento);
    if (sucesso)
    {
        printf("\nO elemento %d est� no cofo!", elemento);
    }
    else
    {
        printf("\nO elemento %d n�o est� no cofo!", elemento);
    }
}

void chamaCofRemove(Cofo *meuCofo)
{
    int elemento, sucesso;

    printf("\nDigite o elemento que voc� deseja retirar do cofo: ");
    scanf("%d", &elemento);
    sucesso = cofRemove(meuCofo, elemento);
    if (sucesso)
    {
        printf("\nItem removido com sucesso!");
    }
    else
    {
        printf("\nN�o foi poss�vel remover o item do cofo!");
    }
}

void chamaCofItems(Cofo *meuCofo)
{
    int numItens;
    numItens = cofNumItems(meuCofo);

    if (numItens == FALSE)
    {
        printf("\nN�o foi poss�vel mostrar itens do cofo!");
    }
    else
    {
        int *itens;
        itens = (int *)malloc(sizeof(int) * numItens);
        if (itens != NULL)
        {
            itens = cofItems(meuCofo);
            for (int i = 0; i < numItens; i++)
            {
                printf("\nItem [%d]: %d", i, itens[i]);
            }
        }
        else
        {
            printf("\nN�o foi poss�vel mostrar itens do cofo!");
        }
    }
}