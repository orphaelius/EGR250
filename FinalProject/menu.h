#define MENUOPT 16
#define CHARMAX 100

/*******************************************************************************
	Function: showMenu()
	Description: Displays menu options
	Parameters: ---
	Return: ---
*******************************************************************************/
void showMenu(void) { 
	printf("");
	char menuOptions[MENUOPT][CHARMAX] = {
		"Enter (1) to display all data",
		"Enter (2) to display only stock name, CEO, and location data",
		"Enter (3) to search for a stock by symbol",
		"Enter (4) to search for a portion of any stock/company name",
		"Enter (5) to display stocks that have a higher current price than user entry",
		"Enter (6) to display stocks that have diminished in value since purchase",
		"Enter (7) to display stocks that have increased in value since purchase",
		"Enter (8) to display stock symbols and value change by percentage since purchase",
		"Enter (9) to display portfolio value by individual stock and total sum",
		"Enter (10) to search for stocks by location data",
		"Enter (11) to search by CEO name",
		"Enter (12) to search by CEO comp ranges",
		"Enter (13) to display CEO who has the greatest total comp",
		"Enter (14) to display the CEO with the lowest total comp",
		"Enter (15) to replace CEO name and total comp package", 
		"Enter (-1) to EXIT program",
	};	
	
	for (size_t i = 0; i < MENUOPT; ++i) {
		printf("%s\n", menuOptions[i]);
	}

	printf("Menu option: "); 
} // End showMenu()
 
