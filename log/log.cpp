#include <iomanip>
#include <iostream>
#include <ctime>
#include "log.h"

using namespace std;

namespace arg3
{
	const char *logNames[] = { "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

	log::log(log::level level, ostream &out) : level_(level), out_(out)
	{}

	ostream &log::header() {
		time_t current_time = time(NULL);

		out_ << "[" << logNames[level_] << "] " << std::put_time(std::localtime(&current_time), "%F %T") << ": ";

		return out_;
	}

	log& log::write(const string &value) {
		header() << value;
		return *this;
	}
	
	log& log::writeln(const string &value) {
		header() << value << endl;

		return *this;
	}

	void log::debug(const string &value, ostream &out) {
		log(DEBUG, out).writeln(value);
	}

	void log::trace(const string &value, std::ostream &out)
	{
		log(TRACE, out).writeln(value);
	}
	void log::info(const string &value, ostream &out)
	{
		log(INFO, out).writeln(value);
	}
	void log::error(const string &value, ostream &out)
	{
		log(ERROR, out).writeln(value);
	}
	void log::warn(const string &value, ostream &out)
	{
		log(WARN, out).writeln(value);
	}

}