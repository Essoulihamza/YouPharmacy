#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strings.h>
typedef struct product //product (code / name / amount / price)
{
    char code[30];
    char name[20];
    int amount;
    float price;
}product;
//globle variables
int products_amount = 0;
product* P_product = NULL;
//function prototype
int menu();
void add_one_product(int style);
void add_products();
void sort();
void selection_sort_by_price();
void bubble_sort_alphabitcly();
void print();
//program start point
int main(void)
{
    system("cls");
    menu();
}
int menu()
{
    int choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n1 - Ajouter un nouveau produit.");
    printf("    ||||    2 - Ajouter plusieurs nouveaux produits.");
    printf("  ||||  3 - Lister tous les produits.");
    printf("\n\n\n4 - Acheter produit.");
    printf("               ||||    5 - Rechercher les produits.");
    printf("              ||||   6 - Etat du stock.");
    printf("\n\n\n7 - Alimenter le stock.");
    printf("            ||||    8 - Supprimer les produits.");
    printf("               ||||   9 - Statistique de vente.\n\n\n");
    printf("\t\t\t\t\t\t\t10 - Exit.");
    printf("\n________________________________________________________________________________________________________________________________________\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            system("cls"); 
            add_one_product(0);
            break;
        case 2: 
            system("cls");
            add_products();
            break;
        case 3: 
            system("cls");
            sort();
            break;
        case 4: 
            system("cls");
            printf("Acheter produit.\n");
            break;
        case 5: 
            system("cls");
            printf("Rechercher les produits.\n");
            break;
        case 6: 
            system("cls");
            printf("Etat du stock.\n");
            break;
        case 7: 
            system("cls");
            printf("Alimenter le stock.\n");
            break;
        case 8: 
            system("cls");
            printf("Supprimer les produits.\n");
            break;
        case 9:
            system("cls");
            printf("Statistique de vente.\n");
            break;
        case 10:
            system("cls");
            printf("Au revoir...");
            free(P_product);
            Sleep(500);
            exit(0);
        default: printf("no choice with this input\n");
            Sleep(1000);
            system("cls");
            menu();
    }
}
void add_one_product(int style)
{
    int choice;
    if( products_amount == 0 )
    {
        P_product = (product*) malloc(sizeof(product));
        if( P_product == NULL )
        {
            printf("out of memory!\n");
            exit(2);
        }
    }else{
        P_product = (product*) realloc(P_product, (1 + products_amount) * sizeof(product));
        if( P_product == NULL )
        {
            printf("out of memory!\n");
            exit(2);
        }
    }
    if( style == 0 )
    {
        printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
        printf("\n------------------------------------------------------------Ajouter un nouveau produit---------------------------------------------------\n");
        printf("\n\n");
        printf("Entrez le code du produit: ");
        scanf("%s", &P_product[products_amount].code);
        printf("\nEntrez le nom du produit: ");
        scanf("%s", &P_product[products_amount].name);
        printf("\nentrer la quantité du produit: ");
        scanf("%d", &P_product[products_amount].amount);
        printf("\nEntrez le prix du produit(DH): ");
        scanf("%f", &P_product[products_amount].price);
        system("cls");
        printf("\nLe produit a été ajouté avec succès."); products_amount++;
        Sleep(1000);
        printf("\n\n");
        printf("1 - revenir au menu.\n");
        printf("2 - quitter le programme.\n\n\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);
        if( choice == 1 )
        {
            system("cls");
            menu();
        }else if( choice == 2 ) 
        {
            system("cls");
            printf("Au revoir...");
            free(P_product);
            Sleep(500);
            exit(0);
        }
    }
    else
    {
        printf("\n\n");
        printf("Entrez le code du produit: ");
        scanf("%s", &P_product[products_amount].code);
        printf("\nEntrez le nom du produit: ");
        scanf("%s", &P_product[products_amount].name);
        printf("\nentrer la quantité du produit: ");
        scanf("%d", &P_product[products_amount].amount);
        printf("\nEntrez le prix du produit(DH): ");
        scanf("%f", &P_product[products_amount].price);
        system("cls");
        printf("\nLe produit a été ajouté avec succès."); products_amount++;
        Sleep(1000);
    }
}
void add_products()
{
    int number_of_products;
    int choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n---------------------------------------------------------Ajouter plusieurs nouveaux produits------------------------------------------------\n");
    printf("\n\n");
    printf("entrez le nombre de produits que vous souhaitez ajouter: ");
    scanf("%d", &number_of_products);
    if( number_of_products == 1 )
    {
        system("cls");
        add_one_product(0);
    }
    for(int i = 1; i <= number_of_products; i++ )
    {
        if( i == 1 ) 
        {
            printf("\n\n\n\nSaisissez les informations du 1er produit:\n");
        }else{
            printf("\n\n\n\nSaisissez les informations du %ième produit\n", i);
        }
        add_one_product(1);
    }
    system("cls");
    Sleep(1000);
    printf("\ntous les %i produits ont été ajoutés avec succès.\n", number_of_products);
    printf("\n\n");
    printf("1 - Lister tous les produits (Nom, prix, prix TTC)\n\n\n");
    printf("2 - revenir au menu.\n\n\n");
    printf("3 - quitter le programme.\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        system("cls");
        sort();
        print();
    }
    else if( choice == 2 )
    {
        system("cls");
        menu();
    }else if( choice == 3 ) 
    {
        system("cls");
        printf("Au revoir...");
        free(P_product);
        Sleep(500);
        exit(0);
    }
}
void print()
{
    int choice;
    if( products_amount == 0 )
    {
        printf("\n\n\n\n\naucun produit disponible pour le moment.\n\n\n\n\n");
    }else{
        printf("CODE                NAME            AMOUNT              PRICE\n\n");
        for( int i = 0; i < products_amount; i++ )
        {
            printf("%s                 %s            %d           %.2f DH      \n",P_product[i].code, P_product[i].name,P_product[i].amount ,P_product[i].price);
        }
        printf("\n\n");
    }
    printf("1 - revenir au menu.\n\n\n");
    printf("2 - quitter le programme.\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        system("cls");
        menu();
    }
    else if( choice == 2 )
    {
        system("cls");
        printf("Au revoir...");
        free(P_product);
        Sleep(500);
        exit(0);
    }
    
}
void sort()
{
    int choice;
    printf("1 - lister tous les produits selon l’ordre alphabétique  croissant du nom.\n\n\n");
    printf("2 - lister tous les produits selon l’ordre  décroissant du prix.\n\n\n");
    printf("3 - revenir au menu.\n\n\n");
    printf("4 - quitter le programme.\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        system("cls");
        bubble_sort_alphabitcly();
        print();
    }else if( choice == 2 )
    {
        system("cls");
        selection_sort_by_price();
        
    }else if( choice == 3 )
    {
        system("cls");
        menu();
    }else if( choice == 4 )
    {
        system("cls");
        printf("Au revoir...");
        free(P_product);
        Sleep(500);
        exit(0);
    }
}
void selection_sort_by_price()
{
    product temp;
    int max_pos;
    for( int i = 0; i < products_amount - 1; i++ )
    {
        max_pos = i;
        for( int j = i + 1; j < products_amount; j++ )
        {
            if(P_product[j].price > P_product[max_pos].price) 
                max_pos = j;
            if (max_pos != i)
            {
                temp = P_product[i];
                P_product[i] = P_product[max_pos];
                P_product[max_pos] = temp;
            }
        }
    }
}
void bubble_sort_alphabitcly()
{
    product temp;
    int count = -1;
    while( count != 0 )
    {
        count = 0;
        for( int i = 0; i < products_amount - 1; i++ )
        {
            if(strcasecmp(P_product[i].name, P_product[i + 1].name) > 0 )
            {
                temp = P_product[i];
                P_product[i] = P_product[i + 1];
                P_product[i + 1] = temp;
                //
                count++;
            }
        }
    }

}
