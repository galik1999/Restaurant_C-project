
#ifndef restaurant
#define restaurant
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 50

typedef struct Kproduct {  
	char* ProductName;
	int quantity;  
	int price;
	struct Kproduct* next;
}Kproduct;

typedef struct list
{
	Kproduct* head;
	Kproduct* tail;
	int size;
}list;

int RemoveTable(int TableNumber, list tables[SIZE]);
int RemoveItem(int TableNumber, list tables[SIZE]);
int OrderItem(int TableNumber, char* ProductName, int Quantity, list* l, list tables[SIZE]);
int AddItems(FILE* in, list* l, char* Product_name, int Quantity);
int CreateProducts(FILE* in, list* l);
void IfNotClosed(int tableNumber, list tables[SIZE]);

#endif