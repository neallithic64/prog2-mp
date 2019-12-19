/*
	Description: Machine Problem for CCPROG2 [v3.4 - FINAL DRAFT]
	Name: LIM, MATTHEW NEAL
	Section: S16B
*/


/*************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in
studying and applying the concepts learned. I have constructed the functions and their
respective algorithms and corresponding code by myself. The program was run, tested,
and debugged by my own efforts. I further certify that I have not copied in part or
whole or otherwise plagiarized the work of other students and/or persons.

											Matthew Neal Tan Lim, DLSU ID# 11829257
*************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_ITEMS 20
#define AD_PASS "H3LLo?"

typedef char string10[11];
typedef char string15[16];
typedef char string20[21];
typedef char string30[31];

typedef struct {
	int year,
		month,
		day;
} structDateType;

typedef struct {
	int productID;
	int sellerID;
	string20 itemName;
	string15 category;
	string30 description;
	int quantity;
	float unitPrice;
} structItemType;

typedef struct {
	int userID;
	string10 password;
	string30 address;
	double contactNo;
	string20 name;
} structUserType;

typedef structItemType arrTransacItem[5];
typedef structItemType arrCart[10];

typedef struct {
	structDateType date;
	arrTransacItem itemList;
	int buyerID,
		sellerID;
	float totalAmount;
} structTransacType;

typedef structUserType arrUsers[MAX_USERS];
typedef structItemType arrItems[MAX_USERS*MAX_ITEMS];

typedef struct {
	int adminID;
	string10 adPass;
	string20 adName;
} structAdminType;

typedef structAdminType arrAdmin[20];


	/*
	
		INITAL and AUXILLIARY FUNCTIONS
	
	*/



	/* The next three functions are used in reading and manipulating an array of
		structItemType elements. The elements will be arranged in order of ascending
		product ID using Selection Sorting.
	*/
void swapItem(structItemType *data1, structItemType *data2) {
	structItemType x = *data1;
	*data1 = *data2;
	*data2 = x;
}
int indexSmallestProdID(arrItems array, int startIndex, int endIndex) {
	int i, indexSmall = startIndex; // set the initial smallest to startIndex
	
	for (i = startIndex; i <= endIndex; i++)
		if (array[indexSmall].productID > array[i].productID) // check if the selected element is less than the current element
			indexSmall = i; // replace to index of new smallest if true
	return indexSmall; // returns index of final "smallest value"
}
void sortProdID(arrItems array, int *nElem) {
	int i, smallest;
	
	for (i = 0; i < *nElem; i++) {
		smallest = indexSmallestProdID(array, i, (*nElem)-1); // find the index of the smallest
		swapItem(&array[i], &array[smallest]); // swap the smallest with the index in for
	}
}



	/* The next two functions are used in reading and manipulating an array of
		structItemType elements. The elements will be arranged in order of ascending
		seller ID using Selection Sorting.
	*/
int indexSmallestSellID(arrItems array, int startIndex, int endIndex) {
	int i, indexSmall = startIndex; // set the initial smallest to startIndex
	
	for (i = startIndex; i <= endIndex; i++)
		if (array[indexSmall].sellerID > array[i].sellerID) // check if the selected element is less than the current element
			indexSmall = i; // replace to index of new smallest if true
	return indexSmall; // returns index of final "smallest value"
}
void sortSellID(arrItems array, int *nElem) {
	int i, smallest;
	
	for (i = 0; i < *nElem; i++) {
		smallest = indexSmallestSellID(array, i, (*nElem)-1); // find the index of the smallest
		swapItem(&array[i], &array[smallest]); // swap the smallest with the index in for
	}
}


	/* The next three functions are used in reading and manipulating an array of
		structUserType elements. The elements will be arranged in order of ascending
		user ID using Selection Sorting.
	*/
void swapUser(structUserType *data1, structUserType *data2) {
	structUserType x = *data1;
	*data1 = *data2;
	*data2 = x;
}
int indexSmallestUserID(arrUsers array, int startIndex, int endIndex) {
	int i, indexSmall = startIndex;
	
	for (i = startIndex; i <= endIndex; i++)
		if (array[indexSmall].userID > array[i].userID)
			indexSmall = i;
	return indexSmall;
}
void sortUserID(arrUsers array, int *nElem) {
	int i, smallest;
	
	for (i = 0; i < *nElem; i++) {
		smallest = indexSmallestUserID(array, i, (*nElem)-1);
		swapUser(&array[i], &array[smallest]);
	}
}


	/* This function accepts a text file Users.txt, reads it, and stores the data inside
		the array declared in main().
	*/
void loadUsers(arrUsers aUsers, int *pElem) {
	FILE *fp;
	char dump;
	
	if ( (fp=fopen("Users.txt", "r")) != NULL ) {
		*pElem = 0;
		while ( fscanf(fp, "%d%c%s%c", &aUsers[*pElem].userID, &dump, aUsers[*pElem].password, &dump) == 4 ) {
			fgets(aUsers[*pElem].name, 21, fp);
				aUsers[*pElem].name[ strlen(aUsers[*pElem].name)-1 ] = '\0';
			fgets(aUsers[*pElem].address, 31, fp);
				aUsers[*pElem].address[ strlen(aUsers[*pElem].address)-1 ] = '\0';
			fscanf(fp, "%lf%c", &aUsers[*pElem].contactNo, &dump);
			(*pElem)++;
		}
		fclose(fp);
	}
}



	/* This function accepts a text file Items.txt, reads it, and stores the data inside
		the array declared in main().
	*/
void loadItems(arrItems aItems, int *pElem) {
	FILE *fp;
	char dump;
	
	if ( (fp=fopen("Items.txt", "r")) != NULL ) {
		*pElem = 0;
		while ( fscanf(fp, "%d%c%d%c", &aItems[*pElem].productID, &dump, &aItems[*pElem].sellerID, &dump) == 4 ) {
			fgets(aItems[*pElem].itemName, 21, fp);
				aItems[*pElem].itemName[ strlen(aItems[*pElem].itemName)-1 ] = '\0';
			fgets(aItems[*pElem].category, 16, fp);
				aItems[*pElem].category[ strlen(aItems[*pElem].category)-1 ] = '\0';
			fgets(aItems[*pElem].description, 31, fp);
				aItems[*pElem].description[ strlen(aItems[*pElem].description)-1 ] = '\0';
			fscanf(fp, "%d%c%f%c", &aItems[*pElem].quantity, &dump, &aItems[*pElem].unitPrice, &dump);
			(*pElem)++;
		}
		fclose(fp);
	}
}



	/* This function accepts a text file Users.txt and writes data from the whole array
		into the Users.txt, overwriting its contents.
	*/
void saveUsers(arrUsers aUsers, int nElem) {
	FILE *fp;
	int i;
	
	if ( (fp=fopen("Users.txt", "w")) != NULL ) {
		for (i = 0; i < nElem; i++) {
			fprintf(fp, "%d %s\n", aUsers[i].userID, aUsers[i].password);
			fprintf(fp, "%s\n%s\n%.0lf\n\n", aUsers[i].name, aUsers[i].address, aUsers[i].contactNo);
		}
		fclose(fp);
	} else printf("Error! File could not be written!\n");
}



	/* This function accepts a text file Items.txt and writes data from the whole array
		into the Items.txt, overwriting its contents.
	*/
