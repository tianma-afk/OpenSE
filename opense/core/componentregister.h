#ifndef COMPONENTREGISTER_H
#define COMPONENTREGISTER_H

#include"componentfactory.h"
// 注册工具类（通过模板实现自动注册）
template <typename T>
class ComponentRegister {
public:
    // 构造函数：在全局变量初始化时自动调用，完成注册
    ComponentRegister() {
        // 调用工厂的注册函数，绑定类型和创建函数
        ComponentFactory::registerComponent(
            T::staticType(),
            [](){ return new T(); } //  lambda表达式：创建组件实例
            );
    }
};

// 宏定义：简化组件注册（在组件类定义后使用）
#define REGISTER_COMPONENT(ClassName) \
static ComponentRegister<ClassName> s_##ClassName##_register;


#endif // COMPONENTREGISTER_H
