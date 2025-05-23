#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char descricao[100];
    int quantidade;
    float preco;
} Produto;

void cadastrarProduto();
void registrarEntrada();
void registrarSaida();
void consultarProdutoCodigo();
void consultarProdutoNome();
void gerarRelatorio();