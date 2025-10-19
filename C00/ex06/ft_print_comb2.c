#include <unistd.h>

void ft_putchar(char c){
    write(1, &c, 1);
}

void print_combination(short a, short b){
    ft_putchar(a / 10 + '0');
    ft_putchar(a % 10 + '0');
    ft_putchar(' ');
    ft_putchar(b / 10 + '0');
    ft_putchar(b % 10 + '0');  
    
    if (!(a == 98 && b == 99)){
        ft_putchar(',');
        ft_putchar(' ');
    }
}

void ft_print_comb2(void){
    short a;
    short b;
    
    a = 0;
    while (a <= 99){
        b = a + 1;
        while (b <= 99){
            print_combination(a, b);    

            b++;        
        }
        a++;
    }
}

int main(){
    ft_print_comb2();
    return (0);
}

