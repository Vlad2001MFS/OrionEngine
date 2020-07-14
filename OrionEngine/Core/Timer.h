#pragma once
#include "Common.h"

namespace oe {
namespace core {

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Reset();

	uint GetMinuts() const;
	uint GetSeconds() const;
	uint GetMilliseconds() const;

	bool IsStarted() const;

private:
	bool mIsStarted;
	uint mStartTime;
};

}
}