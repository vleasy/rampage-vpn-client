#ifndef TELEMTINSTALLER_H
#define TELEMTINSTALLER_H

#include "installerBase.h"

class TelemtInstaller : public InstallerBase {
Q_OBJECT
public:
    explicit TelemtInstaller(QObject *parent = nullptr);

    rampage::ErrorCode
    extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                               SshSession *sshSession, rampage::ContainerConfig &config) override;

    static void uploadClientSettingsSnapshot(SshSession &sshSession, const rampage::ServerCredentials &credentials,
                                             rampage::DockerContainer container,
                                             const rampage::ContainerConfig &config);
};

#endif // TELEMTINSTALLER_H
