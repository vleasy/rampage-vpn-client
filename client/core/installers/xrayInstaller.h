#ifndef XRAYINSTALLER_H
#define XRAYINSTALLER_H

#include "installerBase.h"

class XrayInstaller : public InstallerBase
{
    Q_OBJECT
public:
    explicit XrayInstaller(QObject *parent = nullptr);

    rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                         SshSession* serverController, rampage::ContainerConfig &config) override;
};

#endif // XRAYINSTALLER_H

