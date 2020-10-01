#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
typedef double TData;
int i, check;
void gotoxy(int x, int y)
{
    //Función para posicionar el cursor.
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
TData temporal, resultado;
char datos[20] = "0";
char operador;
struct nodo
{
    TData digito;
    struct nodo *siguiente;
} * AnteriorP;
struct nodo *Actual;
void CrearPila(struct nodo **AnteriorP)
{
    AnteriorP = NULL;
}
int PilaVacia(struct nodo *AnteriorP)
{
    if (!AnteriorP)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int PilaLlena(struct nodo *AnteriorP)
{
    return 0;
}
void IngresarDigito(struct nodo **AnteriorP, TData x)
{
    if (!PilaLlena(*AnteriorP))
    {
        Actual = (struct nodo *)malloc(sizeof(struct nodo));
        Actual->digito = x;
        Actual->siguiente = *AnteriorP;
        *AnteriorP = Actual;
    }
}
void MostrarPila(struct nodo **AnteriorP)
{
    Actual = (struct nodo *)malloc(sizeof(struct nodo));
    Actual = *AnteriorP;
    if (!PilaVacia(*AnteriorP))
    {
        while (Actual != NULL)
        {
            printf("\n%.3f", Actual->digito);
            Actual = Actual->siguiente;
        }
    }
}
void LimpiarCalculadora(struct nodo **AnteriorP)
{ //Elimina los 2 digitos anteriores luego de ser evaluados.
    if (!PilaVacia(*AnteriorP))
    {
        for (i = 0; i < 2; i++)
        {
            Actual = *AnteriorP;
            *AnteriorP = Actual->siguiente;
            free(Actual);
        }
    }
}
void ClearTotal(struct nodo **AnteriorP)
{ //Limpia toda la pila.
    if (!PilaVacia(*AnteriorP))
    {
        while (!PilaVacia(*AnteriorP))
        {
            Actual = *AnteriorP;
            *AnteriorP = Actual->siguiente;
            free(Actual);
        }
    }
}
int CheckArgumentos(struct nodo **AnteriorP)
{
    if ((PilaVacia(*AnteriorP)) || (Actual->siguiente == NULL))
    { //Minimo se necesitan 2 valores.
        gotoxy(30, 10);
        printf("Few Arguments!");
        gotoxy(30, 11);
        printf("Remember the Reverse Polish Notation. Ex: (2 -> 4 -> +)");
        system("pause > NULL");
        system("cls");
        return 1;
    }
    return 0;
}
int CheckArgumentosSingle(struct nodo **AnteriorP){
    if (PilaVacia(*AnteriorP))
    {
        gotoxy(30, 10);
        printf("Few Arguments!");
        system("pause > NULL");
        system("cls");
        return 1;
    }
    return 0;
}
int Factorial(TData digito){
    if (digito != 1)
    {
        return digito * Factorial(digito - 1);
    }
    return digito;
}
//Operaciones de la calculadora
void Evaluacion(struct nodo **AnteriorP, char op)
{
    Actual = *AnteriorP;
    switch (op) //Switch que contiene todas las operaciones.
    {
    case '+':
        if (CheckArgumentos(AnteriorP))
        {
            return;
        }
        resultado = Actual->siguiente->digito + Actual->digito;
        break;
    case '-':
        if (CheckArgumentos(AnteriorP))
        {
            return;
        }
        resultado = Actual->siguiente->digito - Actual->digito;
        break;
    case '*':
        if (CheckArgumentos(AnteriorP))
        {
            return;
        }
        resultado = Actual->siguiente->digito * Actual->digito;
        break;
    case '/':
        if (CheckArgumentos(AnteriorP))
        {
            return;
        }
        resultado = Actual->siguiente->digito / Actual->digito;
        break;
    case '^':
        if (CheckArgumentos(AnteriorP))
        {
            return;
        }
        resultado = pow(Actual->siguiente->digito, Actual->digito);
        break;
    case 'c':
        ClearTotal(AnteriorP);
        system("cls");
        return;
    case 'n':
        if (CheckArgumentosSingle(AnteriorP))
        {
            return;
        }
        resultado = Actual->digito * (-1);
        *AnteriorP = Actual->siguiente;
        free(Actual);
        IngresarDigito(AnteriorP, resultado);
        system("cls");
        return;
    case '!':
        if (CheckArgumentosSingle(AnteriorP))
        {
            return;
        }
        resultado = Factorial(Actual->digito);
        *AnteriorP = Actual->siguiente;
        free(Actual);
        IngresarDigito(AnteriorP, resultado);
        system("cls");
        return;
    case 'i':
        if (CheckArgumentosSingle(AnteriorP))
        {
            return;
        }
        resultado = 1 / Actual->digito;
        *AnteriorP = Actual->siguiente;
        free(Actual);
        IngresarDigito(AnteriorP, resultado);
        system("cls");
        return;
    case '%':
        if (CheckArgumentosSingle(AnteriorP))
        {
            return;
        }
        resultado = Actual->digito / 100;
        *AnteriorP = Actual->siguiente;
        free(Actual);
        IngresarDigito(AnteriorP, resultado);
        system("cls");
        return;
    default:
        gotoxy(30, 10);
        printf("Wrong Operator");
        system("pause > NULL");
        system("cls");
        return;
    }
    if (!PilaVacia(*AnteriorP))
    {
        LimpiarCalculadora(AnteriorP);
        IngresarDigito(AnteriorP, resultado); //Guardar el resultado de nuevo en la pila.
    }
    system("cls");
}
void Leyenda()
{
    gotoxy(30, 0);
    printf("'c' = Clear all the stack");
    gotoxy(30, 1);
    printf("'n' = Turn last number into its oppossite ( n * -1 )");
    gotoxy(30, 2);
    printf("'e' = Exit");
    gotoxy(30, 3);
    printf("'i' = 1/(lastNumber)");
    gotoxy(30, 4);
    printf("'%c' = (lastNumber)/100", 37);
    gotoxy(30, 8);
    printf("Gerardo Torres @gistypical");
}
int main(int argc, char const *argv[])
{
    CrearPila(&AnteriorP);
    gotoxy(30, 5);
    printf("How to: Write a digit an then hit 'enter' for pushing into the stack\n");
    do
    {
        check = 1;
        while (check) //  Mientras sea digito, seguir ingresando.
        {
            Leyenda();
            gotoxy(0, 0);
            scanf("%s", &datos);
            check = isdigit(datos[0]);
            if (check == 0)
            {
                operador = datos[0]; //Se consigue un operador y se sale del while.
                break;
            }
            // temporal = atof(datos); // Si se detecta que es un digito, se pasa a float.
            IngresarDigito(&AnteriorP, atof(datos));
            system("cls");
            MostrarPila(&AnteriorP);
        }
        if (operador == 'e')
        {
            break;
        }
        Evaluacion(&AnteriorP, operador);
        MostrarPila(&AnteriorP);
    } while (PilaVacia);
}
