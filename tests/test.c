#define I3__FILE__ "test.c"

#include "tree.h"
#include "log.h"
#include "workspace.h"
#include "output.h"
#include "con.h"
#include "render.h"
#include <stddef.h>
#include <stdio.h>
#include <MiniFB.h>

void fake_outputs_init(const char *output_spec);

#define WIDTH 1024
#define HEIGHT 768
static unsigned int s_buffer[WIDTH * HEIGHT];

const char* s_outputFormat = "1024x768+0+0";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rect rect = { 0, 0, WIDTH, HEIGHT };

	init_logging();
	tree_init(&rect);

	fake_outputs_init(s_outputFormat);

	DLOG("Test\n");

	Con* workspace = workspace_get("test_ws", NULL);

    Con *con = tree_open_con(NULL, NULL);
    con->layout = L_SPLITH;
    con_focus(con);

    con = tree_open_con(NULL, NULL);
    con->layout = L_SPLITH;
    con_focus(con);

	tree_render();

	if (!mfb_open("i3 docking test", WIDTH, HEIGHT))
		return 0;

	for (;;)
	{
		int state = mfb_update(s_buffer);

		if (state < 0)
			break;
	}

	mfb_close();

	return 0;
}
