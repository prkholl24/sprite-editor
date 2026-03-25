#ifndef PIXEL_H
#define PIXEL_H

#include <QObject>


class pixel : public QObject
{
    Q_OBJECT
public:
    explicit pixel(QObject *parent = nullptr);

    pixel(std::vector<int>& color);

    std::vector<int>& getColor();

    void setColor(std::vector<int>& newColor);

    void setOpacity(int opacity);

private:
    //Color expressed as 4 int values
    //Red, Green, Blue, Alpha (Gamma/Opacity)
    std::vector<int> color;


signals:
};

#endif // PIXEL_H
