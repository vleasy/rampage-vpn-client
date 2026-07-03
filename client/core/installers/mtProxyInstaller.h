#ifndef MTPROXYINSTALLER_H
#define MTPROXYINSTALLER_H

#include "installerBase.h"

#include <QString>

struct MtProxyContainerDiagnostics {
    bool portReachable = false;
    bool upstreamReachable = false;
    int clientsConnected = -1;
    QString lastConfigRefresh;
    QString statsEndpoint;
};

class MtProxyInstaller : public InstallerBase {
Q_OBJECT
public:
    explicit MtProxyInstaller(QObject *parent = nullptr);

    rampage::ErrorCode
    extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                               SshSession *sshSession, rampage::ContainerConfig &config) override;

    static void uploadClientSettingsSnapshot(SshSession &sshSession, const rampage::ServerCredentials &credentials,
                                             rampage::DockerContainer container,
                                             const rampage::ContainerConfig &config);

    static rampage::ErrorCode queryDiagnostics(SshSession &sshSession, const rampage::ServerCredentials &credentials,
                                               rampage::DockerContainer container, int listenPort,
                                               MtProxyContainerDiagnostics &out);
};

#endif // MTPROXYINSTALLER_H
