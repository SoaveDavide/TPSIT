#include <stdio.h>
/// @brief //breve descrizione della funzione
/// @param a //primo parametro/numero
/// @param b //second number
/// @return the sum of the two numerbs
int add(int a, int b)
{
    return a+b;
}
/// @brief compute of two numbers
/// @param a primo paramentro
/// @param b secondo parametro
/// @return the difference of the function
int mul(int a, int b)
{
    return a*b;
}
/// @brief compute of two numbers
/// @param a primo parametro
/// @param b secondo paramentro
/// @return the moltiplication of the function
int sub (int a, int b)
{
    return a-b;
}
/// @brief compute of two numbers
/// @param a primo parametro
/// @param b secondo paramentro
/// @return the division of the function
double division(int a, int b)
{
    return a/b;
}
/// @brief il mio main è senza parametri (main function)
void main(){
    printf("%d\n",add(6,3));
    printf("%d\n",mul(6,3));
    printf("%d\n",sub(6,3));
    printf("%f\n",division(6,3));
}