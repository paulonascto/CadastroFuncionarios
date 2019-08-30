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
            if(cadastro_func(arq_func, 0) == 1){
                system("clear || cls");
                printf("\nCadastro de Funcionário Realizado!\n");
            }
            else{
                system("clear || cls");
                printf("\n\nAinda nao existe departamento cadastrado. Cadastre um primeiro.\n\n");
            }
        break;

        case 3:
            alteraDadosFunc(arq_func);
            break;

        case 4:
            alterarDeptFunc(arq_func);
            break;
        case 5:
            alterarGerenteDept(arq_dept);
            break;
        case 6:
            consultaFunc(arq_func);
            break;
        case 7:
            FolhaPag(arq_func);
            break;
        case 12:
            exibeDept(arq_dept);
            break;

//        case 13:
//        exibeFunc(arq_func);
//           break;

        case 10:
            exibeHistFunc(arq_hist_func);
            break;
        }
    }while(op>0 && op<14);
}

///Lembrar de Apagar
void exibeHistFunc(FILE *a){
    THistoricoFuncionario histFunc;
    fseek(a, 0, SEEK_SET);
    while(fread(&histFunc, sizeof(THistoricoFuncionario), 1, a)==1){
            printf("\nNovo id departamento: %li\n", histFunc.id_departamento);
            printf("Id Funcionario: %li\n", histFunc.id_funcionario);
            printf("Data historico: %s\n", histFunc.data);
    }
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


/// Função usada na consulta de funcionarios. Exibe os dados de um determinado funcionário.
void exibeFunc(FILE *a, long int posArq){
    TFuncionario func;
    fseek(a, posArq * sizeof(TFuncionario),SEEK_SET);
    //while(fread(&func, sizeof(TFuncionario), 1, a)==1)
        fread(&func, sizeof(TFuncionario), 1, a);
        printf("Id Funcionario: %li\n", func.id);
        printf("Matricula: %s\n", func.matricula);
        printf("Nome: %s\n", func.nome);
        printf("Data de nascimento: %s\n", func.dataNascimento);
        printf("CPF: %s\n", func.cpf);
        printf("id departamento: %li\n", func.id_departamento);
        printf("Salario: %.2f\n", func.salario);
        printf("CEP: %s\n", func.cep);
        printf("Estado: %s\n", func.uf);
        printf("Cidade: %s\n", func.cidade);
        printf("Bairro: %s\n", func.bairro);
        printf("Rua: %s\n", func.rua);
        printf("Numero: %u\n", func.Numero);
        printf("Complemento: %s\n", func.complemento);
        printf("Email: %s\n", func.email);
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

/*
    Função que recebe um arquivo, e um char como parâmetro e
    faz a verificação se o que foi digitado já esta presente no arquivo,
    retorna a posição caso encontre, ou -1 pois caso não encontre
*/
int pesquisa_Matricula(FILE *arq_func,char *mat){
   TFuncionario func;
   int posicao=0,verifica;
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
/// Função que verifica ID de departamento
int verificaId_Dept(FILE *arq_dept,int id_departamento){
   TDepartamento dept;
   int posicao=0;
   fseek(arq_dept,0,SEEK_SET);
   while(fread(&dept,sizeof(TDepartamento),1,arq_dept)==1){
       if(dept.id==id_departamento)
            return posicao;
        else
            posicao++;
   }
    printf("\nId departamento informado não existe. Por favor, informe um id valido.\n");
    return -1;
}

/// Função que verifica ID de funcionario
int verificaId_Func(FILE *arq_func, long int id){
    TFuncionario func;
    int posicao=0;
    fseek(arq_func,0,SEEK_SET);
    while(fread(&func,sizeof(TFuncionario),1,arq_func)==1){
        if(func.id==id){
            return posicao;
        }
        else
            posicao++;
    }
    printf("\nId funcionario informado não existe. Por favor, informe um id valido.\n");
    return -1;
}


///Cadastro de Funcionario
//Função que realiza o cadastramento de Funcionário
//Retorna 1, caso o cadastrameto estiver sido realizado
//Com Sucesso
int cadastro_func(FILE *arq_func, int ver){
    long int verificaDep, *ponteiroIdDepartamento, *ponteiroIdFuncionario;
    int x;
    TFuncionario func;
    TDepartamento dept;
    fseek(arq_dept,0,SEEK_SET);
    fread(&dept, sizeof(TDepartamento),1,arq_dept);
    if(dept.id>10 || dept.id==0)
        return 0;
    int sair;
    do{
        if(ver == 0){
            do{
                //system("clear || cls");
                printf("\nDigite a matricula do funcionário: ");
                setbuf(stdin,NULL);
                fgets(func.matricula, MATRICULA, stdin);
                retiraEnter(func.matricula);
            }while(pesquisa_Matricula(arq_func,func.matricula)!=-1 || verificaNum(func.matricula)==0);
        }
        else{
            do{
                system("clear || cls");
                printf("\nDigite a matricula do funcionário que deseja alterar os dados: ");
                setbuf(stdin,NULL);
                fgets(func.matricula, MATRICULA, stdin);
                retiraEnter(func.matricula);
            }while(pesquisa_Matricula(arq_func,func.matricula)==-1 || verificaNum(func.matricula)==0);
            x = pesquisa_Matricula(arq_func,func.matricula);
            fseek(arq_func,x * sizeof(TFuncionario),SEEK_SET);
            fread(&func,sizeof(TFuncionario),1,arq_func);
            verificaDep = func.id_departamento;
        }
        /*do{
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
        }while(verificaCPF(func.cpf)==0);
        do{
            setbuf(stdin,NULL);
            printf("\nDigite o numero do Departamento: ");
            scanf("%li",&func.id_departamento);
        }while(verificaId_Dept(arq_dept,func.id_departamento)==-1);
        */
        printf("\nInforme o salario do funcionario: ");
        scanf("%f", &func.salario);
        /*
        printf("\nInforme o CEP do funcionario: ");
        setbuf(stdin, NULL);
        fgets(func.cep, CEP, stdin);
        retiraEnter(func.cep);

        setbuf(stdin, NULL);
        printf("\nInforme a rua do funcionario: ");
        fgets(func.rua, RUA, stdin);
        retiraEnter(func.rua);

        setbuf(stdin, NULL);
        printf("\nInforme o bairro do funcionario: ");
        fgets(func.bairro, BAIRRO, stdin);
        retiraEnter(func.bairro);

        setbuf(stdin, NULL);
        printf("\nInforme o numero da casa do funcionario: ");
        scanf("%u", &func.Numero);

        setbuf(stdin, NULL);
        printf("\nInforme o complemento do funcionario: ");
        fgets(func.complemento, COMPLEMENTO, stdin);
        retiraEnter(func.complemento);

        setbuf(stdin, NULL);
        printf("\nInforme a cidade do funcionario: ");
        fgets(func.cidade, CIDADE, stdin);
        retiraEnter(func.cidade);

        setbuf(stdin, NULL);
        printf("\nInforme o UF do funcionario: ");
        fgets(func.uf, UF, stdin);
        retiraEnter(func.uf);

        setbuf(stdin, NULL);
        printf("\nInforme o email do funcionario: ");
        fgets(func.email, EMAIL, stdin);
        retiraEnter(func.email);*/


        if(ver==0){
            fseek(arq_func,0,SEEK_END);
            func.id = (ftell(arq_func)/sizeof(TFuncionario)) + 1;
            fwrite(&func, sizeof(TFuncionario), 1, arq_func);
        }
        else{
            if(func.id_departamento != verificaDep){
                THistoricoFuncionario histFunc;

                ponteiroIdDepartamento = &func.id_departamento;
                histFunc.id_departamento = *ponteiroIdDepartamento;

                ponteiroIdFuncionario = &func.id;
                histFunc.id_funcionario = *ponteiroIdFuncionario;

                do{
                    setbuf(stdin,NULL);
                    printf("\nDigite a Data de alteração dos dados (Ex: dd/mm/aaaa): ");
                    fgets(histFunc.data,DATA,stdin);
                    retiraEnter(histFunc.data);
                }while(verificaData(histFunc.data)==0);

                fseek(arq_hist_func, 0, SEEK_END);
                fwrite(&histFunc, sizeof(THistoricoFuncionario), 1, arq_hist_func);
            }
            fseek(arq_func,x * sizeof(TFuncionario),SEEK_SET);
            fwrite(&func, sizeof(TFuncionario), 1, arq_func);

        }
        printf("Deseja sair:1-Sim 2-Não");
        scanf("%d",&sair);
    }while(sair!=1);
    return 1;
}

/// Função que altera dados de funcionários
void alteraDadosFunc(FILE *arq_func){
    cadastro_func(arq_func, 1);
}

/// Função que altera departamento de um funcionário
void alterarDeptFunc(FILE* arq_func){
    TFuncionario func;
    THistoricoFuncionario histFunc;
    long int *ponteiroIdFuncionario;
    int x, verificaIdDep;
    do{
        system("clear || cls");
        printf("\nDigite a matricula do funcionário que deseja alterar o departamento: ");
        setbuf(stdin,NULL);
        fgets(func.matricula, MATRICULA, stdin);
        retiraEnter(func.matricula);
    }while(pesquisa_Matricula(arq_func,func.matricula)==-1 || verificaNum(func.matricula)==0);
    x = pesquisa_Matricula(arq_func,func.matricula);
    fseek(arq_func,x * sizeof(TFuncionario),SEEK_SET);
    fread(&func,sizeof(TFuncionario),1,arq_func);
    do{
        setbuf(stdin,NULL);
        printf("\nDigite o numero do Departamento para qual deseja mover o funcionario: ");
        scanf("%d",&verificaIdDep);
        printf("%d",verificaId_Dept(arq_dept,verificaIdDep)==-1);
    }while(verificaId_Dept(arq_dept,verificaIdDep)==-1);
    if(verificaIdDep!=func.id_departamento){
        func.id_departamento = verificaIdDep;
        ponteiroIdFuncionario = &func.id;
        histFunc.id_funcionario = *ponteiroIdFuncionario;

        do{
            setbuf(stdin,NULL);
            printf("\nDigite a Data de alteração do departamento (Ex: dd/mm/aaaa): ");
            fgets(histFunc.data,DATA,stdin);
            retiraEnter(histFunc.data);
        }while(verificaData(histFunc.data)==0);

        fseek(arq_hist_func, 0, SEEK_END);
        fwrite(&histFunc, sizeof(THistoricoFuncionario), 1, arq_hist_func);
        fseek(arq_func,x * sizeof(TFuncionario),SEEK_SET);
        fwrite(&func,sizeof(TFuncionario),1,arq_func);
    }
    else{
        printf("\nO funcionario ja esta cadastrado no departamento informado!\n");
    }
}

/// Função que pesquisa um determinado funcionário
void consultaFunc(FILE* arq_func){
    long int x;
    TFuncionario func;
    do{
        system("clear || cls");
        printf("\nDigite a matricula do funcionário que deseja buscar os dados: ");
        setbuf(stdin,NULL);
        fgets(func.matricula, MATRICULA, stdin);
        retiraEnter(func.matricula);
    }while(pesquisa_Matricula(arq_func,func.matricula)==-1 || verificaNum(func.matricula)==0);
    x = pesquisa_Matricula(arq_func,func.matricula);
    exibeFunc(arq_func, x);
}

/// Função que gera folha de pagamento.
void FolhaPag(FILE *arq_func){
    int posFunc;
    TFuncionario func;
    do{
        printf("Digite a matricula do Funcionario que deseja gerar a folha de pagamento: ");
        setbuf(stdin, NULL);
        fgets(func.matricula, MATRICULA, stdin);
        retiraEnter(func.matricula);
        posFunc = pesquisa_Matricula(arq_func,func.matricula);
    }while(posFunc==-1);
    fseek(arq_func,posFunc * sizeof(TFuncionario),SEEK_SET);
    fread(&func,sizeof(TFuncionario),1,arq_func);
    printf("Matricula: %s\n", func.matricula);
    printf("Nome: %s\n", func.nome);
    printf("Salario: %.2f\n", func.salario);
}


/// Função que verifica CPF
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

//Função que recebe como parâmetro um arquivo e altera o
//gerente de um determiando departamento
void alterarGerenteDept(FILE *a){
    TFuncionario func;
    long int posDept,posFunc;
    TDepartamento dept;


    do{
        printf("Digite o numero do departamento que deseja alterar o gerente: ");
        scanf("%li",&dept.id);
        posDept = verificaId_Dept(a,dept.id);
        printf("posicao dept: %li",posDept);
    }while(posDept==-1);
    do{
        printf("Digite a matricula do novo gerente: ");
        setbuf(stdin, NULL);
        fgets(func.matricula, MATRICULA, stdin);
        retiraEnter(func.matricula);
        posFunc = pesquisa_Matricula(arq_func,func.matricula);
        printf("Posicao retornada funcionario: %li",posFunc);
    }while(posFunc==-1);
    fseek(arq_dept,posDept * sizeof(TDepartamento),SEEK_SET);
    fread(&dept,sizeof(TDepartamento),1,arq_dept);
    printf("id departamento: %li", dept.id);
    dept.id_gerente = 1+posFunc;
    fseek(arq_dept,posDept * sizeof(TDepartamento),SEEK_SET);
    fwrite(&dept,sizeof(TDepartamento),1,arq_dept);
}
