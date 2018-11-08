//
//  LambdaCuts.hpp
//
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef LambdaCuts_hpp
#define LambdaCuts_hpp

#include "CandidateCuts.hpp"
#include "../Particles/LambdaCandidate.hpp"
#include <stdio.h>

class LambdaCuts: public CandidateCuts {
public:
	LambdaCuts();
	int applyCuts(LambdaCandidate *lambda);
	
private:
	//	std::function<int (LambdaCandidate *)> cuts;
	int d0(LambdaCandidate *lambda);
	int chi2(LambdaCandidate *lambda);
	int lxy(LambdaCandidate *lambda);
	int pt(LambdaCandidate *lambda);
	int prob(LambdaCandidate *lambda);
	int masa(LambdaCandidate *lambda);
};

#endif /* LambdaCuts_hpp */


