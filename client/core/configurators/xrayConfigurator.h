#ifndef XRAY_CONFIGURATOR_H
#define XRAY_CONFIGURATOR_H

#include <QObject>
#include <QJsonObject>

#include "configuratorBase.h"
#include "core/utils/errorCodes.h"
#include "core/utils/routeModes.h"
#include "core/utils/commonStructs.h"
#include "core/models/protocols/xrayProtocolConfig.h"

class XrayConfigurator : public ConfiguratorBase
{
    Q_OBJECT
public:
    XrayConfigurator(SshSession* sshSession, QObject *parent = nullptr);

    rampage::ProtocolConfig createConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container, const rampage::ContainerConfig &containerConfig,
                                const rampage::DnsSettings &dnsSettings,
                                rampage::ErrorCode &errorCode) override;

    rampage::ProtocolConfig processConfigWithLocalSettings(const rampage::ConnectionSettings &settings,
                                                           rampage::ProtocolConfig protocolConfig) override;

    rampage::ErrorCode applyServerSettingsToRemote(const rampage::ServerCredentials &credentials,
                                                   rampage::DockerContainer container,
                                                   rampage::ContainerConfig &containerConfig,
                                                   const rampage::DnsSettings &dnsSettings,
                                                   bool appendNewClient,
                                                   QString *outClientId = nullptr);

private:
    QString prepareServerConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container, const rampage::ContainerConfig &containerConfig,
                                const rampage::DnsSettings &dnsSettings,
                                rampage::ErrorCode &errorCode);

    rampage::ErrorCode uploadServerConfigJson(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                              const rampage::DnsSettings &dnsSettings, const QJsonObject &serverConfig) const;

    rampage::XrayProtocolConfig buildClientProtocolConfig(const rampage::ServerCredentials &credentials,
                                                          rampage::DockerContainer container,
                                                          const rampage::XrayServerConfig &srv,
                                                          const QString &clientId,
                                                          rampage::ErrorCode &errorCode,
                                                          const QString &prefetchedRealityPublicKey = {},
                                                          const QString &prefetchedRealityShortId = {}) const;

    rampage::ErrorCode readRealityKeyFiles(rampage::DockerContainer container,
                                           const rampage::ServerCredentials &credentials,
                                           QString &outPublicKey,
                                           QString &outShortId) const;

    QJsonObject mergeStreamSettingsForServerInbound(const rampage::XrayServerConfig &srv,
                                                    const QJsonObject &existingStreamSettings) const;

    QJsonObject buildStreamSettings(const rampage::XrayServerConfig &srv,
                                    const QString &clientId) const;
};

#endif // XRAY_CONFIGURATOR_H
