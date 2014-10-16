#pragma once

namespace Assert
{
	enum class FailStatus
	{
		EXIT,
		CONTINUE
	};

	typedef FailStatus(*Handler)(const char* condition, const char* msg, const char* file, int line);

	Handler getHandler();
	void setHandler(Handler handler);

	FailStatus reportFailure(const char* condition, const char* file, int line, const char* msg, ...);
}

#define EXIT() __debugbreak()
#define UNUSED(x) do { (void)sizeof(x); } while(0)

#define ASSERT(condition) \
	do \
	{ \
		if(!(condition)) \
		{ \
			if(Assert::reportFailure(#condition, __FILE__, __LINE__, 0) == Assert::FailStatus::EXIT) \
				EXIT(); \
		} \
	} while(0)

#define ASSERT_MSG(condition, msg, ...)\
	do \
	{ \
		if(!(condition)) \
		{ \
			if(Assert::reportFailure(#condition, __FILE__, __LINE__, (msg), __VA_ARGS__) == Assert::FailStatus::EXIT) \
				EXIT(); \
		} \
	} while(0)

#define VERIFY(condition) ASSERT(condition)

#define VERIFY_MSG(condition, msg, ...) ASSERT_MSG(condition, msg, ##__VA_ARGS__)