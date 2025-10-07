/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLAB1_H__
#define __I_ECOLAB1_H__

#include "IEcoBase1.h"

/* IEcoLab1 IID = {277FC00C-3562-4096-AFCF-C125B94EEC90} */
#ifndef __IID_IEcoLab1
static const UGUID IID_IEcoLab1 = {0x01, 0x10, {0x27, 0x7F, 0xC0, 0x0C, 0x35, 0x62, 0x40, 0x96, 0xAF, 0xCF, 0xC1, 0x25, 0xB9, 0x4E, 0xEC, 0x90}};
#endif /* __IID_IEcoLab1 */

typedef struct IEcoLab1* IEcoLab1Ptr_t;

typedef struct IEcoLab1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab1Ptr_t me);

    /* IEcoLab1 */
    int16_t (ECOCALLMETHOD *ConvI)(/* in */ IEcoLab1Ptr_t me, /* in */ int* x, uint32_t n, /* in */ int* h, uint32_t m, /* out */ int* y);
    int16_t (ECOCALLMETHOD *ConvL)(/* in */ IEcoLab1Ptr_t me, /* in */ long* x, uint32_t n, /* in */ long* h, uint32_t m, /* out */ long* y);
    int16_t (ECOCALLMETHOD *ConvF)(/* in */ IEcoLab1Ptr_t me, /* in */ float* x, uint32_t n, /* in */ float* h, uint32_t m, /* out */ float* y);
    int16_t (ECOCALLMETHOD *ConvD)(/* in */ IEcoLab1Ptr_t me, /* in */ double* x, uint32_t n, /* in */ double* h, uint32_t m, /* out */ double* y);
    int16_t (ECOCALLMETHOD *ConvLD)(/* in */ IEcoLab1Ptr_t me, /* in */ long double* x, uint32_t n, /* in */ long double* h, uint32_t m, /* out */ long double* y);

	int16_t (ECOCALLMETHOD *ConvIshape)(/* in */ IEcoLab1Ptr_t me, /* in */ int* x, uint32_t n, /* in */ int* h, uint32_t m, /* in */ const char* shape, /* out */ int* y, uint32_t y_len);
    int16_t (ECOCALLMETHOD *ConvLshape)(/* in */ IEcoLab1Ptr_t me, /* in */ long* x, uint32_t n, /* in */ long* h, uint32_t m, const char* shape, /* out */ long* y, uint32_t y_len);
    int16_t (ECOCALLMETHOD *ConvFshape)(/* in */ IEcoLab1Ptr_t me, /* in */ float* x, uint32_t n, /* in */ float* h, uint32_t m, const char* shape, /* out */ float* y, uint32_t y_len);
    int16_t (ECOCALLMETHOD *ConvDshape)(/* in */ IEcoLab1Ptr_t me, /* in */ double* x, uint32_t n, /* in */ double* h, uint32_t m, const char* shape, /* out */ double* y, uint32_t y_len);
    int16_t (ECOCALLMETHOD *ConvLDshape)(/* in */ IEcoLab1Ptr_t me, /* in */ long double* x, uint32_t n, /* in */ long double* h, uint32_t m, const char* shape, /* out */ long double* y, uint32_t y_len);

} IEcoLab1VTbl, *IEcoLab1VTblPtr;

interface IEcoLab1 {
    struct IEcoLab1VTbl *pVTbl;
} IEcoLab1;


#endif /* __I_ECOLAB1_H__ */
