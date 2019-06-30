#ifndef CHECK_POINT_DATA
#define CHECK_POINT_DATA
#include "Vect2.h"

    class CheckPointData {
        private:
            Vect2 checkPointPos;
        public:
            bool isActive;
            Vect2 GetCheckPointPos() { return checkPointPos; }
            CheckPointData(bool isActive, Vect2 checkPointPos) {
                this->isActive = isActive;
                this->checkPointPos = checkPointPos;
            }
    };


#endif