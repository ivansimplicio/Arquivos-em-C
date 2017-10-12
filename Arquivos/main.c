#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef	struct {
			char nome[30], usuario[30], sexo[30], curso[30], instituicao[30];
			int idade, numero, matricula;
}CADASTRO;

void syst(){
	system("pause");
	system("cls");
}

FILE* open_file(char caminho[], char modo){
	FILE *arquivo;
	switch(toupper(modo)){
		case 'W':	arquivo = fopen(caminho,"w");
			break;
		case 'R':	arquivo = fopen(caminho,"r");
			break;
		case 'A':	arquivo = fopen(caminho,"a");
			break;
	}
	if(arquivo == NULL){
		puts("FALHA NA ABERTURA DO ARQUIVO!");
		exit(0);
	}
	return arquivo;
}

void save_file(CADASTRO	aluno){
	FILE *arquivo;
	arquivo = open_file("cadastro.txt",'a');
	fprintf(arquivo,"%s %s %s %s %s %d %d %d\n",aluno.nome,aluno.curso,aluno.instituicao,aluno.usuario,aluno.sexo,aluno.idade,aluno.numero,aluno.matricula);
	fclose(arquivo);
	printf("\n\nCadastro realizado com sucesso!\n");
	syst();
}

void mostrar(){
	CADASTRO aluno;
	FILE *arquivo;
	arquivo = open_file("cadastro.txt",'r');
	while(!feof(arquivo)){
		fscanf(arquivo,"%s %s %s %s %s %d %d %d\n",&aluno.nome,&aluno.curso,&aluno.instituicao,&aluno.usuario,&aluno.sexo,&aluno.idade,&aluno.numero,&aluno.matricula);
		printf("Aluno: %s\nSexo: %s\nIdade: %d\nNumero: %d\nCurso: %s\nInstituicao: %s\nUsuario: %s\nMatricula: %d\n\n",aluno.nome,aluno.sexo,aluno.idade,aluno.numero,aluno.curso,aluno.instituicao,aluno.usuario,aluno.matricula);
	}
	fclose(arquivo);
	syst();	
}

void mostrar_especifico(){
	CADASTRO aluno;
	FILE *arquivo;
	char usuario[30];
	int opcao,mat,cont=0;
	printf("E necessario informar usuario ou numero da matricula!");
	printf("\n\nEscolha uma opcao: [1] Usuario\t[2] Matricula\n");
	printf("Opcao: ");
	scanf("%d",&opcao);
	system("cls");
	if(opcao == 1){
		printf("Informe o nome do usuario: ");
		fflush(stdin);
		gets(usuario);
		arquivo = open_file("cadastro.txt",'r');
		while(!feof(arquivo)){
			fscanf(arquivo,"%s %s %s %s %s %d %d %d\n",&aluno.nome,&aluno.curso,&aluno.instituicao,&aluno.usuario,&aluno.sexo,&aluno.idade,&aluno.numero,&aluno.matricula);
			if(!(strcmp(aluno.usuario,usuario))){
				printf("Aluno: %s\nSexo: %s\nIdade: %d\nNumero: %d\nCurso: %s\nInstituicao: %s\nUsuario: %s\nMatricula: %d\n\n",aluno.nome,aluno.sexo,aluno.idade,aluno.numero,aluno.curso,aluno.instituicao,aluno.usuario,aluno.matricula);	
				cont++;
			}	
		}
		fclose(arquivo);
		if(cont==0)
			printf("\nO usuario informado nao esta cadastrado!\n");
	}else{
		printf("Informe a matricula: ");
		scanf("%d",&mat);
		arquivo = open_file("cadastro.txt",'r');
		while(!feof(arquivo)){
			fscanf(arquivo,"%s %s %s %s %s %d %d %d\n",&aluno.nome,&aluno.curso,&aluno.instituicao,&aluno.usuario,&aluno.sexo,&aluno.idade,&aluno.numero,&aluno.matricula);
			if(mat == aluno.matricula){
				printf("Aluno: %s\nSexo: %s\nIdade: %d\nNumero: %d\nCurso: %s\nInstituicao: %s\nUsuario: %s\nMatricula: %d\n\n",aluno.nome,aluno.sexo,aluno.idade,aluno.numero,aluno.curso,aluno.instituicao,aluno.usuario,aluno.matricula);	
				cont++;
			}	
		}
		fclose(arquivo);
		printf("\nA matricula informada nao esta cadastrada!\n");
	}
	
	syst();	
}

int menu(){
	int opcao;
	do{
		puts("MENU:");
		puts("1 - CADASTRAR");
		puts("2 - VERIFICAR TODOS CADASTROS");
		puts("3 - VERIFICAR CADASTRO ESPECIFICO");
		puts("0 - SAIR");
		printf("OPCAO: ");
		scanf("%d",&opcao);
		if(opcao < 0 || opcao > 3){
			puts("\nOPCAO INVALIDA, TENTE NOVAMENTE!");
			syst();
		}
	}while(opcao < 0 || opcao > 3);
	system("cls");
	return opcao;
}

void cadastrar(CADASTRO *aluno){
	int opcao;
	do{
		printf("Nome: ");
		fflush(stdin);
		gets(aluno->nome);
		do{
		printf("Sexo: [1] Masculino\t[2] Feminino\n");
		printf("Opcao: ");
		scanf("%d",&opcao);
		if(opcao==1){
			strcpy(aluno->sexo,"Masculino");
		}else{
			if(opcao==2){
				strcpy(aluno->sexo,"Feminino");	
			}else{
				printf("Opcao invalida !\n");
			}	
		}
		}while(opcao != 1 && opcao != 2);
		printf("Idade: ");
		scanf("%d",&aluno->idade);
		printf("Numero: ");
		scanf("%d",&aluno->numero);
		printf("Curso: ");
		fflush(stdin);
		gets(aluno->curso);
		printf("Instituicao: ");
		fflush(stdin);
		gets(aluno->instituicao);
		printf("\n\nConfirma todas informacoes?\n[1] Sim\t[2] Nao\n");
		printf("Opcao: ");
		scanf("%d",&opcao);
		if(opcao==2)
			syst();
	}while(opcao != 1);
	syst();
	printf("Para completar sua matricula e necessario cadastrar um nome de usuario: ");
	printf("\n\nUsuario: ");
	fflush(stdin);
	gets(aluno->usuario);
	srand((unsigned) time (NULL));
	aluno->matricula = 1000 + rand() % 1000;
	printf("Matricula: %d", aluno->matricula);
}

void main(){
	CADASTRO aluno;
	while(1){
		switch(menu()){
			case 1:			cadastrar(&aluno);
							save_file(aluno);
				break;
			case 2:			mostrar();
				break;
			case 3:			mostrar_especifico();	
				break;
			default:		puts("Finalizando o programa...");
							exit(0);
		}	
	}
}