void saveItems(arrItems aItems, int nElem) {
	FILE *fp;
	int i;
	
	if ( (fp=fopen("Items.txt", "w")) != NULL ) {
		for (i = 0; i < nElem; i++) {
			fprintf(fp, "%d %d\n", aItems[i].productID, aItems[i].sellerID);
			fprintf(fp, "%s\n%s\n%s\n", aItems[i].itemName, aItems[i].category, aItems[i].description);
			fprintf(fp, "%d %.2f\n\n", aItems[i].quantity, aItems[i].unitPrice);
		}
		fclose(fp);
	} else printf("Error! File could not be written!\n");
}







	/*
	
		REGISTER USER FUNCTIONS
	
	*/



	/* This function will check against the input array of users if the incoming input
		userID is unique or not. If it is unique, the function returns 1, otherwise
		it returns 0. Used in registerUser().
	*/
int checkUser(arrUsers aUsers, int *pCount, int IDinput) {
	int i;
	
	for(i = 0; i <= (*pCount); i++)
		if (IDinput == aUsers[i].userID)
			return 0;
	return 1;
}



	/* This function will register a new user and stores the data into the array. First,
		it calls checkUser() first to see if the input userID is unique. Then, it fills
		the next free array element (using a counter *pCount) with the given input
		structure.
	*/
void registerUser(arrUsers *aUsers, int *pCount) {
	char dump;
	int placeholdUserID;
	
	printf("Enter userID: ");
	scanf("%d%c", &placeholdUserID, &dump);
	
	if ( checkUser(*aUsers, pCount, placeholdUserID) ) { // checking that there's no other matches
		(*aUsers)[*pCount].userID = placeholdUserID;
		
		printf("Enter password: ");
		fgets((*aUsers)[*pCount].password, 11, stdin);
		(*aUsers)[*pCount].password[ strlen((*aUsers)[*pCount].password) - 1] = '\0';
		printf("Enter address: ");
		fgets((*aUsers)[*pCount].address, 31, stdin);
		(*aUsers)[*pCount].address[ strlen((*aUsers)[*pCount].address) - 1] = '\0';
		printf("Enter contact number: ");
		scanf("%lf%c", &(*aUsers)[*pCount].contactNo, &dump);
		printf("Enter name: ");
		fgets((*aUsers)[*pCount].name, 21, stdin);
		(*aUsers)[*pCount].name[ strlen((*aUsers)[*pCount].name) - 1] = '\0';
		
		(*pCount)++;
	} else printf("\tError! UserID already exists!\n");
}



	/* This function will check with the entire list of users (array) and check if the
		log in credentials match with one of the users. If so, the function returns the
		index of the user's location. Otherwise, it returns -1, the truth state for no
		found users.
	*/
int checkLogIn(int inputID, string10 inputPass, arrUsers userList, int *pUser) {
	int i;
	for (i = 0; i < (*pUser); i++) {
		if ( (inputID == userList[i].userID) && (strcmp(inputPass, userList[i].password) == 0) ) {
			printf("\tLog in successful!\n");
			return i;
		}
	}
	printf("\tLog in unsuccessful!\n");
	return -1;
}






	/*
	
		USER - SELL Functions
	
	*/



	/* This function checks if the inputted product ID is unique or not. Returns 1 if so,
		else returns 0 if the input product ID already exists. To be used in addNewItem().
	*/
int checkUniqueProdID(arrItems aItems, int *nItems, int prodID) {
	int i;
	for (i = 0; i < (*nItems); i++)
		if (prodID == aItems[i].productID)
			return 0;
	return 1;
}



	/* This function checks all the items and counts the number of items under
		a specific seller ID. If the counter is 20 or over, returns 0 (meaning
		the seller/user can't sell any more items). Otherwise, returns 1 (assumes
		that the seller/user can sell more items, still). To be used in addNewItem().
	*/
int checkSellItemLimit(arrItems aItems, int *nItems, int sellID) {
	int i, itemCount = 0;
	for (i = 0; i < (*nItems); i++)
		if (aItems[i].sellerID == sellID)
			itemCount++;
	if (itemCount >= 20)
		return 0;
		else return 1;
}



	/* This function allows user to create a new item to store in the aItems array.
		"The program should check that the seller has not reached the limit yet
		before allowing the user to add an item to sell. [...] Afterwhich, the user
		is shown the Sell Menu again." The function increments the pointer for nItems
		once done, before terminating.
	*/
void addNewItem(arrItems aItems, int *nItems, int userID) {
	int tempProdID;
	char dump;
	
	printf("Enter product ID: ");
	scanf("%d%c", &tempProdID, &dump);
	if (checkUniqueProdID(aItems, nItems, tempProdID) && checkSellItemLimit(aItems, nItems, userID)) {
		aItems[*nItems].productID = tempProdID;
		
		printf("Enter item name: ");
		fgets(aItems[*nItems].itemName, 21, stdin);
			aItems[*nItems].itemName[strlen(aItems[*nItems].itemName)-1] = '\0';
		printf("Enter item category: ");
		fgets(aItems[*nItems].category, 16, stdin);
			aItems[*nItems].category[strlen(aItems[*nItems].category)-1] = '\0';
		printf("Enter item description: ");
		fgets(aItems[*nItems].description, 31, stdin);
			aItems[*nItems].description[strlen(aItems[*nItems].description)-1] = '\0';
		printf("Enter quantity: ");
		scanf("%d%c", &aItems[*nItems].quantity, &dump);
		printf("Enter unit price: ");
		scanf("%f%c", &aItems[*nItems].unitPrice, &dump);
		
		aItems[*nItems].sellerID = userID;
		(*nItems)++;
	} else printf("\tProduct ID already exists or seller has exceeded item limit! Exiting to Sell Menu...\n");
}



	// Function Prototype for showMyProducts, to be used in editStock()
		void showMyProducts(arrItems aItems, int *nItems, int sellerID);



	/* This function returns the index of a specific product ID input in the
		array of items.
	*/
int findProdID(arrItems aItems, int *nItems, int prodID) {
	int i;
	for (i = 0; i < *nItems; i++)
		if (aItems[i].productID == prodID)
			return i;
	return -1;
}



	/* This function first displays all the seller's products in table format [copy the
		format of showProducts()]. Then, it prompts the seller for the product ID of
		the item they want to edit. "If an invalid productID is given [i.e., the
		product ID inputted doesn't exist], a message should be shown, then the
		user is redirected back to the Sell Menu." Otherwise, they will be shown a menu.
	*/
void editStock(arrItems aItems, int *nItems, int sellID) {
	int edStockOpt, tempProdID, i;
	char dump;
	int replenAmt;
	float newPrice;
	
		// display table
	showMyProducts(aItems, nItems, sellID);
	
		// prodID prompt
	printf("\tEnter product ID to edit: ");
	scanf("%d%c", &tempProdID, &dump);
	i = findProdID(aItems, nItems, tempProdID);
	
	if (i != -1 && (aItems[i].sellerID == sellID) ) {
		while (edStockOpt != 6) {
			printf("\t\tSelect option:\n");
			printf("\t\t\t1: Replenish\n");
			printf("\t\t\t2: Change Price\n");
			printf("\t\t\t3: Change Item Name\n");
			printf("\t\t\t4: Change Category\n");
			printf("\t\t\t5: Change Description\n");
			printf("\t\t\t6: Finish Editing\n");
			scanf("%d%c", &edStockOpt, &dump);
			
			switch(edStockOpt) {
				case 1: { printf("\t\t\tReplenish selected. How much would you like to replenish?\n");
					scanf("%d%c", &replenAmt, &dump);
					aItems[i].quantity += replenAmt;
					break;
				}
				case 2: { printf("\t\t\tChange Price selected...\n");
					scanf("%f%c", &newPrice, &dump);
					aItems[i].unitPrice = newPrice;
					break;
				}
				case 3: { printf("\t\t\tChange Item Name selected...\n");
					fgets(aItems[i].itemName, 21, stdin);
						aItems[i].itemName[strlen(aItems[i].itemName)-1] = '\0';
					break;
				}
				case 4: { printf("\t\t\tChange Category selected...\n");
					fgets(aItems[i].category, 16, stdin);
						aItems[i].category[strlen(aItems[i].category)-1] = '\0';
					break;
				}
				case 5: { printf("\t\t\tChange Description selected...\n");
					fgets(aItems[i].description, 31, stdin);
						aItems[i].description[strlen(aItems[i].description)-1] = '\0';
					break;
				}
				case 6: { printf("\t\t\tReturning to Sell Menu...\n"); break;
				}
			}
		}
	} else printf("\t\tProduct ID not found or unauthorised editing of item! Returning to Sell Menu...\n\n");
}



	/* The information should be shown in this sequence: productID, item name,
		category, unit price, quantity. The data should be shown in table
		format, sorted in increasing order based on the productID. Numbers
		should be right justified, strings should be left justified in their
		"columns". Hint: use the capacity of the containers to determine the
		size of the "columns" and refer to CCPROG1 notes on printf().
	*/
