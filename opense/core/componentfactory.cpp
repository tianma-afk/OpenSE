#include "componentfactory.h"

// 在这里定义静态成员（整个程序只存在一份）
std::unordered_map<QString, std::function<Component*()>> ComponentFactory::creators;
std::unordered_map<QString, ComponentMeta> ComponentFactory::metaMap;

Component* ComponentFactory::createComponent(const QString &type) {
    auto it = creators.find(type);
    if (it != creators.end()) {
        return it->second();
    }
    return nullptr;
}

void ComponentFactory::registerComponent(const QString &type, std::function<Component*()> creator) {
    creators[type] = creator;
}

void ComponentFactory::registerComponent(
    const QString &type,
    std::function<Component*()> creator,
    const ComponentMeta &meta
    ) {
    creators[type] = creator;
    metaMap[type] = meta; // 同时存储元信息
}

std::vector<ComponentMeta> ComponentFactory::getAllComponentsMeta() {
    std::vector<ComponentMeta> metas;
    for (auto &pair : metaMap) {
        metas.push_back(pair.second);
    }
    return metas;
}

ComponentMeta ComponentFactory::getComponentMeta(const QString &type) {
    return metaMap[type];
}
