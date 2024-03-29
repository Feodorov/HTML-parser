#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <gtest/gtest.h>
#include <Windows.h>
#include <string>
#include "iconv.h"
#include "HTMLLexer.h"
#include "HTMLParser.h"
#include "HTMLElement.h"


log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("logger");

/*
TEST(test_case_1, test_3_wcin)
{
	HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
	BOOL res = SetConsoleCP(CP_UTF8);
	_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stdin), _O_U8TEXT);
	iconv_t cd = iconv_open("CP1251", "UCS-2LE");
	ASSERT_NE(cd, (iconv_t) - 1);

	unsigned long numIn;
	size_t buff_size_in = 16, buff_size_out = 8;
	char ch_in[16], ch_out[8];
	const char * ch_in_ptr = ch_in; 
	char * ch_out_ptr = ch_out;
	int nconv;
	do 
	{
		ReadConsole(hConIn, ch_in, buff_size_in, &numIn, NULL );
		buff_size_in = numIn;
		nconv = iconv(cd, &ch_in_ptr, &buff_size_in, &ch_out_ptr, &buff_size_out);
		int i = 1;
	} while (ch_in[0] != 0x0d);
	
	wprintf(L"\x043a\x043e\x0448\x043a\x0430");
	EXPECT_NE(iconv_close(cd), -1);
}*/