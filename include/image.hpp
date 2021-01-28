#ifndef IMAGE_H
#define IMAGE_H

struct Image
{
    Image(int _h, int _w, int _c): h(_h), w(_w), c(_c)
    {
        data = new float[h * w * c];
    }
    virtual ~Image()
    {
        if (data) delete data;
    }
    int h;
    int w;
    int c;
    float* data;
};

#endif
