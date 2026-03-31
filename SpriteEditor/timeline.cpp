#include "timeline.h"
#include "controller.h"
#include "ui_timeline.h"

Timeline::Timeline(QWidget *parent, Controller* controller)
    : QWidget(parent)
    , ui(new Ui::Timeline)
    , selectedIndex(-1)
{
    ui->setupUi(this);

    ui->frameLayout->addStretch();

    connect(ui->addFrameButton, &QPushButton::clicked,
            this, &Timeline::onAddFrameClicked);
    connect(ui->removeFrameButton, &QPushButton::clicked,
            this, &Timeline::onRemoveFrameClicked);

    connect(ui->fpsSlider, &QSlider::valueChanged,
            this, &Timeline::onFpsSliderChanged);

    // Note: sendPixmap -> updateButtonImage is connected in MainWindow
    // since the timeline is created by Qt Designer without a controller reference

    addFrame();
}

Timeline::~Timeline()
{
    delete ui;
}

void Timeline::addFrame()
{
    QPushButton* frameBtn = new QPushButton(ui->scrollContent);
    frameBtn->setFixedSize(FRAME_SIZE, FRAME_SIZE);
    frameBtn->setText(QString::number(frameButtons.size() + 1));

    frameBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #ffffff;"
        "   border: 2px solid #cccccc;"
        "}"
        "QPushButton:hover {"
        "   border: 2px solid #888888;"
        "}"
    );

    connect(frameBtn, &QPushButton::clicked, this, &Timeline::onFrameClicked);

    int insertIndex = ui->frameLayout->count() - 1;
    ui->frameLayout->insertWidget(insertIndex, frameBtn);

    frameButtons.append(frameBtn);

    int newIndex = frameButtons.size() - 1;

    // Emit frameAdded FIRST so the model can add the frame
    emit frameAdded(newIndex);

    // Then select the new frame (this emits frameSelected)
    selectFrame(newIndex);
}

void Timeline::removeFrame(int index)
{
    if (index < 0 || index >= frameButtons.size()) {
        return;
    }

    if (frameButtons.size() <= 1) {
        return;
    }

    QPushButton* btn = frameButtons.takeAt(index);
    ui->frameLayout->removeWidget(btn);
    delete btn;

    for (int i = 0; i < frameButtons.size(); i++) {
        frameButtons[i]->setText(QString::number(i + 1));
    }

    if (selectedIndex >= frameButtons.size()) {
        selectedIndex = frameButtons.size() - 1;
    }
    updateFrameStyles();

    emit frameRemoved(index);
}

int Timeline::frameCount() const
{
    return frameButtons.size();
}

int Timeline::selectedFrame() const
{
    return selectedIndex;
}

void Timeline::selectFrame(int index)
{
    if (index < 0 || index >= frameButtons.size()) {
        return;
    }

    selectedIndex = index;
    updateFrameStyles();

    ui->scrollArea->ensureWidgetVisible(frameButtons[index]);

    emit frameSelected(index);
}

int Timeline::fps() const
{
    return ui->fpsSlider->value();
}

void Timeline::setFps(int value)
{
    ui->fpsSlider->setValue(value);
}

void Timeline::setFrameCount(int count)
{
    // Block signals to avoid triggering model changes while syncing
    blockSignals(true);

    // Clear all existing buttons
    while (!frameButtons.isEmpty()) {
        QPushButton* btn = frameButtons.takeLast();
        ui->frameLayout->removeWidget(btn);
        delete btn;
    }
    selectedIndex = -1;

    // Add the specified number of frames
    for (int i = 0; i < count; ++i) {
        addFrame();
    }

    blockSignals(false);

    // Select the first frame after syncing
    if (count > 0) {
        selectFrame(0);
    }
}

void Timeline::onFrameClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (!clickedBtn) {
        return;
    }

    int index = frameButtons.indexOf(clickedBtn);
    if (index >= 0) {
        selectFrame(index);
    }
}

void Timeline::onAddFrameClicked()
{
    addFrame();
}

void Timeline::onRemoveFrameClicked()
{
    removeFrame(selectedIndex);
}

void Timeline::onFpsSliderChanged(int value)
{
    emit fpsChanged(value);
}

void Timeline::updateFrameStyles()
{
    for (int i = 0; i < frameButtons.size(); i++) {
        if (i == selectedIndex) {
            frameButtons[i]->setStyleSheet(
                "QPushButton {"
                "   background-color: #e0e0ff;"
                "   border: 3px solid #4444ff;"
                "}"
            );
        } else {
            frameButtons[i]->setStyleSheet(
                "QPushButton {"
                "   background-color: #ffffff;"
                "   border: 2px solid #cccccc;"
                "}"
                "QPushButton:hover {"
                "   border: 2px solid #888888;"
                "}"
            );
        }
    }
}

void Timeline::updateButtonImage(int index, QPixmap image) {
    if (index < 0 || index >= frameButtons.size())
        return;
    frameButtons[index]->setIcon(QIcon(image));
    frameButtons[index]->setIconSize(frameButtons[index]->size());
}
