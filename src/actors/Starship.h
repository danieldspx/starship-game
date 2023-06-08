//
// Created by daniel on 08/06/23.
//

#ifndef CANVAS_CLION_STARSHIP_H
#define CANVAS_CLION_STARSHIP_H

#include "../base/interfaces/IEntity.h"

class Starship: public IEntity {
public:
    void render(int screenWidth, int screenHeight) override;
};


#endif //CANVAS_CLION_STARSHIP_H