void showMyProducts(arrItems aItems, int *pItems, int sellID) {
	int i;
	
	printf("\n\t|  PRODUCT ID  |  ITEM NAME  |  CATEGORY  |  UNIT PRICE  |  QUANTITY  |\n");
	for (i = 0; i < *pItems; i++)
		if (aItems[i].sellerID == sellID)
			printf("\t  %-10d  %-20s  %-15s  %-10.2f  %-10d\n", aItems[i].productID, aItems[i].itemName,
				aItems[i].category, aItems[i].unitPrice, aItems[i].quantity);
	printf("\n\n");
}



	/* All the information (including product description, but excluding seller’s
		userID) about each product whose quantity is BELOW 5 should be shown. Display
		should be done one at a time per product. Allow the user to press N to see the
		next and press X to exit the view.
	*/
void showMyLowProducts(arrItems aItems, int *pItems, int sellID) {
	char letter = 'n';
	int i = 0;
	
	printf("\n\t|  PRODUCT ID  |  \tITEM NAME\t  |  CATEGORY  |  UNIT PRICE  |  QUANTITY  |  \t\tDESCRIPTION\t\t  |\n");
	for (i = 0; (i < *pItems) && (letter != 'X') && (letter != 'x'); i++) {
		if ((aItems[i].sellerID == sellID) && (aItems[i].quantity < 5) && ((letter == 'n') || (letter == 'N'))) {
			printf("\t\t%-10d    %-20s\t%-15s\t%-10.2f\t%-10d\t%30s\n", aItems[i].productID, aItems[i].itemName,
				aItems[i].category, aItems[i].unitPrice, aItems[i].quantity, aItems[i].description);
			do { letter = getch();
			} while ((letter != 'N') && (letter != 'n') && (letter != 'X') && (letter != 'x'));
		}
	}
}







	/*
	
		USER - BUY Functions
	
	*/



	/* This function will load an input arrCart from a <userID>.bag binary file. If the
		file does not yet exist, a blank binary file will be made first. What should be
		"returned" (via pointers) are the contents of the .bag file loaded into the
		array, as well as the number of items in the cart (represented by *nCart).
	*/
void loadCart(int userID, arrCart aCart, int *nCart) {
	FILE *fpCart;
	string20 filename;
	itoa(userID, filename, 10);
	strcat(filename, ".bag");
	*nCart = 0;
	
	if ( (fpCart = fopen(filename, "rb")) != NULL ) {
		while ( fread(&aCart[*nCart], sizeof(structItemType), 1, fpCart) == 1 )
			(*nCart)++;
		fclose(fpCart);
	} else {
		fpCart = fopen(filename, "wb");
		fclose(fpCart);
	}
}



	/* This function will save all the logged items from an arrCart into a binary file
		named <userID>.bag.
	*/
void saveCart(int userID, arrCart aCart, int *nCart) {
	FILE *fpCart;
	int i;
	string20 filename;
	itoa(userID, filename, 10);
	strcat(filename, ".bag");
	
	if ( (fpCart = fopen(filename, "wb")) != NULL ) {
		for (i = 0; i < *nCart; i++)
			fwrite(&aCart[i], sizeof(structItemType), 1, fpCart);
		fclose(fpCart);
	}
}



	// Function Prototype for showProductsBySeller, to be used in viewAllProducts()
		void showProductsBySeller(arrItems aItems, int *nItems, int sellID);



	/* "The program displays all items from 1 seller at a time, sorted in increasing
		order based on seller ID. So, show seller ID first, then followed by a table
		of the products of that seller. The table is similar as the one discussed in
		Show My Products. When the user press N, the next seller ID is shown and under
		it, the table of products of that seller, and so on. The user can press X to
		exit this view and go back to the Buy Menu."
	*/
void viewAllProducts(arrUsers aUsers, int *nUsers, arrItems aItems, int *nItems) {
	int i, currentUserID;
	char letter = 'n';
	for (i = 0; (i < *nUsers) && ((letter != 'x') || (letter != 'X')); i++) {
		currentUserID = aUsers[i].userID;
		showProductsBySeller(aItems, nItems, currentUserID);
		do { letter = getch();
			} while ((letter != 'n') && (letter != 'N') && (letter != 'x') && (letter != 'X'));
	}
}



	/* This function accepts a seller ID input and displays all products sold by that
		seller. "...the program displays the seller’s ID and below it the table of
		that seller’s products (the table is in same format as [...] Show My Products)."
		
			Additional feature: this function will first count how many products a
				certain user is selling. If the number is at least 1, their products are
				displayed. Otherwise, the function will print an error message.
	*/
void showProductsBySeller(arrItems aItems, int *nItems, int sellID) {
	int i, prodCount = 0;
	
	printf("Seller ID: %d\n", sellID);
	for (i = 0; i < *nItems; i++)
		if (aItems[i].sellerID == sellID)
			prodCount++;
	
	if (prodCount > 0) {
		printf("\t|  PRODUCT ID  |  \tITEM NAME\t  |  CATEGORY  |  UNIT PRICE  |  QUANTITY  |\n");
		for (i = 0; i < *nItems; i++) {
			if (aItems[i].sellerID == sellID) {
				printf("\t\t%-10d    %-20s\t%-15s\t%-10.2f\t%-10d\n", aItems[i].productID, aItems[i].itemName,
					aItems[i].category, aItems[i].unitPrice, aItems[i].quantity);
			}
		}
	} else printf("This user is not selling anything!\n");
}


/* This function accepts a category the user wants to see. "Product info display should

	be similar to showMyLowProducts, including typing N and X to navigate through the
	display. Only those products that fit the given category should be displayed."
*/
void searchByCategory(arrItems aItems, int *nItems, string15 categKey) {
	char letter = 'n';
	int i;
	printf("\t|  PRODUCT ID  |  ITEM NAME  |  CATEGORY  |  UNIT PRICE  |  QUANTITY  |\n");
	for (i = 0; (i < *nItems) && (letter != 'x'); i++) {
		if ( strcmp(aItems[i].category, categKey) == 0 ) {
			printf("\t%-10d\t%-20s\t%-15s\t%-10.2f\t%-10d\n", aItems[i].productID, aItems[i].itemName,
				aItems[i].category, aItems[i].unitPrice, aItems[i].quantity);
			do { letter = getch();
				} while ((letter != 'n') && (letter != 'x'));
		}
	}
}



