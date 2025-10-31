/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_X_QueryInterface(/* in */ IEcoCalculatorXPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));
    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }
    

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_Y_QueryInterface(/* in */ IEcoCalculatorYPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)2 * sizeof(IEcoUnknownPtr_t));
    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_X_AddRef(/* in */ IEcoCalculatorXPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_Y_AddRef(/* in */ IEcoCalculatorYPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)2 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_X_Release(/* in */ IEcoCalculatorXPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_Y_Release(/* in */ IEcoCalculatorYPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)2 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Conv
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_ConvI(IEcoLab1Ptr_t me, int* x, uint32_t n, int* h, uint32_t m, int* y) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i, j;

    if (me == 0 || x == 0 || h == 0 || y == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    for (i = 0; i < n + m - 1; ++i) {
        y[i] = 0;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            y[i + j] += x[i] * h[j];
        }
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvL(IEcoLab1Ptr_t me, long* x, uint32_t n, long* h, uint32_t m, long* y) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i, j;

    if (me == 0 || x == 0 || h == 0 || y == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    for (i = 0; i < n + m - 1; ++i) {
        y[i] = 0;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            y[i + j] += x[i] * h[j];
        }
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvF(IEcoLab1Ptr_t me, float* x, uint32_t n, float* h, uint32_t m, float* y) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i, j;

    if (me == 0 || x == 0 || h == 0 || y == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    for (i = 0; i < n + m - 1; ++i) {
        y[i] = 0.0f;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            y[i + j] += x[i] * h[j];
        }
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvD(IEcoLab1Ptr_t me, double* x, uint32_t n, double* h, uint32_t m, double* y) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i, j;

    if (me == 0 || x == 0 || h == 0 || y == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    for (i = 0; i < n + m - 1; ++i) {
        y[i] = 0.0;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            y[i + j] += x[i] * h[j];
        }
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvLD(IEcoLab1Ptr_t me, long double* x, uint32_t n, long double* h, uint32_t m, long double* y) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t i, j;

    if (me == 0 || x == 0 || h == 0 || y == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    for (i = 0; i < n + m - 1; ++i) {
        y[i] = 0.0L;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            y[i + j] += x[i] * h[j];
        }
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvIshape(IEcoLab1Ptr_t me, int* x, uint32_t n, int* h, uint32_t m, const char* shape, int* y, uint32_t y_len) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoMemoryAllocator1* pIMem = pCMe->m_pIMem;
    uint32_t i, j, full_len, start;
    int *temp;

    if (me == 0 || x == 0 || h == 0 || y == 0 || y_len == 0 || shape == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

	full_len = n + m - 1;
	temp = (int*)pIMem->pVTbl->Alloc(pIMem, (full_len) * sizeof(int));

    for (i = 0; i < full_len; ++i) {
        temp[i] = 0;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            temp[i + j] += x[i] * h[j];
        }
    }

    if (strcmp(shape, "full") == 0) {
        y_len = full_len;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[i];
        }
    }
    else if (strcmp(shape, "same") == 0) {
        y_len = n;
        start = (full_len - n) / 2;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[start + i];
        }
    }
    else if (strcmp(shape, "valid") == 0) {
        if (n >= m) {
            y_len = n - m + 1;
        } else {
            y_len = 0;
        }
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[m - 1 + i];
        }
    }
    else {
        pIMem->pVTbl->Free(pIMem, temp);
        return ERR_ECO_POINTER; 
    }

    pIMem->pVTbl->Free(pIMem, temp);

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvLshape(IEcoLab1Ptr_t me, long* x, uint32_t n, long* h, uint32_t m, const char* shape, long* y, uint32_t y_len) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoMemoryAllocator1* pIMem = pCMe->m_pIMem;
    uint32_t i, j, full_len, start;
    long *temp;

    if (me == 0 || x == 0 || h == 0 || y == 0 || y_len == 0 || shape == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    full_len = n + m - 1;
	temp = (long*)pIMem->pVTbl->Alloc(pIMem, (full_len) * sizeof(long));

    for (i = 0; i < full_len; ++i) {
        temp[i] = 0;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            temp[i + j] += x[i] * h[j];
        }
    }

    if (strcmp(shape, "full") == 0) {
        y_len = full_len;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[i];
        }
    }
    else if (strcmp(shape, "same") == 0) {
        y_len = n;
        start = (full_len - n) / 2;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[start + i];
        }
    }
    else if (strcmp(shape, "valid") == 0) {
        if (n >= m) {
            y_len = n - m + 1;
        } else {
            y_len = 0;
        }
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[m - 1 + i];
        }
    }
    else {
        pIMem->pVTbl->Free(pIMem, temp);
        return ERR_ECO_POINTER; 
    }

    pIMem->pVTbl->Free(pIMem, temp);

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvFshape(IEcoLab1Ptr_t me, float* x, uint32_t n, float* h, uint32_t m, const char* shape, float* y, uint32_t y_len) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoMemoryAllocator1* pIMem = pCMe->m_pIMem;
    uint32_t i, j, full_len, start;
    float *temp;

    if (me == 0 || x == 0 || h == 0 || y == 0 || y_len == 0 || shape == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    full_len = n + m - 1;
	temp = (float*)pIMem->pVTbl->Alloc(pIMem, (full_len) * sizeof(float));

    for (i = 0; i < full_len; ++i) {
        temp[i] = 0;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            temp[i + j] += x[i] * h[j];
        }
    }

    if (strcmp(shape, "full") == 0) {
        y_len = full_len;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[i];
        }
    }
    else if (strcmp(shape, "same") == 0) {
        y_len = n;
        start = (full_len - n) / 2;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[start + i];
        }
    }
    else if (strcmp(shape, "valid") == 0) {
        if (n >= m) {
            y_len = n - m + 1;
        } else {
            y_len = 0;
        }
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[m - 1 + i];
        }
    }
    else {
        pIMem->pVTbl->Free(pIMem, temp);
        return ERR_ECO_POINTER; 
    }

    pIMem->pVTbl->Free(pIMem, temp);

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvDshape(IEcoLab1Ptr_t me, double* x, uint32_t n, double* h, uint32_t m, const char* shape, double* y, uint32_t y_len) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoMemoryAllocator1* pIMem = pCMe->m_pIMem;
    uint32_t i, j, full_len, start;
    double *temp;

    if (me == 0 || x == 0 || h == 0 || y == 0 || y_len == 0 || shape == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    full_len = n + m - 1;
	temp = (double*)pIMem->pVTbl->Alloc(pIMem, (full_len) * sizeof(double));

    for (i = 0; i < full_len; ++i) {
        temp[i] = 0;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            temp[i + j] += x[i] * h[j];
        }
    }

    if (strcmp(shape, "full") == 0) {
        y_len = full_len;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[i];
        }
    }
    else if (strcmp(shape, "same") == 0) {
        y_len = n;
        start = (full_len - n) / 2;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[start + i];
        }
    }
    else if (strcmp(shape, "valid") == 0) {
        if (n >= m) {
            y_len = n - m + 1;
        } else {
            y_len = 0;
        }
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[m - 1 + i];
        }
    }
    else {
        pIMem->pVTbl->Free(pIMem, temp);
        return ERR_ECO_POINTER; 
    }

    pIMem->pVTbl->Free(pIMem, temp);

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_ConvLDshape(IEcoLab1Ptr_t me, long double* x, uint32_t n, long double* h, uint32_t m, const char* shape, long double* y, uint32_t y_len) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoMemoryAllocator1* pIMem = pCMe->m_pIMem;
    uint32_t i, j, full_len, start;
    long double *temp;

    if (me == 0 || x == 0 || h == 0 || y == 0 || y_len == 0 || shape == 0) {
        return ERR_ECO_POINTER;
    }
    if (n < 1 || m < 1) {
        return ERR_ECO_POINTER;
    }

    full_len = n + m - 1;
	temp = (long double*)pIMem->pVTbl->Alloc(pIMem, (n + m - 1) * sizeof(long double));
    for (i = 0; i < full_len; ++i) {
        temp[i] = 0;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            temp[i + j] += x[i] * h[j];
        }
    }

    if (strcmp(shape, "full") == 0) {
        y_len = full_len;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[i];
        }
    }
    else if (strcmp(shape, "same") == 0) {
        y_len = n;
        start = (full_len - n) / 2;
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[start + i];
        }
    }
    else if (strcmp(shape, "valid") == 0) {
        if (n >= m) {
            y_len = n - m + 1;
        } else {
            y_len = 0;
        }
        for (i = 0; i < y_len; ++i) {
            y[i] = temp[m - 1 + i];
        }
    }
    else {
        pIMem->pVTbl->Free(pIMem, temp);
        return ERR_ECO_POINTER; 
    }

    pIMem->pVTbl->Free(pIMem, temp);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
