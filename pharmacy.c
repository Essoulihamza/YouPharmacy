//YouCode PHARMACY MANAGEMENT PROJECT
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strings.h>
#include <time.h>
typedef struct product //product (code / name / amount / price)
{
    char code[30];
    char name[20];
    int amount;
    float price;
}product;
typedef struct date
{
    int day;
    int month;
    int year;
}date;
typedef struct buyed_product{
    product info;
    date date;
}Buyed_product;
//globle variables
int products_amount = 0;
int sales = 0;
product* P_product = NULL;
Buyed_product* B_product = NULL;
//function prototype
int menu();
//add
void get_product_info();
void add_one_product(int style);
void add_products();
//sort & print
void sort();
void bubble_sort_alphabitcly();
void selection_sort_by_price();
void print();
//buy
void buy_product();
void sale_product(char* code, int amount);
//search
void search_products();
void search_by_code();
void search_by_amount();
//stock
void stock_status();
void stock_supply();
void delete_products();
//statistics
void sales_statistics();
void totat_sale_price();
void average_sale_price();
void max_sale_price();
void min_sale_price();
//usefull functions
int is_avialable(char* code, int amount);
void exit_program();
void go_back();
//program start point
int main(void)
{
    menu();
    free(B_product);
    free(P_product);
}
int menu()
{
    system("cls");
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
        case 1:     add_one_product(0);
            break;
        case 2:     add_products();
            break;
        case 3:     sort();
            break;
        case 4:     buy_product();
            break;
        case 5:     search_products();
            break;
        case 6:     stock_status();
            break;
        case 7:     stock_supply();
            break;
        case 8:     delete_products();
            break;
        case 9:     sales_statistics();
            break;
        case 10:    exit_program(0);
            break;
        default: 
            printf("no choice with this input\n");
            Sleep(2000);
            menu();
    }
}
void add_one_product(int style)
{
    int choice; //for menu
    if( products_amount == 0 )
    {
        P_product = (product*) malloc(sizeof(product)); //allocate memory for the first time
        if( P_product == NULL )
        {
            exit_program(2);
        }
    }
    else
    {
        P_product = (product*) realloc(P_product,  (products_amount + 1) * sizeof(product)); //reallocate the memory to insert new items
        if( P_product == NULL )
        {
            exit_program(2);
        }
    }
    if( style == 0 )
    {
        system("cls");
        printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
        printf("\n------------------------------------------------------------Ajouter un nouveau produit---------------------------------------------------\n");
        get_product_info();
        printf("\n\n");
        printf("1 - ajouter un autre produit.\n");
        printf("2 - revenir au menu.\n");
        printf("3 - quitter le programme.\n\n\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);
        if( choice == 1 )
        {
            add_one_product(0);
        }else if( choice == 2 ) 
        {
            menu();
        }else if( choice == 3 )
        {
            exit_program(0);
        }
    }
    else
    {
        get_product_info();
    }
}
void exit_program(int error)
{
    system("cls");
    printf("Au revoir...");
    free(B_product);
    free(P_product);
    Sleep(500);
    exit(error);
}
void add_products()
{
    system("cls");
    int number_of_products;
    int choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n---------------------------------------------------------Ajouter plusieurs nouveaux produits------------------------------------------------\n");
    printf("\n\n");
    printf("entrez le nombre de produits que vous souhaitez ajouter: ");
    scanf("%d", &number_of_products);
    if( number_of_products == 1 )
    {
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
    printf("1 - ajouter quelques autres produits.\n\n\n");
    printf("2 - Lister tous les produits (Nom, prix, prix TTC)\n\n\n");
    printf("3 - revenir au menu.\n\n\n");
    printf("4 - quitter le programme.\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        add_products();
    }
    else if( choice == 2 )
    {
        sort();
    }
    else if( choice == 3 )
    {
        menu();
    }else if( choice == 4 ) 
    {
        exit_program(0);
    }
}
void print()
{
    int choice;
    if( products_amount == 0 )
    {
        printf("\n\n\n\n\naucun produit disponible pour le moment.\n\n\n\n\n");
    }
    else
    {
        printf("CODE                NOME            QUANTITE              PRIX           PRIX(TTC)\n\n");
        for( int i = 0; i < products_amount; i++ )
        {
            float ttc = P_product[i].price + (P_product[i].price * 0.15 );
            printf("%s                 %s            %d           %.2f DH           %.2f DH\n",P_product[i].code, P_product[i].name,P_product[i].amount ,P_product[i].price, ttc );
        }
        printf("\n\n");
    }
    printf("1 - revenir au menu.\n\n\n");
    printf("2 - quitter le programme.\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }
    else if( choice == 2 )
    {
        exit_program(0);
    }
}
void sort()
{
    system("cls");
    int choice;
    printf("1 - lister tous les produits selon l'ordre alphabétique  croissant du nom.\n\n\n");
    printf("2 - lister tous les produits selon l'ordre  décroissant du prix.\n\n\n");
    printf("3 - revenir au menu.\n\n\n");
    printf("4 - quitter le programme.\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        bubble_sort_alphabitcly();
    }else if( choice == 2 )
    {
        selection_sort_by_price();   
    }else if( choice == 3 )
    {
        menu();
    }else if( choice == 4 )
    {
        exit_program(0);
    }
}
void selection_sort_by_price()
{
    system("cls");
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
    print();
}
void bubble_sort_alphabitcly()
{
    system("cls");
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
    print();
}
void buy_product()
{
    system("cls");
    char code[30];
    int amount, choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n-----------------------------------------------------------------Acheter produit---------------------------------------------------------\n");
    printf("\n\n\n");
    printf("entrez le code du produit que vous souhaitez acheter: ");
    scanf("%s", &code);
    if( is_avialable(code, 0) == 0 )
    {
        printf("\n\n\nce produit n'est pas disponible pour le moment.\n\n\n");
        Sleep(1000);
        system("cls");
        go_back();
    }
    else
    {
        printf("\nentrez la quantité que vous souhaitez: ");
        scanf("%d", &amount);
        if( is_avialable(code, amount) == -1)
        {
            printf("\n\n\nIl n'y a pas assez de quantité pour ce produit.\n\n\n");
            Sleep(3000);
            system("cls");
            go_back();
        }
        else if (is_avialable(code, amount) == 1)
        {
            if(sales == 0)
            {
                B_product = (Buyed_product*) malloc(sizeof(Buyed_product));
                if(B_product == NULL )
                {
                    printf("Mémoire insuffisante!\n");
                    exit_program(2);
                }
            }
            else if( sales > 0 )
            {
                B_product = (Buyed_product*) realloc(B_product, (sales+1)*sizeof(Buyed_product));
                if(B_product == NULL )
                {
                    printf("Mémoire insuffisante!\n");
                    exit_program(2);
                }
            }
            sale_product(code, amount);
        }

    }
    printf("\n\n\n");
    printf("1 - revenir au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 ) 
    {
        menu();
    }
    else if ( choice == 2 )
    {
        exit_program(0);
    }
}
void search_products()
{
    system("cls");
    int choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n---------------------------------------------------------------rechercher un produit---------------------------------------------------\n");
    printf("\n\n");
    printf("recherche par: \n\n");
    printf("\t\t1 - Code.\n");
    printf("\t\t2 - Quantite.\n");
    printf("\n\n\n");
    printf("3 - revenir au menu.\n");
    printf("4 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 ) 
    {
        search_by_code();
    }
    else if ( choice == 2 )
    {
        search_by_amount();
    }
    else if( choice == 3 )
    {
        menu();
    }
    else if( choice == 4 ) 
    {
        exit_program(0);
    }
}
void search_by_code()
{
    system("cls");
    char code[30];
    int style = 0, choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n---------------------------------------------------------------rechercher un produit---------------------------------------------------\n");
    printf("\n\n\n");
    printf("entrer le code du produit: ");
    scanf("%s", &code);
    for( int i = 0; i < products_amount; i++ )
    {
        if(strcasecmp(code, P_product[i].code) == 0)
        {
            printf("c'est le produit que vous recherchez:\n\n\n");
            printf("\t\t\tCode: %s        Name: %s      Quantité: %i       Prix: %.2f DH    Prix(TTC): %.2f \n\n", P_product[i].code, P_product[i].name, P_product[i].amount, P_product[i].price, P_product[i].price + P_product[i].price * 0.15 );
            style++;
        }
    }
    if( style ==  0 ) 
    {
        printf("\n\nce produit n'existe pas!");
    }
    printf("\n\n\n");
    printf("1 - revenir au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }
    else if( choice == 2 ) 
    {
        exit_program(0);
    }

}
void search_by_amount()
{
    system("cls");
    int style = 0, choice, amount;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n---------------------------------------------------------------rechercher un produit---------------------------------------------------\n");
    printf("\n\n\n");
    printf("entrez la quantité du produit que vous recherchez: ");
    scanf("%d", &amount);
    for( int i = 0; i < products_amount; i++ )
    {
        if(P_product[i].amount == amount )
        {
            printf("c'est les produits que vous recherchez:\n\n\n");
            printf("\t\t\tCode: %s        Name: %s      Quantité: %i       Prix: %.2f DH    Prix(TTC): %.2f \n\n", P_product[i].code, P_product[i].name, P_product[i].amount, P_product[i].price, P_product[i].price + P_product[i].price * 0.15 );
            style++;
        }
        else{
            Sleep(1000);
            printf("\t\t\tRecherche...");
        }
    }
    if(style == 0) 
    {
        printf("\n\nce produit n'existe pas!");
    }
    printf("\n\n\n");
    printf("1 - revenir au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }else if( choice == 2 ) 
    {
        exit_program(0);
    }
}
void stock_status()
{
    system("cls");
    int choice, style = 0;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n-----------------------------------------------------------------Etat du stock-----------------------------------------------------------\n");
    printf("\n\n\n");
    for( int i = 0; i < products_amount; i++ )
    {
        if(P_product[i].amount <= 3 )
        {
            printf("\t\t\tCode: %s        Name: %s      %i      %.2f DH\n\n", P_product[i].code, P_product[i].name, P_product[i].amount, P_product[i].price);
            style ++;
        }
    }
    if(style == 0) 
    {
        printf("\n\nil n'y a pas de produit inferieur à 3!\n\n\n\n\n\n");
    }
    printf("1 - revenir au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }else if( choice == 2 ) 
    {
        exit_program(0);
    }
}
void stock_supply()
{
    system("cls");
    char code[30];
    int amount, choice, style = 0;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n----------------------------------------------------------------Alimenter le stock--------------------------------------------------------\n");
    printf("\n\n\n");
    printf("Entrez le code du produit que vous souhaitez mettre à jour sa quantite: ");
    scanf("%s", code);
    printf("Entrez la quantite que vous souhaitez ajouter: ");
    scanf("%d", &amount);
    for( int i = 0; i < products_amount; i++ )
    {
        if(strcasecmp(code, P_product[i].code) == 0)
        {
            P_product[i].amount += amount;
            style ++;
        }
    }
    if(style == 0) 
    {
        printf("\n\nce produit n'existe pas!");
    }
    printf("\n\n\n");
    printf("1 - revenir au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }else if( choice == 2 ) 
    {
        exit_program(0);
    }
}
void delete_products()
{
    system("cls");
    char code[30];
    int choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n--------------------------------------------------------------Supprimer les produits-----------------------------------------------------\n");
    printf("\n\n\n");
    printf("Entrez le code du produit que vous souhaitez supprimer: ");
    scanf("%s", &code);
    if( is_avialable(code, 0) == 0)
    {
        printf("\n\nce produit n'existe pas\n\n\n");
    }
    else{
        for(int i = 0; i < products_amount; i++ )
        {
            if(strcasecmp(code, P_product[i].code) == 0 )
            {
                for(int j = i; j < products_amount - 1; j++ )
                {
                    P_product[j] = P_product[j + 1];
                }
                products_amount--;
                P_product = realloc(P_product, products_amount*sizeof(product));
            }
        }
    }
    printf("\n\n\n");
    printf("1 - revenir au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }
    else if( choice == 2 ) 
    {
        exit_program(0);
    }
}
void sales_statistics()
{
    system("cls");
    int choice;
    printf("\n_______________________________________________________________Gestion de Pharmacie_____________________________________________________\n");
    printf("\n---------------------------------------------------------------Statistique de vente-----------------------------------------------------\n");
    printf("\n\n\n");
    printf("1 - Afficher le total des prix des produits vendus en journee courante.\n\n");
    printf("2 - Afficher la moyenne des prix des produits vendus en journee courante.\n\n");
    printf("3 - Afficher le Max des prix des produits vendus en journee courante.\n\n");
    printf("4 - Afficher le Min des prix des produits vendus en journee courante.\n\n");
    printf("5 - retour au menu\n");
    printf("6 - fermer le programme");
    printf("\n\n\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            system("cls");
            totat_sale_price();
            break;
        case 2: 
            system("cls");
            average_sale_price();
            break;
        case 3:
            system("cls");
            max_sale_price();
            break;
        case 4:
            system("cls");
            min_sale_price();
            break;
        case 5:
            menu();
            break;
        case 6:
            exit_program(0);
            break;
    }
}
void totat_sale_price()
{
    float total = 0;
    if(sales == 0)
    {
        printf("\n\n\n\nla valeur totale des ventes aujourd'hui est: %.2f\n\n\n", total);
    }
    else
    {
        time_t now = time(NULL);
        struct tm* date = localtime(&now);
        int day = date->tm_mday;
        int month = date->tm_mon;
        int year = date->tm_year;
        for(int i = 0; i < sales; i++ )
        {
            if( B_product[i].date.year == year && B_product[i].date.month == month && B_product[i].date.day == day )
                total = total + B_product[i].info.price * B_product[i].info.amount;
        }
        printf("\n\n\n\nla valeur totale des ventes aujourd'hui est: %.2f\n\n\n", total);
    }
    go_back();
}
void average_sale_price()
{
    float average = 0;
    if(sales == 0)
    {
        printf("\n\n\nla valeur moyenne des ventes aujourd'hui est: %.2f DH\n\n\n", average);
    }else
    {
        time_t now = time(NULL);
        struct tm* date = localtime(&now);
        int day = date->tm_mday;
        int month = date->tm_mon;
        int year = date->tm_year;
        for(int i = 0; i < sales; i++ )
        {
            if( B_product[i].date.year == year && B_product[i].date.month == month && B_product[i].date.day == day )
                average += B_product[i].info.price;
        }
        average = average / sales;
        printf("\n\n\nla valeur moyenne des ventes aujourd'hui est: %.2f DH\n\n\n", average);
    }
    go_back();
}
void max_sale_price()
{
    float max = 0;
    if(sales == 0)
    {
        printf("\n\nle Max des prix des produits vendus aujourd'hui est: %.2f DH\n\n\n", max);
    }
    else
    {
        time_t now = time(NULL);
        struct tm* date = localtime(&now);
        int day = date->tm_mday;
        int month = date->tm_mon;
        int year = date->tm_year;
        for(int i = 0; i < sales; i++ )
        {
            if( B_product[i].date.year == year && B_product[i].date.month == month &&  B_product[i].date.day == day && B_product[i].info.price > max )
                max = B_product[i].info.price;
        }
        printf("\n\nle Max des prix des produits vendus aujourd'hui est: %.2f DH\n\n\n", max);
    }
    go_back();
}
void min_sale_price()
{
    float min = 0;
    if(sales == 0 )
    {
        printf("\n\nle Min des prix des produits vendus aujourd'hui est: %.2f DH\n\n\n", min);
    }
    else
    {
        time_t now = time(NULL);
        struct tm* date = localtime(&now);
        int day = date->tm_mday;
        int month = date->tm_mon;
        int year = date->tm_year ;
        for(int i = 0; i < sales; i++ )
        {
            if( B_product[i].date.year == year && B_product[i].date.month == month &&  B_product[i].date.day == day && B_product[i].info.price <= min )
                            min = B_product[i].info.price;
        }
        printf("\n\nle Min des prix des produits vendus aujourd'hui est: %.2f DH\n\n\n", min);
    }
    go_back();
}
int is_avialable(char* code, int amount)
{
    int answer = 0;
    for(int i = 0; i < products_amount; i++ )
    {
        if(strcasecmp(code, P_product[i].code) == 0 )
        {
            answer = 1;
            if(P_product[i].amount < amount)
            {
                answer = -1;
            }
        }
    }
    return answer;
}
void get_product_info()
{
    char code[30];
    printf("\n\n");
    printf("Entrez le code du produit: ");
    scanf("%s", &code);
    if( is_avialable(code, 0) == 1)
    {
        printf("\n\n\n\nce produit existe déjà\n\n\n");
        Sleep(2000);
        add_products();
    }
    else
    {
        strcpy(P_product[products_amount].code, code);
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
void sale_product(char* code, int amount)
{
    time_t now = time(NULL);
    struct tm* date = localtime(&now);
    for(int i = 0; i < products_amount; i++ )
    {
        if(strcasecmp(code, P_product[i].code) == 0 )
        {
            strcpy(B_product[sales].info.code, code);
            strcpy(B_product[sales].info.name, P_product[i].name);
            B_product[sales].info.amount = amount;
            B_product[sales].info.price = P_product[i].price + (P_product[i].price * 0.15);
            B_product[sales].date.day = date->tm_mday;
            B_product[sales].date.month = date->tm_mon;
            B_product[sales].date.year = date->tm_year; 
            P_product[i].amount -= amount;
            sales++;
        }
    }
}
void go_back()
{
    int choice;
    printf("1 - retour au menu.\n");
    printf("2 - quitter le programme.\n");
    printf("entrez votre choix: ");
    scanf("%d", &choice);
    if( choice == 1 )
    {
        menu();
    }
    else if ( choice == 2 ){
        exit_program(0);
    }
    
}
