#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QString>
#include <unordered_map>
#include <functional>
#include "components/component.h"

class ComponentFactory {
private:
    // 仅声明静态成员（不定义）
    static std::unordered_map<QString, std::function<Component*()>> creators;
public:
    static Component* createComponent(const QString &type);
    static void registerComponent(const QString &type, std::function<Component*()> creator);
};

#endif // COMPONENTFACTORY_H
