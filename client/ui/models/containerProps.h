#ifndef CONTAINERPROPS_H
#define CONTAINERPROPS_H

#include <QObject>
#include "core/utils/containerEnum.h"
#include "core/utils/containers/containerUtils.h"

class ContainerProps : public QObject
{
    Q_OBJECT

public:
    explicit ContainerProps(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString containerTypeToString(int containerIndex) const {
        return rampage::ContainerUtils::containerTypeToString(static_cast<rampage::DockerContainer>(containerIndex));
    }

    Q_INVOKABLE int defaultProtocol(int containerIndex) const {
        return static_cast<int>(rampage::ContainerUtils::defaultProtocol(static_cast<rampage::DockerContainer>(containerIndex)));
    }

    Q_INVOKABLE int containerFromString(const QString &container) const {
        return static_cast<int>(rampage::ContainerUtils::containerFromString(container));
    }

    Q_INVOKABLE bool isUnsupportedContainer(int containerIndex) const {
        return rampage::ContainerUtils::isUnsupportedContainer(static_cast<rampage::DockerContainer>(containerIndex));
    }
};

#endif // CONTAINERPROPS_H

