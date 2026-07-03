#ifndef TORINSTALLER_H
#define TORINSTALLER_H

#include "installerBase.h"

class TorInstaller : public InstallerBase
{
    Q_OBJECT
public:
    explicit TorInstaller(QObject *parent = nullptr);

    rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                         SshSession* serverController, rampage::ContainerConfig &config) override;
};

#endif // TORINSTALLER_H

