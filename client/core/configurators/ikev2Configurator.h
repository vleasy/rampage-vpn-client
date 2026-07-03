#ifndef IKEV2_CONFIGURATOR_H
#define IKEV2_CONFIGURATOR_H

#include <QObject>
#include <QProcessEnvironment>

#include "configuratorBase.h"
#include "core/utils/errorCodes.h"
#include "core/utils/routeModes.h"
#include "core/utils/commonStructs.h"

class Ikev2Configurator : public ConfiguratorBase
{
    Q_OBJECT
public:
    Ikev2Configurator(SshSession* sshSession, QObject *parent = nullptr);

    struct ConnectionData {
        QByteArray clientCert; // p12 client cert
        QByteArray caCert; // p12 server cert
        QString clientId;
        QString password; // certificate password
        QString host; // host ip
    };

    rampage::ProtocolConfig createConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                const rampage::ContainerConfig &containerConfig,
                                const rampage::DnsSettings &dnsSettings,
                                rampage::ErrorCode &errorCode) override;

    QString genIkev2Config(const ConnectionData &connData);
    QString genMobileConfig(const ConnectionData &connData);
    QString genStrongSwanConfig(const ConnectionData &connData);

    ConnectionData prepareIkev2Config(const rampage::ServerCredentials &credentials,
        rampage::DockerContainer container, rampage::ErrorCode &errorCode);
};

#endif // IKEV2_CONFIGURATOR_H
