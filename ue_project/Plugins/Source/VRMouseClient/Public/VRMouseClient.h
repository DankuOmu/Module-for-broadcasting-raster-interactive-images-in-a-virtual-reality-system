// VRMouseClient.h
#pragma once

#include "LevelEditor.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Blueprint.h"

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <system_error>
#include <memory>
#include <mutex>

#undef UpdateResource

#pragma comment(lib, "ws2_32.lib")

class VRImageTranslator {
public:
    AActor* object;
    UMaterial* mtl;

    VRImageTranslator();
    VRImageTranslator(UObject* context);

    ~VRImageTranslator();

    bool UpdateTexture(const std::string& data);
};

class VRMouseClient {
public:
    VRImageTranslator* Translator;
    UObject* root;

    VRMouseClient();
    VRMouseClient(UObject* context);
    ~VRMouseClient();

    // Подключение к серверу трансляции
    bool Connect(const std::string& host, int port);

    // Отправка события мыши
    bool SendMouseEvent(const std::string& eventType, int x, int y);

    // Получение данных
    std::string RecieveData(void);

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