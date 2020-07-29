#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct nodoAVL{  //Estructura del nodo estropajo.
    int area;
    int altura;
    char color[15];
    char textura[15];
    struct nodoAVL *hIzq;
    struct nodoAVL *hDer;
};
struct nodoAVL *constructorNodo(int area, char col[15], char tex[15]){  //Constructor de un nodo por parametros
    struct nodoAVL *nodo=(struct nodoAVL*)malloc(sizeof(struct nodoAVL));
    nodo->area=area;
    strcpy(nodo->color,col);
    strcpy(nodo->textura,tex);
    nodo->hIzq=NULL;
    nodo->hDer=NULL;
    nodo->altura=0;
    return nodo;
}
struct arbolAVL{  //Estructura del árbol
    struct nodoAVL *raiz;
};

//Declaración de funciones
void menu(); //Función menú
int getAltura(struct nodoAVL *nodo); //Función para obtener la altura de un nodo
void listarPreorden(struct nodoAVL *raiz); //Función para listar Preorden
void listarInorden(struct nodoAVL *raiz); //Función para listar Inorden
void listarPostorden(struct nodoAVL *raiz); //Función para listar Postorden
int max(int a, int b); //Función para retornar el máximo de dos datos (Usado para actualizar la altura)
void updateAltura(struct nodoAVL *raiz); //Actualiza la altura, obteniendo el mayor de ambos hijos +1
struct nodoAVL* rotacionSimple(struct nodoAVL *raiz, bool rotacionIzquierda); //Función de rotación simple
struct nodoAVL* rotacionDoble(struct nodoAVL *raiz, bool rotacionIzquierda); //Función de rotación doble
int getBalance(struct nodoAVL *raiz); //Función para obtener el balance, y saber que rotación realizar
struct nodoAVL* insertar(struct nodoAVL *raiz, int area, char color[15], char textura[15]); //Función de insertar
struct nodoAVL* balancearInsercion(struct nodoAVL *raiz,int area);  //Función para balancear después de insertar
struct nodoAVL* eliminar(struct nodoAVL *raiz, int area);  //Función para eliminar
struct nodoAVL* mayorNodo(struct nodoAVL *nodo);  //Función para obtener un nodo auxiliar con el nodo de mayor valor
struct nodoAVL* balancearEliminacion(struct nodoAVL *raiz, int area);  //Función para balancear después de eliminar
void modificar(struct nodoAVL *raiz,int area, char color[15], char textura[15]); //Función para modificar los datos de un estropajo
int buscar (struct nodoAVL *raiz, int area); //Función buscar para validar la eliminiación y modificar
//******** MAIN **********
int main() {
    struct arbolAVL *arbol=(struct arbolAVL*) malloc(sizeof(struct arbolAVL));
    arbol->raiz=NULL;
    int opcion=-1;
    printf("Hola, bienvenido al menu de arboles de estropajo.\n");
    printf("A continuacion, ingrese una opcion:\n");
    while (opcion!=0){
        menu();
        scanf("%d",&opcion);
        if (opcion>6 || opcion<0) printf("Ingrese una opcion valida.\n");
        if (opcion==1){
            int area=0;
            char color[15], textura[15];
            printf("A continuacion, ingrese los siguientes datos del estropajo: \n");
            printf("Area:\n");
            scanf("%d",&area);
            printf("Color: \n");
            scanf("%s",&color);
            printf("Material:\n");
            scanf("%s",&textura);
            arbol->raiz=insertar(arbol->raiz,area,color,textura);
        }
        if (opcion==2) {
            int opcionEliminar=-1;
            int areaEliminar=0;
            printf("Seleccione de que manera se va a listar el arbol:\n");
            printf("1.- Preorden\n");
            printf("2.- Inorden\n");
            printf("3.- Postorden\n");
            scanf("%d",&opcionEliminar);
            if (opcionEliminar==1) listarPreorden(arbol->raiz);
            if (opcionEliminar==2) listarInorden(arbol->raiz);
            if (opcionEliminar==3) listarPostorden(arbol->raiz);
            if (opcionEliminar>3 || opcionEliminar<1){
                printf("No ha seleccionado una opcion valida, por lo tanto\n");
                printf("se listara automaticamente de manera preorden:\n");
                listarPreorden(arbol->raiz);
            }
            printf("**********************************************\n");
            printf("Ahora ingrese el area del estropajo que desea eliminar:\n");
            scanf("%d",&areaEliminar);
            int verificarEliminacion=buscar(arbol->raiz,areaEliminar);
            if (verificarEliminacion==1){
                arbol->raiz=eliminar(arbol->raiz,areaEliminar);
                printf("ESTROPAJO ELIMINADO CON EXITO\n");
                printf("VOLVIENDO AL MENU...\n");
            }else printf("No se ha encontrado el nodo a eliminar.\n Volviendo al menu principal...\n");

        }
        if (opcion==3){
            int opcionModificar=-1;
            int areaModificar=0;
            int area=0;
            char color[15], textura[15];
            printf("Seleccione de que manera se va a listar el arbol:\n");
            printf("1.- Preorden\n");
            printf("2.- Inorden\n");
            printf("3.- Postorden\n");
            scanf("%d",&opcionModificar);
            if (opcionModificar==1) listarPreorden(arbol->raiz);
            if (opcionModificar==2) listarInorden(arbol->raiz);
            if (opcionModificar==3) listarPostorden(arbol->raiz);
            if (opcionModificar>3 || opcionModificar<1){
                printf("No ha seleccionado una opcion valida, por lo tanto\n");
                printf("se listara automaticamente de manera preorden:\n");
                listarPreorden(arbol->raiz);
            }
            printf("Ingrese el area del estropajo que desea modificar:\n");
            scanf("%d",&areaModificar);
            int verificacionModificar=buscar(arbol->raiz,areaModificar);
            if (verificacionModificar==1){
                printf("Ahora ingrese el nuevo color del estropajo:\n");
                scanf("%s",&color);
                printf("Y ahora la nueva textura:\n");
                scanf("%s",&textura);
                modificar(arbol->raiz,areaModificar,color,textura);
            }else printf("No se ha encontrado el nodo a modificar.\n Volviendo al menu principal...\n");

        }
        if (opcion==4) listarPreorden(arbol->raiz);
        if (opcion==5) listarInorden(arbol->raiz);
        if (opcion==6) listarPostorden(arbol->raiz);
    }
    printf("Haz salido con exito.\n");
    return 0;
}
void menu(){  //Función menú
    printf("*********************************************\n");
    printf("1.- Anadir un estropajo al arbol.\n");
    printf("2.- Eliminar un estropajo.\n");
    printf("3.- Modificar un estropajo.\n");
    printf("4.- Listar arbol de manera Preorden.\n");
    printf("5.- Listar arbol de manera Inorden. \n");
    printf("6.- Listar arbol de manera Postorden. \n");
    printf("0.- Salir.\n");
    printf("*********************************************\n");
}
int getAltura(struct nodoAVL *nodo){  //Función para obtener la altura de un nodo
    if (nodo==NULL) return -1;
    else return nodo->altura;
}

