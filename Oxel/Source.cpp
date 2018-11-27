#include <iostream>
#include <thread>
#include "Oxel.cpp"
using namespace OpenGames::Oxel;
int main()
{
	Oxel oxel;

	oxel.init();

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_" << std::endl;
	std::cout << "Vendor:\t" << vendor << std::endl;
	std::cout << "Renderer:\t" << renderer << std::endl;
	std::cout << "OpenGl version:\t" << version << std::endl;

	std::thread updateThread([&oxel]() -> void {
		double lastTimeMeasure = 0.0;
		while(!oxel.windowShouldClose())
			if(glfwGetTime() - lastTimeMeasure >= oxel.TICK_RATE)
			{
				oxel.update();
				lastTimeMeasure = glfwGetTime();
			}
	});
	while(!oxel.windowShouldClose())
	{
		oxel.render();
	}
	std::cout << "_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_,-=+=-,_" << std::endl;
	std::exit(0);
}