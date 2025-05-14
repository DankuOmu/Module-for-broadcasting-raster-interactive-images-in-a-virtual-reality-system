// VRMouseClient.cpp
#include "VRMouseClient.h"
#include "Engine/StaticMeshActor.h"
#include "IImageWrapperModule.h"
#include <iostream>
#include <sstream>
#include <mutex>




VRImageTranslator::VRImageTranslator(UObject* context) {
    // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Image Translator"));
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
    FRotator rot(90.f, 0.f, 180.f);
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
    UE_LOG(LogTemp, Warning, TEXT("updating texture"));
    TArray<uint8> LoadedData;
    uint32 w = 2560, h = 1600;
    FString path = FPaths::ProjectContentDir() + FString(data.c_str());
    FFileHelper::LoadFileToArray(LoadedData, *path);
    /*for (size_t i = 0; i < data.size(); i++) {
        LoadedData.Add(data[i]);
    }*/

    // UTexture2D* tex = CreateTextureFromImageData(LoadedData, 1920, 1080);
    UTexture2D* tex = UTexture2D::CreateTransient(w, h, PF_R8G8B8A8);
    FTexturePlatformData* PlatformData = tex->GetPlatformData();
    void* TexData = PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
    // TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

    if (ImageWrapper->SetCompressed(LoadedData.GetData(), LoadedData.Num())) {
        TArray<uint8> UncompressedRGBA;
        if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA)) {
            FMemory::Memcpy(TexData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
        } else {
            UE_LOG(LogTemp, Warning, TEXT("Failed to decompress"))
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to set data in image wrapper"))
    }
    
    PlatformData->Mips[0].BulkData.Unlock();
    tex->UpdateResource();

    TArray<UStaticMeshComponent*> Components;
    object->GetComponents<UStaticMeshComponent>(Components);
    int n = Components.Num();
    UStaticMeshComponent* StaticMeshComponent = Components[1];

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

    res = connect(m_socket, result->ai_addr, (int)result->ai_addrlen);
    freeaddrinfo(result);

    if (res == SOCKET_ERROR) {
        std::cerr << "connect failed: " << WSAGetLastError() << std::endl;
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
    
    Translator->UpdateTexture(RecieveData());

    return true;
}

std::string VRMouseClient::RecieveData(void) {
    std::lock_guard<std::recursive_mutex> lock(m_socketMutex);
    char recvbuf[1000000];
    int bytesReceived = recv(m_socket, recvbuf, sizeof(recvbuf) - 1, 0);

    if (bytesReceived > 0) {
        recvbuf[bytesReceived] = '\0';
        // UE_LOG(LogTemp, Warning, TEXT("DATA: %s"), UTF8_TO_TCHAR(recvbuf));
        UE_LOG(LogTemp, Warning, TEXT("%d bytes of data received"), bytesReceived);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("RECEIVED ERROR!"));
    }
    std::string res(recvbuf, recvbuf + bytesReceived);
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