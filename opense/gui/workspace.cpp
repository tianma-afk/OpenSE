#include "workspace.h"
#include<QStyleOption>
#include<QDragEnterEvent>
#include<QMimeData>
WorkSpace::WorkSpace(QWidget *parent)
    : QWidget{parent}
{
    this->initialUI();
}

void WorkSpace::paintEvent(QPaintEvent *event)
{
    //保证样式表正常绘制
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    // 注意：如果有子部件或其他绘制逻辑，需要在这里继续处理
    QWidget::paintEvent(event);
}

void WorkSpace::initialUI()
{
    // 1. 初始化图形场景和视图
    this->scene = new WSScene(this);
    this->view = new QGraphicsView(this->scene, this);
    this->view->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    this->view->setAcceptDrops(true);                  // 允许拖放
    this->setAcceptDrops(true); // 允许接收拖放
    // 3. 定义手机屏幕区域（根据实际图片调整坐标！）
    this->screenRect = QRectF(-155, -355, 310, 710);
    this->scene->setSceneRect(this->screenRect);
    // 4. 布局：视图充满工作区
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(this->view);
    setLayout(layout);

    // 设置视图属性以最佳方式显示图片
    this->view->setRenderHint(QPainter::SmoothPixmapTransform); // 平滑缩放
    this->view->setResizeAnchor(QGraphicsView::AnchorViewCenter); // 调整大小时锚定中心
    this->view->setAlignment(Qt::AlignCenter); // 居中显示

    this->setAttribute(Qt::WA_AcceptDrops, true); // 显式开启拖放支持
    this->view->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 让视图对鼠标事件“透明”，优先触发父部件事件
}

void WorkSpace::drawComponent(const QString &componentType, const QPointF &scenePos)
{
    // 关键：通过工厂创建组件，无需知道具体类
    qDebug()<<"创建component";
    Component *component = ComponentFactory::createComponent(componentType);
    if (component!=nullptr) {
        component->setPos(scenePos);
        this->scene->addItem(component);
        qDebug()<<"加入组件";
        emit signal_addItemInList(nullptr,component);
    }
}

// 处理拖拽进入：只接受文本类型的组件数据
void WorkSpace::dragEnterEvent(QDragEnterEvent *event) {
    qDebug()<<"进入";
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction(); // 接受拖拽
    }
}

void WorkSpace::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

// 处理放置：在屏幕区域内创建组件
void WorkSpace::dropEvent(QDropEvent *event) {
    QString componentType = event->mimeData()->text();
    if (componentType.isEmpty()) return;
    QPointF scenePos = this->view->mapToScene(event->position().toPoint());
    if (this->screenRect.contains(scenePos)) {
        this->drawComponent(componentType,scenePos);
    }
    event->acceptProposedAction();
}
