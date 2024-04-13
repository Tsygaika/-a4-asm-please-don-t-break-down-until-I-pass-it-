#include <stdio.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS

void main() {
	setlocale(LC_ALL, "Rus");

	int choice, flag = 1;
	puts("Выберите:\n1)а4.1\n2)а4.2");
	scanf_s("%d", &choice);
	switch (choice) {
	case 1:
		while (flag) {

			unsigned char A[16], B[16];
			int C[32];
			int tmp, i, k = 0;

			printf("Введите массив А:");
			for (i = 0; i < 16; i++) {
				scanf_s("%d", &tmp);
				if (tmp >= 0 && tmp <= 255) {
					A[i] = (unsigned char)tmp;
				}
				else {
					printf("\nВведено число не из диапазона [0;255]\n");
					return;
				}
			}

			printf("Введите массив B:");
			for (i = 0; i < 16; i++) {
				scanf_s("%d", &tmp);
				if (tmp >= 0 && tmp <= 255) {
					B[i] = (unsigned char)tmp;
				}
				else {
					printf("\nВведено число не из диапазона [0;255]\n");
					return;
				}
			}

			printf("\nМассив А:");
			for (i = 0; i < 16; i++) {
				printf(" %d", A[i]);
			}

			printf("\nМассив B:");
			for (i = 0; i < 16; i++) {
				printf(" %d", B[i]);
			}

			_asm {
				lea esi, [A]; // записываем адрес массива А 
				lea edi, [B]; // записываем адрес массива В
				lea edx, [C]; // записываем адрес массива С
				mov [k], 0; // k = 0 (количество таких пар)
				mov ecx, 16; // ecx = 16

			CYCLE:
				mov al, [esi]; // al = A[esi]
				cmp al, [edi]; // сравниваем A[esi] и B[edi]
				jne NEXT; //если они не равны, то переходим к следующим элементам

				cbw; //превращаем A[esi] в слово
				mov bl, 3; // bl = 3
				div bl; //делим A[esi] на 3
				mov bl, 2; //bl = 2
				cmp ah, bl; //сравниваем остаток с 2
				jne NEXT; //если они не равны, то переходим к следующим элементам
							//если все условия выполнены, то сохраняем адреса в массив С
				mov [edx], esi; //сначала сохраняем адрес элемента из А
				add edx, 4; //переходим к следующему элементу в С
				mov [edx], edi; //сохраняем адрес элемента из В
				add edx, 4; //переходим к следующему элементу в С

				inc[k]; //увеличиваем k на 1
			NEXT:
				inc esi; //esi++
				inc edi; //edi++
				loop CYCLE; //переходим к следующей итерации цикла
			}


			printf("\nКоличество пар таких элементов: %d", k);
			printf("\nМассив C:");
			for (i = 0; i < 2 * k; i++) {
				printf("%p ", C[i]);
			}

			printf("\nВведите 0, чтобы выйти: ");
			scanf_s("%d", &flag);

		}
		break;

	case 2:
		while (flag) {

			int i, k = 0, tmp;
			unsigned short int A[16], B[16];
			int C[32];

			printf("Введите массив А:");
			for (i = 0; i < 16; i++) {
				scanf_s("%d", &tmp);
				if (tmp >= 0 && tmp <= 65535) {
					A[i] = (unsigned short int)tmp;
				}
				else {
					printf("\nВведено число не из диапазона [0;65535]\n");
					return;
				}
			}

			printf("Введите массив B:");
			for (i = 0; i < 16; i++) {
				scanf_s("%d", &tmp);
				if (tmp >= 0 && tmp <= 65535) {
					B[i] = (unsigned short int)tmp;
				}
				else {
					printf("\nВведено число не из диапазона [0;65535]\n");
					return;
				}
			}

			printf("\nМассив А:");
			for (i = 0; i < 16; i++) {
				printf(" %d", A[i]);
			}

			printf("\nМассив B:");
			for (i = 0; i < 16; i++) {
				printf(" %d", B[i]);
			}

			_asm {
				lea esi, [A]; 
				lea edi, [B]; 
				lea edx, [C]; 
				mov [k], 0; 
				mov ecx, 16; 

			CYCLE2:
				mov ax, [esi]; 
				cmp ax, [edi];
				jne NEXT2;

				mov bl, 3; 
				div bl;
				mov bl, 2;
				cmp ah, bl;
				jne NEXT2;

				mov[edx], esi;
				add edx, 4;
				mov[edx], edi;
				add edx, 4;

				inc[k];
			NEXT2:
				add esi, 2; 
				add edi, 2;
				loop CYCLE2;
			}


			printf("\nКоличество пар таких элементов: %d", k);
			printf("\nМассив C:");
			for (i = 0; i < 2 * k; i++) {
				printf("%p ", C[i]);
			}

			printf("\nВвведите 0, чтобы выйти: ");
			scanf_s("%d", &flag);
		}
		break;

	default:
		printf("Такой функции нет");
		break;
	}
}
