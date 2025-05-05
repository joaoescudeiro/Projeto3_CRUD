#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

void cadastrarProduto() {
    Produto p;
    FILE *arquivo = fopen("estoque.dat", "ab");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &p.codigo);
    getchar();

    printf("Nome: ");
    fgets(p.nome, 50, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Descricao: ");
    fgets(p.descricao, 100, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Preco unitario: ");
    scanf("%f", &p.preco);

    fwrite(&p, sizeof(Produto), 1, arquivo);
    fclose(arquivo);

    printf("Produto cadastrado.\n");
}

void registrarEntrada() {
    int codigo, quantidade;
    printf("Digite o codigo do produto para entrada: ");
    scanf("%d", &codigo);
    printf("Quantidade a adicionar: ");
    scanf("%d", &quantidade);

    FILE *arquivo = fopen("estoque.dat", "rb+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Produto p;
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (p.codigo == codigo) {
            p.quantidade += quantidade;
            fseek(arquivo, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, arquivo);
            encontrado = 1;
            printf("Entrada registrada.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }

    fclose(arquivo);
}