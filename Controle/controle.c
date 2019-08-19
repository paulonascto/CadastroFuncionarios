#include "controle.h"

void menu(){
    int op;

    do{
        printf("1 - Cadastro de Departamento\n2 - Cadastro de Funcionário\n3 - Alterar Funcionário\n4 - Alterar Departamento Funcionário\n5 - Alterar o Gerente de um Departamento\n");
        printf("6 - Consultar Matrícula do Funcionário\n7 - Gerar Folha Pagamento\n8 - Alterar o Salário de um Funcionário\n9 - Relatório de Funcionários por departamento\n10 - Histórico do Salário em um período\n11 - Gerentes de um departamento :");
        scanf("%d",&op);
        switch(op){
        case 1:
            cadastro_dept(arq_func,&func);
        }
        system("clear || cls");
    }while(op>0 && op<12);
}

int cadastro_dept(FILE *arq_func,TDepartamento *dept){
    int sair;
    do{
        printf("\nInforme o Nome do Departamento:");
        setbuf(stdin,NULL);
        fgets(dept->nome,NOME_DEP,stdin);
        if(pesquisa_nome(arq_func,dept.nome)){
            printf("Codigo do Funcionário Gerente")
            fscanf("%d",dept->id_gerente);
        }

        fseek(a,0,SEEK_END);
        fwrite(&rf,sizeof(rf),1,a);

        dept->id++;
        printf("Deseja sair:1-Sim 2-Não");
        scanf("%d",&sair);
    }while(sair!=2);
    return 1;
}
