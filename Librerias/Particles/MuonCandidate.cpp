//
//  MuonCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "MuonCandidate.hpp"

MuonCandidate::MuonCandidate(float px, float py, float pz):ParticleCandidate(px, py, pz, MUON_MASS) {}

double MuonCandidate::getETA(){
	return four_momentum.Eta();
}
