#include <stdio.h>


int Calcula(int Xv, int Xd) {
    return Xv - Xd; 
}
//chamar função antes do main() p n zoar o cdg

int main() {
    int val, desc, tot; 
    int* Xv;
    int* Xd;
    int* Xt;
    
    Xt = &tot; 
    Xv = &val;  
    Xd = &desc; 
    //%d p decimal / %c p caractere / %f p float
    printf("Digite o valor do produto: \n");
    scanf("%d", Xv);//pontero #1
    
    printf("Digite o desconto do produto: \n");
    scanf("%d", Xd);//pontero #2
    
    if (*Xv <= *Xd) {
        printf("Erro, não é possivel aplicar um desconto maior que o valor do Produto\n"); 
    } else {
        *Xt = Calcula(*Xv, *Xd);//chama função la de cima e aplica aki
        printf("Valor Original do Produto: %d\n", *Xv);
        printf("Valor do desconto: %d\n", *Xd); 
        printf("Valor Final do Produto: %d\n", *Xt); 
    }

    return 0;
}
