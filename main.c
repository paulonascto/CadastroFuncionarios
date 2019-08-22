#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "controle.h"

int main(){

    setlocale(LC_ALL, "Portuguese");

    arq_func = fopen("dados_func.dat","rb+");
    arq_hist_func = fopen("dados_hist_func.dat","rb+");
    arq_dept = fopen("dados_dept.dat","rb+");
    arq_hist_dept = fopen("dados_hist_dept.dat","rb+");
    arq_hist_sal = fopen("dados_hist_sal.dat","rb+");

    if(!arq_func || !arq_hist_func || !arq_dept || !arq_hist_dept || !arq_hist_sal){/*if(arq==NULL*/
        arq_func = fopen("dados_func.dat","wb+");
        arq_hist_func = fopen("dados_hist_func.dat","wb+");
        arq_dept = fopen("dados_dept.dat","wb+");
        arq_hist_dept = fopen("dados_hist_dept.dat","wb+");
        arq_hist_sal = fopen("dados_hist_sal.dat","wb+");
    }
    if(arq_func || arq_hist_func || arq_dept || arq_hist_dept || arq_hist_sal){
        menu();
       // fclose(arq_dept);

    }
    fclose(arq_func);
    fclose(arq_hist_func);
    fclose(arq_dept);
    fclose(arq_hist_dept);
    fclose(arq_hist_sal);

    return 0;
}

