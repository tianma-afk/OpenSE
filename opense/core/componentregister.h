#ifndef COMPONENTREGISTER_H
#define COMPONENTREGISTER_H

#include "components/component.h"
#include "core/componentFactory.h"
#include "core/componentMeta.h"

template <typename T>
class ComponentRegister {
public:
    // 构造函数：接收元信息，完成注册
    ComponentRegister(const ComponentMeta &meta) {
        ComponentFactory::registerComponent(
            T::staticType(),
            [](){ return new T(); },
            meta // 传入元信息
            );
    }
};

// 宏定义：注册组件时指定元信息
#define REGISTER_COMPONENT(ClassName, iconPath, description) \
static ComponentRegister<ClassName> s_##ClassName##_register( \
    ComponentMeta{ClassName::staticType(), iconPath, description} \
    );


#endif // COMPONENTREGISTER_H
