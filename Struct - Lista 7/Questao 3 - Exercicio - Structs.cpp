#include <stdio.h>
#include <string.h>

struct Funcionario{
	int codigo, horasExtras;
	char nome[50], cargo[30];
	float salarioBase, valorHora, bruto, liquido;
};

float calcular_valor_hora(float salarioBase){
	return salarioBase / 160;
}

float calcular_bruto(struct Funcionario f){
	float valorHoraExtra = f.valorHora * 1.5;
	return f.salarioBase + (f.horasExtras * valorHoraExtra);
}

float calcular_liquido(float bruto){
	return bruto - (bruto * 0.10);
}

void cadastrar(struct Funcionario funcionario[], int *total){

	if(*total == 8){
		printf("\nCADASTRO CHEIO!\n");
		return;
	}

	printf("\n=====CADASTRO %d=====\n", *total + 1);
	printf("CODIGO: ");
	scanf("%d", &funcionario[*total].codigo);
	printf("NOME: ");
	scanf(" %49[^\n]", funcionario[*total].nome);
	printf("CARGO: ");
	scanf(" %29[^\n]", funcionario[*total].cargo);
	printf("SALARIO BASE: ");
	scanf("%f", &funcionario[*total].salarioBase);
	printf("HORAS EXTRAS: ");
	scanf("%d", &funcionario[*total].horasExtras);

	funcionario[*total].valorHora = calcular_valor_hora(funcionario[*total].salarioBase);
	funcionario[*total].bruto = calcular_bruto(funcionario[*total]);
	funcionario[*total].liquido = calcular_liquido(funcionario[*total].bruto);

	(*total)++;
	
	printf("\nFUNCIONARIO CADASTRADO!\n");
}

void exibir(struct Funcionario funcionario[], int total){

	if(total == 0){
		printf("\nNENHUM FUNCIONARIO CADASTRADO\n");
		return;
	}

	for(int i = 0; i < total; i++){
		printf("\nCodigo: %d", funcionario[i].codigo);
		printf("\nNome: %s", funcionario[i].nome);
		printf("\nCargo: %s", funcionario[i].cargo);
		printf("\nValor da hora: R$ %.2f", funcionario[i].valorHora);
		printf("\nSalario bruto: R$ %.2f", funcionario[i].bruto);
		printf("\nDesconto (10%%): R$ %.2f", funcionario[i].bruto * 0.10);
		printf("\nSalario liquido: R$ %.2f\n", funcionario[i].liquido);
	}
}

void resumo(struct Funcionario funcionario[], int total){

	if(total == 0){
		printf("\nNENHUM FUNCIONARIO CADASTRADO\n");
		return;
	}

	int maior = 0;
	float totalBruto = 0, totalLiquido = 0;

	for(int i = 0; i < total; i++){
		totalBruto += funcionario[i].bruto;
		totalLiquido += funcionario[i].liquido;

		if(funcionario[i].liquido > funcionario[maior].liquido){
			maior = i;
		}
	}

	printf("\nMAIOR SALARIO LIQUIDO: %s (R$ %.2f)", funcionario[maior].nome, funcionario[maior].liquido);
	printf("\nCUSTO TOTAL DA FOLHA (bruto): R$ %.2f", totalBruto);
	printf("\nTOTAL LIQUIDO PAGO: R$ %.2f\n", totalLiquido);
}

int main(void){
	struct Funcionario funcionario[8];

	int total = 0;
	int opcao;

	do{
		printf("\n\n----- MENU -----");
		printf("\n1 - CADASTRAR FUNCIONARIO");
		printf("\n2 - EXIBIR SALARIOS");
		printf("\n3 - MAIOR LIQUIDO E CUSTO DA FOLHA");
		printf("\n0 - SAIR");
		printf("\n------------------");
		printf("\n\nESCOLHA UMA OPCAO: ");
		scanf("%d", &opcao);

		switch(opcao){

			case 1:
				cadastrar(funcionario, &total);
				break;

			case 2:
				exibir(funcionario, total);
				break;

			case 3:
				resumo(funcionario, total);
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