/* This function accepts keywords of the product the user wants to see. Note that
	substring search is applied here [...]. Those that match, the info display should
	be similar to showMyLowProducts, including typing N and X to navigate through the
	display.
*/
void searchByName(arrItems aItems, int *nItems, string20 searchKey) {
	char letter = 'n';
	int i;
	printf("\t|  PRODUCT ID  |  ITEM NAME  |  CATEGORY  |  UNIT PRICE  |  QUANTITY  |\n");
	for (i = 0; (i < *nItems) && (letter != 'x'); i++) {
		if ( strstr(aItems[i].itemName, searchKey) != NULL ) {
			printf("\t%-10d\t%-20s\t%-15s\t%-10.2f\t%-10d\n", aItems[i].productID, aItems[i].itemName,
				aItems[i].category, aItems[i].unitPrice, aItems[i].quantity);
			do { letter = getch();
				} while ((letter != 'n') && (letter != 'x'));
		}
	}
}



	/* This function returns the index of a searched product ID. If the product ID
		could not be found, this returns -1 instead. To be used in BUY:addToCart.
	*/
int doesItemExist(arrItems aItems, int *nItems, int prodID) {
	int i;
	for (i = 0; i < *nItems; i++)
		if (aItems[i].productID == prodID)
			return i;
	return -1;
}



	/* "The user is asked to input the productID and the quantity that the user wants to
		buy. Note that: the productID should be existing, the quantity should also be
		available, and a buyer cannot buy his own product. Otherwise, error messages
		will be displayed and item is not added to the cart." (abridged)
		
		conditions:
			- item must exist ==> product id must match an item in the array
			- quantity bought must be less than or equal to the current item
			- buyer's current id is not the same as the seller id
			- DON'T FORGET: check if item also exists in the cart, add qty if so
	*/
void addToCart(arrCart aCart, int *nCart, arrItems aItems, int *nItems, int userID) {
	int tempProdID, prodQty;
	int productIndex, i = 0, done = 0;
	char dump;
	
	if (*nCart < 10) {
		printf("Enter product ID to buy from and quantity to buy: ");
		scanf("%d%c%d%c", &tempProdID, &dump, &prodQty, &dump);
		productIndex = doesItemExist(aItems, nItems, tempProdID);
		if ( (productIndex != -1) && (aItems[productIndex].quantity >= prodQty) && (aItems[productIndex].sellerID != userID) ) {
			for (i = 0; i < *nCart; i++)
				if (aCart[i].productID == tempProdID) { // if item already exists in the cart
					aCart[i].quantity += prodQty; // just add to quantity
					done = 1;
				}
			if ((done == 0) && (i == *nCart)) { // otherwise, if item doesn't exist yet in the cart
				aCart[*nCart] = aItems[productIndex]; // copy over the whole struct
				aCart[*nCart].quantity = prodQty; // but edit only the quantity
				(*nCart)++; // increment the counter
			}
			printf("Product ID %d added to cart. You now have %d items in your cart.\n", tempProdID, *nCart);
		} else printf("Error! Product ID doesn't exist, or you're buying too much, or you're buying from your own products!\n");
	} else printf("Cart is full! Please edit your cart or check out first before adding more items.\n");
}



	/* This function just displays the number of items found in the cart
		in a table format. Used in BUY:editCart.
	*/
void displayCart(arrCart aCart, int *nCart) {
	int i;
	printf("\t|  PRODUCT ID  |  ITEM NAME  |  CATEGORY  |  UNIT PRICE  |  QUANTITY  |\n");
	for (i = 0; i < *nCart; i++)
		printf("\t%-10d\t%-20s\t%-15s\t%-10.2f\t%-10d\n", aCart[i].productID, aCart[i].itemName,
			aCart[i].category, aCart[i].unitPrice, aCart[i].quantity);
}



	/* This function will remove a single item from the cart. The user will be asked for
		to input the product ID of the item they want to delete. The product (if it
		exists) will be deleted from the cart array and the rest of the items will be
		adjusted accordingly to ensure that there are no garbage values. The cart's
		counter will be decremented accordingly. Used in BUY:editCart.
	*/
void removeItemFromCart(arrCart aCart, int *nCart, int delProdID) {
		// variable delcarations
	int i, cartIndex = -1;
	
		// searching for product in cart and recording index in cart
	for (i = 0; i < *nCart; i++)
		if (aCart[i].productID == delProdID)
			cartIndex = i;
	
		// moving all items after item deleted a space backward (and decrement counter)
	if (cartIndex != -1) {
		for (i = cartIndex; i < *nCart; i++)
			aCart[i] = aCart[i+1];
		(*nCart)--;
	} else printf("Specific item not found! Quitting...\n");
}



	/* This function will remove all items by a specified seller from the cart. This is
		done through looping calls to removeItemFromCart(). Used in BUY:editCart.
	*/
void removeSellerFromCart(arrCart aCart, int *nCart, int delSellID) {
	int i;
	for (i = 0; i < *nCart; i++)
		if (aCart[i].sellerID == delSellID)
			removeItemFromCart(aCart, nCart, aCart[i].productID);
}



	/* Edit Cart: All items in the Cart will be displayed first following the display
		format described in Show All Products by a Specific Seller (of course, no input
		seller ID is necessary).
			- Remove all items from Seller - The user is asked to input the seller ID.
				All items in the cart that is sold by this seller is deleted from the cart.
			- Remove Specific Item - The user is asked to input the product ID. That item
				in the cart will be removed.
			- Edit Quantity - The user is asked to input the product ID and the new
				quantity. The item’s quantity is updated.
			- Finish Edit Cart - The program goes back to Buy Menu.
	*/
void editCart(arrCart aCart, int *nCart) {
	int edCartOpt = 1, tempSellIDdel, tempProdID, tempQuan, i;
	char dump;
	
		// display table
	displayCart(aCart, nCart);
	
		// edit cart menu
	while (edCartOpt != 4) {
		printf("\t\tSelect option:\n");
		printf("\t\t\t1: Remove All Items from a Seller\n");
		printf("\t\t\t2: Remove a Specific Item\n");
		printf("\t\t\t3: Edit Quantity\n");
		printf("\t\t\t4: Finish Edit Cart\n");
		scanf("%d%c", &edCartOpt, &dump);
		
		switch(edCartOpt) {
			case 1: { printf("\t\t\tRemove All Items from a Seller selected. Input seller ID to delete...\n");
				scanf("%d%c", &tempSellIDdel, &dump);
				removeSellerFromCart(aCart, nCart, tempSellIDdel);
				break;
			}
			case 2: { printf("\t\t\tRemove Specific Item selected. Please input product ID to delete: \n");
				scanf("%d%c", &tempProdID, &dump);
				removeItemFromCart(aCart, nCart, tempProdID);
				break;
			}
			case 3: { printf("\t\t\tEdit Quantity selected. Input product ID and quantity: \n");
				scanf("%d %d%c", &tempProdID, &tempQuan, &dump);
				for (i = 0; i < *nCart; i++)
					if (aCart[i].productID == tempProdID)
						aCart[i].quantity = tempQuan;
				break;
			}
			case 4: { printf("\t\t\tReturning to Buy Menu...\n"); break;
			}
		}
	}
}



	/* This function will take an input structTransacType and save it to the binary file
		Transactions.dat.
	*/
void saveTransac(structTransacType *pTran) {
	FILE *fp;
	
	if ( (fp = fopen("Transactions.dat", "ab")) != NULL ) {
		fwrite(pTran, sizeof(structTransacType), 1, fp);
		fclose(fp);
	} else printf("Error appending to file!\n");
}



	/* Function prototype for checkoutSeller() */
