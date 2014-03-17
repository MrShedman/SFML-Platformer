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

#include <Application.h>

int main()
{
	Application app(1280, 720);
	app.run();
	
	return 0;
}