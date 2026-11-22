#include <stdio.h>
#include <string.h>

struct Aluno{
	char nome[50];
	int matricula; 
	float n1, n2, media;
};


float calcular_media(struct Aluno a){
	return (a.n1 + a.n2)/2;
}

void cadastrar(struct Aluno aluno[], int *total){
 	
 	if (*total == 10) {
        printf("\nCadastro cheio!\n");
        return;
    }
    
		printf("=========CADASTRO %d=========\n", *total + 1);
		
		printf("DIGITE SUA MATRICULA: ");
		scanf("%d", &aluno[*total].matricula);
		getchar();
		
		printf("DIGITE SEU NOME: ");
		scanf(" %49[^\n]", aluno[*total].nome);
	
		printf("DIGITE SUA NOTA 1: ");
		scanf("%f", &aluno[*total].n1);
		
		printf("DIGITE SUA NOTA 2: ");
		scanf("%f", &aluno[*total].n2);
		
		aluno[*total].media = calcular_media(aluno[*total]);
		
		(*total)++;
		printf("ALUNO CADASTRADO!\n\n");
	}

void situacao(struct Aluno aluno[], int total){
	if(total == 0){
		printf("\n NENHUM ALUNO CADASTRADO");
		return;
	}
	for(int i = 0; i < total; i++){
		printf("\nNOME : %s\n", aluno[i].nome);
		printf("MEDIA : %.2f\n", aluno[i].media);
		printf("SITUACAO: ");
		
		if(aluno[i].media >= 6){
			printf("APROVADO!\n");	
		}else{
			printf("REPROVADO!\n\n");
		}
	}
}

void maior_nota(struct Aluno aluno[], int total){
	if(total == 0){
		printf("\n NENHUM ALUNO CADASTRADO");
		return;
	}
	int maior = 0;
	for(int i = 0; i< total;i++){
		if(aluno[i].media > aluno[maior].media){
			maior = i; 
		}
	}
	printf("MAIOR MEDIA: %s com %.2f\n", aluno[maior].nome, aluno[maior].media);
	
}

void menor_nota(struct Aluno aluno[], int total){
	if(total == 0){
		printf("\n NENHUM ALUNO CADASTRADO");
		return;
	}
	int menor = 0;
	for(int i = 0; i< total; i++){
		if(aluno[i].media < aluno[menor].media){
			menor = i; 
		}
	}
	printf("MENOR MEDIA: %s com %.2f\n", aluno[menor].nome, aluno[menor].media);
	
}

void media_geral(struct Aluno aluno[], int total){
	if(total == 0){
		printf("\n NENHUM ALUNO CADASTRADO");
		return;
	}
	float soma = 0;
	for(int i = 0; i < total; i++){
		soma += aluno[i].media;
	}
	float mediaGeral = soma / total;
	printf("\nMEDIA GERAL: %.2f", mediaGeral);
}

void acima_da_media(struct Aluno aluno[], int total){
	if(total == 0){
		printf("\n NENHUM ALUNO CADASTRADO");
		return;
	}
	
	int qntAlunos = 0;
	printf("ALUNOS COM MEDIA >= 6.00: \n");
	for(int i = 0; i < total; i++){
		if(aluno[i].media >= 6){
			printf("%s - %.2f\n", aluno[i].nome, aluno[i].media);
			qntAlunos++;
		}
	}
	printf("\nQUANTIDADE DE ALUNOS ACIMA DA MEDIA: %d\n", qntAlunos);
	
}

int main(void){
	struct Aluno aluno[10];
	
	int total = 0;
	int opcao;
	
	do{
		printf("\n\n----- MENU -----");
		printf("\n1 - CADASTRAR ALUNO");
		printf("\n2 - EXIBIR SITACAO DO ALUNO");
		printf("\n3 - ALUNO COM MAIOR MEDIA");
		printf("\n4 - ALUNO COM MENOR MEDIA");
		printf("\n5 - EXIBIR MEDIA GERAL DA TURMA");
		printf("\n6 - ALUNOS ACIMA DA MEDIA");
		printf("\n0 - SAIR");
		printf("\n------------------");
		printf("\n\nESCOLHA UMA OPCAO: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			
			case 1:
				cadastrar(aluno, &total);
				break;
			
			case 2:
				situacao(aluno, total);
				break;
			
			case 3:
				maior_nota(aluno, total);
				break;

			case 4:
				menor_nota(aluno, total);
				break;

			case 5:
				media_geral(aluno, total);
				break;

			case 6:
				acima_da_media(aluno, total);
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
 
