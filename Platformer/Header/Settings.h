#pragma once

struct Settings
{
	Settings(bool vSync, unsigned int frameLimit, bool keyRepeat, bool fullScreen)
		:
	vSync(vSync),
	frameLimit(frameLimit),
	keyRepeat(keyRepeat),
	fullScreen(fullScreen)

	{}

	bool vSync;
	unsigned int frameLimit;
	bool keyRepeat;
	bool fullScreen;
};