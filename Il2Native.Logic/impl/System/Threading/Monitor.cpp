#include "CoreLib.h"

// Method : System.Threading.Monitor.Enter(object)
void CoreLib::System::Threading::Monitor::Enter(object* obj)
{
	auto object_extras = __object_extras_storage_instance->operator[](obj);
    object_extras->monitor.lock();  
}

// Method : System.Threading.Monitor.ReliableEnter(object, ref bool)
void CoreLib::System::Threading::Monitor::ReliableEnter_Ref(object* obj, bool& lockTaken)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
	lockTaken = object_extras->monitor.try_lock_for(std::chrono::milliseconds::max());
}

// Method : System.Threading.Monitor.Exit(object)
void CoreLib::System::Threading::Monitor::Exit(object* obj)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
    object_extras->monitor.unlock();
}

// Method : System.Threading.Monitor.ReliableEnterTimeout(object, int, ref bool)
void CoreLib::System::Threading::Monitor::ReliableEnterTimeout_Ref(object* obj, int32_t timeout, bool& lockTaken)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
    lockTaken = object_extras->monitor.try_lock_for(std::chrono::milliseconds(timeout));
}

// Method : System.Threading.Monitor.IsEnteredNative(object)
bool CoreLib::System::Threading::Monitor::IsEnteredNative(object* obj)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
    auto lockTaken = object_extras->monitor.try_lock_for(std::chrono::milliseconds(1));
	if (lockTaken)
	{
		object_extras->monitor.unlock();
	}

	return !lockTaken;
}

// Method : System.Threading.Monitor.ObjWait(bool, int, object)
bool CoreLib::System::Threading::Monitor::ObjWait(bool exitContext, int32_t millisecondsTimeout, object* obj)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
	return std::cv_status::no_timeout == object_extras->monitor.wait_for(millisecondsTimeout == -1 ? std::chrono::milliseconds::max() : std::chrono::milliseconds(millisecondsTimeout));
}

// Method : System.Threading.Monitor.ObjPulse(object)
void CoreLib::System::Threading::Monitor::ObjPulse(object* obj)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
	object_extras->monitor.notify_one();
}

// Method : System.Threading.Monitor.ObjPulseAll(object)
void CoreLib::System::Threading::Monitor::ObjPulseAll(object* obj)
{
	if (obj == nullptr)
	{
		throw __new<CoreLib::System::ArgumentNullException>();
	}

	auto object_extras = __object_extras_storage_instance->operator[](obj);
	object_extras->monitor.notify_all();
}
