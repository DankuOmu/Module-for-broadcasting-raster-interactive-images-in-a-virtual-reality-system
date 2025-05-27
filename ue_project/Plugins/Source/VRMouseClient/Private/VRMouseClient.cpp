// VRMouseClient.cpp
#include "VRMouseClient.h"
#include "Engine/StaticMeshActor.h"
#include "IImageWrapperModule.h"
#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <thread>


VRImageTranslator::VRImageTranslator(UObject* context) {
    UE_LOG(LogTemp, Warning, TEXT("Image Translator loaded"));

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
    FName path = "/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane";
    const FAssetData& plane_asset = AssetRegistry.GetAssetByObjectPath(path);
    UStaticMesh* plane = Cast<UStaticMesh>(plane_asset.GetAsset());

    FString name = plane->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s is loaded"), *name);

    UWorld* world = GEngine->GetWorldFromContextObject(context, EGetWorldErrorMode::ReturnNull);

    FVector pos(-500.f, 0.f, 100.f);
    FRotator rot(0.f, -90.f, 90.f);
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.Owner = world->GetFirstPlayerController()->GetPawn();
    SpawnInfo.Instigator = world->GetFirstPlayerController()->GetPawn()->GetInstigator();
    
    AActor* obj = world->SpawnActor<AStaticMeshActor>(pos, rot, SpawnInfo);
    UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(obj, UStaticMeshComponent::StaticClass(), TEXT("Mesh"));
    UMaterial* Material = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("/Game/M_Image.M_Image")));
    mtl = Material;

    MeshComponent->SetStaticMesh(plane);
    MeshComponent->SetMaterial(0, Material);
    MeshComponent->SetWorldLocation(pos);
    MeshComponent->SetWorldRotation(rot);
    MeshComponent->SetIsReplicated(true);

    MeshComponent->RegisterComponent();
    obj->AddOwnedComponent(MeshComponent);
    obj->SetRootComponent(MeshComponent);
    object = obj;

}

bool VRImageTranslator::UpdateTexture(const std::string& data) {
    if (data.size() < 4)
        return false;

    UE_LOG(LogTemp, Warning, TEXT("updating texture"));
    TArray<uint8> LoadedData;
    uint32 w = 2560, h = 1600;

    for (size_t i = 0; i < data.size(); i++) {
        LoadedData.Add(data[i]);
    }

    UTexture2D* tex = nullptr;
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

    if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(LoadedData.GetData(), LoadedData.Num()))
    {
        TArray<uint8> UncompressedBGRA;
        if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
        {
            tex = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
            FTexturePlatformData* PlatformData = tex->GetPlatformData();

            //Valid?
            if (!tex) return false;
            //~~~~~~~~~~~~~~

            //Out!
            w = ImageWrapper->GetWidth();
            h = ImageWrapper->GetHeight();

            //Copy!
            void* TextureData = PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
            FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
            PlatformData->Mips[0].BulkData.Unlock();

            //Update!
            tex->UpdateResource();
        }
        else
            return false;
    }
    else
        return false;

    TArray<UStaticMeshComponent*> Components;
    object->GetComponents<UStaticMeshComponent>(Components);
    int n = Components.Num();
    UStaticMeshComponent* StaticMeshComponent = Components[1];
    FVector scale((double)w / h, 1, 1);
    object->SetActorScale3D(scale);

    UMaterialInstanceDynamic* dynamic = StaticMeshComponent->CreateDynamicMaterialInstance(0, mtl);
    dynamic->SetTextureParameterValue("Texture", tex);

    return true;
}

VRMouseClient::VRMouseClient()
    : m_socket(INVALID_SOCKET), m_connected(false) {
    InitWinsock();
    Translator = nullptr;
}

