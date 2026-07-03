#ifndef SOCKS5INSTALLER_H
#define SOCKS5INSTALLER_H

#include "installerBase.h"

class Socks5Installer : public InstallerBase
{
    Q_OBJECT
public:
    explicit Socks5Installer(QObject *parent = nullptr);

    rampage::ContainerConfig generateConfig(rampage::DockerContainer container, int port, rampage::TransportProto transportProto) override;
    rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                         SshSession* serverController, rampage::ContainerConfig &config) override;
};

#endif // SOCKS5INSTALLER_H

