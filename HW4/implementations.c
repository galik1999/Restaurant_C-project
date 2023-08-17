#include "restaurant.h"

int RemoveTable(int TableNumber, list tables[SIZE])
// Printing the information of the table order and frees the table.
{
	int payment = 0;
	float tip = 0;
	if (tables[TableNumber].head == NULL)      
	{
		printf("The table number %d is not ordered yet\n", TableNumber);    
		return 1;
	}
	Kproduct* temp = tables[TableNumber].head;
	printf("Table number %d bill is:\n", TableNumber);
	while (temp != NULL)
	{
		payment += temp->price * temp->quantity;
		printf("%d %s.", temp->quantity, temp->ProductName);
		temp = temp->next;
	}
	tip = 0.15 * payment;
	printf("%d nis+%g nis for tips,please!\n", payment, tip);

	while (tables[TableNumber].head != NULL)
	{
		Kproduct* tempo = tables[TableNumber].head;
		tables[TableNumber].head = tables[TableNumber].head->next;
		free(tempo->ProductName);
		free(tempo);
	}
}

int RemoveItem(int TableNumber, list tables[SIZE])
// Cancel last order of the table.
{
	if (TableNumber > SIZE)
	{
		printf("There is no such table");
		return 1;
	}
	if (tables[TableNumber].head == NULL)
	{
		printf("There is no such order");
		return 1;
	}
	Kproduct* temp = tables[TableNumber].head;
	tables[TableNumber].head = tables[TableNumber].head->next;
	printf("%d %s was returned to the kitchen from table number %d\n", temp->quantity, temp->ProductName, TableNumber);
	free(temp->ProductName);
	free(temp);
}

int OrderItem(int TableNumber, char* ProductName, int Quantity, list* kitchenStock, list tables[SIZE])
// add new item for the table as their order.
{
	// 1- wrong. 0- right.
	Kproduct* temp = kitchenStock->head;
	Kproduct* q = NULL;
	if (TableNumber > SIZE)
	{
		printf("The number of the table is wrong.");
		return 1; //1 means wrong input.
	}
	if (Quantity < 0)
	{
		printf("The Quantity is wrong.");
		return 1;
	}
	while (temp != NULL)
	{
		if (strcmp(temp->ProductName, ProductName) == 0)
		{
			if (Quantity > temp->quantity)
			{
				printf("We don't have enough quantity for the order.\n");
				return 1;
			}
			temp->quantity--;
			q = (Kproduct*)malloc(sizeof(Kproduct));
			if (q == NULL)
			{
				printf("Error allocating memory.");
				exit(1);
			}
			q->quantity = temp->quantity;
			q->ProductName = temp->ProductName;
			q->price = temp->price;
			q->next = tables[TableNumber].head;
			tables[TableNumber].head = q;
			tables[TableNumber].head->quantity = Quantity; // Saveing the quantity of the bought items.

			printf("%d %s were added to the table number %d\n", Quantity, ProductName, TableNumber);
			return 0; // zero means the job is done.
		}
		temp = temp->next;
	}
	printf("We don't have %s here, sorry!\n", ProductName);
	return 1;
}

int AddItems(FILE* in, list* kitchenStock, char* Product_name, int Quantity)
// Adding MORE items to the kitchens stock.
{
	Kproduct* temp = kitchenStock->head;
	if (Quantity < 0)
	{
		printf("The quantity of the items can not be a negative number\n");
		return 1;
	}
	while (temp != NULL) // Checking existance by name;
	{
		if (strcmp(temp->ProductName, Product_name) == 0)
		{
			temp->quantity = temp->quantity + Quantity;
			printf("%d %s were added to the kitchen\n", Quantity, Product_name);
			return 0;
		}
		temp = temp->next;
	}
	printf("The input Item does not exist in the kitchen\n");
	return 1;
}

