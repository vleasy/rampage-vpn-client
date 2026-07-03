#ifndef INSTALLERBASE_H
#define INSTALLERBASE_H

#include <QObject>
#include <QJsonObject>

#include "core/utils/containerEnum.h"
#include "core/utils/protocolEnum.h"
#include "core/utils/errorCodes.h"
#include "core/utils/routeModes.h"
#include "core/utils/commonStructs.h"
#include "core/utils/selfhosted/sshSession.h"
#include "core/models/containerConfig.h"

class InstallerBase : public QObject
{
    Q_OBJECT
public:
    explicit InstallerBase(QObject *parent = nullptr);

    virtual rampage::ContainerConfig generateConfig(rampage::DockerContainer container, int port, rampage::TransportProto transportProto);

    virtual rampage::ErrorCode extractConfigFromContainer(rampage::DockerContainer container, const rampage::ServerCredentials &credentials,
                                                 SshSession* sshSession, rampage::ContainerConfig &config);

    rampage::ContainerConfig createBaseConfig(rampage::DockerContainer container, int port, rampage::TransportProto transportProto);

protected:
};

#endif // INSTALLERBASE_H