static int32_t ECOCALLMETHOD CEcoLab1_X_Addition(/* in */ IEcoCalculatorXPtr_t me, /* in */ int32_t a, /* in */ int32_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));
    int32_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

static int32_t ECOCALLMETHOD CEcoLab1_X_Subtraction(/* in */ IEcoCalculatorXPtr_t me, /* in */ int32_t a, /* in */ int32_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));
    int32_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}

static int32_t ECOCALLMETHOD CEcoLab1_Y_Multiplication(IEcoCalculatorYPtr_t me, int32_t a, int32_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)2 * sizeof(IEcoUnknownPtr_t));
    int32_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

static int32_t ECOCALLMETHOD CEcoLab1_Y_Division(IEcoCalculatorYPtr_t me, int32_t a, int32_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)2 * sizeof(IEcoUnknownPtr_t));
    int32_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}
/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;
    IEcoUnknown* pOuterUnknown = (IEcoUnknown*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**)&pCMe->m_pInnerUnknown);
    if (result != 0 || pCMe->m_pInnerUnknown == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIX);
    }

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_ConvI,
	CEcoLab1_ConvL,
	CEcoLab1_ConvF,
	CEcoLab1_ConvD,
	CEcoLab1_ConvLD,
	CEcoLab1_ConvIshape,
	CEcoLab1_ConvLshape,
	CEcoLab1_ConvFshape,
	CEcoLab1_ConvDshape,
	CEcoLab1_ConvLDshape
};

IEcoCalculatorXVTbl g_X_x8A1ED3A6B4454B86B7C1D1E9F0A2B3C4VTbl = {
    CEcoLab1_X_QueryInterface,
    CEcoLab1_X_AddRef,
    CEcoLab1_X_Release,
    CEcoLab1_X_Addition,
    CEcoLab1_X_Subtraction
};

IEcoCalculatorYVTbl g_Y_x5F2B9C8D6E1A49479A8B6C5D4E3F2A1BVTbl = {
    CEcoLab1_Y_QueryInterface,
    CEcoLab1_Y_AddRef,
    CEcoLab1_Y_Release,
    CEcoLab1_Y_Multiplication,
    CEcoLab1_Y_Division
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
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Создание таблицы функций интерфейса IEcoCalculatorX */
    pCMe->m_pVTblIX = &g_X_x8A1ED3A6B4454B86B7C1D1E9F0A2B3C4VTbl;

    /* Создание таблицы функций интерфейса IEcoCalculatorY */
    pCMe->m_pVTblIY = &g_Y_x5F2B9C8D6E1A49479A8B6C5D4E3F2A1BVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    pCMe->m_pIX = 0;

    pCMe->m_pIY = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

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
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
