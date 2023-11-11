#include <stdio.h>
#include <string.h>
#include "binary.h"

int sign_up(char name[10], char password[10])
{
    char fname[20];
    char fpassword[20];
    FILE *file;
    file = fopen("users.nnp", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%[^:]:%19s,", fname, fpassword) == 2)
        {
            if (strcmp(name, fname) == 0)
            {
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    }
    {
        for (int i = 0; i < (int)strlen(password); i++)
        {
            password[i] = password[i] * 2;
        }
        file = fopen("users.nnp", "a");
        fprintf(file, "%s:%s,", name, password);
        fclose(file);
        return 0;
    }
}


int login(char name[20], char password[20])
{
    char fname[20];
    char fpassword[20];
    for (int i = 0; i < (int)strlen(password); i++)
        {
            password[i] = password[i] * 2;
        }
    char commaname[20] = ",";
    strcat(commaname, name);
    FILE *file;
    file = fopen("users.nnp", "r");
    if (file == NULL)
    {
        return -1;
    }
    while (fscanf(file, "%[^:]:%[^,]", fname, fpassword) == 2)
    {
        if ((strcmp(commaname, fname) == 0 || strcmp(name, fname) == 0) && strcmp(password, fpassword) == 0)
        {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return -1;
}


int main(void)
{
    char command[8];
    char name[20];
    char password[20];
    while (1)
    {
        printf("Digite um comando: ");
        scanf("%s", command);
        scanf("%s", name);
        scanf("%s", password);
        if (strcmp(command, "sign-up") == 0)
        {
            printf("signing up");
            if (sign_up(name, password) != 0)
                printf("Este nome já existe, por favor, escolha outro nome.\n");
            else
            {
                printf("Conta criada com sucesso!\n");
            }
        }
        else if (strcmp(command, "login") == 0)
        {
            printf("loging in\n");
            if (login(name, password) == 0)
            {
                printf("Login realizado com sucesso!\n");
                programa(name);
                break;
            }
            else
            {
                printf("Nome ou senha incorretos.\n");
            }
        }
        else if (strcmp(command, "reset") == 0)
        {
            if (strcmp(name, "admin") == 0 && strcmp(password, "173946") == 0)
            {
                remove("users.nnp");
                FILE *file;
                file = fopen("users.nnp", "a");
                fprintf(file, ",");
                fclose(file);
            }
            else
            {
                printf("Erro ao tentar assignar adm.\n");
            }
        }
        else if (strcmp(command, "sair") == 0)
        {
            return 0;
        }
        else {
            printf("Comando inexistente.\n");
            printf("Comandos:\n     login\n     sign-up\n     reset\n     sair\n");
        }
    }
    return 0;
}