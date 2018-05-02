
//
//  ParticleCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "ParticleCandidate.hpp"

ParticleCandidate::ParticleCandidate(float px, float py, float pz, float mass):four_momentum(px, py, pz, mass) {
	mass_pdg = mass;
	invariant_mass = sqrt(pow(this->getEnergy(), 2) -  pow(this->getMomentum(), 2));
}

ParticleCandidate::ParticleCandidate(FourMomentum fm, float mass){
	four_momentum = fm;
	mass_pdg = mass;
	invariant_mass = sqrt(pow(this->getEnergy(), 2) -  pow(this->getMomentum(), 2));
}

float ParticleCandidate::getEnergy() {
	return four_momentum.getEnergy();
}

float ParticleCandidate::getMomentum() {
	return four_momentum.getMomentum();
}

float ParticleCandidate::getTransverseMomentum() {
	return four_momentum.getTransverseMomentum();
}

float ParticleCandidate::getPDGMass() {
	return mass_pdg;
}

float ParticleCandidate::getInvariantMass(){
	return invariant_mass;
}
	
FourMomentum ParticleCandidate::getFourMomentum() {
	return four_momentum;
}

void ParticleCandidate::fit() {
}
