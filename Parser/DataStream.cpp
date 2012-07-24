#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include "DataStream.h"

#define BUFFER_SIZE 1000

DataStream::DataStream()
{
	hConIn = GetStdHandle(STD_INPUT_HANDLE);
	if(INVALID_HANDLE_VALUE == hConIn) throw std::exception();
	SetConsoleCP(CP_UTF8);
	_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stdin), _O_U8TEXT);

	cd = iconv_open("CP1251", "UCS-2LE");
	if((iconv_t)-1 == cd) throw std::exception();
	rd = iconv_open("UCS-2LE", "CP1251");
	if((iconv_t)-1 == rd) throw std::exception();
};

DataStream::~DataStream()
{
	iconv_close(cd);
	iconv_close(rd);
};

unsigned char DataStream::get()
{
	if(m_data.empty())
		read_data_from_console();
	unsigned char c = m_data.front();
	m_data.pop_front();
	return c;
};

void DataStream::read_data_from_console()
{
	unsigned long numIn;
	size_t buff_size_in = 2 * BUFFER_SIZE, buff_size_out = BUFFER_SIZE;
	char ch_in[2 * BUFFER_SIZE], ch_out[BUFFER_SIZE];
	const char * ch_in_ptr = ch_in; 
	char * ch_out_ptr = ch_out;

	ReadConsole(hConIn, ch_in, buff_size_in, &numIn, NULL );
	if ((0x0d == ch_in[0]) & (0x00 == ch_in[1])) throw std::exception(); //EOF
	buff_size_in = 2 * numIn;
	iconv(cd, &ch_in_ptr, &buff_size_in, &ch_out_ptr, &buff_size_out);
	m_data.clear();
	m_data.insert(m_data.begin(), ch_out, ch_out + BUFFER_SIZE - buff_size_out);
};

void DataStream::write(const char * data, size_t length)
{
	char * ch_out = new char[2 * length + 2];
	memset(ch_out, 0, 2 * length + 2);
	size_t buff_size_out = 2 * length, buff_size_in = length;
	
	const char * ch_in_ptr = data; 
	char * ch_out_ptr = ch_out;

	iconv(rd, &ch_in_ptr, &buff_size_in, &ch_out_ptr, &buff_size_out);

	wprintf_s(L"%s\n", ch_out);
	delete[] ch_out;
};