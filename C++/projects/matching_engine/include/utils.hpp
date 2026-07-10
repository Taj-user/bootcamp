#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>

bool send_all(SOCKET fd, const char* buffer, int length);