void listarPreorden(struct nodoAVL *raiz){  //Función para listar Preorden
    if (raiz!=NULL){
        printf("Area: %d, Color: %s, Material: %s, altura: %d\n",raiz->area,raiz->color,raiz->textura,raiz->altura);
        listarPreorden(raiz->hIzq);
        listarPreorden(raiz->hDer);
    }
}

void listarInorden(struct nodoAVL *raiz){  //Función para listar Inorden
    if (raiz!=NULL){
        listarInorden(raiz->hIzq);
        printf("Area: %d, Color: %s, Material: %s, altura: %d\n",raiz->area,raiz->color,raiz->textura,raiz->altura);
        listarInorden(raiz->hDer);
    }
}

void listarPostorden(struct nodoAVL *raiz){  //Función para listar Postorden
    if (raiz!=NULL){
        listarPostorden(raiz->hIzq);
        listarPostorden(raiz->hDer);
        printf("Area: %d, Color: %s, Material: %s, altura: %d\n",raiz->area,raiz->color,raiz->textura,raiz->altura);
    }
}
int max(int a, int b){  //Función para retornar el máximo de dos datos (Usado para actualizar la altura)
    if (a>=b) return a;
    else return b;
}

void updateAltura(struct nodoAVL *raiz){  //Actualiza la altura, obteniendo el mayor de ambos hijos +1
    if (raiz!=NULL) raiz->altura=max(getAltura(raiz->hIzq),getAltura(raiz->hDer))+1;
}

struct nodoAVL* rotacionSimple(struct nodoAVL *raiz, bool rotacionIzquierda){  //Función de rotación simple
    if (rotacionIzquierda){
        struct nodoAVL *aux=raiz;
        struct nodoAVL *auxhDer=raiz->hDer;
        aux->hDer=auxhDer->hIzq;
        auxhDer->hIzq=aux;
        aux=auxhDer;
        updateAltura(aux);
        updateAltura(auxhDer);
        return aux;
    }else{
        struct nodoAVL *aux=raiz;
        struct nodoAVL *auxhIzq=raiz->hIzq;
        aux->hIzq=auxhIzq->hDer;
        auxhIzq->hDer=aux;
        aux=auxhIzq;
        updateAltura(aux);
        updateAltura(auxhIzq);
        return aux;
    }
}
struct nodoAVL* rotacionDoble(struct nodoAVL *raiz, bool rotacionIzquierda){  //Función de rotación doble
    if (rotacionIzquierda){
        raiz->hDer=rotacionSimple(raiz->hDer,false);
        return rotacionSimple(raiz,true);
    }else{
        raiz->hIzq=rotacionSimple(raiz->hIzq,true);
        return rotacionSimple(raiz,false);
    }
}

