#ifndef AWGCONFIGURATOR_H
#define AWGCONFIGURATOR_H

#include <QObject>

#include "wireguardConfigurator.h"

class AwgConfigurator : public WireguardConfigurator
{
    Q_OBJECT
public:
    AwgConfigurator(SshSession* sshSession, QObject *parent = nullptr);

    rampage::ProtocolConfig createConfig(const rampage::ServerCredentials &credentials, rampage::DockerContainer container,
                                const rampage::ContainerConfig &containerConfig,
                                const rampage::DnsSettings &dnsSettings,
                                rampage::ErrorCode &errorCode) override;
};

#endif // AWGCONFIGURATOR_H