void checkOutSeller(arrUsers aUsers, int *nUsers, arrCart aCart, int *nCart, arrItems aItems, int *nItems, int userID, structTransacType *pTran, int tempSellID);


	/* All: All items in the Cart will be bought by the user.
		- Each transaction will contain all items from the same seller only.
		A display of summary of each transaction should be displayed on the screen in a
		table format, listing the quantity, product ID, item name, unit price, and
		total price for item. Below it, the total amount due for the transaction and
		payable to sellerID and seller name will be shown. Transaction info will be
		added to Transactions.dat. Items bought should be removed from the cart and
		product quantity must also be updated in the Items array.
	*/
void checkOutAll(arrUsers aUsers, int *nUsers, arrCart aCart, int *nCart, arrItems aItems, int *nItems, int userID, structTransacType *pTran) {
	int i, currSellID;
	
	for (i = *nCart; i >= 0; i--) {
		currSellID = aCart[i].sellerID;
		checkOutSeller(aUsers, nUsers, aCart, nCart, aItems, nItems, userID, pTran, currSellID);
	}
}



	/* By a Specific Seller: The user is asked to input the seller ID whose items in cart
		he wishes to check out. A summary of the transaction is shown, transaction data
		is added to the binary file, items bought should be removed from the cart,
		quantity in Items array should be updated.
	*/
void checkOutSeller(arrUsers aUsers, int *nUsers, arrCart aCart, int *nCart, arrItems aItems, int *nItems, int userID, structTransacType *pTran, int tempSellID) {
	int i, j, prodIndex, found = 0, tranCount = 0; // tranCount is the number of items in the transaction
	string20 sellerName;
	(*pTran).totalAmount = 0.0;
	(*pTran).buyerID = userID;
	
	for (i = 0; (i <= *nCart) && (tranCount < 5); i++) {
		found = 0;
		if (aCart[i].sellerID == tempSellID) {
			prodIndex = i;
			found = 1;
		}
		if (found) {
				// add to transaction
			(*pTran).totalAmount += (aCart[prodIndex].quantity * aCart[prodIndex].unitPrice);
			(*pTran).itemList[tranCount] = aCart[prodIndex];
			(*pTran).sellerID = aCart[prodIndex].sellerID;
			
				// update quantity in Items
			for (j = 0; j < *nItems; j++)
				if (aItems[j].productID == aCart[prodIndex].productID)
					aItems[j].quantity -= aCart[prodIndex].quantity;
			
				// remove item from cart
			for (j = prodIndex; j < (*nCart)-1; j++)
				aCart[j] = aCart[j+1];
			(*nCart)--;
			
			tranCount++;
		}
	}
	
		// looking for seller's name in aUsers
	for (i = 0; i < *nUsers; i++)
		if ((*pTran).itemList[0].sellerID == aUsers[i].userID)
			strcpy(sellerName, aUsers[i].name);
	
		// receipt display
	printf("Transaction Summary:\n");
	printf("**********************************************************\n");
	printf("| QUANTITY | PRODUCT ID | UNIT PRICE | TOTAL PRICE |\n");
	for (i = 0; i < tranCount; i++)
		printf("| %-8d | %10d | %8.2f | %9.2f |\n", (*pTran).itemList[i].quantity,
			(*pTran).itemList[i].productID, (*pTran).itemList[i].unitPrice,
			(*pTran).itemList[i].quantity * (*pTran).itemList[i].unitPrice);
	printf("**********************************************************\n");
	printf("Total Amount Due: %.2f\n", (*pTran).totalAmount);
	printf("Paid by ID %d to seller %s (ID %d)\n", (*pTran).buyerID, sellerName, (*pTran).sellerID);
	printf("**********************************************************\n");
	printf("\n");
	
		// fwrite to binary
	saveTransac(pTran);
}



	/* Specific Item: The user is asked to input the product ID of the item he had
		included in the cart to check out. A summary/receipt is displayed, transaction
		is added in the binary file, item should be removed from the cart, and quantity
		should be updated in Items array.
	*/
void checkOutOneItem(arrUsers aUsers, int *nUsers, arrCart aCart, int *nCart, arrItems aItems, int *nItems, int userID, structTransacType *pTran, int tempProdID) {
	int i, prodIndex, found = 0;
	string20 sellerName;
	(*pTran).totalAmount = 0;
	
	for (i = 0; i < *nCart; i++)
		if (aCart[i].productID == tempProdID) {
			prodIndex = i;
			found = 1;
		}
	
	if (found) {
			// filling up transac
		(*pTran).buyerID = userID;
		(*pTran).totalAmount += (aCart[prodIndex].quantity*aCart[prodIndex].unitPrice);
		(*pTran).itemList[0] = aCart[prodIndex];
		(*pTran).sellerID = aCart[prodIndex].sellerID;
		
			// looking for seller's name in aUsers
		for (i = 0; i < *nUsers; i++)
			if ((*pTran).itemList[0].sellerID == aUsers[i].userID)
				strcpy(sellerName, aUsers[i].name);
		
			// receipt display
		printf("Transaction Summary:\n");
		printf("**********************************************************\n");
		printf("| QUANTITY | PRODUCT ID | UNIT PRICE | TOTAL PRICE |\n");
		printf("| %-8d | %10d | %8.2f | %9.2f |\n", (*pTran).itemList[i].quantity,
			(*pTran).itemList[i].productID, (*pTran).itemList[i].unitPrice,
			(*pTran).itemList[i].quantity * (*pTran).itemList[i].unitPrice);
		printf("**********************************************************\n");
		printf("Total Amount Due: %.2f\n", (*pTran).totalAmount);
		printf("Paid by ID %d to seller %s (ID %d)\n", (*pTran).buyerID, sellerName, (*pTran).sellerID);
		printf("**********************************************************\n");
		printf("\n");
		
			// fwrite to binary
		saveTransac(pTran);
		
			// remove item from cart
		for (i = prodIndex; i < (*nCart)-1; i++)
			aCart[i] = aCart[i+1];
		(*nCart)--;
		
			// update quantity in Items
		for (i = 0; i < *nItems; i++)
			if (aItems[i].productID == aCart[prodIndex].productID)
				aItems[i].quantity -= aCart[prodIndex].quantity;
	} else printf("Product not found! Exiting...\n");
}



	/* This function takes an input cart and tries to update two aspects: item quantity
		and price. The function will check if cart's quantity is GREATER THAN current
		available quantity, and it will also check if the price matches the current price.
		The buyer is given notice that he can still go to Edit Cart.
			- if quantity is greater, set cart.quantity to max possible
			- if price is different, update cart.price to current price
		If either change was done, the user will be notified of the update/s.
			- show old vs new
	*/
void updateCart(arrCart aCart, int *nCart, arrItems aItems, int *nItems) {
	int i, j;
	
	for (i = 0; i < *nCart; i++)
		for (j = 0; j < *nItems; j++) {
				// checking and updating qty
			if ((aCart[i].productID == aItems[j].productID) && (aCart[i].quantity > aItems[j].quantity)) {
				printf("\tUpdating quantity for product ID %d.\n", aCart[i].productID);
				printf("\tOld quantity: %d; Updated quantity: %d\n", aCart[i].quantity, aItems[j].quantity);
				aCart[i].quantity = aItems[j].quantity;
			}
				// checking and updating price
			if ((aCart[i].productID == aItems[j].productID) && (aCart[i].unitPrice != aItems[j].unitPrice)) {
				printf("\tUpdating price for product ID %d.\n", aCart[i].productID);
				printf("\tOld price: %.2f; Updated price: %.2f\n", aCart[i].unitPrice, aItems[j].unitPrice);
				aCart[i].unitPrice = aItems[j].unitPrice;
			}
		}
	printf("You may still return to Edit Cart to edit your selection!\n\n");
}



	/* Check Out Menu: Get the date as input from the user. Note that one final check
		is done with the availability (because part of the items to be checked out might
		have been saved in the past, but the seller might have updated the information
		already (like quantity and price)).
			- check if each item in the cart are up-to-date (price)
				- if no, update each item with the new price
				- also display the old vs new price
			- check if each item in the cart are up-to-date (quantity)
				- if no, update it to the max that the seller can sell
				- also display the old vs new quantity
	*/
