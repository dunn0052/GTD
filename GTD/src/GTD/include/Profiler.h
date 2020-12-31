#pragma once

// View data by dragging JSON file to a chrome://tracing

/* Usage: Begin timing sessions by calling Instrumentor::Get().BeginSession($SESSON_NAME$, $JSON_OUTPUT_PATH$);*/
/* End session by calling  Instrumentor::Get().EndSession() */
/* 
 Notes: If program dies before EndSession() is called, the function data will still be available, 
 but will be missing a ]} at the end of the file. Append a ]} at the end and it will fix this issue. 
 This cannot be controlled as destructors are not called upon a program being killed.
 */

/* 
    Place a PROFILE_FUNCTION in any function once the Instrumentor is active 
    to get info on when that function was called and how long it took.
	Note that putting this in every function may result in a json file too big to be opened.
	To time a specific section of a function you can limit the scope by enclosing
	the PROFILE_SCOPE($your_scope_name$) just to its own scope by adding {} around
	the scope you want tested.
*/

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

// Profiling on 1; Profilling off 0
#define PROFILING 1
#if PROFILING

// Windows has __FUNCSIG__, Linux is __PRETTY_FUNCTION__
#ifdef MS_WIN
#define FUNCTION_SIG __FUNCSIG__
#elif defined(__unix__) //linux
#define FUNCTION_SIG __PRETTY_FUNCTION__
#endif

// Macros to get function signatures in the JSON
#define PROFILE_SCOPE( NAME ) Timer timer##_LINE_( NAME )
#define PROFILE_FUNCTION() PROFILE_SCOPE(FUNCTION_SIG)

#else

// If profiling is set to 0, disabled, don't compile
#define PROFILE_SCOPE( NAME )
#define PROFILE_FUNCTION()
#endif


struct ProfileResult
{
	std::string Name;
	size_t Start;
	size_t End;
	size_t ThreadID;
};

struct ProfileSession
{
	std::string Name;
};

class Profile
{

private:
	ProfileSession * current_session;
	std::ofstream json_stream;
	int profileCount;
	bool closed;

	/* private constructor since only the singleton instance exists */
	Profile()
		:current_session(nullptr), profileCount(0), closed(false) { }

	~Profile()
	{
		if (!closed)
		{
			EndSession();
		}
	}

	Profile(const Profile& other) = delete;
	Profile& operator=(const Profile& other) = delete;
	Profile(const Profile&& other) noexcept = delete;
	Profile& operator=(const Profile&& other) noexcept = delete;

public:
	void BeginSession(const std::string& name, const std::string& filepath = "results.json")
	{
		json_stream.open(filepath);
		WriteHeader();
		current_session = new ProfileSession{ name };
	}

	void EndSession()
	{
		WriteFooter();
		json_stream.close();
		delete current_session;
		current_session = nullptr;
		profileCount = 0;
		closed = true;
	}

	void WriteProfile(const ProfileResult& result)
	{
		/* next item timed */
		if (profileCount++ > 0)
		{
			json_stream << ",";
		}

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		/* Either lock this area or create files per thread and combine after finished */
		/* creates timing entry to the JSON file. 
		This is broken into parts for clarification of all the parts required
		*/
		json_stream << "{\"cat\":\"function\",\"dur\":" << (result.End - result.Start) << ",\"name\":\"" << name << "\",\"ph\":\"X\",\"pid\":0,\"tid\":" << result.ThreadID << ",\"ts\":" << result.Start << "}";

		/* flush here so data isn't lost in case of crash */
		json_stream.flush();
	}

	void WriteHeader()
	{
		json_stream << "{\"otherData\": {},\"traceEvents\":[";
		json_stream.flush();
	}

	void WriteFooter()
	{
		/* If the program dies before this can be called, 
			it can just be manually added to the end of the json file 
		*/
		/* @TODO have this added to the end of WriteProfile() 
			so we don't have to worry about writing the footer
		*/
		json_stream << "]}";
		json_stream.flush();
	}

	static Profile& Get()
	{
		/* Singleton intance*/
		static Profile instance;
		return instance;
	}

};


class Timer
{
public:
	Timer(const char* name) 
		:name(name), stopped(false)
	{
		startTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!stopped)
		{
			/* Stop in destructor to measure full function time */
			Stop();
		}
	}

	Timer(const Timer& timer) = delete;
	Timer& operator=(const Timer& other) = delete;
	Timer(const Timer&& timer) noexcept = delete;
	Timer& operator=(const Timer&& other) noexcept = delete;

	void Stop()
	{
		auto endTime = std::chrono::high_resolution_clock::now();

		size_t start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
		size_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

		Profile::Get().WriteProfile({ name, start, end, threadID });

		stopped = true;
	}

private:
	const char* name;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
	bool stopped;
};



