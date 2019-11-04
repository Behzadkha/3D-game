#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
using namespace std;
class particle{
public:
	particle();
	float px,py,pz;
	float dx,dy,dz;
	float speed;
	float rx,ry,rz;
	int red,green,blue;
	int size;
	int material;
	int age;
	vector<float> tracex, tracey,tracez;
	
};
#endif