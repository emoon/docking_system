#define I3__FILE__ "test.c"

#include "tree.h"
#include "log.h"
#include "workspace.h"
#include "output.h"
#include "con.h"
#include "render.h"
#include <stddef.h>
#include <stdio.h>

void fake_outputs_init(const char *output_spec);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rect rect = { 0, 0, 1024, 768 };

	init_logging();
	tree_init(&rect);

	fake_outputs_init("1024x768+0+0");

	DLOG("Test\n");

	Con* workspace = workspace_get("test_ws", NULL);

    Con *con = tree_open_con(NULL, NULL);
    con->layout = L_SPLITH;
    con_focus(con);

    con = tree_open_con(NULL, NULL);
    con->layout = L_SPLITH;
    con_focus(con);

	tree_render();

	return 0;
}
