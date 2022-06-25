  //  "Copyright 2022 <Andres Matarrita>"
#include "nodo.hpp"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//  procedure nodo_init:
nodo_t* nodo_init(int64_t number , int sumas , char signo ,
 int64_t error , std::string numeroErroneo) {
    //   Iguala atributos a parametros;
    nodo_t* nodo = new nodo_t;
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

//  procedure nodo_destroy:
void nodo_destroy(nodo_t* nodo) {
    assert(nodo);

    //  Borra atributos
    nodo->number = 0;
    nodo->next = NULL;
    //  Libera nodo
    delete nodo;
}
//  end procedure

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
        printf("%c%" PRIu64 ":" ,  nodo->signo , nodo->number);
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

//  procedure nodo_getSigno:
char nodo_getSigno(nodo_t* nodo) {
    //  retorna atributo signo;
    return nodo->signo;
}
//  end procedure

//  procedure nodo_getNumber:
int64_t nodo_getNumber(nodo_t* nodo) {
    //  retorna atributo Numero;
    return nodo->number;
}
//  end procedure

//  procedure nodo_addDesglose:
void nodo_addDesglose(nodo_t* nodo , int64_t digito) {
    //  Agrega un numero int al vector desglose;
    nodo->desglose[nodo->posicion] = digito;
    //  Incrementa posicionVector;
    nodo->posicion++;
}
//  end procedure

//  procedure nodo_setSumas:
void nodo_setSumas(nodo_t* nodo , int sumas) {
    //  Iguala atributo sumas al parametro recibido;
    nodo->sumas = sumas;
}
//  end procedure

