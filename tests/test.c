#define I3__FILE__ "test.c"

#include "tree.h"
#include "log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rect rect = { 0, 0, 1024, 1024 };

	init_logging();

	DLOG("Test\n");

	tree_init(&rect);

	return 0;
}
