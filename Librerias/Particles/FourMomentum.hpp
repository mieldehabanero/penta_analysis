//
//  FourMomentum.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef FourMomentum_hpp
#define FourMomentum_hpp

class FourMomentum {
private:
	float e;
	float px;
	float py;
	float pz;
	
public:
	FourMomentum(float x, float y, float z, float mass);
	FourMomentum(){};
	float getEnergy();
	float getMomentum();
	float getTransverseMomentum();
	std::vector<float> getTransverseMomentumVtx();
	std::vector<float> getMomentumVtx();
	
	// Overload + operator to add two Box objects.
	FourMomentum operator+(const FourMomentum& fm2) {
		FourMomentum fm1;
		fm1.e = this->e + fm2.e;
		fm1.px = this->px + fm2.px;
		fm1.py = this->py + fm2.py;
		fm1.pz = this->pz + fm2.pz;
		return fm1;
	}
};

#endif /* FourMomentum_hpp */