void checkOutMenu(arrUsers aUsers, int *nUsers, arrCart aCart, int *nCart, arrItems aItems, int *nItems, int userID) {
	int chkMenuOpt = 0, tempProdID, tempSellID;
	char dump;
	structTransacType transac;
	
	printf("enter today's date (YYYY MM DD): ");
	scanf("%d %d %d%c", &transac.date.year, &transac.date.month, &transac.date.day, &dump);
	
		// recheck for cart updates!
	updateCart(aCart, nCart, aItems, nItems);
	
		// menu
	while (chkMenuOpt != 4) {
		printf("\t\tSelect option:\n");
		printf("\t\t\t1: Check Out All Items\n");
		printf("\t\t\t2: Check Out All Items By a Seller\n");
		printf("\t\t\t3: Check Out One Item\n");
		printf("\t\t\t4: Exit Check Out\n");
		scanf("%d%c", &chkMenuOpt, &dump);
		
		switch(chkMenuOpt) {
			case 1: { printf("\t\t\tCheck Out All Items selected.\n");
				checkOutAll(aUsers, nUsers, aCart, nCart, aItems, nItems, userID, &transac);
				break;
			}
			case 2: { printf("\t\t\tCheck Out All Items By a Seller selected.\n");
				printf("Enter seller ID to check out: ");
				scanf("%d%c", &tempSellID, &dump);
				checkOutSeller(aUsers, nUsers, aCart, nCart, aItems, nItems, userID, &transac, tempSellID);
				break;
			}
			case 3: { printf("\t\t\tCheck Out One Item selected.\n");
				printf("Enter product ID to check out: ");
				scanf("%d%c", &tempProdID, &dump);
				checkOutOneItem(aUsers, nUsers, aCart, nCart, aItems, nItems, userID, &transac, tempProdID);
				break;
			}
			case 4: { printf("\t\t\tReturning to Buy Menu...\n"); break;
			}
		}
	}
}





	/*
	
		ADMIN Functions
	
	*/



	/* This function loads the array of admins with info from the binary file
		adminLog.dat.
	*/
void loadAdmin(arrAdmin aAdmin, int *adminCount) {
	FILE *fp;
	
	if ( (fp = fopen("adminLog.dat", "rb")) != NULL ) {
		*adminCount = 0;
		while ( fread(&aAdmin[*adminCount], sizeof(structAdminType), 1, fp) == 1 )
			(*adminCount)++;
		fclose(fp);
	} else printf("adminLog.dat is not found!\n");
}



	/* This function saves the contents of aAdmin into the binary file adminLog.dat.
	*/
void saveAdmin(arrAdmin aAdmin, int adminCount) {
	FILE *fp;
	int i;
	
	if ( (fp = fopen("adminLog.dat", "wb")) != NULL ) {
		for (i = 0; i < adminCount; i++)
			fwrite(&aAdmin[i], sizeof(structAdminType), 1, fp);
		fclose(fp);
	} else printf("adminLog.dat could not be written!\n");
}



	/* This function checks if the admin's input ID is valid. That is, the input ID has
		not been taken by some other existing admin. Returns 0 if there is, otherwise
		return 1 (admin may resume registering).
	*/
int checkAdLogIn(arrAdmin aAdmin, int *adminCount, int adIDinput) {
	int i;
	
	for(i = 0; i <= (*adminCount); i++)
		if (adIDinput == aAdmin[i].adminID)
			return 0;
	return 1;
}



	/* This function registers a new admin to store into the array of admins. Before the
		user can sign up, they must enter the master key "H3LLo?". Then, the user may
		register their info.
	*/
void registerAdmin(arrAdmin *aAdmin, int *adminCount) {
	string10 mainAdPass;
	int tempAdID;
	char dump;
	
	printf("Enter main admin key: ");
	fgets(mainAdPass, 11, stdin);
		mainAdPass[ strlen(mainAdPass)-1 ] = '\0';
	
	if ( strcmp(mainAdPass, AD_PASS) == 0 ) {
		printf("Key successful. \n");
		printf("Enter admin ID: ");
		scanf("%d%c", &tempAdID, &dump);
		
		if (checkAdLogIn(*aAdmin, adminCount, tempAdID)) {
			(*aAdmin)[*adminCount].adminID = tempAdID;
			printf("Enter password: ");
			fgets((*aAdmin)[*adminCount].adPass, 11, stdin);
				(*aAdmin)[*adminCount].adPass[ strlen((*aAdmin)[*adminCount].adPass)-1 ] = '\0';
			printf("Enter name: ");
			fgets((*aAdmin)[*adminCount].adName, 21, stdin);
				(*aAdmin)[*adminCount].adName[ strlen((*aAdmin)[*adminCount].adName) - 1] = '\0';
			
			(*adminCount)++;
		} else printf("Admin ID already exists!\n");
	} else printf("Unauthorised!\n");
}



	/* This function takes an ID and password input. If log in was successful, return the
		index of the admin's slot. Otherwise, log in fails.
	*/
int adminLogIn(arrAdmin aAdmin, int *adminCount, int adID, string10 adPass) {
	int i;
	for (i = 0; i < *adminCount; i++)
		if ( (adID == aAdmin[i].adminID) && (strcmp(adPass, aAdmin[i].adPass) == 0) ) {
			printf("\tLog in successful!\n");
			return i;
		}
	printf("\tLog in unsuccessful!\n");
	return -1;
}



	/* This function will take the array of users and prints all the information
		out in a table format.
			NOTES: fix formatting of table.
	*/
void displayAllUsers(arrUsers aUsers, int *nUsers) {
	int i;
	printf("\t| USERNAME |   PASSWORD   | \t   NAME   \t | \t\tADDRESS\t\t | CONTACT NO |\n");
	for (i = 0; i < *nUsers; i++)
		printf("\t %10d  %-10s\t    %-20s   %-30s  %10.0lf \n", aUsers[i].userID,
			aUsers[i].password, aUsers[i].name, aUsers[i].address,
			aUsers[i].contactNo);
	printf("\n");
}



	/* This function will take the array of users and the array of items and prints out
		all users who are selling items along with how many products they are selling.
		This will all be done in a table format.
	*/
void displayAllSellers(arrUsers aUsers, int *nUsers, arrItems aItems, int *nItems) {
	int i = 0, j = 0, currSeller, itemSellCount = 0;
	
		// sort all items by seller ID, and all users by user ID
	sortSellID(aItems, nItems);
	sortUserID(aUsers, nUsers);
	
	printf("\t| USERNAME |   PASSWORD   | \t   NAME   \t | \t\tADDRESS\t\t | CONTACTNO | ITEM COUNT |\n");
		// reading
	for (i = 0; i < *nUsers; i++) {
		currSeller = aUsers[i].userID;
		itemSellCount = 0;
		
		while (aItems[j].sellerID == currSeller) {
				itemSellCount++;
				j++;
		}
		
		if (itemSellCount > 0) {
			printf("\t %10d  %-10s\t    %-20s   %-30s  %10.0lf  %10d\n", aUsers[i].userID,
			aUsers[i].password, aUsers[i].name, aUsers[i].address,
			aUsers[i].contactNo, itemSellCount);
		}
	}
	printf("\n");
}



	/* This function takes in three input dates, the first two make the range while the
		third one is being tested. The function checks if the third date is falls between
		the range of the first two dates. This is done by converting the three dates into
		a time_t format, then doing comparison on them. Note that the starting and ending
		dates are also included in the range. This function returns 1 if it falls in
		between, otherwise it returns 0.
	*/
