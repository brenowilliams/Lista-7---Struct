#include <stdio.h>
#include <string.h>

struct Data{
	int dia, mes, ano;
};

struct Paciente{
	int codigo;
	char nome[50];
};

struct Consulta{
	struct Paciente paciente;
	struct Data data;
	char descricao[100];
};

int buscar(struct Paciente paciente[], int total, int codigo){
	for(int i = 0; i < total; i++){
		if(paciente[i].codigo == codigo){
			return i;
		}
	}
	return -1;
}

struct Data ler_data(void){
	struct Data d;

	printf("DIA: ");
	scanf("%d", &d.dia);
	printf("MES: ");
	scanf("%d", &d.mes);
	printf("ANO: ");
	scanf("%d", &d.ano);

	return d;
}

int datas_iguais(struct Data a, struct Data b){
	return a.dia == b.dia && a.mes == b.mes && a.ano == b.ano;
}

int contar_consultas(struct Consulta consulta[], int totalC, int codigo){
	int cont = 0;

	for(int i = 0; i < totalC; i++){
		if(consulta[i].paciente.codigo == codigo){
			cont++;
		}
	}
	return cont;
}

void cadastrar_paciente(struct Paciente paciente[], int *total){
	int cod;

	if(*total == 15){
		printf("\nCADASTRO CHEIO!\n");
		return;
	}

	printf("\nCODIGO: ");
	scanf("%d", &cod);

	if(buscar(paciente, *total, cod) != -1){
		printf("\nCODIGO JA CADASTRADO!\n");
		return;
	}

	paciente[*total].codigo = cod;

	printf("NOME: ");
	scanf(" %49[^\n]", paciente[*total].nome);

	(*total)++;
	printf("\nPACIENTE CADASTRADO!\n");
}

void listar_pacientes(struct Paciente paciente[], int total){
	if(total == 0){
		printf("\nNENHUM PACIENTE CADASTRADO\n");
		return;
	}

	for(int i = 0; i < total; i++){
		printf("\nCodigo: %d", paciente[i].codigo);
		printf("\nNome: %s\n", paciente[i].nome);
	}
}

void registrar_consulta(struct Paciente paciente[], int totalP, struct Consulta consulta[], int *totalC){
	int cod;

	if(*totalC == 30){
		printf("\nLIMITE DE CONSULTAS ATINGIDO!\n");
		return;
	}

	if(totalP == 0){
		printf("\nNENHUM PACIENTE CADASTRADO\n");
		return;
	}

	printf("\nCODIGO DO PACIENTE: ");
	scanf("%d", &cod);

	int pos = buscar(paciente, totalP, cod);
	if(pos == -1){
		printf("\nPACIENTE NAO ENCONTRADO!\n");
		return;
	}

	consulta[*totalC].paciente = paciente[pos];

	printf("DATA DA CONSULTA\n");
	consulta[*totalC].data = ler_data();

	printf("DESCRICAO DO ATENDIMENTO: ");
	scanf(" %99[^\n]", consulta[*totalC].descricao);

	(*totalC)++;
	printf("\nCONSULTA REGISTRADA!\n");
}

void pesquisar_por_paciente(struct Consulta consulta[], int totalC){
	int cod, achou = 0;

	printf("\nCODIGO DO PACIENTE: ");
	scanf("%d", &cod);

	for(int i = 0; i < totalC; i++){
		if(consulta[i].paciente.codigo == cod){
			printf("\nPaciente: %s", consulta[i].paciente.nome);
			printf("\nData: %02d/%02d/%d", consulta[i].data.dia, consulta[i].data.mes, consulta[i].data.ano);
			printf("\nDescricao: %s\n", consulta[i].descricao);
			achou = 1;
		}
	}

	if(achou == 0){
		printf("\nNENHUMA CONSULTA ENCONTRADA PARA ESSE CODIGO\n");
	}
}

void listar_por_data(struct Consulta consulta[], int totalC){
	struct Data busca;
	int achou = 0;

	printf("\nDATA PARA PESQUISA\n");
	busca = ler_data();

	for(int i = 0; i < totalC; i++){
		if(datas_iguais(consulta[i].data, busca)){
			printf("\nPaciente: %s (codigo %d)", consulta[i].paciente.nome, consulta[i].paciente.codigo);
			printf("\nDescricao: %s\n", consulta[i].descricao);
			achou = 1;
		}
	}

	if(achou == 0){
		printf("\nNENHUMA CONSULTA NESSA DATA\n");
	}
}

void consultas_por_paciente(struct Paciente paciente[], int totalP, struct Consulta consulta[], int totalC){
	if(totalP == 0){
		printf("\nNENHUM PACIENTE CADASTRADO\n");
		return;
	}

	for(int i = 0; i < totalP; i++){
		printf("\n%s (codigo %d): %d consulta(s)", paciente[i].nome, paciente[i].codigo,
		       contar_consultas(consulta, totalC, paciente[i].codigo));
	}
	printf("\n");
}

void paciente_mais_atendido(struct Paciente paciente[], int totalP, struct Consulta consulta[], int totalC){
	if(totalP == 0){
		printf("\nNENHUM PACIENTE CADASTRADO\n");
		return;
	}

	int maior = 0;
	int maiorQtd = contar_consultas(consulta, totalC, paciente[0].codigo);

	for(int i = 1; i < totalP; i++){
		int qtd = contar_consultas(consulta, totalC, paciente[i].codigo);
		if(qtd > maiorQtd){
			maiorQtd = qtd;
			maior = i;
		}
	}

	if(maiorQtd == 0){
		printf("\nNENHUMA CONSULTA REGISTRADA\n");
		return;
	}

	printf("\nPACIENTE COM MAIS ATENDIMENTOS: %s (%d consultas)\n", paciente[maior].nome, maiorQtd);
}

int main(void){
	struct Paciente paciente[15];
	struct Consulta consulta[30];

	int totalP = 0, totalC = 0;
	int opcao;

	do{
		printf("\n\n----- MENU -----");
		printf("\n1 - CADASTRAR PACIENTE");
		printf("\n2 - LISTAR PACIENTES");
		printf("\n3 - REGISTRAR CONSULTA");
		printf("\n4 - CONSULTAS DE UM PACIENTE");
		printf("\n5 - CONSULTAS POR DATA");
		printf("\n6 - NUMERO DE CONSULTAS POR PACIENTE");
		printf("\n7 - PACIENTE COM MAIS ATENDIMENTOS");
		printf("\n0 - SAIR");
		printf("\n------------------");
		printf("\n\nESCOLHA UMA OPCAO: ");
		scanf("%d", &opcao);

		switch(opcao){

			case 1:
				cadastrar_paciente(paciente, &totalP);
				break;

			case 2:
				listar_pacientes(paciente, totalP);
				break;

			case 3:
				registrar_consulta(paciente, totalP, consulta, &totalC);
				break;

			case 4:
				pesquisar_por_paciente(consulta, totalC);
				break;

			case 5:
				listar_por_data(consulta, totalC);
				break;

			case 6:
				consultas_por_paciente(paciente, totalP, consulta, totalC);
				break;

			case 7:
				paciente_mais_atendido(paciente, totalP, consulta, totalC);
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
