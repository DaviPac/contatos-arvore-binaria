#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct contato
{
    char nome[30];
    long numero;
    struct contato *anterior;
    struct contato *maior;
    struct contato *menor;
}
contato;

contato *cont_dir(contato *contato) {
    if (contato->menor == NULL) {
        return contato;
    }
    else {
        return cont_dir(contato->menor);
    }
}

contato *cont_esq(contato *contato) {
    if (contato->maior == NULL) {
        return contato;
    }
    else {
        return cont_esq(contato->maior);
    }
}

void deletar(char nome[30], contato **contatos)
{
    if (contatos == NULL)
    {
        printf("Sua lista de contatos esta vazia.\n");
        return;
    }
    if (strcmp(nome, (*contatos)->nome) < 0 && (*contatos)->menor != NULL)
    {
        deletar(nome, &(*contatos)->menor);
    }
    else if (strcmp(nome, (*contatos)->nome) > 0 && (*contatos)->maior != NULL)
    {
        deletar(nome, &(*contatos)->maior);
    }
    else if (strcmp(nome, (*contatos)->nome) == 0)
    {
        contato *prox;
        if ((*contatos)->maior == NULL && (*contatos)->menor == NULL) {
            if ((*contatos)->anterior == NULL) {
                (*contatos) = NULL;
                return;
            }
            else if (strcmp(nome, (*contatos)->anterior->nome) < 0) {
                (*contatos)->anterior->menor = NULL;
                return;
            }
            else {
                (*contatos)->anterior->maior = NULL;
                return;
            }
            return;
        }
        else if ((*contatos)->maior == NULL) {
            prox = cont_esq((*contatos)->menor);
        }
        else {
            prox = cont_dir((*contatos)->maior);
        }
        strcpy((*contatos)->nome, prox->nome);
        (*contatos)->numero = prox->numero;
        if (strcmp(prox->anterior->menor->nome, prox->nome) == 0) {
            prox->anterior->menor = NULL;
        }
        else {
            prox->anterior->maior = NULL;
        }
        printf("%s deletado com sucesso!\n", nome);
    }
    else
    {
        printf("%s nao esta nos seus contatos.\n", nome);
    }
}

void save(contato *contatos, char filename[14])
{
    FILE *file;
    file = fopen(filename, "r");
    if (contatos->nome == NULL)
    {
        return;
    }
    fclose(file);
    file = fopen(filename, "a");
    if (contatos->menor != NULL)
    {
        save(contatos->menor, filename);
    }
    if (strcmp(contatos->nome, "") != 0)
    {
        fprintf(file, "%s:%ld,", contatos->nome, contatos->numero);
    }
    if (contatos->maior != NULL)
    {
        save(contatos->maior, filename);
    }
    fclose(file);
}


void modificar_contatos(char nome[30], contato *contatos)
{
    if (contatos == NULL)
    {
        printf("Sua lista de contatos esta vazia.\n");
        return;
    }
    if (strcmp(nome, contatos->nome) > 0)
    {
        if (contatos->maior != NULL)
        {
            modificar_contatos(nome, contatos->maior);
        }
        else
        {
            printf("%s nao esta nos seus contatos.\n", nome);
            return;
        }
    }
    else if (strcmp(nome, contatos->nome) < 0)
    {
        if (contatos->menor != NULL)
        {
            modificar_contatos(nome, contatos->menor);
        }
        else
        {
            printf("%s nao esta nos seus contatos.\n", nome);
            return;
        }
    }
    else
    {
        scanf("%s", contatos->nome);
        scanf("%ld", &(contatos->numero));
        for (int i = 0; i < 10; i++)
        return;
    }
}


void search_contatos(char nome[30], contato *contatos)
{
    if (contatos == NULL)
    {
        printf("Sua lista de contatos esta vazia.\n");
        return;
    }
    if (strcmp(nome, contatos->nome) > 0)
    {
        if (contatos->maior != NULL)
        {
            search_contatos(nome, contatos->maior);
        }
        else
        {
            printf("%s nao esta nos seus contatos.\n", nome);
            return;
        }
    }
    else if (strcmp(nome, contatos->nome) < 0)
    {
        if (contatos->menor != NULL)
        {
            search_contatos(nome, contatos->menor);
        }
        else
        {
            printf("%s nao esta nos seus contatos.\n", nome);
            return;
        }
    }
    else
    {
        printf("%s\n    %ld\n", contatos->nome, contatos->numero);
        return;
    }
}


