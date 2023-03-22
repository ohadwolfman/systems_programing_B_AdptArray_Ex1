#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC prtFunc;
}AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC prtFunc){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->prtFunc = prtFunc;
    return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem){
    PElement* newpElemArr;
    if (pArr == NULL)
        return FAIL;

    if (idx >= pArr->ArrSize)
    {
        if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        //free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }
    // Delete Previous Elem
    if((pArr->pElemArr)[idx]) {
        pArr->delFunc((pArr->pElemArr)[idx]);
        (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
    }
    else{
        (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
    }
    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr) {
    int i;
    if (pArr == NULL)
        return;
    for (i = 0; i < pArr->ArrSize; ++i) {
        if((pArr->pElemArr)[i]!=NULL){
            pArr->delFunc((pArr->pElemArr)[i]);
        }
    }
    free(pArr->pElemArr);
    free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if (pArr == NULL || idx < 0 || idx >= (pArr->ArrSize) || pArr->pElemArr[idx]==NULL)
        return NULL;
    return pArr->copyFunc(pArr->pElemArr[idx]);
}

int GetAdptArraySize(PAdptArray pArr){
    if (pArr == NULL)
        return 0;
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr){
    if (pArr == NULL)
        return;
    for (int i = 0; i < pArr->ArrSize; i++) {
        if (pArr->pElemArr[i]) {
            pArr->prtFunc(pArr->pElemArr[i]);
        }
    }
}
