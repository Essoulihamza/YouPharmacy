#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct product
{
    char code[30];
    char name[20];
    float price;
}product;
int product_amount = 0;
int main(void)
{
    int a;
    product* pointer = malloc(sizeof(product));
    scanf("%d", &a);
    if( a == 0 )
    {
        printf("the code: ");
        scanf("%s", &pointer[product_amount].code);
        printf("enter the name: ");
        scanf("%s", &pointer[product_amount].name);
        printf("enter the price: ");
        scanf("%f", &pointer[product_amount].price);
        product_amount++;
    } 
    printf("CODE\t\tNAME\t\tPRICE\n\n");
    for(int i = 0; i < product_amount; i++ )
    {
        printf("%s\t%s\t%f\n",pointer[i].code, pointer[i].name, pointer[i].price);
    }
    scanf("%d", &a);
    if( a != 0 )
    {
        int size;
        char name[20];
        printf("how many product do you want to add?: ");
        scanf("%d", &size);
        pointer = realloc(pointer, (1+size)*sizeof(product));
        for( int i = product_amount; i < (product_amount + size); i++ )
        {
            printf("the code of %i : ", i+1);
            scanf("%s", &pointer[i].code);
            printf("enter the name: ");
            scanf("%s", &pointer[i].name);
            printf("enter the price: ");
            scanf("%f", &pointer[i].price);
        }
        product_amount += size;
        
    }
    printf("CODE\t\tNAME\t\tPRICE\n\n");
    for(int i = 0; i < product_amount; i++ )
    {
        printf("%s\t%s\t%f\n",pointer[i].code, pointer[i].name, pointer[i].price);
    }
    
    
}