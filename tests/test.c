#define I3__FILE__ "test.c"

#include "tree.h"
#include "log.h"
#include "workspace.h"
#include "output.h"
#include "con.h"
#include "render.h"
#include "callbacks.h"
#include <stddef.h>
#include <stdio.h>
#include <MiniFB.h>

void fake_outputs_init(const char *output_spec);

#define WIDTH 1024
#define HEIGHT 768
static unsigned int s_buffer[WIDTH * HEIGHT];

const char* s_outputFormat = "1024x768+0+0";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static uint32_t s_colors[] =
{
    0xffb27474,
    0xffb28050,
    0xffa9b250,
    0xff60b250,

    0xff4fb292,
    0xff4f71b2,
    0xff8850b2,
    0xffb25091,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fillRect(uint32_t* buffer, Rect rect, int width, uint32_t color)
{
    buffer += (rect.y * width) + rect.x;

    for (int y = 0; y < rect.height; ++y)
    {
        for (int x = 0; x < rect.width; ++x)
            buffer[x] = color;

        buffer += width;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void renderCon(Con* con)
{
	static int i = 0;

	fillRect(s_buffer, con->rect, WIDTH, s_colors[i++ & 0x7]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static DockSysCallbacks callbacks =
{
	renderCon,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rect rect = { 0, 0, WIDTH, HEIGHT };

	init_logging();
	tree_init(&rect);

	docksys_set_callbacks(&callbacks);

	fake_outputs_init(s_outputFormat);

	DLOG("Test\n");

	Con* workspace = workspace_get("test_ws", NULL);

    Con *con = tree_open_con(NULL, NULL);
	tree_split(focused, HORIZ);

    con = tree_open_con(NULL, NULL);
    con = tree_open_con(NULL, NULL);

    con_focus(con);

	tree_split(con, VERT);
    con = tree_open_con(NULL, NULL);
    con = tree_open_con(NULL, NULL);

	if (!mfb_open("i3 docking test", WIDTH, HEIGHT))
		return 0;

	tree_render();

	for (;;)
	{
		int state = mfb_update(s_buffer);

		if (state < 0)
			break;
	}

	mfb_close();

	return 0;
}
