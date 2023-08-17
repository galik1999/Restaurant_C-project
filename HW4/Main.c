#include "restaurant.h"


int main()
{
	FILE* input, * instructions;
	Kproduct p;
	int j, tableNumber = 0;
	char New[SIZE], check, command; // First storage of string before allocating memory.
	list tables[SIZE], kitchenStock;

	for (j = 0; j < SIZE; j++)
	{
		tables[j].head = NULL;
		tables[j].tail = NULL;
	}
	if ((input = fopen("Manot.txt", "rt")) == NULL)
	{
		printf("Could not open the FILE.");
		exit(1);
	}
	if (fscanf(input, "%c", &check) == EOF)
	{
		printf("There are no products in the kitchen stock");
		exit(1);
	}
	fseek(input, 0, SEEK_SET);
	if ((instructions = fopen("Instructions.txt", "rt")) == NULL)
	{
		printf("Could not open the FILE.");
		exit(1);
	}
	if (fscanf(instructions, "%c", &command) != EOF)
	{
		CreateProducts(input, &kitchenStock); // Initializing the data about the product in the kitchen.
	}
	while (fscanf(instructions, "%c", &command) != EOF)
	{
		switch (command)
		{
		case '2': // adding more inventory for an existing item in the kitchen.
			fscanf(instructions, "%s %d", New, &p.quantity);
			p.ProductName = (char*)malloc(sizeof(char) * strlen(New) + 1);
			if (p.ProductName == NULL)
			{
				printf("Error allocating memory for the name of the product.");

				exit(1);
			}
			strcpy(p.ProductName, New);
			AddItems(input, &kitchenStock, p.ProductName, p.quantity); // Adding new products to quantity.
			break;
		case '3': // order item for table.
			fscanf(instructions, "%d %s %d", &tableNumber, New, &p.quantity);
			p.ProductName = (char*)malloc(sizeof(char) * strlen(New) + 1);
			if (p.ProductName == NULL)
			{
				printf("Error allocating memory for the name of the product.");
				exit(1);
			}
			strcpy(p.ProductName, New);
			OrderItem(tableNumber, p.ProductName, p.quantity, &kitchenStock, &tables);
			break;
		case '4': // cancel last order.
			fscanf(instructions, "%c %d", &command, &tableNumber);
			RemoveItem(tableNumber, &tables);
			break;
		case '5': // close table.
			fscanf(instructions, "%d", &tableNumber);
			RemoveTable(tableNumber, &tables);
			break;
		default:
			break;
		}
	}
	IfNotClosed(tableNumber, tables);
	fclose(input);
	fclose(instructions);
	return 0;
}