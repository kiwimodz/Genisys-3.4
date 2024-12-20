#include "Includes.h"

#define INVALID_SOCKET -1
#define SOCKET_TIME_OUT 7000

time_t get_tick_count()
{
	time_t tv;
	time(&tv);
	return tv;
}

sockets::sockets(const std::string& ip, uint16_t port, socket_type type)
{
	this->ip_ = inet_addr(ip.data());
	this->port_ = port;
	this->type_ = type;
	this->connected_ = false;
	this->socket_ = INVALID_SOCKET;

	memset(&this->server_addr, 0, sizeof(sockaddr_in));
}

sockets::sockets(uint32_t ip, uint16_t port, socket_type type)
{
	this->ip_ = ip;
	this->port_ = port;
	this->type_ = type;
	this->connected_ = false;
	this->socket_ = INVALID_SOCKET;

	memset(&this->server_addr, 0, sizeof(sockaddr_in));
}

void sockets::close()
{
	shutdown(this->socket_, 2);
	socketclose(this->socket_);

	this->connected_ = false;
	this->socket_ = INVALID_SOCKET;
}

bool sockets::connect()
{
	if (this->socket_ == INVALID_SOCKET)
	{
		this->server_addr.sin_family = AF_INET;
		this->server_addr.sin_port = htons(this->port_);
		this->server_addr.sin_addr.s_addr = this->ip_;

		if (this->type_ == socket_type::SOCKET_TYPE_TCP)
		{
			auto sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (sockfd < 0)
			{
				printf("[Socket]: Failed to create TCP socket\n");
				//v3 = false;
				return false;
			}

			if (::connect(sockfd, (sockaddr*)&this->server_addr, sizeof(this->server_addr)) < 0)
			{
				printf("[Socket]: Failed to connect to %08X:%i\n", this->ip_, this->port_);
				//v3 = false;
				return false;
			}

			this->socket_ = sockfd;
			this->connected_ = true;
			return true;
		}

		auto sockfd = ::socket(AF_INET, SOCK_DGRAM, 0);
		if (sockfd < 0)
		{
			printf("[Socket]: Failed to create UDP socket\n");
			//v3 = false;
			return false;
		}

		this->socket_ = sockfd;
		this->connected_ = true;
		return true;
	}

	return true;
}

bool sockets::receive(void* data, size_t length)
{
	if (!this->connected_ || this->socket_ == INVALID_SOCKET)
	{
		printf("[Socket]: You must be connected before receiving data\n");
		//v3 = false;
		return false;
	}

	char* current_position = (char*)data;
	time_t start_time = get_tick_count();
	size_t data_remaining = length;
	int recv_length = 0;

	while (data_remaining > 0)
	{
		if ((get_tick_count() - start_time) > SOCKET_TIME_OUT)
		{
			printf("[Socket]: Receive timedout\n");
			//v3 = false;
			return false;
		}

		int chunk = std::min<size_t>(data_remaining, 2048);
		if (this->type_ == socket_type::SOCKET_TYPE_TCP)
		{
			recv_length = ::recv(this->socket_, current_position, chunk, 0);
		}
		else
		{
			socklen_t recvlen;
			recv_length = ::recvfrom(this->socket_, current_position, chunk, 0, (sockaddr*)&this->server_addr, &recvlen);
		}

		if (recv_length < 0)
		{
			printf("[Socket]: Receive failed\n");
			//v3 = false;
			return false;
		}
		else if (recv_length < chunk)
		{
			return true;
		}

		data_remaining -= recv_length;
		current_position += recv_length;
	}

	return true;
}

bool sockets::send(const void* data, size_t length)
{
	if (!this->connected_ || this->socket_ == INVALID_SOCKET)
	{
		printf("[Socket]: You must be connected before sending data\n");
		//v3 = false;
		return false;
	}

	char* current_position = (char*)data;
	time_t start_time = get_tick_count();
	size_t data_remaining = length;
	int send_length = 0;

	while (data_remaining > 0)
	{
		if ((get_tick_count() - start_time) > SOCKET_TIME_OUT)
		{
			printf("[Socket]: Send timedout\n");
			//v3 = false;
			return false;
		}

		int chunk = std::min<size_t>(data_remaining, 2048);
		if (this->type_ == socket_type::SOCKET_TYPE_TCP)
		{
			send_length = ::send(this->socket_, current_position, chunk, 0);
		}
		else
		{
			send_length = ::sendto(this->socket_, current_position, chunk, 0, (sockaddr*)&this->server_addr, sizeof(this->server_addr));
		}

		if (send_length < 0)
		{
			printf("[Socket]: Send failed\n");
			//v3 = false;
			return false;
		}
		else if (send_length < chunk)
		{
			return true;
		}

		data_remaining -= send_length;
		current_position += send_length;
	}

	return true;
}