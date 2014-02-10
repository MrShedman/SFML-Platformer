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

#include <Game.h>

int main()
{
	Game game(1280, 720);
	game.run();

	return 0;
}