#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "controle.h"

void menu(){
    int op;
    do{
        printf("\n1 - Cadastro de Departamento\n2 - Cadastro de Funcionário\n3 - Alterar Funcionário\n4 - Alterar Departamento Funcionário\n5 - Alterar o Gerente de um Departamento\n");
        printf("6 - Consultar Matrícula do Funcionário\n7 - Gerar Folha Pagamento\n8 - Alterar o Salário de um Funcionário\n9 - Relatório de Funcionários por departamento\n10 - Histórico do Salário em um período\n11 - Gerentes de um departamento :");
        scanf("%d",&op);
        switch(op){
        case 1:
            if(cadastro_dept(arq_dept)){
                system("clear || cls");
                printf("\nCadastro de Departamento Realizado!\n");
            }
        break;
        case 2:
            if(cadastro_func(arq_func)){
                system("clear || cls");
                printf("\nCadastro de Funcionário Realizado!\n");
            }
        break;
        case 12:
            exibeDept(arq_dept);
            break;
        case 13:
            exibeFunc(arq_func);
            break;
        }
    }while(op>0 && op<14);
}

///Lembrar de apagar essa função que só estavamos usando para ver se o conteudo estava indo diretamente pro arquivo
void exibeDept(FILE *a){
    TDepartamento dept;
    fseek(a,0,SEEK_SET);
    while(fread(&dept, sizeof(TDepartamento), 1, a)==1){
        printf("id: %li\n", dept.id);
        printf("id gerente: %li\n", dept.id_gerente);
        printf("nome: %s\n", dept.nome);
        printf("ramal: %hu\n", dept.Ramal);
        printf("sigla: %s\n", dept.sigla);
    }
}


///Lembrar de apagar essa função que só estavamos usando para ver se o conteudo estava indo diretamente pro arquivo
void exibeFunc(FILE *a){
    TFuncionario func;
    fseek(a,0,SEEK_SET);
    while(fread(&func, sizeof(TFuncionario), 1, a)==1){
        printf("id: %li\n", func.id);
        printf("matricula: %s\n", func.matricula);
    }
}

//Essa função recebe como parâmetro uma string
//E tira o espaço e também o "ENTER", que não foi utilizado
void retiraEnter(char *string){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n'){
		string[tamanho] = '\0';
	}
	else {
		while (getc(stdin) != '\n')
			continue;
	}
}

//Essa função recebe como parâmetro uma string
//E verifica, se a variável contém ao menos uma palavra
//Retorna 0, caso a variável estiver vazia
int verificaLetra(char *palavra){
    int i,t;
    if(strlen(palavra)==0)
        return 0;
    if(palavra[0]==' ')
        return 0;
    for(i=0;i<strlen(palavra);i++){
        t=isdigit(palavra[i]);
        if(t!=0)
            return 0;
    }
    return 1;
}

//Essa função recebe como parâmetro uma string
//E verifica, se a variável contém somente numeros
//Retorna 0, caso a variável tiver recebido alguma letra
int verificaNum(char *ramal){
    int i;
    if(strlen(ramal)==0)
        return 0;
    if(ramal[0]==' ')
        return 0;
    for(i=0;i<strlen(ramal);i++){
        if(isalpha(ramal[i])!=0){
            return 0;
        }
    }
    return 1;
}

///Cadastro de Departamento
//Função que realiza o cadastramento de departamento
//Retorna 1, caso o cadastrameto estiver sido realizado
//Com Sucesso
int cadastro_dept(FILE *arq_dept){
    TDepartamento dept;
    int sair;
    char verificaRamal[10];
    do{
        do{
            system("clear || cls");
            setbuf(stdin,NULL);
            printf("\nInforme o Nome do Departamento: ");
            fgets(dept.nome, NOME_DEP, stdin);
            retiraEnter(dept.nome);
        }while(verificaLetra(dept.nome)==0);
        printf("\nDigite o nome da sigla: ");
        setbuf(stdin,NULL);
        fgets(dept.sigla, SIGLA, stdin);
        retiraEnter(dept.sigla);
        do{
            printf("\nDigite o Número do RAMAL: ");
            setbuf(stdin,NULL);
            fgets(verificaRamal, 10, stdin);
            retiraEnter(verificaRamal);
        }while(verificaNum(verificaRamal)==0);
        dept.Ramal = strtol(verificaRamal, NULL, 10);

        fseek(arq_dept,0,SEEK_END);
        dept.id = (ftell(arq_dept)/sizeof(TDepartamento)) + 1;
        fwrite(&dept, sizeof(TDepartamento), 1, arq_dept);
        printf("Deseja sair:1-Sim 2-Não");
        scanf("%d",&sair);
    }while(sair != 1);
    return 1;
}

