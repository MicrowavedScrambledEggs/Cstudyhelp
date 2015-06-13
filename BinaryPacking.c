/*Rough program emulating a stock database for one of those stores that used to be
  2 dollar shops but are now under-$10 shops. Written to practise binary 
  operations. Feel free to improve it
  
  Product info for each product is stored inside integers inside an integer array.
  A better implementation would be to store the integers inside a linked list. If 
  you want to make a linked list, be my guest
  */

#include <stdio.h>

#define PROD_SIZE sizeof(Product)
#define INVENTORY_SIZE 20
#define NUM_OP 4
#define NUM_CATS (sizeof(categories)/sizeof(*categories))

typedef enum Category {FOOD, TOY, TOOL, HOME};
typedef enum Category Category;
char *categories[4] = {"Food", "Toy", "Tools", "Homeware"};

typedef struct product{
	//comments refer to when they get packed into an int
	Category cat;//2 bits because 4 types
	int price;//in cents, 10 bits to get up to 1023 cents
	int quantity; //4 bits for up to 15 
	//id was originally 0 - 65535 but the left most bit still made the value
	//negative if it was 1
	int id;//uses the last 16 bits: 0 - 32767
} Product;

void print_menu(void);
void add_product(int products[]);
Product *find_product(int id, int products[]);
int product_exists(int id, int products[]);
Product *unpack_product(int prod_int);
void print_product(Product *prod);
void print_inventory(int products[]);
int pack_product(Category cat, int price, int quantity, int id);

int main(void){
	
	int products[INVENTORY_SIZE];
	int i, id, choice = 0;
	
	//initialises product ints to 0
	for(i = 0; i < INVENTORY_SIZE; i++){
		products[i] = 0;
	}
	
	printf("\nWelcome to Bust'a'Bargin's inventory manager\n");
	
	while(choice != 3){
		print_menu();
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice){
			case(0):add_product(products); 
					break;
			case(1):printf("\nEnter id of product: ");
					scanf("%d", &id);
					print_product(find_product(id, products)); 
					break;
			case(2):print_inventory(products); 
					break;
		}
	}
	
	return 0;
}

void print_menu(){
	
	int i;
	char *options[NUM_OP] = {"Add Product", "Find Product", "Print Inventory", "Exit"};
	
	printf("\n");
	for(i = 0; i < NUM_OP; i++){
		printf("%d: %s\n", i, options[i]);
	}
}

void add_product(int products[]){
	
	Category cat;
	int price, quantity, id, i;
	
	printf("\nSelect category of product.\n");
	printf("Key:\n");
	for(i = 0; i < NUM_CATS; i++){
		printf("%d: %s\n", i, categories[i]);
	}
	scanf("%d", &cat);
	while(cat < 0 || cat > 3){
		printf("Invalid category. Please re-enter: ");
		scanf("%d", &cat);
	}
	printf("Enter price of product in cents (Max price 1023 cents. Best bargains in town remember!): ");
	scanf("%d", &price);
	while(price < 0 || price > 1023){
		printf("Price invalid. Please enter a price between 0 and 1023 cents: ");
		scanf("%d", &price);
	}
	printf("Enter quantity of product (Max is 15. We're not a wholesale store): ");
	scanf("%d", &quantity);
	while(quantity < 0 || quantity > 15){
		printf("Quantity invalid. Please enter a quantity between 0 and 15: ");
		scanf("%d", &quantity);
	}
	printf("Enter product id (0 - 32767): ");
	scanf("%d", &id);
	while(id < 0 || id > 32767){
		printf("Id invalid. Please enter a number between 0 and 32767: ");
		scanf("%d", &id);
	}
	while(product_exists(id, products)){
		printf("Id already in use. Please enter another: ");
		scanf("%d", &id);
	}
	for(i = 0; i < INVENTORY_SIZE; i++){
		if(products[i] == 0){//adds the product to the first empty cell after packing it to an int
			products[i] = pack_product(cat, price, quantity, id);
			break;
		}
	}
}

int pack_product(Category cat, int price, int quantity, int id){
	
	int prod_int = 0;
	prod_int |= cat;
	prod_int |= price << 2;
	prod_int |= quantity << 12;
	prod_int |= id << 16;
	return prod_int;
}

int product_exists(int id, int products[]){
	
	int i, id_mask = 65535;
	
	for(i = 0; i < INVENTORY_SIZE; i++){
		if(products[i] == 0) return 0;
		if(((products[i]&(id_mask<<16))>>16) == id) return 1;
	}
	return 0;
}

Product *find_product(int id, int products[]){
	
	int i, id_mask = 65535;
	
	for(i = 0; i < INVENTORY_SIZE; i++){
		if(products[i] == 0) return NULL;
		if(((products[i]&(id_mask<<16))>>16) == id) return unpack_product(products[i]);
	}
	return NULL;
}

Product *unpack_product(int prod_int){
	
	int id_mask = 65535, cat_mask = 3, price_mask = 1023, quan_mask = 15;
	Product *unpacked = malloc(PROD_SIZE);
	
	unpacked->cat = prod_int&cat_mask;
	unpacked->price = (prod_int&(price_mask<<2))>>2;
	unpacked->quantity = (prod_int&(quan_mask<<12))>>12;
	unpacked->id = (prod_int&(id_mask<<16))>>16;
	
	return unpacked;
}

void print_product(Product *product){
	
	if(product == NULL){
		printf("\nCould not find product\n");
		return;
	}
	
	int dollars, cents;
	//converting price
	dollars = product->price /100;
	cents = product->price - (dollars*100);
	
	printf("\nId: %d\n", product->id);
	printf("Category: %s\n", categories[product->cat]);
	printf("Price: $%d.%d\n", dollars, cents);
	printf("Quantity: %d\n", product->quantity);
	
	free(product);
}

void print_inventory(int products[]){
	int i;
	
	for(i = 0; i < INVENTORY_SIZE; i++){
		if(products[i] == 0) return;
		print_product(unpack_product(products[i]));
	}
}

