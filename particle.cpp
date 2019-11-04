#include "particle.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
particle::particle(){
		this->px = 0;
		this->py = 0;
		this->pz = 0;
		this->dx = RandomFloat(-10.0,10.0);
		this->dy = 200;
		this->dz = RandomFloat(-10.0,10.0);
		this->speed = 0.001;
		this->rx = rand() % 360;
		this->ry = rand() % 360;
		this->rz = rand() % 360;
		this->red = rand() % 2; 
		this->green = rand() % 2; 
		this->blue = rand() % 2; 
		this->size = 0.02;
		this->material = rand()% 3;
		this->age = 0;
	}