void free_contatos(contato *contatos)
{
    if (contatos == NULL)
    {
        return;
    }
    if (contatos->menor != NULL)
    {
        free_contatos(contatos->menor);
    }
    if (contatos->maior != NULL)
    {
        free_contatos(contatos->maior);
    }
    free(contatos);
}


void print_contatos(contato *contatos)
{
    if (contatos == NULL)
    {
        printf("Sua lista de contatos esta vazia.\n");
        return;
    }
    if (contatos->menor != NULL)
    {
        print_contatos(contatos->menor);
    }
    if (strcmp(contatos->nome, "") != 0)
    {
        printf("%s\n    %ld\n", contatos->nome, contatos->numero);
    }
    if (contatos->maior != NULL)
    {
        print_contatos(contatos->maior);
    }
}


void armazenar_contato(char nome[30], long numero, contato **contatos, contato *anterior)
{
    if (*contatos == NULL)
    {
        *contatos = malloc(sizeof(contato));
        strcpy((*contatos)->nome, nome);
        (*contatos)->numero = numero;
        (*contatos)->maior = NULL;
        (*contatos)->menor = NULL;
        (*contatos)->anterior = anterior;
    }
    else if (strcmp(nome, (*contatos)->nome) > 0)
    {
        armazenar_contato(nome, numero, &((*contatos)->maior), *contatos);
    }
    else if (strcmp(nome, (*contatos)->nome) < 0)
    {
        armazenar_contato(nome, numero, &((*contatos)->menor), *contatos);
    }
    else
    {
        printf("%s ja esta nos seus contatos.\n", nome);
    }
}


void load(contato **contatos, char filename[14])
{
    FILE *file;
    char nome[30];

    long numero;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo de contatos.\n");
        return;
    }

    while (fscanf(file, "%[^:]:%ld,", nome, &numero) == 2)
    {
        armazenar_contato(nome, numero, contatos, NULL);
    }
    fclose(file);
}

void lower(char *palavra) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] < 'a') {
            palavra[i] += 'a' - 'A';
        }
    }
}

void programa(char usuario[10])
{
    char user[14];
    strcpy(user, usuario);
    strcat(user, ".ctt");
    contato *contatos = NULL;
    while (1)
    {
        long n;
        char nome[30];
        char cmd[30];
        for (int i = 0; i < 30; i++) {
            cmd[i] = '\0';
        }
        scanf("%s", cmd);
        lower(cmd);
        if (strcmp(cmd, "lista") == 0)
        {
            print_contatos(contatos);
        }
        else if (strcmp(cmd, "sair") == 0)
        {
            remove(user);
            save(contatos, user);
            free_contatos(contatos);
            break;
        }
        else if (strcmp(cmd, "ver") == 0)
        {
            scanf("%s", nome);
            search_contatos(nome, contatos);
        }
        else if (strcmp(cmd, "adicionar") == 0)
        {
            scanf("%s", nome);
            printf("Digite o numero de %s: ", nome);
            scanf("%ld", &n);
            armazenar_contato(nome, n, &contatos, NULL);
            printf("%s adicionado com sucesso!", nome);
        }
        else if (strcmp(cmd, "modificar") == 0)
        {
            scanf("%s", nome);
            modificar_contatos(nome, contatos);
        }
        else if (strcmp(cmd, "deletar") == 0)
        {
            scanf("%s", nome);
            deletar(nome, &contatos);
            remove(user);
            save(contatos, user);
        }
        else if (strcmp(cmd, "load") == 0)
        {
            load(&contatos, user);
        }
        else
        {
            printf("%s nao e um comando valido. Os comandos validos sao:\n adicionar\n ver\n lista\n load\n save\n sair\n", nome);
        }
    }
}
