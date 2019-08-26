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
        }while(verificaData(func.dataNascimento)==0);
        do{
            setbuf(stdin,NULL);
            printf("\nDigite seu CPF: ");
            fgets(func.cpf,CPF,stdin);
            retiraEnter(func.cpf);
        }while(verificaData(func.cpf)==0);

        fseek(arq_dept,0,SEEK_END);
        func.id = (ftell(arq_func)/sizeof(TFuncionario)) + 1;
        fwrite(&func, sizeof(TFuncionario), 1, arq_func);
        printf("Deseja sair:1-Sim 2-Não");
        scanf("%d",&sair);
    }while(sair!=1);
    return 1;
}

int verificaCPF(char *cpf){
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; //se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        //digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) //multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; //se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        //digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) //multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; //se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}


//Esta função recebe como paramêtro uma string e faz a verificação
//se o que foi digitado foi somente numeros e verifica se
//a data digitada está entre 20/06/1960 a 01/01/2019
int verificaData(char *valor){
    int i;
    if(verificaNum(valor) == 0)
        return 0;
    int dia = -1, ano = -1, mes = -1;
    sscanf(valor,"%d%*c%d%*c%d",&dia,&mes,&ano); //
    if(ano > 2019 || ano < 1961){ // Ano não pode ser menor que 1961 ou maior que 2019
        return 0;
    }

    if(ano == 1960){       //data de nascimento limite.
        if(mes < 07){
            if(dia < 21)
                return 0;
        }
    }
    if(mes > 12){  // Mes não pode ser maior que 12.
        return 0;
    }
    if(((ano % 4 == 0) || (ano % 400 == 0)) && (ano % 100 != 0)){ // verifica se ano é bissexto.
        if(mes == 02){
            if(dia > 29){
                return 0;
            }
        }
        if(mes == 01 || mes == 03 || mes == 05 || mes == 07 || mes == 8 || mes == 10 || mes == 12){
            if(dia > 31){
                return 0;
            }
        }
        else{
            if(dia > 30){
                return 0;
            }
        }
    }
    else{
        if(mes == 02){
            if(dia > 28){
                return 0;
            }
        }
        if(mes == 01 || mes == 03 || mes == 05 || mes == 07 || mes == 8 || mes == 11 || mes == 12){
            if(dia > 31){
                return 0;
            }
        }
        else{
            if(dia > 30){
                return 0;
            }
        }
    }
    return 1;
}
