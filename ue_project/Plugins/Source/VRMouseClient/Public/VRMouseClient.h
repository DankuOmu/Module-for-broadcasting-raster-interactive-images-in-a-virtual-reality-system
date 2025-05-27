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
#include <thread>

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

    // Ïîäêëþ÷åíèå ê ñåðâåðó òðàíñëÿöèè
    bool Connect(const std::string& host, int port);

    // Îòïðàâêà ñîáûòèÿ ìûøè
    bool SendMouseEvent(const std::string& eventType, int x, int y);


    // Ïîëó÷åíèå äàííûõ
    std::string RecieveData(void);

    bool SendWorldClickEvent(const std::string& eventType, float x, float y, float z);

    // Ïðîâåðêà ïîäêëþ÷åíèÿ
    bool IsConnected() const;

    // Çàêðûòèå ñîåäèíåíèÿ
    void Disconnect();

private:
    SOCKET m_socket;
    mutable std::recursive_mutex m_socketMutex;
    bool m_connected;

    // Èíèöèàëèçàöèÿ Winsock
    static void InitWinsock();

    // Î÷èñòêà Winsock
    static void CleanupWinsock();

    // Âíóòðåííÿÿ ôóíêöèÿ îòïðàâêè äàííûõ
    bool SendData(const std::string& data);

};

