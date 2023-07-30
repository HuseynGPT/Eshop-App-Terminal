#pragma once
#pragma once


class Exception :public exception
{
	str _text;
	int _line;
	str _source;
	str _time;
public:
	Exception(str text = "exception", int line = 0, str source = "", str time = "") :exception(text.c_str())
	{
		this->_line = line;
		this->_source = source;
		this->_time = time;
		this->_text = "Message: " + str(exception::what())
			+ "\nSource: " + this->_source
			+ "\nTime: " + this->_time
			+ "\nLine: " + to_string(this->_line);
	}

	char const* what()const override { return this->_text.c_str(); }

};

class DatabaseException :public Exception
{
public:
	DatabaseException() :Exception() {}
	DatabaseException(str text = "Database exception", int line = 0, str source = "", str time = "") :Exception(text, line, source, time) {}
};

class InvalidArgument :public Exception
{
public:
	InvalidArgument() :Exception() {}
	InvalidArgument(str text = "InvalidArgument exception", int line = 0, str source = "", str time = "") :Exception(text, line, source, time) {}
};