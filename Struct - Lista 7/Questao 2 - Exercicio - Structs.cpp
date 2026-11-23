#include <stdio.h>
#include <string.h>

struct Produto{
	char nome[50];
	int codigo, estoque;
	float preco;
};

int buscar(struct Produto p[], int total, int codigo){
	for(int i = 0; i < total; i++){
		if(p[i].codigo == codigo){
			return i;
		}
	}
	return -1;
}

void aumentarEstoque(int *estoque, int quantidade){
	*estoque += quantidade;
}

int diminuirEstoque(int *estoque, int quantidade){
	if(quantidade > *estoque){
		return 0;
	}
	*estoque -= quantidade;
	return 1;
}

void cadastrar(struct Produto p[], int *total){
	int cod;

	if(*total == 15){
		printf("\nCADASTRO CHEIO!\n");
		return;
	}

	printf("\nCODIGO: ");
	scanf("%d", &cod);

	if(buscar(p, *total, cod) != -1){
		printf("\nCODIGO JA CADASTRADO!\n");
		return;
	}

	p[*total].codigo = cod;

	printf("NOME: ");
	scanf(" %49[^\n]", p[*total].nome);

	printf("PRECO: ");
	scanf("%f", &p[*total].preco);

	printf("QUANTIDADE EM ESTOQUE: ");
	scanf("%d", &p[*total].estoque);

	(*total)++;
	printf("\nPRODUTO CADASTRADO!\n");
}

void listar(struct Produto p[], int total){
	if(total == 0){
		printf("\nNENHUM PRODUTO CADASTRADO\n");
		return;
	}

	for(int i = 0; i < total; i++){
		printf("\nCodigo: %d", p[i].codigo);
		printf("\nNome: %s", p[i].nome);
		printf("\nPreco: R$ %.2f", p[i].preco);
		printf("\nEstoque: %d\n", p[i].estoque);
	}
}

void repor(struct Produto p[], int total){
	int cod, quantidade;

	printf("\nCODIGO DO PRODUTO: ");
	scanf("%d", &cod);

	int pos = buscar(p, total, cod);
	if(pos == -1){
		printf("\nPRODUTO NAO ENCONTRADO!\n");
		return;
	}

	printf("QUANTIDADE A REPOR: ");
	scanf("%d", &quantidade);

	if(quantidade <= 0){
		printf("\nQUANTIDADE INVALIDA!\n");
		return;
	}

	aumentarEstoque(&p[pos].estoque, quantidade);
	printf("\nESTOQUE ATUALIZADO! Novo estoque: %d\n", p[pos].estoque);
}

void vender(struct Produto p[], int total){
	int cod, quantidade;

	printf("\nCODIGO DO PRODUTO: ");
	scanf("%d", &cod);

	int pos = buscar(p, total, cod);
	if(pos == -1){
		printf("\nPRODUTO NAO ENCONTRADO!\n");
		return;
	}

	printf("QUANTIDADE VENDIDA: ");
	scanf("%d", &quantidade);

	if(quantidade <= 0){
		printf("\nQUANTIDADE INVALIDA!\n");
		return;
	}

	if(diminuirEstoque(&p[pos].estoque, quantidade)){
		printf("\nVENDA REGISTRADA! Estoque restante: %d\n", p[pos].estoque);
	}else{
		printf("\nESTOQUE INSUFICIENTE! Disponivel: %d\n", p[pos].estoque);
	}
}

void consultar(struct Produto p[], int total){
	int cod;

	printf("\nCODIGO DO PRODUTO: ");
	scanf("%d", &cod);

	int pos = buscar(p, total, cod);
	if(pos == -1){
		printf("\nPRODUTO NAO ENCONTRADO!\n");
		return;
	}

	printf("\nCodigo: %d", p[pos].codigo);
	printf("\nNome: %s", p[pos].nome);
	printf("\nPreco: R$ %.2f", p[pos].preco);
	printf("\nEstoque: %d\n", p[pos].estoque);
}

void valor_total(struct Produto p[], int total){
	if(total == 0){
		printf("\nNENHUM PRODUTO CADASTRADO\n");
		return;
	}

	float soma = 0;
	int maior = 0;

	for(int i = 0; i < total; i++){
		float valor = p[i].preco * p[i].estoque;
		soma += valor;

		if(valor > p[maior].preco * p[maior].estoque){
			maior = i;
		}
	}

	printf("\nVALOR TOTAL EM ESTOQUE: R$ %.2f\n", soma);
	printf("MAIOR VALOR EM ESTOQUE: %s (R$ %.2f)\n", p[maior].nome, p[maior].preco * p[maior].estoque);
}

int main(void){
	struct Produto produto[15];

	int total = 0;
	int opcao;

	do{
		printf("\n\n----- MENU -----");
		printf("\n1 - CADASTRAR PRODUTO");
		printf("\n2 - LISTAR PRODUTOS");
		printf("\n3 - REPOR ESTOQUE");
		printf("\n4 - REGISTRAR VENDA");
		printf("\n5 - CONSULTAR PRODUTO");
		printf("\n6 - VALOR TOTAL DO ESTOQUE");
		printf("\n0 - SAIR");
		printf("\n------------------");
		printf("\n\nESCOLHA UMA OPCAO: ");
		scanf("%d", &opcao);

		switch(opcao){

			case 1:
				cadastrar(produto, &total);
				break;

			case 2:
				listar(produto, total);
				break;

			case 3:
				repor(produto, total);
				break;

			case 4:
				vender(produto, total);
				break;

			case 5:
				consultar(produto, total);
				break;

			case 6:
				valor_total(produto, total);
				break;

			case 0:
				printf("\nENCERRANDO\n");
				break;

			default:
				printf("\nOPCAO INVALIDA!\n");
		}
	} while (opcao != 0);

	return 0;
}
