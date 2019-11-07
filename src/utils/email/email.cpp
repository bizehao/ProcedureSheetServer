#include "email.h"
#include <ctime>

const string MyMail::base64_encode(const char* bytes_to_encode,
	unsigned int in_len) const {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *( bytes_to_encode++ );
		if (i == 3) {
			char_array_4[0] = ( char_array_3[0] & 0xfc ) >> 2;
			char_array_4[1] = ( ( char_array_3[0] & 0x03 ) << 4 ) + ( ( char_array_3[1] & 0xf0 ) >> 4 );
			char_array_4[2] = ( ( char_array_3[1] & 0x0f ) << 2 ) + ( ( char_array_3[2] & 0xc0 ) >> 6 );
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; ( i < 4 ); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = ( char_array_3[0] & 0xfc ) >> 2;
		char_array_4[1] = ( ( char_array_3[0] & 0x03 ) << 4 ) + ( ( char_array_3[1] & 0xf0 ) >> 4 );
		char_array_4[2] = ( ( char_array_3[1] & 0x0f ) << 2 ) + ( ( char_array_3[2] & 0xc0 ) >> 6 );
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; ( j < i + 1 ); j++)
			ret += base64_chars[char_array_4[j]];

		while (( i++ < 3 ))
			ret += '=';
	}
	return ret;
}

const string MyMail::get_filename() const {
	const char* x = "/";
	auto it = std::find_end(filepath_.begin(), filepath_.end(), x, x + 1);
	int n = it - filepath_.begin();
	string name = filepath_.substr(n + 1, filepath_.length() - n - 1);
	return name;
}

const std::string MyMail::get_response(tcp::socket& sock) {
	asio::streambuf buffer;
	for (;;) {
		string msg;
		asio::read_until(sock, buffer, "\r\n");
		std::istream in(&buffer);
		std::getline(in, msg);
		return msg;
	}
}

void MyMail::mail(tcp::socket& sock, asio::io_context& io_context) {

	if (host_.size() == 0) {
		throw std::runtime_error("Error! Need set host!!");
	}

	if (to_.size() == 0) {
		throw std::runtime_error("Error! Need set mail to mail");
	}

	tcp::resolver resolver(io_context);
	tcp::resolver::query query(host_, "25");
	tcp::resolver::iterator it_endpt = resolver.resolve(query);
	tcp::resolver::iterator end;
	asio::error_code error = asio::error::host_not_found;
	while (error && it_endpt != end) {
		sock.close();
		sock.connect(*it_endpt++, error);
	}
	if (error) {
		sock.close();
		throw std::runtime_error("HOST can't be connected!!");
	}

	send(sock, "HELO " + user_ + "\r\n");
	get_response(sock);

	send(sock, "auth login\r\n");
	get_response(sock);

	string user_base64 = base64_encode(user_.data(),
		user_.length());
	string pass_base64 = base64_encode(pass_.data(),
		pass_.length());
	send(sock, user_base64 + "\r\n");
	get_response(sock);
	send(sock, pass_base64 + "\r\n");
	get_response(sock);

	send(sock, "mail from: <" + user_ + ">\r\n");
	get_response(sock);
	send(sock, "rcpt to: <" + to_ + ">\r\n");
	get_response(sock);

	send(sock, "data\r\n");
	get_response(sock);
	send(sock, "From:" + user_ + "\r\n");
	//std::cout << get_response(sock) << std::endl;//
	send(sock, "subject:" + subject_ + "\r\nMime-Version: 1.0\r\n"
		"Content-Type: multipart/mixed;   "
		"boundary=\"INVT\"\r\n\r\n");
	//std::cout << get_response(sock) << std::endl;//
	send(sock, "--INVT\r\nContent-Type: text/plain;\r\n  "
		"charset=\"utf8\"\r\n\r\n" + content_ + "\r\n\r\n");
	//std::cout << get_response(sock) << std::endl;//
	if (filepath_.size() > 0) {
		string fname = get_filename();
		string attach = "--INVT\r\nContent-Type: application/octet-stream;\r\n"
			"  name=\"" + fname + "\"\r\nContent-Transfer-Encoding: base64\r\n"
			"Content-Disposition: attachment;\r\n  filename=\"" + fname + "\"\r\n\r\n";

		send(sock, attach);
		std::ifstream fin(filepath_.data(), std::ios_base::binary);
		fin.seekg(0, fin.end);
		int length = fin.tellg();
		fin.seekg(0, fin.beg);
		char* buffer = new char[length];
		fin.read(buffer, length);
		string fc_base = base64_encode(buffer, length);
		send(sock, fc_base + "\r\n");
		//std::cout << get_response(sock) << std::endl;//
		fin.close();
		delete[] buffer;
	}
	send(sock, "\r\n.\r\n");
	get_response(sock);
	send(sock, "quit\r\n");
	get_response(sock);
	sock.close();
}

std::string bzh::seedEmail(std::string to_user) {
	static asio::io_context io_context;
	static asio::ip::tcp::socket sock(io_context);
	MyMail email;
	email.set_to(to_user);
	email.set_subject("验证码:");
	std::string msg;
	std::srand(std::time(nullptr));
	for (int i = 0; i < 6; i++) {
		int x = 1 + std::rand() % 9;
		msg.append(std::to_string(x));
	}
	email.set_content(msg);
	email.mail(sock, io_context);
	return "111";
}

string MyMail::host_ = "";
string MyMail::user_ = "";
string MyMail::pass_ = "";
