//
//  FourMomentum.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "FourMomentum.hpp"

FourMomentum::FourMomentum(float x, float y, float z, float mass) {

	px = x;
	py = y;
	pz = z;
	e = sqrt(pow(mass, 2) + pow(this->getMomentum(), 2));
}

float FourMomentum::getEnergy() {
	try {
		if(e <= 0){
			throw e;
		}
	} catch (float e) {
//		cout << "An exception ocurred, the value of energy can't be " << e << ", Energy must be calculated." << endl;
	}
	return e;
}

float FourMomentum::getMomentum() {
	return sqrt(pow(px, 2) + pow(py, 2) + pow(pz, 2));
}

float FourMomentum::getTransverseMomentum() {
	return sqrt(pow(px, 2) + pow(py, 2));
}

std::vector<float> FourMomentum::getMomentumVtx(){
	std::vector<float> vec = {px, py, pz};
	return vec;
}

std::vector<float> FourMomentum::getTransverseMomentumVtx(){
	std::vector<float> vec = {px, py};
	return vec;
}
