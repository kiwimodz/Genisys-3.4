#pragma once

enum socket_type
{
	SOCKET_TYPE_TCP,
	SOCKET_TYPE_UDP
};

class sockets
{
private:
	int socket_;
	uint32_t ip_;
	uint16_t port_;
	socket_type type_;
	sockaddr_in server_addr;

public:
	bool connected_;

	sockets() = default;
	sockets(const std::string& ip, uint16_t port, socket_type type = SOCKET_TYPE_TCP);
	sockets(uint32_t ip, uint16_t port, socket_type type = SOCKET_TYPE_TCP);

	void close();
	bool connect();
	bool receive(void* data, size_t length);
	bool send(const void* data, size_t length);
};