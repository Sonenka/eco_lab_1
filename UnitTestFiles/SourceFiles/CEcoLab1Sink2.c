/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab1Sink2.h"
#include "IEcoConnectionPointContainer.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink2_QueryInterface(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoLab1Events ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink2_AddRef(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;

    if (me == 0 ) {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink2_Release(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1Sink2((IEcoLab1Events*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция OnMyCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова
 * </описание>
 *
 */

void CEcoLab1Sink2_printIntPolynom(const void* array, size_t size) {
    int* arr = (int*)array;
    size_t i;
    for (i = 0; i < size; ++i) {
        if (i == 0) {
            printf("%dx^%d ", arr[i], i);
            continue;
        }

        if (arr[i] >= 0) {
            printf("+ %dx^%d ", arr[i], i);
        }
        else {
            printf("- %dx^%d ", abs(arr[i]), i);
        }
    }
    printf("\n");
}

void CEcoLab1Sink2_printIntPolynomStep(const void* x, const void* h, const void* y, int i, int j) {
    int* xi = (int*)x;
    int* yi = (int*)y;
    int* hi = (int*)h;

    printf("  x[%d]: %d * h[%d]: %d -> y[%d]: %d", 
           i, xi[i], j, hi[j], i + j, yi[i + j]);
}

int16_t ECOCALLMETHOD CEcoLab1Sink2_OnConvCall(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;
    if (me == 0) {
        return -1;
    }
    printf(">>> CONVOLUTION PROCESS INITIATED <<<\n");
    Sleep(400);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink2_OnConvElemCall(/* in */ struct IEcoLab1Events* me, const void* x, const void* h, const void* y, int i, int j) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;
    if (me == 0) {
        return -1;
    }

    printf("-- Step %d.%d\n", i, j);
    printf("- ");
    CEcoLab1Sink2_printIntPolynomStep(x, h, y, i, j);
    printf("\n-----------------\n");
    Sleep(400);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink2_OnConvStepResultCall(/* in */ struct IEcoLab1Events* me, const void* y, size_t size, int step)  {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;
    if (me == 0) {
        return -1;
    }

    printf("- STEP %d RESULT: ", step);
    CEcoLab1Sink2_printIntPolynom(y, size);
    Sleep(400);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink2_BeforeConv(/* in */ struct IEcoLab1Events* me, /* in */ const void* x, size_t n, const void* h, size_t m, const void* y) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;
    if (me == 0) {
        return -1;
    }
    printf("--------- INPUT POLYNOMIALS -----------\n");
    printf("X: ");
    CEcoLab1Sink2_printIntPolynom(x, n);
    printf("H: ");
    CEcoLab1Sink2_printIntPolynom(h, m);
    printf("Y (initial): ");
    CEcoLab1Sink2_printIntPolynom(y, n + m - 1);
    printf("----------------------------------------\n");
    Sleep(400);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink2_AfterConv(/* in */ struct IEcoLab1Events* me, /* in */ const void* y, size_t size) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)me;
    if (me == 0) {
        return -1;
    }
    printf("\n------- FINAL RESULT----------\n");
    printf("CONVOLUTION RESULT: ");
    CEcoLab1Sink2_printIntPolynom(y, size);
    printf("---------------------------\n");
    Sleep(200);
    return 0;
}


/*
 *
 * <сводка>
 *   Функция Advise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink2_Advise(/* in */ struct CEcoLab1Sink2* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);

    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*)me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink2_Unadvise(/* in */ struct CEcoLab1Sink2* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint * pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie) {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);
        if (result == 0) {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0) {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

/* Create Virtual Table IEcoLab1VTblEvents */
IEcoLab1VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C877VTblEvents = {
    CEcoLab1Sink2_QueryInterface,
    CEcoLab1Sink2_AddRef,
    CEcoLab1Sink2_Release,
    CEcoLab1Sink2_OnConvCall,
    CEcoLab1Sink2_OnConvElemCall,
    CEcoLab1Sink2_OnConvStepResultCall,
    CEcoLab1Sink2_BeforeConv,
    CEcoLab1Sink2_AfterConv
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1Sink2(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1Events** ppIEcoLab1Events) {
    int16_t result = -1;
    CEcoLab1Sink2* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab1Events == 0 || pIMem == 0 ) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1Sink2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink2));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab1Events = &g_x2D2E3B9214F248A6A09ECB494B59C877VTblEvents;

    *ppIEcoLab1Events = (IEcoLab1Events*)pCMe;

    return 0;
};

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1Sink2(IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink2* pCMe = (CEcoLab1Sink2*)pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
