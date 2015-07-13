#define I3__FILE__ "test.c"

#include "tree.h"
#include "log.h"
#include "workspace.h"
#include <stddef.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rect rect = { 0, 0, 1024, 1024 };

	init_logging();

	tree_init(&rect);

	DLOG("Test\n");

	Con* con = workspace_get("test_ws", NULL);

	printf("%p\n", con);


	return 0;
}
