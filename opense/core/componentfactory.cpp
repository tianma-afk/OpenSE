#include "componentfactory.h"

// 在这里定义静态成员（整个程序只存在一份）
std::unordered_map<QString, std::function<Component*()>> ComponentFactory::creators;

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
