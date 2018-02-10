//
//  angles.cpp
//  MazeV1
//
//  Created by Alexa Orrico on 2/8/18.
//  Copyright © 2018 Andrew and Alexa. All rights reserved.
//

#include <stdio.h>
#include <cmath>

double check_angle(double angle) {
    if (angle < double(0))
        angle += 360;
    else if (angle >= double(360))
        angle -= 360;
    return (angle);
}
