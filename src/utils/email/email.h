#pragma once

#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "asio.hpp"

using asio::ip::tcp;
using std::string;

class MyMail {
public:
	~MyMail() {};

	static void init(const string& host, const string& user, const string& pass) {
		host_ = host;
		user_ = user;
		pass_ = pass;
	}

	void set_to(const string& to) {
		to_ = to;
	}

	void set_subject(const string& subject) {
		subject_ = subject;
	}

	void set_content(const string& content) {
		content_ = content;
	}

	void set_attachfile(const string& filepath) {
		filepath_ = filepath;
	}

	bool is_base64(unsigned char c) const {
		return ( isalnum(c) || ( c == '+' ) || ( c == '/' ) );
	}
	const string base64_encode(const char* bytes_to_encode,
		unsigned int in_len) const;
	void send(tcp::socket& sock, const string& msg) {
		asio::write(sock, asio::buffer(msg));
	}

	const string get_response(tcp::socket& sock);
	const string get_filename() const;
	void mail(tcp::socket& sock, asio::io_context& io_context);

private:
	const char* base64_chars = "ABCDEFGHIJK\
LMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static string host_;
	static string user_;
	static string pass_;
	string to_ = "";
	string subject_ = "";
	string content_ = "";
	string filepath_ = "";
};
namespace bzh {
	std::string seedEmail(std::string to_user);//tcp::socket& sock, asio::io_context& io_context
};

