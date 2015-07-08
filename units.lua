
StaticLibrary {
	Name = "docking_system",

	Env = { CPPPATH = { "include", }, },

	Sources = FGlob {
		Dir = "core",
		Extensions = { ".c", ".h", ".s", ".m" },
		Filters = {
			{ Pattern = "[/\\]windows[/\\]"; Config = { "win32-*", "win64-*" } },
			{ Pattern = "[/\\]macosx[/\\]"; Config = "mac*-*" },
			{ Pattern = "[/\\]x11[/\\]"; Config = { "x11-*" } },
		},

		Recursive = true,
	},

	Propagate = {
		Libs = {
			"user32.lib"; Config = "win32-*",
			"ws2_32.lib"; Config = "win32-*",
			"gdi32.lib"; Config = "win32-*",
		},

		Frameworks = { "Cocoa" },
	},
}

Program {

	Name = "test",

	Env = { CPPPATH = { "include", }, },

	Depends = { "docking_system" },
	Sources = { "tests/test.c" }, 

	Libs = { "X11"; Config = "x11-*" },
}

Default "test"
