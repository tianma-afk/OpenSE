#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QString>
#include <unordered_map>
#include <functional>
#include"core/componentmeta.h"
#include "components/component.h"

class ComponentFactory {
private:
    // 仅声明静态成员（不定义）
    static std::unordered_map<QString, std::function<Component*()>> creators;
    static std::unordered_map<QString, ComponentMeta> metaMap;
public:
    static Component* createComponent(const QString &type);
    static void registerComponent(const QString &type, std::function<Component*()> creator);
    // 注册组件（新增元信息参数）
    static void registerComponent(
        const QString &type,
        std::function<Component*()> creator,
        const ComponentMeta &meta
        );

    // 获取所有组件的元信息（供组件面板使用）
    static std::vector<ComponentMeta> getAllComponentsMeta();

    // 根据类型获取单个组件的元信息
    static ComponentMeta getComponentMeta(const QString &type);
};

#endif // COMPONENTFACTORY_H
