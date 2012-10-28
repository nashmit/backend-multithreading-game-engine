
#include "engine.h"

referenceCounting::~referenceCounting() {}

int referenceCounting::GetCount() {
    return count;
}

void referenceCounting::Increase() {
    count++;
}

void referenceCounting::Decrease() {
    count--;
    if(count==0) {
        //printf("DISTRUS\n");
        delete this;
    }
}
