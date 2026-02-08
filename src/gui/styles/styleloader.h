#ifndef STYLELOADER_H
#define STYLELOADER_H

#include <QString>

class StyleLoader
{
public:
    enum Style {
        Base = 0,
    };

    static void attach(Style style = Base);
};

#endif // STYLELOADER_H