int isDateInRange(structDateType startDate, structDateType endDate, structDateType inputDate) {
	struct tm startStruc, endStruc, inputStruc;
	time_t start, end, input;
	
	startStruc.tm_year = startDate.year - 1900;
	startStruc.tm_mon = startDate.month - 1;
	startStruc.tm_mday = startDate.day;
	startStruc.tm_hour = startStruc.tm_min = startStruc.tm_sec = 0;
	endStruc.tm_year = endDate.year - 1900;
	endStruc.tm_mon = endDate.month - 1;
	endStruc.tm_mday = endDate.day;
	endStruc.tm_hour = endStruc.tm_min = endStruc.tm_sec = 0;
	inputStruc.tm_year = inputDate.year - 1900;
	inputStruc.tm_mon = inputDate.month - 1;
	inputStruc.tm_mday = inputDate.day;
	inputStruc.tm_hour = inputStruc.tm_min = inputStruc.tm_sec = 0;
	
	startStruc.tm_isdst = endStruc.tm_isdst = inputStruc.tm_isdst = -1;
	
	start = mktime(&startStruc);
	end = mktime(&endStruc);
	input = mktime(&inputStruc);
	
	if ((input >= start) && (input <= end))
		return 1;
		else return 0;
}



	/* Given two dates to serve as the start and end dates, this function will check the
		contents of Transactions.dat which transactions occurred between the start and end
		dates, and show the total amount of all the transactions.
	*/
void showTotalSales(structDateType startDate, structDateType endDate) {
	FILE *fpTran;
	structTransacType tempTrans;
	float totalTran = 0.0;
	
	if ( (fpTran = fopen("Transactions.dat", "rb")) != NULL ) {
		while (fread(&tempTrans, sizeof(structTransacType), 1, fpTran) == 1)
			if ( isDateInRange(startDate, endDate, tempTrans.date) ) {
				totalTran += tempTrans.totalAmount;
			}
		fclose(fpTran);
		printf("\n\t\tTotal amount from transactions = %.2f\n\n", totalTran);
	} else printf("Transations.dat is not found!\n\n");
}



	/* Given two dates to serve as the start and end dates, this function will check the
		contents of Transactions.dat which transactions occurred between the start and end
		dates, and display the total sales for each seller in the following table format:
		seller ID, seller name, total sales in the duration.
	*/
void showSellerSales(structDateType startDate, structDateType endDate, arrUsers aUsers, int *nUsers) {
	FILE *fp;
	structTransacType tempTrans;
	int i, tempSellerID;
	float totalSales = 0.0;
	string20 sellerName;
	
	printf("\n\t| SELLER ID | \tSELLER NAME\t | \tTOTAL SALES\t |\n");
	if ( (fp = fopen("Transactions.dat", "rb")) != NULL ) {
		for (i = 0; i < *nUsers; i++) {
			tempSellerID = aUsers[i].userID; // take the next seller
			strcpy(sellerName, aUsers[i].name);
			fseek(fp, 0, SEEK_SET); // move all the way to the start of the bin file
			totalSales = 0.0; // reset the value
			while (fread(&tempTrans, sizeof(structTransacType), 1, fp) == 1) { // read every transaction
				if ( (tempTrans.sellerID == tempSellerID) && isDateInRange(startDate, endDate, tempTrans.date) )
					totalSales += tempTrans.totalAmount;
			}
			if (totalSales > 0.0)
				printf("\t| %10d | %20s | %18.2f |\n", tempSellerID, sellerName, totalSales);
		}
		fclose(fp);
		printf("\n");
	} else printf("Transations.dat is not found!\n\n");
}



	/* Given two dates to serve as the start and end dates, this function will check the
		contents of Transactions.dat which transactions occurred between the start and end
		dates, and display the total amount for each buyer in the following table format:
		buyer ID, buyer name, total amount bought in the duration
	*/
void showShopaholics(structDateType startDate, structDateType endDate, arrUsers aUsers, int *nUsers) {
	FILE *fp;
	structTransacType tempTrans;
	int i, tempBuyerID;
	float totalBought = 0.0;
	string20 buyerName;
	
	printf("\n\t| BUYER ID | BUYER NAME | AMOUNT BOUGHT |\n");
	if ( (fp = fopen("Transactions.dat", "rb")) != NULL ) {
		for (i = 0; i < *nUsers; i++) {
			tempBuyerID = aUsers[i].userID; // take the next buyer
			strcpy(buyerName, aUsers[i].name);
			fseek(fp, 0, SEEK_SET); // move all the way to the start of the bin file
			totalBought = 0.0; // reset the value
			while (fread(&tempTrans, sizeof(structTransacType), 1, fp) == 1) { // read every transaction
				if ( (tempTrans.buyerID == tempBuyerID) && isDateInRange(startDate, endDate, tempTrans.date) )
					totalBought += tempTrans.totalAmount;
			}
			if (totalBought > 0.0)
				printf("\t| %10d | %20s | %18.2f |\n", tempBuyerID, buyerName, totalBought);
		}
		fclose(fp);
		printf("\n");
	} else printf("Transations.dat is not found!\n\n");
}



	/*
		other functions end here
	*/