//FUnção que recebe um arquivo, e um char como parâmetro e
//faz a verificação se o que foi digitado já esta presente no arquivo,
//retorna a posição caso encontre, ou -1 pois caso não encontre
int pesquisa_Matricula(FILE *arq_func,char *mat){
   TFuncionario func;
   int posicao=0,verifica;
   /*posicionando no início do arquivo*/
   fseek(arq_func,0,SEEK_SET);
   while(fread(&func,sizeof(TFuncionario),1,arq_func)==1){
      verifica = strcmp(func.matricula,mat);
      if(verifica==0)
         return posicao;
      else
         posicao++;
   }
   return -1;
}

///Cadastro de Funcionario
//Função que realiza o cadastramento de Funcionário
//Retorna 1, caso o cadastrameto estiver sido realizado
//Com Sucesso
int cadastro_func(FILE *arq_func){
    TFuncionario func;
    int sair;
    do{
        do{
            system("clear || cls");
            printf("\nDigite a matricula do funcionário: ");
            setbuf(stdin,NULL);
            fgets(func.matricula, MATRICULA, stdin);
            retiraEnter(func.matricula);
        }while(pesquisa_Matricula(arq_func,func.matricula)!=-1 || verificaNum(func.matricula)==0);
        do{
            setbuf(stdin,NULL);
            printf("\nInforme o Nome do Funcionario: ");
            fgets(func.nome, NOME, stdin);
            retiraEnter(func.nome);
        }while(verificaLetra(func.nome)==0);
        do{
            setbuf(stdin,NULL);
            printf("\nDigite a Data de Nascimento (Ex: dd/mm/aaaa): ");
            fgets(func.dataNascimento,DATA,stdin);
            retiraEnter(func.dataNascimento);
        }while(verificarData(func.dataNascimento)==0);


        fseek(arq_dept,0,SEEK_END);
        func.id = (ftell(arq_func)/sizeof(TFuncionario)) + 1;
        fwrite(&func, sizeof(TFuncionario), 1, arq_func);
        printf("Deseja sair:1-Sim 2-Não");
        scanf("%d",&sair);
    }while(sair!=1);
    return 1;
}

//Verifica se o ano é bissexto ou não, retorna 0
//caso não for
int bissexto(int *data){
    return(data[2]%4==0 && data[2]%100!=0) || (data[2]%400 == 0);
}

//Verifica se as data no caso o mes, está no limite
//e retorna o ultimo dia de um determinado mes a partir
//da logica de um calendario
int ultimoDia(int *data){

    if(data[1]==2)
        return 28 + bissexto(data);
    if(data[1] == 4 || data[1] == 6 || data[1] == 9 || data[1] == 11)
        return 30;
    return 31;
}

//Esta função recebe como paramêtro uma string e faz a verificação
//se o que foi digitado foi somente numeros e verifica se
//a data digitada está entre 20/06/1960 a 01/01/2019
int verificarData(char *entrada){
  char string[3] = "//";

  if (strstr(entrada, string) != NULL) ///strstr - localiza a primeira ocorrência de uma substring específica em uma string (use //)
    return 0;

  if (verificaNum(entrada)!=0)
    return 0;

  int i = 0;
  int data[3];

  sscanf(entrada,"%d%*c%d%*c%d",&data[0],&data[1],&data[2]);

  // Realize suas validações. Se alguma não for atingida, retorne '0'
  if(data[0]<1 || data[0] > ultimoDia(data))
    return 0;
  if(data[1]<1 || data[1]>12)
    return 0;
  if(data[2]<1961 || data[2]>2019)
    return 0;

  return 1;
}
