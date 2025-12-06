/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

#include "IEcoConnectionPointContainer.h"
#include "IEcoConnectionPoint.h"
#include "IEcoLab1Events.h"
#include "CEcoLab1Sink.h"
#include "CEcoLab1Sink2.h"

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */

void print_poly_int(const int *p, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        if (i > 0 && p[i] >= 0) {
            printf(" + ");
        }
        if (i == 0) {
            printf("%d", p[i]);
        } else if (i == 1) {
            printf("%d*x", p[i]);
        } else {
            printf("%d*x^%d", p[i], i);
        }
    }
    printf("\n");
}

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
	/* Указатель на интерфейс контейнера точек подключения */
	IEcoConnectionPointContainer* pICPC = 0;
	/* Указатель на интерфейс точки подключения */
	IEcoConnectionPoint* pICP = 0;
	/* Указатель на обратный интерфейс */
	IEcoLab1Events* pIEcoLab1Sink = 0;
	IEcoLab1Events* pIEcoLab1Sink2 = 0;
	IEcoUnknown* pISinkUnk = 0;
	uint32_t cAdvise = 0;

    int i, deg;
	int32_t ans = 0;
	clock_t start, end;
	double elapsed1, elapsed2;
	FILE* File1 = 0;
	FILE* File2 = 0;

	/* открываем файлы */
	fopen_s(&File1, "result1.csv", "w");
	if (File1 == 0) return -1;
	fprintf(File1, "func_name,type,length,time\n");

	fopen_s(&File2, "result2.csv", "w");
	if (File2 == 0) return -1;
	fprintf(File2, "func_name,type,length,time\n");

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }


	/* Проверка поддержки подключений обратного интерфейса */
	result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pICPC);
	if (result != 0 || pICPC == 0) {
		/* Освобождение интерфейсов в случае ошибки */
		goto Release;
	}
	/* Запрос на получения интерфейса точки подключения */
	result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1Events, &pICP);
	if (result != 0 || pICP == 0) {
		/* Освобождение интерфейсов в случае ошибки */
		goto Release;
	}

	/* Освобождение интерфейса */
	pICPC->pVTbl->Release(pICPC);
	/* Создание экземпляра обратного интерфейса */
	result = createCEcoLab1Sink(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink);

	if (pIEcoLab1Sink != 0) {
		result = pIEcoLab1Sink->pVTbl->QueryInterface(pIEcoLab1Sink, &IID_IEcoUnknown, (void**)&pISinkUnk);
		if (result != 0 || pISinkUnk == 0) {
			/* Освобождение интерфейсов в случае ошибки */
			goto Release;
		}

		/* Подключение */
		result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
		/* Проверка */
		if (result == 0 && cAdvise == 1) {
			/* Сюда можно добавить код */
		}

		/* Освобождение интерфейса */
		pISinkUnk->pVTbl->Release(pISinkUnk);
	}

	{
		int n = 8;
		int m = 7;
		uint32_t y_len = n + m - 1;

		int* xInt;
		int* hInt; 
		int* y_fullInt; 
		int* y_shapeInt;

		xInt = (int*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(int));
		hInt = (int*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(int));
		y_fullInt = (int*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(int));

		for (i = 0; i < n; ++i) xInt[i] = (rand() % 21) - 10;
		for (i = 0; i < m; ++i) hInt[i] = (rand() % 21) - 10;

		pIEcoLab1->pVTbl->ConvI(pIEcoLab1, xInt, n, hInt, m, y_fullInt);

		pIMem->pVTbl->Free(pIMem, xInt);
		pIMem->pVTbl->Free(pIMem, hInt);
		pIMem->pVTbl->Free(pIMem, y_fullInt);

		if (pIEcoLab1Sink != 0) {
			/* Отключение */
			result = pICP->pVTbl->Unadvise(pICP, cAdvise);
			pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
		}
		getchar();
	}

	/* Создание экземпляра обратного интерфейса */
	result = createCEcoLab1Sink2(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink2);

	if (pIEcoLab1Sink2 != 0) {
		result = pIEcoLab1Sink2->pVTbl->QueryInterface(pIEcoLab1Sink2, &IID_IEcoUnknown, (void**)&pISinkUnk);
		if (result != 0 || pISinkUnk == 0) {
			/* Освобождение интерфейсов в случае ошибки */
			goto Release;
		}

		/* Подключение */
		result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
		/* Проверка */
		if (result == 0 && cAdvise == 1) {
			/* Сюда можно добавить код */
		}

		/* Освобождение интерфейса */
		pISinkUnk->pVTbl->Release(pISinkUnk);
	}

	{
		int n = 4;
		int m = 3;
		uint32_t y_len = n + m - 1;

		int* xInt;
		int* hInt; 
		int* y_fullInt; 
		int* y_shapeInt;

		xInt = (int*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(int));
		hInt = (int*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(int));
		y_fullInt = (int*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(int));

		for (i = 0; i < n; ++i) xInt[i] = (rand() % 11) - 10;
		for (i = 0; i < m; ++i) hInt[i] = (rand() % 11) - 10;

		pIEcoLab1->pVTbl->ConvI(pIEcoLab1, xInt, n, hInt, m, y_fullInt);

		pIMem->pVTbl->Free(pIMem, xInt);
		pIMem->pVTbl->Free(pIMem, hInt);
		pIMem->pVTbl->Free(pIMem, y_fullInt);

		if (pIEcoLab1Sink2 != 0) {
			/* Отключение */
			result = pICP->pVTbl->Unadvise(pICP, cAdvise);
			pIEcoLab1Sink2->pVTbl->Release(pIEcoLab1Sink2);
			pICP->pVTbl->Release(pICP);
		}
		getchar();
	}
	
	/* Диапазон длин векторов */
	//for (deg = 100; deg < 1000; deg ++) {
	//	int n = deg;
	//	int m = deg;
	//	uint32_t y_len = n + m - 1;

	//	int* xInt; 
	//	int* hInt; 
	//	int* y_fullInt; 
	//	int* y_shapeInt;

	//	long* xLong; 
	//	long* hLong; 
	//	long* y_fullLong; 
	//	long* y_shapeLong;

	//	float* xFloat; 
	//	float* hFloat; 
	//	float* y_fullFloat; 
	//	float* y_shapeFloat;

	//	double* xDouble; 
	//	double* hDouble; 
	//	double* y_fullDouble; 
	//	double* y_shapeDouble;

	//	long double* xLongDouble; 
	//	long double* hLongDouble; 
	//	long double* y_fullLongDouble; 
	//	long double* y_shapeLongDouble;

	//	/* --- INT --- */
	//	xInt = (int*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(int));
	//	hInt = (int*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(int));
	//	y_fullInt = (int*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(int));
	//	y_shapeInt = (int*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(int));

	//	for (i = 0; i < n; ++i) xInt[i] = (rand() % 21) - 10;
	//	for (i = 0; i < m; ++i) hInt[i] = (rand() % 21) - 10;

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvI(pIEcoLab1, xInt, n, hInt, m, y_fullInt);
	//	end = clock();
	//	elapsed1 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File1, "Conv,int,%d,%lf\n", n, elapsed1);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvIshape(pIEcoLab1, xInt, n, hInt, m, "full", y_shapeInt, y_len);
	//	end = clock();
	//	elapsed2 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File2, "ConvShape,int,%d,%lf\n", n, elapsed2);

	//	pIMem->pVTbl->Free(pIMem, xInt);
	//	pIMem->pVTbl->Free(pIMem, hInt);
	//	pIMem->pVTbl->Free(pIMem, y_fullInt);
	//	pIMem->pVTbl->Free(pIMem, y_shapeInt);

	//	/* --- LONG --- */
	//	xLong = (long*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(long));
	//	hLong = (long*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(long));
	//	y_fullLong = (long*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(long));
	//	y_shapeLong = (long*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(long));

	//	for (i = 0; i < n; ++i) xLong[i] = (rand() % 21) - 10;
	//	for (i = 0; i < m; ++i) hLong[i] = (rand() % 21) - 10;

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvL(pIEcoLab1, xLong, n, hLong, m, y_fullLong);
	//	end = clock();
	//	elapsed1 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File1, "Conv,long,%d,%lf\n", n, elapsed1);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvLshape(pIEcoLab1, xLong, n, hLong, m, "full", y_shapeLong, y_len);
	//	end = clock();
	//	elapsed2 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File2, "ConvShape,long,%d,%lf\n", n, elapsed2);

	//	pIMem->pVTbl->Free(pIMem, xLong);
	//	pIMem->pVTbl->Free(pIMem, hLong);
	//	pIMem->pVTbl->Free(pIMem, y_fullLong);
	//	pIMem->pVTbl->Free(pIMem, y_shapeLong);

	//	/* --- FLOAT --- */
	//	xFloat = (float*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(float));
	//	hFloat = (float*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(float));
	//	y_fullFloat = (float*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(float));
	//	y_shapeFloat = (float*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(float));

	//	for (i = 0; i < n; ++i) xFloat[i] = (float)((rand() % 21) - 10);
	//	for (i = 0; i < m; ++i) hFloat[i] = (float)((rand() % 21) - 10);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvF(pIEcoLab1, xFloat, n, hFloat, m, y_fullFloat);
	//	end = clock();
	//	elapsed1 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File1, "Conv,float,%d,%lf\n", n, elapsed1);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvFshape(pIEcoLab1, xFloat, n, hFloat, m, "full", y_shapeFloat, y_len);
	//	end = clock();
	//	elapsed2 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File2, "ConvShape,float,%d,%lf\n", n, elapsed2);

	//	pIMem->pVTbl->Free(pIMem, xFloat);
	//	pIMem->pVTbl->Free(pIMem, hFloat);
	//	pIMem->pVTbl->Free(pIMem, y_fullFloat);
	//	pIMem->pVTbl->Free(pIMem, y_shapeFloat);

	//	/* --- DOUBLE --- */
	//	xDouble = (double*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(double));
	//	hDouble = (double*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(double));
	//	y_fullDouble = (double*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(double));
	//	y_shapeDouble = (double*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(double));

	//	for (i = 0; i < n; ++i) xDouble[i] = (double)((rand() % 21) - 10);
	//	for (i = 0; i < m; ++i) hDouble[i] = (double)((rand() % 21) - 10);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvD(pIEcoLab1, xDouble, n, hDouble, m, y_fullDouble);
	//	end = clock();
	//	elapsed1 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File1, "Conv,double,%d,%lf\n", n, elapsed1);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvDshape(pIEcoLab1, xDouble, n, hDouble, m, "full", y_shapeDouble, y_len);
	//	end = clock();
	//	elapsed2 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File2, "ConvShape,double,%d,%lf\n", n, elapsed2);

	//	pIMem->pVTbl->Free(pIMem, xDouble);
	//	pIMem->pVTbl->Free(pIMem, hDouble);
	//	pIMem->pVTbl->Free(pIMem, y_fullDouble);
	//	pIMem->pVTbl->Free(pIMem, y_shapeDouble);

	//	/* --- LONG DOUBLE --- */
	//	xLongDouble = (long double*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(long double));
	//	hLongDouble = (long double*)pIMem->pVTbl->Alloc(pIMem, m * sizeof(long double));
	//	y_fullLongDouble = (long double*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(long double));
	//	y_shapeLongDouble = (long double*)pIMem->pVTbl->Alloc(pIMem, y_len * sizeof(long double));

	//	for (i = 0; i < n; ++i) xLongDouble[i] = (long double)((rand() % 21) - 10);
	//	for (i = 0; i < m; ++i) hLongDouble[i] = (long double)((rand() % 21) - 10);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvLD(pIEcoLab1, xLongDouble, n, hLongDouble, m, y_fullLongDouble);
	//	end = clock();
	//	elapsed1 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File1, "Conv,long double,%d,%lf\n", n, elapsed1);

	//	start = clock();
	//	pIEcoLab1->pVTbl->ConvLDshape(pIEcoLab1, xLongDouble, n, hLongDouble, m, "full", y_shapeLongDouble, y_len);
	//	end = clock();
	//	elapsed2 = (double)(end - start) / CLOCKS_PER_SEC;
	//	fprintf(File2, "ConvShape,long double,%d,%lf\n", n, elapsed2);

	//	pIMem->pVTbl->Free(pIMem, xLongDouble);
	//	pIMem->pVTbl->Free(pIMem, hLongDouble);
	//	pIMem->pVTbl->Free(pIMem, y_fullLongDouble);
	//	pIMem->pVTbl->Free(pIMem, y_shapeLongDouble);
	//}
	//printf("EcoLab2\n");

	//ans = pIX->pVTbl->Addition(pIX, 2, 7);
	//if (ans == 9) {
	//	printf("IEcoCalculatorX::Addition(2, 7) = %d    [OK]\n", ans);
	//} else {
	//	printf("IEcoCalculatorX::Addition(2, 7) = %d    [INCORRECT]\n", ans);
	//}

	//ans = pIX->pVTbl->Subtraction(pIX, 50, 20);
	//if (ans == 30) {
	//	printf("IEcoCalculatorX::Subtraction(50, 20) = %d    [OK]\n", ans);
	//} else {
	//	printf("IEcoCalculatorX::Subtraction(50, 20) = %d    [INCORRECT]\n", ans);
	//}

	//ans = pIY->pVTbl->Multiplication(pIY, 6, 8);
	//if (ans == 48) {
	//	printf("IEcoCalculatorY::Multiplication(6, 8) = %d    [OK]\n", ans);
	//} else {
	//	printf("IEcoCalculatorY::Multiplication(6, 8) = %d    [INCORRECT]\n", ans);
	//}

	//ans = pIY->pVTbl->Division(pIY, 99, 11);
	//if (ans == 9) {
	//	printf("IEcoCalculatorY::Division(99, 11) = %d    [OK]\n", ans);
	//} else {
	//	printf("IEcoCalculatorY::Division(99, 11) = %d    [INCORRECT]\n", ans);
	//}

	//pIX->pVTbl->Release(pIX);
	//pIY->pVTbl->Release(pIY);

	//result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
	//if (result == 0) {
	//	pIX->pVTbl->Release(pIX);
	//	printf("Check: IEcoLab1 -> IEcoCalculatorX  [accessible]\n");
	//} else {
	//	printf("Check: IEcoLab1 -> IEcoCalculatorX  [missing] (code=%d)\n", result);
	//}

	//result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
	//if (result == 0) {
	//	pIY->pVTbl->Release(pIY);
	//	printf("Check: IEcoLab1 -> IEcoCalculatorY  [accessible]\n");
	//} else {
	//	printf("Check: IEcoLab1 -> IEcoCalculatorY  [missing] (code=%d)\n", result);
	//}

	//result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoLab1, (void**)&pIEcoLab1);
	//if (result == 0) {
	//	pIEcoLab1->pVTbl->Release(pIEcoLab1);
	//	printf("Check: IEcoLab1 -> IEcoLab1  [accessible]\n");
	//} else {
	//	printf("Check: IEcoLab1 -> IEcoLab1  [missing] (code=%d)\n", result);
	//}

	//result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void**)&pIY);
	//if (result == 0) {
	//	pIY->pVTbl->Release(pIY);
	//	printf("Check: IEcoCalculatorX -> IEcoCalculatorY  [accessible]\n");
	//} else {
	//	printf("Check: IEcoCalculatorX -> IEcoCalculatorY  [missing] (code=%d)\n", result);
	//}

	//result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void**)&pIEcoLab1);
	//if (result == 0) {
	//	pIEcoLab1->pVTbl->Release(pIEcoLab1);
	//	printf("Check: IEcoCalculatorX -> IEcoLab1  [accessible]\n");
	//} else {
	//	printf("Check: IEcoCalculatorX -> IEcoLab1  [missing] (code=%d)\n", result);
	//}

	//result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, (void**)&pIX);
	//if (result == 0) {
	//	pIX->pVTbl->Release(pIX);
	//	printf("Check: IEcoCalculatorX -> IEcoCalculatorX  [accessible]\n");
	//} else {
	//	printf("Check: IEcoCalculatorX -> IEcoCalculatorX  [missing] (code=%d)\n", result);
	//}

	//result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**)&pIX);
	//if (result == 0) {
	//	pIX->pVTbl->Release(pIX);
	//	printf("Check: IEcoCalculatorY -> IEcoCalculatorX  [accessible]\n");
	//} else {
	//	printf("Check: IEcoCalculatorY -> IEcoCalculatorX  [missing] (code=%d)\n", result);
	//}

	//result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorY, (void**)&pIY);
	//if (result == 0) {
	//	pIY->pVTbl->Release(pIY);
	//	printf("Check: IEcoCalculatorY -> IEcoCalculatorY  [accessible]\n");
	//} else {
	//	printf("Check: IEcoCalculatorY -> IEcoCalculatorY  [missing] (code=%d)\n", result);
	//}

	//result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void**)&pIEcoLab1);
	//if (result == 0) {
	//	pIEcoLab1->pVTbl->Release(pIEcoLab1);
	//	printf("Check: IEcoCalculatorY -> IEcoLab1  [accessible]\n");
	//} else {
	//	printf("Check: IEcoCalculatorY -> IEcoLab1  [missing] (code=%d)\n", result);
	//}

	//getchar();

	//fclose(File1);
	//fclose(File2);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }
    return result;
}

