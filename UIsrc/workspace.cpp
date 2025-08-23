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

    // 将视图坐标（鼠标位置）转换为场景坐标
    QPointF scenePos = this->view->mapToScene(event->position().toPoint());
    qDebug()<<scenePos;
    // 检查是否在手机屏幕区域内
    if (this->screenRect.contains(scenePos)) {
        // 创建组件并添加到场景
        Component *item = new Component(componentType);
        item->setPos(scenePos); // 放置在拖拽结束位置
        this->scene->addItem(item);
    }

    event->acceptProposedAction();
}

// 组件项构造函数：根据类型初始化样式
WorkSpace::Component::Component(const QString &type) : type(type) {
    setFlag(QGraphicsItem::ItemIsMovable);    // 允许移动
    setFlag(QGraphicsItem::ItemIsSelectable); // 允许选中

    // 根据组件类型设置样式
    if (type == "button") {
        size = QSizeF(100, 30);
        color = Qt::green;
        text = "按钮";
    } else if (type == "label") {
        size = QSizeF(120, 25);
        color = Qt::yellow;
        text = "文本标签";
    } else if (type == "textbox") {
        size = QSizeF(150, 30);
        color = Qt::white;
        text = "输入框";
    } else {
        size = QSizeF(80, 80);
        color = Qt::gray;
        text = "组件";
    }
}

// 定义组件边界（用于碰撞检测和绘制范围）
QRectF WorkSpace::Component::boundingRect() const {
    return QRectF(0, 0, size.width(), size.height());
}

// 绘制组件外观
void WorkSpace::Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    qDebug()<<"绘制组件";
    // 绘制组件背景（圆角矩形）
    painter->setPen(Qt::black); // 边框色
    painter->setBrush(color); // 背景色
    painter->drawRoundedRect(boundingRect(), 5, 5); // 圆角

    // 绘制组件文本（居中）
    painter->drawText(boundingRect(), Qt::AlignCenter, text);
}