int CreateProducts(FILE* in, list* kitchenStock)
// initialize the kitchen stock.
{
	Kproduct* temp;
	kitchenStock->head = NULL;
	kitchenStock->tail = NULL;
	kitchenStock->size = 0;
	int flag = 0;
	char name[SIZE];
	int quantity, price;
	temp = (Kproduct*)malloc(sizeof(Kproduct));
	if (temp == NULL)
	{
		printf("Error allocating a new node to the list.");
		while (kitchenStock->head != NULL)
		{
			temp = (kitchenStock->head);
			kitchenStock->head = (kitchenStock->head)->next;
			free(temp);
		}
		exit(1);
	}
	while (fscanf(in, "%s %d %d", name, &quantity, &price) != EOF)
	{

		if ((quantity) < 0)
		{
			printf("The quantity can't be a negative number.\n");
			break;
		}
		if ((price) < 0)
		{
			printf("The price can't be a negative number\n");
			break;
		}

		if ((kitchenStock->head) == NULL) // First iteration of scanning the information from the input FILE.
		{
			// Allocating memory for the string.
			temp->ProductName = (char*)malloc(sizeof(char) * (strlen(name) + 1));
			if (temp->ProductName == NULL)
			{
				// free what is needed.
				while (kitchenStock->head != NULL)
				{
					temp = kitchenStock->head;
					free((kitchenStock->head)->ProductName);
					kitchenStock->head = (kitchenStock->head)->next;
					free(temp);
				}
				printf("Could not allocate new string.");
				exit(1);
			}

			if (quantity > 0 && price > 0)
			{
				temp->quantity = quantity;
				temp->price = price;
				strcpy(temp->ProductName, name);
				temp->next = kitchenStock->tail;
				kitchenStock->head = temp;
				kitchenStock->tail = temp;
				kitchenStock->size++;
			}


			temp = (Kproduct*)malloc(sizeof(Kproduct)); // Creating a new node for the next scanning (if needed).
			if (temp == NULL)
			{
				while (kitchenStock->head != NULL)
				{
					temp = kitchenStock->head;
					kitchenStock->head = (kitchenStock->head)->next;
					free(temp);
				}
				printf("Could not allocate new node.");
				exit(1);
			}
			(kitchenStock->head)->next = temp;
		}
		else if (kitchenStock->head != NULL) // Not-the-first iteration of scanning information.
		{
			temp->ProductName = (char*)malloc(sizeof(char) * (strlen(name) + 1));
			if (temp->ProductName == NULL)
			{
				// free what is needed.
				while (kitchenStock->head != NULL)
				{
					temp = kitchenStock->head;
					free((kitchenStock->head)->ProductName);
					kitchenStock->head = (kitchenStock->head)->next;
					free(temp);
				}
				printf("Could not allocate new string.");
				exit(1);
			}
			if (strcmp(name, (kitchenStock->tail)->ProductName) == 0)
			{
				printf("You can't enter the same name twice.\n");
				flag = 1;
			}
			if (flag == 0)
			{
				if (quantity > 0 && price > 0)
				{
					temp->quantity = quantity;
					temp->price = price;
					strcpy(temp->ProductName, name);
					temp->next = kitchenStock->tail;
					kitchenStock->tail = temp;
					kitchenStock->size++;
				}
			}
			flag = 0;
			
			temp = (Kproduct*)malloc(sizeof(Kproduct)); // Creating a new node for the next scanning (if needed).
			if (temp == NULL)
			{
				while (kitchenStock->head != NULL)
				{
					temp = kitchenStock->head;
					kitchenStock->head = (kitchenStock->head)->next;
					free(temp);
				}
				printf("Could not allocate a new node.");
				exit(1);
			}
			(kitchenStock->tail)->next = temp;
		}
	}
	(kitchenStock->tail)->next = NULL;
	printf("The kitchen was created\n");
	return 0;
}

void IfNotClosed(int tableNumber, list tables[SIZE])
{
	int i;
	Kproduct* temp;
	for (i = 0; i < SIZE; i++)
	{

		{
			while (tables[i].head != NULL)
			{
				temp = tables[i].head;
				tables[i].head = tables[i].head->next;
				free(temp->ProductName);
				free(temp);
			}
		}

	}
}