//
//  ParticleCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef ParticleCandidate_hpp
#define ParticleCandidate_hpp

#include "TLorentzVector.h"

class ParticleCandidate {
private:
	float mass_pdg;
	float invariant_mass;

protected:
	TLorentzVector four_momentum;
	
public:
	ParticleCandidate(float px, float py, float pz, float mass);
	ParticleCandidate(TLorentzVector fm, float mass);
	
	float getEnergy();
	float getMomentum();
	float getTransverseMomentum();
	
	float getPDGMass();
	float getInvariantMass();
	TLorentzVector getFourMomentum();
	void fit();
};

// Member functions definitions including constructor


#endif /* ParticleCandidate_hpp */
