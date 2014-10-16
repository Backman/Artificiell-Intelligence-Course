#include "Assert.h"
#include <cstdio>
#include <cstdarg>

namespace Assert
{
	FailStatus defaultHandler(const char* condition, const char* msg, const char* file, int line)
	{
		std::printf("%s(%d): Assert Failure: ", file, line);

		if (condition != NULL)
		{
			std::printf("'%s' ", condition);
		}

		if (msg != NULL)
		{
			std::printf("%s", msg);
		}

		std::printf("\n");

		return FailStatus::EXIT;
	}

	Handler& getAssertHandlerInstance()
	{
		static Handler handler = &defaultHandler;
		return handler;
	}

	Handler getHandler()
	{
		return getAssertHandlerInstance();
	}

	void setHandler(Handler handler)
	{
		getAssertHandlerInstance() = handler;
	}

	FailStatus reportFailure(const char* condition, const char* file, const int line, const char* msg, ...)
	{
		const char* message = NULL;
		if (msg != NULL)
		{
			char msgBuf[1024];
			va_list args;
			va_start(args, msg);
			vsnprintf_s(msgBuf, 1024, msg, args);
			va_end(args);

			message = msgBuf;
		}

		return getAssertHandlerInstance()(condition, message, file, line);
	}
}