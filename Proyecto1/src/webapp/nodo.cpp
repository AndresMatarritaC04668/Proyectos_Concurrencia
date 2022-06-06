  //  "Copyright 2022 <Andres Matarrita>"
#include "nodo.hpp"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>



/**
 @brief Inicializa los valores del nodo al darle los valores de los parametros
 @param number Numero a demostrar con goldbach
 @param sumas Cantidad de sumas posibles encontradas
 @param signo Char que identifica si un numero es negativo ('-')
 @return Retorna un puntero a un nodo 
*/
//  procedure nodo_init:
nodo_t* nodo_init(int64_t number , int sumas , char signo , int64_t error , std::string numeroErroneo){
    //   Iguala atributos a parametros;
    nodo_t* nodo = (nodo_t*) malloc(1*sizeof(nodo_t));
    nodo->number = number;
    nodo->sumas = sumas;
    nodo->signo = signo;
    nodo->error = error;
    nodo->numeroErroneo = numeroErroneo;
    //  Inicializa atributos
    nodo->posicion = 0;
    nodo->desglose[0] = 0;
    nodo->next = NULL;

    return nodo;
}

/**
 @brief Libera a el nodo y sus valores
 @param nodo Nodo que se va a liberar
*/
//  procedure nodo_destroy:
void nodo_destroy(nodo_t* nodo) {
    assert(nodo);

    //  Borra atributos
    nodo->number = 0;
    nodo->next = NULL;
    //  Libera nodo
    free(nodo);
}
//  end procedure


/**
 @brief Imprime los datos del nodo y si es negativo imprime
        el desglose de sumas del numero
 @param nodo Nodo que contiene los datos que se van a imprimir 
 */
//  procedure nodo_print:
void nodo_print(nodo_t* nodo) {
    assert(nodo);

    int64_t comparacion = 5;

    if ( nodo_getNumber(nodo)<= comparacion ) {
        //  Imprime "NA" si es menor que 5;
        printf("%c" , nodo_getSigno(nodo));
        printf("%" PRIu64": NA" , nodo_getNumber(nodo) );

    } else {
         //  Imprime Informacion;
        printf("%C%" PRIu64 ":" ,  nodo->signo , nodo->number);
        printf(" %i Sumas" ,  nodo->sumas);

        if (nodo->signo == '-') {
            //  Imprime desglose si es negativo;
            printf(": ");
            if (nodo-> number%2 == 0) {
                for (int i = 0; i< nodo->posicion ; i++) {
                    printf(" %" PRIu64  , nodo->desglose[i]);
                    ++i;
                    printf(" %c" ,  '+');
                    printf(" %" PRIu64  , nodo->desglose[i]);

                if (i < nodo-> posicion-1) {
                        printf(" %c" ,  ',');
                    }
                }
            } else {
                for (int i = 0; i < nodo-> posicion ; i++) {
                  printf(" %" PRIu64  , nodo->desglose[i]);
                  ++i;
                  printf(" %c" ,  '+');
                  printf(" %" PRIu64  , nodo->desglose[i]);
                  ++i;
                  printf(" %c" ,  '+');
                  printf(" %" PRIu64  , nodo->desglose[i]);
                  if (i < nodo-> posicion-1) {
                        printf(" %c" ,  ',');
                    }
                }
            }
        }
    }
    printf("\n");
}
//  end procedure


/**
 @brief Devuelve el char signo de un numero
 @param nodo Contiene el char a devolver

 @return Retorna un char:
 '-' Si el numero es negativo
 ' ' Si el numero es positivo
*/
//  procedure nodo_getSigno:
char nodo_getSigno(nodo_t* nodo) {
    //  retorna atributo signo;
    return nodo->signo;
}
//  end procedure


/**
 @brief Devuelve el numero int64_t de un nodo 
 @param nodo Contiene el numero a devolver

 @return Retorna el valor del atributo number
 */
//  procedure nodo_getNumber:
int64_t nodo_getNumber(nodo_t* nodo) {
    //  retorna atributo Numero;
    return nodo->number;
}
//  end procedure


/**
 @brief Agrega al vector deslose un numero que forma parte de las posibles sumas
 *      del teorema de golbach
 @param nodo Nodo al que se le cambiaran los valores
 @param digito Numero que se almacenara en el vector desglose
 @return Retorna un char:
 */
//  procedure nodo_addDesglose:
void nodo_addDesglose(nodo_t* nodo , int64_t digito) {
    //  Agrega un numero int al vector desglose;
    nodo->desglose[nodo->posicion] = digito;
    //  Incrementa posicionVector;
    nodo->posicion++;
}
//  end procedure


/**
 @brief Cambia el valor del atributo "sumas" de un nodo
 @param nodo Nodo al que se aplicara el cambio
 @param sumas int que contiene el nuevo valor de sumas
*/
//  procedure nodo_setSumas:
void nodo_setSumas(nodo_t* nodo , int sumas) {
    //  Iguala atributo sumas al parametro recibido;
    nodo->sumas = sumas;
}
//  end procedure