int main() {
		// external option variables; must keep separate!
	int optMain = 0;
		int optUser = 1;
			int optBuy = 1, optSell = 1;
		int optAdmin = 1;
	
	
		// other variables for functions
	char dump;
	int userCount = 0, itemCount = 0, cartCount = 0, adminCount = 0; // counters
	int idInput; // identifier for the current user
		string10 passInput; // temp password for logging in
	int adIDInput;
		string10 adPass; // temp password for admin log in
	int chkLog; // index of CURRENT USER!
	int adLog; // index of CURRENT ADMIN!
	int sellerIDView;
	string15 searchCategKey; // search query used in BUY:searchByCategory
	string20 searchNameKey; // search query used in BUY:searchByName
	structDateType startDate, endDate; // start and end dates for ADMIN
	
	
		// array of struct variables
	arrUsers aUsers;
	arrItems aItems;
	arrCart aCart;
	arrAdmin aAdmin;
	
		// initialisation
	loadUsers(aUsers, &userCount);
	loadItems(aItems, &itemCount);
	sortProdID(aItems, &itemCount);
	loadAdmin(aAdmin, &adminCount);
	
	printf("\tWelcome to Prog's Stop'n'Shop!\n");
	
	
		/* MENU */
	while (optMain != 4) { // exit opt
		optUser = 1; optBuy = 1; optSell = 1; optAdmin = 1; // resetting option variables
		sortProdID(aItems, &itemCount); // resorting by product ID
		printf("\nMAIN MENU - Select option:\n");
		printf("\t1: Register User\n\t2: User Menu\n\t3: Admin Menu\n\t4: Exit\n");
		scanf("%d%c", &optMain, &dump);
		
		if (optMain) {
				// resetting choice variabes
			optUser = 1, optBuy = 1, optSell = 1, optAdmin = 1;
			
			switch (optMain) {
				case 1: { printf("Register User selected.\n");
					if (userCount < MAX_USERS)
						registerUser(&aUsers, &userCount);
						else printf("Max users have been reached! Exiting...\n");
				} break;
				
				case 2: { printf("\n\tUSER MENU - LOGIN\n");
					printf("Please enter userID: ");
					scanf("%d%c", &idInput, &dump);
					printf("Please enter password: ");
					fgets(passInput, 11, stdin);
						passInput[ strlen(passInput)-1 ] = '\0';
					
						// checking user credentials here
					chkLog = checkLogIn(idInput, passInput, aUsers, &userCount);
					if (chkLog == -1) break; // if log in fails
					
					while (optUser != 0) { // back opt
						if (optUser >= 0 && optUser <= 2) {
							printf("\nWelcome back, %s!\n", aUsers[chkLog].name);
							
							loadCart(idInput, aCart, &cartCount);
							optBuy = 1, optSell = 1;
							
							printf("\n\tUSER MENU - Select option:\n");
							printf("\t0: Return to main menu\n");
							printf("\t1: Sell Menu\n");
							printf("\t2: Buy Menu\n");
							scanf("%d%c", &optUser, &dump);
							
							switch (optUser) {
								case 0: { printf("Returning to main menu...\n"); break;
								}
								case 1: {
									while (optSell != 0) {
										printf("\n\tUSER SELL MENU - Select option:\n");
										printf("\t\t0: Return to User Menu\n");
										printf("\t\t1: Add New Item\n");
										printf("\t\t2: Edit Stock\n");
										printf("\t\t3: Show My Products\n");
										printf("\t\t4: Show My Low-Stock Products\n");
										scanf("%d%c", &optSell, &dump);
										
										switch (optSell) {
											case 0: { printf("Returning to User Menu...\n"); break;
											}
											case 1: { printf("Add New Item Selected...\n");
												addNewItem(aItems, &itemCount, idInput);
												break;
											}
											case 2: { printf("Edit Stock selected...\n");
												editStock(aItems, &itemCount, idInput);
												break;
											}
											case 3: { printf("Showing your products...\n");
												showMyProducts(aItems, &itemCount, idInput);
												break;
											}
											case 4: { printf("Showing your low-stock products...\n");
												showMyLowProducts(aItems, &itemCount, idInput);
												break;
											}
										}
									}
									
									break;
								}
								case 2: {
									while (optBuy != 0) {
										printf("\n\tUSER BUY MENU - Select option:\n");
										printf("\t\t0: Return to User Menu\n");
										printf("\t\t1: View All Products\n");
										printf("\t\t2: Show all products by a specific seller\n");
										printf("\t\t3: Search product by category\n");
										printf("\t\t4: Search product by name\n");
										printf("\t\t5: Add to cart\n");
										printf("\t\t6: Edit cart\n");
										printf("\t\t7: Check Out Menu\n");
										scanf("%d%c", &optBuy, &dump);
										
										switch (optBuy) {
											case 0: { printf("Exiting Buy Menu...\n");
												saveCart(idInput, aCart, &cartCount);
												break;
											}
											case 1: { printf("Viewing all products...\n");
												viewAllProducts(aUsers, &userCount, aItems, &itemCount);
												break;
											}
											case 2: { printf("Showing all products of a seller...\n");
												printf("Please enter seller's ID: ");
												scanf("%d%c", &sellerIDView, &dump);
												showProductsBySeller(aItems, &itemCount, sellerIDView);
												break;
											}
											case 3: { printf("Searching by category...\n");
												printf("Please enter your search key: ");
												fgets(searchCategKey, 16, stdin);
													searchCategKey[ strlen(searchCategKey)-1 ] = '\0';
												searchByCategory(aItems, &itemCount, searchCategKey);
												break;
											}
											case 4: { printf("Searching by name...\n");
												printf("Please enter your search key: ");
												fgets(searchNameKey, 21, stdin);
													searchNameKey[ strlen(searchNameKey)-1 ] = '\0';
												searchByName(aItems, &itemCount, searchNameKey);
												break;
											}
											case 5: { printf("Add to cart...\n");
												addToCart(aCart, &cartCount, aItems, &itemCount, idInput);
												break;
											}
											case 6: { printf("Edit cart...\n");
												editCart(aCart, &cartCount);
												break;
											}
											case 7: { printf("Check Out Menu...\n");
												checkOutMenu(aUsers, &userCount, aCart, &cartCount, aItems, &itemCount, idInput);
												break;
											}
										}
									}
									break;
								}
							}
						} else printf("Invalid input. Please try again.\n");
					}
				} break;
				
				case 3: { printf("ADMIN MENU - LOGIN\n");
					optAdmin = 1;
					
					printf("Enter admin ID: ");
					scanf("%d%c", &adIDInput, &dump);
					printf("Enter admin password: ");
					scanf("%s%c", adPass, &dump);
					adLog = adminLogIn(aAdmin, &adminCount, adIDInput, adPass);
					if ( adLog == -1 ) break;
					
					while (optAdmin != 0) { // back opt
						printf("Welcome, admin %s!\n", aAdmin[adLog].adName);
						printf("\n\tADMIN MENU - Select option:\n");
						printf("\t\t0: Return to main menu\n");
						printf("\t\t1: Show All Users\n");
						printf("\t\t2: Show All Sellers\n");
						printf("\t\t3: Show Total Sales in Given Duration\n");
						printf("\t\t4: Show Sellers Sales\n");
						printf("\t\t5: Show Shopaholics\n");
						printf("\t\t6: Register New Admin\n");
						scanf("%d%c", &optAdmin, &dump);
						
						switch (optAdmin) {
							case 0: { printf("Returning to main menu...\n"); break;
							}
							case 1: { printf("Displaying all users...\n");
								displayAllUsers(aUsers, &userCount);
								break;
							}
							case 2: { printf("Displaying all sellers...\n");
								displayAllSellers(aUsers, &userCount, aItems, &itemCount);
								break;
							}
							case 3: { printf("Showing total sales in a period...\n");
								printf("Please enter starting date (YYYY MM DD): ");
								scanf("%d %d %d%c", &startDate.year, &startDate.month, &startDate.day, &dump);
								printf("Please enter ending date (YYYY MM DD): ");
								scanf("%d %d %d%c", &endDate.year, &endDate.month, &endDate.day, &dump);
								showTotalSales(startDate, endDate);
								break;
							}
							case 4: { printf("Showing sales...\n");
								printf("Please enter starting date (YYYY MM DD): ");
								scanf("%d %d %d%c", &startDate.year, &startDate.month, &startDate.day, &dump);
								printf("Please enter ending date (YYYY MM DD): ");
								scanf("%d %d %d%c", &endDate.year, &endDate.month, &endDate.day, &dump);
								showSellerSales(startDate, endDate, aUsers, &userCount);
								break;
							}
							case 5: { printf("Showing shopaholics...\n");
								printf("Please enter starting date (YYYY MM DD): ");
								scanf("%d %d %d%c", &startDate.year, &startDate.month, &startDate.day, &dump);
								printf("Please enter ending date (YYYY MM DD): ");
								scanf("%d %d %d%c", &endDate.year, &endDate.month, &endDate.day, &dump);
								showShopaholics(startDate, endDate, aUsers, &userCount);
								break;
							}
							case 6: { printf("Registering new admin...\n");
								if (adminCount < 20)
									registerAdmin(&aAdmin, &adminCount);
									else printf("Max admins reached!\n");
								break;
							}
						}
					}
				} break;
				
				case 4: { printf("\nExiting...\n");
					saveUsers(aUsers, userCount);
					saveItems(aItems, itemCount);
					saveAdmin(aAdmin, adminCount);
				} break;
			}
		} else printf("Invalid input. Please try again.\n");
	}
	return 0;
}
