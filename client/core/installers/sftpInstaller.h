#ifndef SFTPINSTALLER_H
#define SFTPINSTALLER_H

#include "installerBase.h"

class SftpInstaller : public InstallerBase
{
    Q_OBJECT
public:
    explicit SftpInstaller(QObject *parent = nullptr);

    rampage::ContainerConfig generateConfig(rampage::DockerContainer container, int port, rampage::TransportProto transportProto) override;
    rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                         SshSession* serverController, rampage::ContainerConfig &config) override;
};

#endif // SFTPINSTALLER_H

