#ifndef ARG3_LOG_H
#define ARG3_LOG_H

#include <iostream>
#include <string>

namespace arg3
{
	class log
	{
	public:
		typedef enum { ERROR, WARN, INFO, DEBUG, TRACE } level;

		static void trace(const std::string &value, std::ostream &out = std::cout);
		static void debug(const std::string &value, std::ostream &out = std::cout);
		static void info(const std::string &value, std::ostream &out = std::cout);
		static void error(const std::string &value, std::ostream &out = std::cout);
		static void warn(const std::string &value, std::ostream &out = std::cout);

		log(level level, std::ostream &out = std::cout);

		log &write(const std::string &value);
		log &writeln(const std::string &value);

		template<typename T>
		log &operator<<(const T &value)
		{
			header() << value;
		}
	protected:
		std::ostream &header();
	private:
		level level_;
		std::ostream &out_;
	};
}

#endif
