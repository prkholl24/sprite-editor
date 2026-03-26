#include "frame.h"

Frame::Frame(QObject *parent)
    : QObject{parent}
{}

Frame::Frame(int width, int height){

    this->width = width;
    this->height = height;

    std::vector<int> defaultColor {255, 255, 255, 1};

    for (int i = 0; i < width; i++ ){
        for(int z = 0; z < height; z++){

            pixels[i][z].setColor(defaultColor);

        }
    }



}

Pixel& Frame::getPixel(int x, int y) {
    return pixels[x][y];
}

void Frame::setPixel(int x, int y, Pixel& p) {
    pixels[x][y] = p;
}

void Frame::changeResolution(int w, int h) {
    width = w;
    height = h;
    clearAll();



    /*What behavior do we want?
     * Do we want it to keep the image in the bottom left?
     * Stay in the middle?
     * If its in the middle, it must be a square so things can be mapped propperly.
     * Why do we need/have a width and height if the image is a square?
     * We only need one dimension.
     */



}

void Frame::clearAll(){
    for(std::vector<Pixel> i : pixels){
        i.clear();
    }

    pixels.clear();

}

