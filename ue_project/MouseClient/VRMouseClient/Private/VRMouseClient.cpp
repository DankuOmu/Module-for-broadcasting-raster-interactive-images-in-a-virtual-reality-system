// VRMouseClient.cpp
#include "VRMouseClient.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>

bool VRMouseClient::SendImage(const std::string& imageData) {
    if (!m_connected) return false;

    uint64_t timestamp = GetCurrentTimestampMs();

    std::ostringstream oss;
    oss << "IMAGE:" << timestamp << "," << imageData << "\n";

    return SendData(oss.str());
}

VRMouseClient::VRMouseClient()
    : m_socket(INVALID_SOCKET), m_connected(false) {
    InitWinsock();
}

VRMouseClient::~VRMouseClient() {
    Disconnect();
    CleanupWinsock();
}

void VRMouseClient::InitWinsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup failed");
    }
}

void VRMouseClient::CleanupWinsock() {
    WSACleanup();
}

bool VRMouseClient::Connect(const std::string& host, int port) {
    std::lock_guard<std::recursive_mutex> lock(m_socketMutex);

    if (m_connected) {
        Disconnect();
    }

    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* result = nullptr;
    std::string portStr = std::to_string(port);

    int res = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &result);
    if (res != 0) {
        std::cerr << "getaddrinfo failed: " << res << std::endl;
        return false;
    }

    m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (m_socket == INVALID_SOCKET) {
        std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return false;
    }

    res = connect(m_socket, result->ai_addr, (int)result->ai_addrlen);
    freeaddrinfo(result);

    if (res == SOCKET_ERROR) {
        std::cerr << "connect failed: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    m_connected = true;
    std::cout << "Connected to server at " << host << ":" << port << std::endl;
    return true;
}

// Получение текущего времени в миллисекундах с эпохи
static uint64_t GetCurrentTimestampMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
        ).count();
}

// Отправка события мыши с координатами и таймстампом
bool VRMouseClient::SendMouseEvent(const std::string& eventType, int x, int y) {
    if (!m_connected) {
        std::cerr << "Not connected to server" << std::endl;
        return false;
    }

    uint64_t timestamp = GetCurrentTimestampMs();

    std::ostringstream oss;
    oss << "MOUSE:" << eventType << "," << x << "," << y << "," << timestamp << "\n";
    std::string message = oss.str();

    return SendData(message);
}

bool VRMouseClient::SendData(const std::string& data) {
    std::lock_guard<std::recursive_mutex> lock(m_socketMutex);

    if (!m_connected) {
        return false;
    }

    int res = send(m_socket, data.c_str(), (int)data.length(), 0);
    if (res == SOCKET_ERROR) {
        std::cerr << "send failed: " << WSAGetLastError() << std::endl;
        Disconnect();
        return false;
    }

    return true;
}

bool VRMouseClient::IsConnected() const {
    return m_connected;
}

void VRMouseClient::Disconnect() {
    std::lock_guard<std::recursive_mutex> lock(m_socketMutex);

    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }

    m_connected = false;

    std::cout << "Disconnected from server" << std::endl;
}
