// VRMouseClient.h
#pragma once

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <system_error>
#include <memory>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")

class VRMouseClient {
public:
    VRMouseClient();
    ~VRMouseClient();

    // Подключение к серверу трансляции
    bool Connect(const std::string& host, int port);

    // Отправка события мыши
    bool SendMouseEvent(const std::string& eventType, int x, int y);

    bool SendWorldClickEvent(const std::string& eventType, float x, float y, float z);

    // Проверка подключения
    bool IsConnected() const;

    // Закрытие соединения
    void Disconnect();

private:
    SOCKET m_socket;
    mutable std::recursive_mutex m_socketMutex;
    bool m_connected;

    // Инициализация Winsock
    static void InitWinsock();

    // Очистка Winsock
    static void CleanupWinsock();

    // Внутренняя функция отправки данных
    bool SendData(const std::string& data);
};