int getBalance(struct nodoAVL *raiz){  //Función para obtener el balance, y saber que rotación realizar
    if (raiz==NULL) return 0;
    else return getAltura(raiz->hIzq)-getAltura(raiz->hDer);
}

struct nodoAVL* insertar(struct nodoAVL *raiz, int area, char color[15], char textura[15]){  //Función de insertar
    if (raiz==NULL) return constructorNodo(area,color,textura);
    else{
        if (area<raiz->area) raiz->hIzq=insertar(raiz->hIzq,area,color,textura);
        else raiz->hDer=insertar(raiz->hDer,area,color,textura);
    }
    updateAltura(raiz);
    raiz=balancearInsercion(raiz,area);
    return raiz;
}
struct nodoAVL* balancearInsercion(struct nodoAVL *raiz,int area){  //Función para balancear después de insertar
    int balance=getBalance(raiz);
    if (balance>1 && area<raiz->hIzq->area) return rotacionSimple(raiz,false);
    if (balance<-1 && area>raiz->hDer->area) return rotacionSimple(raiz,true);
    if (balance>1 && area>raiz->hIzq->area)  return rotacionDoble(raiz,false);
    if (balance<-1 && area<raiz->hDer->area) return rotacionDoble(raiz, true);
    return raiz;
}
struct nodoAVL* eliminar(struct nodoAVL *raiz, int area){
    if (raiz==NULL) return raiz;
    else{
        if (area<raiz->area) raiz->hIzq=eliminar(raiz->hIzq,area);
        else if (area>raiz->area) raiz->hDer=eliminar(raiz->hDer,area);
        else{
            struct nodoAVL *aux;
            if (raiz->hIzq==NULL && raiz->hDer==NULL) raiz=0;
            else if(raiz->hIzq==NULL){
                aux=raiz;
                raiz=aux->hDer;
                aux=0;
            }else if(raiz->hDer==NULL){
                aux=raiz;
                raiz=aux->hIzq;
                aux=0;
            }
            else{
                struct nodoAVL *aux=mayorNodo(raiz->hDer);
                raiz->area=aux->area;
                strcpy(raiz->color,aux->color);
                strcpy(raiz->textura,aux->textura);
                raiz->hDer=eliminar(raiz->hDer,raiz->area);
            }

        }
    }
    updateAltura(raiz);
    balancearEliminacion(raiz,area);
    return raiz;
}
struct nodoAVL* mayorNodo(struct nodoAVL *nodo){ //Función para obtener un nodo auxiliar con el nodo de mayor valor
    struct nodoAVL *aux=nodo;
    while (aux->hIzq!=NULL) aux=aux->hIzq;
    return aux;
}

struct nodoAVL* balancearEliminacion(struct nodoAVL *raiz, int area) {  //Función para balancear después de eliminar
    int balance = getBalance(raiz);
    if (balance > 1 && getBalance(raiz->hIzq) >= 0) return rotacionSimple(raiz, false);
    if (balance > 1 && getBalance(raiz->hIzq) < 0) return rotacionDoble(raiz, false);
    if (balance < -1 && getBalance(raiz->hDer) <= 0) return rotacionSimple(raiz, true);
    if (balance < -1 && getBalance(raiz->hIzq) > 0) return rotacionDoble(raiz, true);
    return raiz;
}

void modificar(struct nodoAVL *raiz,int area, char color[15], char textura[15]){  //Función para modificar los datos de un estropajo
    struct nodoAVL *aux;
    if (raiz!=NULL) {
        if (raiz->area==area) {
            aux=raiz;
            strcpy(aux->color,color);
            strcpy(aux->textura,textura);
            raiz=aux;
        }
        else{
            if (area>raiz->area) modificar(raiz->hDer,area,color,textura);
            else modificar(raiz->hIzq,area,color,textura);
        }
    }
}

int buscar (struct nodoAVL *raiz, int area){ //Función buscar para validar la eliminiación y modificar
    if (raiz==NULL) return 0;
    else{
        if (area==raiz->area) return 1;
        else{
            if (area>raiz->area && raiz->hDer!=NULL) return buscar(raiz->hDer,area);
            else if (area<raiz->area && raiz->hIzq!=NULL) return buscar (raiz->hIzq,area);
        }
    }
    return 0;
}