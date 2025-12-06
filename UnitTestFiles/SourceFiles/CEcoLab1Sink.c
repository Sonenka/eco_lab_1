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

#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"

int16_t long_pause = 400;
int16_t pause = 200;

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
int16_t ECOCALLMETHOD CEcoLab1Sink_QueryInterface(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
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
uint32_t ECOCALLMETHOD CEcoLab1Sink_AddRef(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

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
uint32_t ECOCALLMETHOD CEcoLab1Sink_Release(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1Sink((IEcoLab1Events*)pCMe);
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

void CEcoLab1Sink_printIntPolynom(const void* array, size_t size) {
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

void CEcoLab1Sink_printIntPolynomStep(const void* x, const void* h, const void* y, int i, int j) {
    int* xi = (int*)x;
    int* yi = (int*)y;
    int* hi = (int*)h;

    printf("\tx[%d] = %dx^%d ", i, xi[i], i);
    printf("\th[%d] = %dx^%d ", j, hi[j], j);
    printf("\ty[%d] = %dx^%d ", i + j, yi[i + j], i + j);
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnConvCall(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) {
        return -1;
    }
    printf("The convolution of polymoms is starting!\n");
    Sleep(long_pause);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnConvElemCall(/* in */ struct IEcoLab1Events* me, const void* x, const void* h, const void* y, int i, int j) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) {
        return -1;
    }

    printf("Step %d.%d: \n", i, j);
    CEcoLab1Sink_printIntPolynomStep(x, h, y, i, j);
    printf("\n");
    Sleep(long_pause);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnConvStepResultCall(/* in */ struct IEcoLab1Events* me, const void* y, size_t size, int step)  {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) {
        return -1;
    }

    printf("Convolution step %d result: \n", step);
    CEcoLab1Sink_printIntPolynom(y, size);
    printf("\n");
    Sleep(long_pause);
    return 0;
}


int16_t ECOCALLMETHOD CEcoLab1Sink_BeforeConv(/* in */ struct IEcoLab1Events* me, /* in */ const void* x, size_t n, const void* h, size_t m, const void* y) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) {
        return -1;
    }
    printf(" Polynom x: ");
    CEcoLab1Sink_printIntPolynom(x, n);
    printf(" Polynom h: ");
    CEcoLab1Sink_printIntPolynom(h, m);
    printf(" Polynom y: ");
    CEcoLab1Sink_printIntPolynom(y, n + m - 1);
    printf("\n");
    Sleep(long_pause);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_AfterConv(/* in */ struct IEcoLab1Events* me, /* in */ const void* y, size_t size) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) {
        return -1;
    }
    printf("Final polynom:\n");
    CEcoLab1Sink_printIntPolynom(y, size);
    printf("\n");
    Sleep(pause);
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
int16_t ECOCALLMETHOD CEcoLab1Sink_Advise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1) {
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
int16_t ECOCALLMETHOD CEcoLab1Sink_Unadvise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1) {
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
IEcoLab1VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents = {
    CEcoLab1Sink_QueryInterface,
    CEcoLab1Sink_AddRef,
    CEcoLab1Sink_Release,
    CEcoLab1Sink_OnConvCall,
    CEcoLab1Sink_OnConvElemCall,
    CEcoLab1Sink_OnConvStepResultCall,
    CEcoLab1Sink_BeforeConv,
    CEcoLab1Sink_AfterConv
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
int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1Events** ppIEcoLab1Events) {
    int16_t result = -1;
    CEcoLab1Sink* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab1Events == 0 || pIMem == 0 ) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1Sink*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab1Events = &g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents;

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
void ECOCALLMETHOD deleteCEcoLab1Sink(IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
