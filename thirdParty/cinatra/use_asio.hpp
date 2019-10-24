#pragma once

//MSVC : define environment path 'ASIO_STANDALONE_INCLUDE', e.g. 'E:\bdlibs\asio-1.10.6\include'
#include <asio.hpp>
namespace boost
{
	namespace asio
	{
		using namespace ::asio;
	}
	namespace system
	{
		using ::std::error_code;
	}
}
