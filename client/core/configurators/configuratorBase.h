#ifndef CONFIGURATORBASE_H
#define CONFIGURATORBASE_H

#include <QObject>
#include <QScopedPointer>

#include "core/utils/containerEnum.h"
#include "core/utils/containers/containerUtils.h"
#include "core/utils/protocolEnum.h"
#include "core/utils/errorCodes.h"
#include "core/utils/routeModes.h"
#include "core/utils/commonStructs.h"
#include "core/models/containerConfig.h"
#include "core/models/protocolConfig.h"

class SshSession;

class ConfiguratorBase : public QObject
{
    Q_OBJECT
public:
    explicit ConfiguratorBase(SshSession* sshSession, QObject *parent = nullptr);

    static QScopedPointer<ConfiguratorBase> create(rampage::Proto protocol,
                                                   SshSession* sshSession);

    virtual rampage::ProtocolConfig createConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                        const rampage::ContainerConfig &containerConfig,
                                        const rampage::DnsSettings &dnsSettings,
                                        rampage::ErrorCode &errorCode) = 0;

    virtual rampage::ProtocolConfig processConfigWithLocalSettings(const rampage::ConnectionSettings &settings,
                                                                   rampage::ProtocolConfig protocolConfig);
    virtual rampage::ProtocolConfig processConfigWithExportSettings(const rampage::ExportSettings &settings,
                                                                     rampage::ProtocolConfig protocolConfig);

protected:
    void applyDnsToNativeConfig(const rampage::DnsSettings &dns, rampage::ProtocolConfig &protocolConfig);

    SshSession* m_sshSession;
};

#endif // CONFIGURATORBASE_H
