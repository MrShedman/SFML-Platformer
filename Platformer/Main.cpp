#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib") 
#pragma comment(lib, "sndfile.lib")
#endif // SFML_STATIC

#define MINX 1280
#define MINY 720

#include <Game.h>

int main()
{
	Game game(MINX, MINY);
	game.run();

	return 0;
}