VRMouseClient::VRMouseClient(UObject* context)
    : m_socket(INVALID_SOCKET), m_connected(false) {
    InitWinsock();
    Translator = nullptr;
    root = context;
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

    u_long mode = 1;
    int nbres = ioctlsocket(m_socket, FIONBIO, &mode);

    res = connect(m_socket, result->ai_addr, (int)result->ai_addrlen);
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    while (WSAGetLastError() == 10035)
         res = connect(m_socket, result->ai_addr, (int)result->ai_addrlen);

    freeaddrinfo(result);

    int err = WSAGetLastError();

    if (res == SOCKET_ERROR and err != 10056) {
        // std::cerr << "connect failed: " << WSAGetLastError() << std::endl;
        UE_LOG(LogTemp, Warning, TEXT("connection failed: %d"), err);
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return false;
    }

    m_connected = true;
    UE_LOG(LogTemp, Warning, TEXT("Connected to the server"));
    std::cout << "Connected to server at " << host << ":" << port << std::endl;

    return true;
}

bool VRMouseClient::SendMouseEvent(const std::string& eventType, int x, int y) {
    UE_LOG(LogTemp, Warning, TEXT("Mouse event"));
    if (!m_connected) {
        std::cerr << "Not connected to server" << std::endl;
        return false;
    }

    std::ostringstream oss;
    oss << "MOUSE:" << eventType << "," << x << "," << y << "\n";
    std::string message = oss.str();

    // RecieveData();

    return SendData(message);
}

bool VRMouseClient::SendData(const std::string& data) {
    std::lock_guard<std::recursive_mutex> lock(m_socketMutex);
    UE_LOG(LogTemp, Warning, TEXT("Send data"));


    if (!m_connected) {
        return false;
    }

    int res = send(m_socket, data.c_str(), (int)data.length(), 0);

    if (res == SOCKET_ERROR) {
        std::cerr << "send failed: " << WSAGetLastError() << std::endl;
        Disconnect();
        return false;
    }

    if (!Translator)
        Translator = new VRImageTranslator(root);
    
    // Translator->UpdateTexture(RecieveData());

    return true;
}

std::string VRMouseClient::RecieveData(void) {
    // std::lock_guard<std::recursive_mutex> lock(m_socketMutex);
    char* recvbuf = nullptr;
    char size[8];
    int sz = 0;
    // int bytesReceived = recv(m_socket, recvbuf, sizeof(recvbuf) - 1, 0);
    int bytesReceived = recv(m_socket, size, 8, 0);
    if (bytesReceived == 8) {
        while (bytesReceived == 8 and (size[0] != 'I' || size[1] != 'M' || size[2] != 'G')) {
            bytesReceived = recv(m_socket, size, 8, 0);
        }
        if (bytesReceived < 8)
            return "";
        for (int i = 0; i < 4; i++)
            sz = (sz << 8) + size[i + 4];
        if (sz < 0)
            return "";
        recvbuf = new char[sz*2];
        bytesReceived = recv(m_socket, recvbuf, sz*2, 0);
        if (bytesReceived > 0) {
            UE_LOG(LogTemp, Warning, TEXT("%d bytes of data received"), bytesReceived);
        } else {
            UE_LOG(LogTemp, Warning, TEXT("RECEIVED ERROR: Image data"));
        }
    } else {
        UE_LOG(LogTemp, Warning, TEXT("RECEIVED ERROR: Image size"));
    }

    


    //if (bytesReceived > 0) {
    //    recvbuf[bytesReceived] = '\0';
    //    // UE_LOG(LogTemp, Warning, TEXT("DATA: %s"), UTF8_TO_TCHAR(recvbuf));
    //    UE_LOG(LogTemp, Warning, TEXT("%d bytes of data received"), bytesReceived);
    //} else {
    //    UE_LOG(LogTemp, Warning, TEXT("RECEIVED ERROR!"));
    //}
    std::string res(recvbuf, recvbuf + max(bytesReceived, 0));
    return res;
}

bool VRMouseClient::IsConnected() const {
    return m_connected;
}

void VRMouseClient::Disconnect() {
    UE_LOG(LogTemp, Warning, TEXT("DISCONNECT"));
    std::lock_guard<std::recursive_mutex> lock(m_socketMutex);


    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }

    m_connected = false;

    if (WSAGetLastError() != 0) {
        std::cout << "Disconnected from server" << std::endl;
    }
}