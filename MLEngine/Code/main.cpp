#include <memory>
#include <thread>
#include "Assert\Assert.h"
#include "Core/Engine.h"
#include "Messages\MessageManager.h"

void ExceptionHandler(const char* message);
int guardedMain();


int main()
{
	mauveassert::Assert::InitExceptionHandler(&ExceptionHandler);
	try{
		guardedMain();
	}
	catch(std::exception e)
	{
		mauveassert::Assert::HandleException(e.what());
	}
#ifdef _DEBUG
	DEBUGWRITEINFO("Closed with no errors", "");
	system("pause");
#endif
	return 0;
}

int guardedMain()
{
	//Do our config
	EngineConfig currentConf;
	currentConf.resX = 1024;
	currentConf.resY = 768;
	float sixtyFPS = (1.0f / 120.0f) * 1000;

	//Make our engine
	Engine currentEngine = Engine();
	currentConf = currentEngine.ReadConfigFile("data\\config\\EngineConfig.json");
	currentEngine.Init(currentConf);
	while(true)
	{
		long timeToWait = (long)sixtyFPS - (long)(glfwGetTime() * 1000);
		if (timeToWait <= 0)
		{
			float delta = (float)glfwGetTime();
			if (!currentEngine.Update(delta))
			{
				break;
			}
			glfwSetTime(0.0f);
		}
		//else
		//{
		//	std::this_thread::yield();
		//}
	}
	return 0;
}

void ExceptionHandler(const char* message)
{
	//Just close it
#ifdef _DEBUG 
	std::cout << "Handling an exception :-)" << message << std::endl;
	system("pause");
#else
	std::stringstream s;
	s << "I'm sorry but I've had to quit due to an error :-(" << std::endl <<std::endl << "Details: " << message;
	MessageBox(
		NULL,
		s.str().c_str(),
		"Mauve lamp has fallen..",
		MB_ICONSTOP
		);
#endif

	std::exit(1);
}