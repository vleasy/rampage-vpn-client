#ifndef WIREGUARD_CONFIGURATOR_H
#define WIREGUARD_CONFIGURATOR_H

#include <QHostAddress>
#include <QObject>
#include <QProcessEnvironment>

#include "configuratorBase.h"
#include "core/utils/errorCodes.h"
#include "core/utils/routeModes.h"
#include "core/utils/commonStructs.h"
#include "core/utils/selfhosted/scriptsRegistry.h"

class WireguardConfigurator : public ConfiguratorBase
{
    Q_OBJECT
public:
    WireguardConfigurator(SshSession* sshSession,
                          bool isAwg, QObject *parent = nullptr);

    struct ConnectionData
    {
        QString clientPrivKey; // client private key
        QString clientPubKey;  // client public key
        QString clientIP;      // internal client IP address
        QString serverPubKey;  // tls-auth key
        QString pskKey;        // preshared key
        QString host;          // host ip
        QString port;
    };

    rampage::ProtocolConfig createConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                const rampage::ContainerConfig &containerConfig,
                                const rampage::DnsSettings &dnsSettings,
                                rampage::ErrorCode &errorCode) override;

    rampage::ProtocolConfig processConfigWithLocalSettings(const rampage::ConnectionSettings &settings,
                                                           rampage::ProtocolConfig protocolConfig) override;
    rampage::ProtocolConfig processConfigWithExportSettings(const rampage::ExportSettings &settings,
                                                            rampage::ProtocolConfig protocolConfig) override;

    static ConnectionData genClientKeys();

private:
    QList<QHostAddress> getIpsFromConf(const QString &input);
    ConnectionData prepareWireguardConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                          const rampage::WireGuardServerConfig* serverConfig,
                                          const rampage::AwgServerConfig* awgServerConfig,
                                          const rampage::DnsSettings &dnsSettings,
                                          rampage::ErrorCode &errorCode);

    bool m_isAwg;
    QString m_serverConfigPath;
    QString m_serverPublicKeyPath;
    QString m_serverPskKeyPath;
    rampage::ProtocolScriptType m_configTemplate;
    QString m_protocolName;
    QString m_defaultPort;
};

#endif // WIREGUARD_CONFIGURATOR_H
