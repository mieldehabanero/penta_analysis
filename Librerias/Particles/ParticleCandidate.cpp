
//
//  ParticleCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "ParticleCandidate.hpp"

ParticleCandidate::ParticleCandidate(float px, float py, float pz, float mass) {
	mass_pdg = mass;
	float e = sqrt(pow(mass, 2) + pow(px, 2) + pow(py, 2) + pow(pz, 2));
	four_momentum = TLorentzVector(px, py, pz, e);
	invariant_mass = four_momentum.Mag();
}

ParticleCandidate::ParticleCandidate(TLorentzVector fm, float mass){
	mass_pdg = mass;
	four_momentum = TLorentzVector(fm);
	invariant_mass = four_momentum.Mag();
}

float ParticleCandidate::getEnergy() {
	return four_momentum.E();
}

float ParticleCandidate::getMomentum() {
	return four_momentum.Vect().Mag();
}

float ParticleCandidate::getTransverseMomentum() {
	return sqrt(pow(four_momentum.Px(), 2) + pow(four_momentum.Py(), 2));
}

float ParticleCandidate::getPDGMass() {
	return mass_pdg;
}

float ParticleCandidate::getInvariantMass(){
	return invariant_mass;
}
	
TLorentzVector ParticleCandidate::getFourMomentum() {
	return four_momentum;
}

void ParticleCandidate::fit() {
}
