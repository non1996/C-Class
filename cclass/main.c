#include "linklist\\linklist.h"

#include <stdio.h>

struct abc {
	int i;
	struct abc *next;
};

struct abc test[4] = { 10, test + 1, 20, test + 2, 30, test + 3, 40, NULL };

int main() {
	int integer[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	linklist *list = new(linklist);

	for (int i = 0; i < 10; ++i)
		invoke(list, push_back, &integer[i]);

	linklist_foreach_begin(int, int_ptr, list) {
		printf("%d, ", *int_ptr);
	}linklist_foreach_end

	delete(list);
}