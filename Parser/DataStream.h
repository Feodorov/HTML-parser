#ifndef DATA_STREAM_H_
#define DATA_STREAM_H_

#include <list>
#include <Windows.h>
#include <boost/shared_ptr.hpp>
#include "iconv.h"

typedef boost::shared_ptr<class DataStream> DataStream_Ptr;

class DataStream{
public:
	DataStream();
	~DataStream();
	unsigned char get();
	void write(const char * data, size_t length);
private:
	void read_data_from_console();
	iconv_t cd;
	iconv_t rd;
	HANDLE hConIn;
	std::list<unsigned char> m_data;
};

#endif //DATA_STREAM_H_