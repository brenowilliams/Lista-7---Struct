#include <stdio.h>
#include <string.h>

struct Produto{
	int codigo, estoque;
	char nome[50];
	float preco;
};

struct Venda{
	struct Produto produto;
	int quantidade;
	float valorTotal;
};

int buscar(struct Produto produto[], int total, int codigo){
	for(int i = 0; i < total; i++){
		if(produto[i].codigo == codigo){
			return i;
		}
	}
	return -1;
}

void cadastrar_produto(struct Produto produto[], int *total){
	int cod;

	if(*total == 10){
		printf("\nCADASTRO CHEIO!\n");
		return;
	}

	printf("\nCODIGO: ");
	scanf("%d", &cod);

	if(buscar(produto, *total, cod) != -1){
		printf("\nCODIGO JA CADASTRADO!\n");
		return;
	}

	produto[*total].codigo = cod;

	printf("NOME: ");
	scanf(" %49[^\n]", produto[*total].nome);
	printf("PRECO: ");
	scanf("%f", &produto[*total].preco);
	printf("ESTOQUE: ");
	scanf("%d", &produto[*total].estoque);

	(*total)++;
	printf("\nPRODUTO CADASTRADO!\n");
}

void listar_produtos(struct Produto produto[], int total){
	if(total == 0){
		printf("\nNENHUM PRODUTO CADASTRADO\n");
		return;
	}

	for(int i = 0; i < total; i++){
		printf("\nCodigo: %d", produto[i].codigo);
		printf("\nNome: %s", produto[i].nome);
		printf("\nPreco: R$ %.2f", produto[i].preco);
		printf("\nEstoque: %d\n", produto[i].estoque);
	}
}

void registrar_venda(struct Produto produto[], int totalP, struct Venda venda[], int *totalV){
	int cod, qtd;

	if(*totalV == 20){
		printf("\nLIMITE DE VENDAS ATINGIDO!\n");
		return;
	}

	if(totalP == 0){
		printf("\nNENHUM PRODUTO CADASTRADO\n");
		return;
	}

	printf("\nCODIGO DO PRODUTO: ");
	scanf("%d", &cod);

	int pos = buscar(produto, totalP, cod);
	if(pos == -1){
		printf("\nPRODUTO NAO ENCONTRADO!\n");
		return;
	}

	printf("QUANTIDADE VENDIDA: ");
	scanf("%d", &qtd);

	if(qtd <= 0){
		printf("\nQUANTIDADE INVALIDA!\n");
		return;
	}

	if(qtd > produto[pos].estoque){
		printf("\nESTOQUE INSUFICIENTE! Disponivel: %d\n", produto[pos].estoque);
		return;
	}

	venda[*totalV].produto = produto[pos];
	venda[*totalV].quantidade = qtd;
	venda[*totalV].valorTotal = produto[pos].preco * qtd;

	produto[pos].estoque -= qtd;

	(*totalV)++;
	printf("\nVENDA REGISTRADA! Total: R$ %.2f | Estoque restante: %d\n",
	       venda[*totalV - 1].valorTotal, produto[pos].estoque);
}

void listar_vendas(struct Venda venda[], int total){
	if(total == 0){
		printf("\nNENHUMA VENDA REGISTRADA\n");
		return;
	}

	for(int i = 0; i < total; i++){
		printf("\nVenda %d", i + 1);
		printf("\nProduto: %s (codigo %d)", venda[i].produto.nome, venda[i].produto.codigo);
		printf("\nQuantidade: %d", venda[i].quantidade);
		printf("\nValor total: R$ %.2f\n", venda[i].valorTotal);
	}
}

void calcular_faturamento(struct Produto produto[], int totalP, struct Venda venda[], int totalV){
	if(totalP == 0){
		printf("\nNENHUM PRODUTO CADASTRADO\n");
		return;
	}

	if(totalV == 0){
		printf("\nNENHUMA VENDA REGISTRADA\n");
		return;
	}

	float total = 0;
	for(int i = 0; i < totalV; i++){
		total += venda[i].valorTotal;
	}

	int maior = 0;
	float maiorFat = -1;

	for(int i = 0; i < totalP; i++){
		float fat = 0;
		for(int j = 0; j < totalV; j++){
			if(venda[j].produto.codigo == produto[i].codigo){
				fat += venda[j].valorTotal;
			}
		}
		if(fat > maiorFat){
			maiorFat = fat;
			maior = i;
		}
	}

	printf("\nFATURAMENTO TOTAL: R$ %.2f", total);
	printf("\nPRODUTO COM MAIOR FATURAMENTO: %s (R$ %.2f)\n", produto[maior].nome, maiorFat);
}

int main(void){
	struct Produto produto[10];
	struct Venda venda[20];

	int totalP = 0, totalV = 0;
	int opcao;

	do{
		printf("\n\n----- MENU -----");
		printf("\n1 - CADASTRAR PRODUTO");
		printf("\n2 - LISTAR PRODUTOS");
		printf("\n3 - REGISTRAR VENDA");
		printf("\n4 - LISTAR VENDAS");
		printf("\n5 - FATURAMENTO");
		printf("\n0 - SAIR");
		printf("\n------------------");
		printf("\n\nESCOLHA UMA OPCAO: ");
		scanf("%d", &opcao);

		switch(opcao){

			case 1:
				cadastrar_produto(produto, &totalP);
				break;

			case 2:
				listar_produtos(produto, totalP);
				break;

			case 3:
				registrar_venda(produto, totalP, venda, &totalV);
				break;

			case 4:
				listar_vendas(venda, totalV);
				break;

			case 5:
				calcular_faturamento(produto, totalP, venda, totalV);
				break;

			case 0:
				printf("\nENCERRANDO\n");
				break;

			default:
				printf("\nOPCAO INVALIDA!\n");
		}
	} while(opcao != 0);

	return 0;
}
