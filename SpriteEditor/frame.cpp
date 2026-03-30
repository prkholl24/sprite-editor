/**
 * @file frame.cpp
 * @brief implementation of the Frame class.
 *
 * This class manages a 2D array of Pixel objects which represents a still image.
 *
 * @authors Charles Adair, Armando Calrillo, Brady Nelson, Lindsey Reese, Kent Wilkison, Parker Hollingsed
 * @date 3/26/2026
 *
 * Last Revision: 3/26/2026 3:00PM MST by Charles Adair
 */
#include "frame.h"
#include <iostream>

Frame::Frame(int x, int y)
    : width(x), height(y)
{
    pixels.resize(width);
    for (int i = 0; i < width; i++) {
        pixels[i].resize(height);
    }
 }

Pixel& Frame::getPixel(int x, int y) {
    return pixels[x][y];
}

int Frame::getWidth() const {
    return width;
}

int Frame::getHeight() const {
    return height;
}

QJsonObject Frame::toJson() const {
    QJsonObject json;

    QJsonArray jsonPixel;
    QJsonArray Inner;


    for (const std::vector<Pixel> &row : pixels){
        QJsonArray Inner;
        for (const Pixel &column : row){
            Inner.append(column.toJson());
        }
        jsonPixel.append(Inner);

    }

    json["PixelGrid"] = jsonPixel;
    json["Size"] = width;

    return json;
}


Frame Frame::fromJson(const QJsonObject &json){
    std::cout << "in FrameFromJson" << std::endl;
    Frame copyFrame(json["Size"].toInt(),json["Size"].toInt());
    QJsonArray jsonArray = json["PixelGrid"].toArray();

     std::cout << "Frame:62" << std::endl;

    int x = 0;
    for (auto main : std::as_const(jsonArray)){
        int y = 0;
         std::cout << "Frame Outter array" << std::endl;
        QJsonArray inner = main.toArray();
        for (const QJsonValue &inner : std::as_const(inner)){
             std::cout << "Frame Inner Array: y: " << y << " x: "<< x << std::endl;
            Pixel testingPixel = Pixel::fromJson(inner.toObject());
            copyFrame.getPixel(x,y) = testingPixel;
            y++;
        }
        x++;
    }
    std::cout << "above return copyFrame in frame" << std::endl;
    return copyFrame;
}
