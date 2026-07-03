#ifndef OPENVPN_CONFIGURATOR_H
#define OPENVPN_CONFIGURATOR_H

#include <QObject>
#include <QProcessEnvironment>

#include "configuratorBase.h"
#include "core/utils/errorCodes.h"
#include "core/utils/routeModes.h"
#include "core/utils/commonStructs.h"

class OpenVpnConfigurator : public ConfiguratorBase
{
    Q_OBJECT
public:
    OpenVpnConfigurator(SshSession* sshSession, QObject *parent = nullptr);

    struct ConnectionData
    {
        QString clientId;
        QString request;    // certificate request
        QString privKey;    // client private key
        QString clientCert; // client signed certificate
        QString caCert;     // server certificate
        QString taKey;      // tls-auth key
        QString host;       // host ip
    };

    rampage::ProtocolConfig createConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                               const rampage::ContainerConfig &containerConfig,
                               const rampage::DnsSettings &dnsSettings,
                               rampage::ErrorCode &errorCode) override;

    rampage::ProtocolConfig processConfigWithLocalSettings(const rampage::ConnectionSettings &settings,
                                                           rampage::ProtocolConfig protocolConfig) override;
    rampage::ProtocolConfig processConfigWithExportSettings(const rampage::ExportSettings &settings,
                                                            rampage::ProtocolConfig protocolConfig) override;

    static ConnectionData createCertRequest();

private:
    ConnectionData prepareOpenVpnConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                       const rampage::DnsSettings &dnsSettings,
                                       rampage::ErrorCode &errorCode);
    rampage::ErrorCode signCert(rampage::DockerContainer container, const rampage::ServerCredentials &credentials, 
                      const rampage::DnsSettings &dnsSettings, QString clientId);
};

#endif // OPENVPN_CONFIGURATOR_H
