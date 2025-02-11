#include "src/http_core.h"

int main()
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	HashTable table;
	initializeHashTable(&table);

	launch_server(&table);

	freeHashTable(&table);

	return 0;
}
