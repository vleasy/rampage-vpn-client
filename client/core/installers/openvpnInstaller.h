#ifndef OPENVPNINSTALLER_H
#define OPENVPNINSTALLER_H

#include "installerBase.h"

class OpenVpnInstaller : public InstallerBase
{
    Q_OBJECT
public:
    explicit OpenVpnInstaller(QObject *parent = nullptr);

    rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                         SshSession* serverController, rampage::ContainerConfig &config) override;
};

#endif // OPENVPNINSTALLER_H

