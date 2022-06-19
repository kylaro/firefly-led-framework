#include "ExecTimer.h"
#include <stdio.h>
#include <cstring>


ExecTimer::ExecTimer(){
    timer = new Timing();
    name = NULL;
}


void ExecTimer::start(const char* s){
    if(name != NULL){
        free(name);
    }
    name = (char *)malloc(strlen(s)*sizeof(char));
    strcpy(name, s);
    times.clear();
    lastTime = 0;
    timer->reset();
}

void ExecTimer::add(const char* s){
    times[s] = timer->timerUs() - lastTime;
    lastTime = timer->timerUs();
}


void ExecTimer::print(){
    auto iter = times.begin();
    printf("\n~~~%s~~~\n", name);
    while(iter != times.end()){
        printf("%s = %d us\n", iter->first, iter->second);
        iter++;
    }
    printf("~~~ FPS = %.1f /sec ~~~\n", fps());
}

double ExecTimer::fps(){
    double fps = 1000000.0/(double)lastTime;
    return fps;
}

ExecTimer::~ExecTimer(){
    free(name);
    delete(timer);
}
