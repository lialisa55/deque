#include <stdbool.h>
#include <stdlib.h>
#include "Deque.h"

typedef struct deque_{
    ITEM *deque[MAX_TAMANHO];
    int inicio;
    int fim;
    int tamanho;
} DEQUE;

DEQUE* deque_criar(){
    DEQUE *deque = (DEQUE*) malloc(sizeof(DEQUE));
    if(deque){
        deque->inicio = 0;
        deque->fim = 0;
        deque->tamanho = 0;
    }
    return (deque);
};
void deque_apagar(DEQUE** deque){
    if (deque && *deque){
        while (!deque_vazia(*deque)){
            ITEM *item = deque_remover_inicio(*deque);
            free(item); 
        }
        free(*deque);
        *deque = NULL;
    }
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    if(deque && !deque_cheia(deque)){
        deque->inicio = (deque->inicio - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        deque->deque[deque->inicio] = item;
        deque->tamanho++;
        return true;
    }
    return false;
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    if(deque && !deque_cheia(deque)){
        deque->deque[deque->fim] = item;  
        deque->fim = (deque->fim+1) % MAX_TAMANHO;
        deque->tamanho++;
        return true;
    }
    return false;

};

ITEM* deque_remover_inicio(DEQUE* deque){
    if(deque && !deque_vazia(deque)){
        ITEM *item = deque->deque[deque->inicio];
        deque->deque[deque->inicio] = NULL;
        deque->inicio = (deque->inicio+1) % MAX_TAMANHO;
        deque->tamanho--;
        return item;
    }
    return NULL;
};

ITEM* deque_remover_fim(DEQUE* deque){
    if(deque && !deque_vazia(deque)){
        int indice_fim = (deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        ITEM *item = deque->deque[indice_fim];
        deque->deque[indice_fim] = NULL;
        deque->fim = indice_fim;
        deque->tamanho--;
        return item;
    }
    return NULL;
};

ITEM* deque_primeiro(DEQUE* deque){
    if(deque && !deque_vazia(deque)){
        return deque->deque[deque->inicio];
    }
    return NULL;
}

ITEM* deque_ultimo(DEQUE* deque){
    if(deque && !deque_vazia(deque)){
        int ultimo_indice = (deque->fim - 1 + MAX_TAMANHO) % MAX_TAMANHO;
        return deque->deque[ultimo_indice];
    }
    return NULL;
}

int deque_contar(DEQUE* deque){
    if(deque){
        return deque->tamanho;
    }
}

bool deque_vazia(DEQUE* deque){
    return deque && deque->tamanho == 0;
}

bool deque_cheia(DEQUE* deque){
    return deque && deque->tamanho == MAX_TAMANHO;
}