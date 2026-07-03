#ifndef AWGINSTALLER_H
#define AWGINSTALLER_H

#include "installerBase.h"

class AwgInstaller : public InstallerBase
{
    Q_OBJECT
public:
    explicit AwgInstaller(QObject *parent = nullptr);

    rampage::ContainerConfig generateConfig(rampage::DockerContainer container, int port, rampage::TransportProto transportProto) override;
    rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                         SshSession* serverController, rampage::ContainerConfig &config) override;

private:
    void generateAwgParameters(rampage::AwgServerConfig &serverConfig, bool isAwg2 = false);
};

#endif // AWGINSTALLER_H

