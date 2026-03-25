#ifndef PIXEL_H
#define PIXEL_H

#include <QObject>


class Pixel : public QObject
{
    Q_OBJECT
public:
    explicit Pixel(QObject *parent = nullptr);

    //Constructor which takes a color
    Pixel(std::vector<int>& color);

    //Copy Constructor
    Pixel(Pixel& px);

    //Assignment Operator
    void operator=(Pixel& px);

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
