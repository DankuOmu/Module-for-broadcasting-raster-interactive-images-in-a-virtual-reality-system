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

    // ����������� � ������� ����������
    bool Connect(const std::string& host, int port);

    // �������� ������� ����
    bool SendMouseEvent(const std::string& eventType, int x, int y);

    // ��������� ������
    std::string RecieveData(void);

    // �������� �����������
    bool IsConnected() const;

    // �������� ����������
    void Disconnect();

private:
    SOCKET m_socket;
    mutable std::recursive_mutex m_socketMutex;
    bool m_connected;

    // ������������� Winsock
    static void InitWinsock();

    // ������� Winsock
    static void CleanupWinsock();

    // ���������� ������� �������� ������
    bool SendData(const std::string& data);
};