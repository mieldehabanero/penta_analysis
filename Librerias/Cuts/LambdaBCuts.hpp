//
//  LambdaBCuts.hpp
//  
//
//  Created by Ricardo Zamora on 6/5/18.
//

#ifndef LambdaBCuts_hpp
#define LambdaBCuts_hpp

#include "CandidateCuts.hpp"
#include "../Particles/LambdaBCandidate.hpp"
#include <stdio.h>

class LambdaBCuts: public CandidateCuts {
public:
	LambdaBCuts();
	int applyCuts(LambdaBCandidate *lambda_b);
	
private:
	//	std::function<int (LambdaBCandidate *)> cuts;
	int pt(LambdaBCandidate *lambda_b);
	int prob(LambdaBCandidate *lambda_b);
	int masa(LambdaBCandidate *lambda_b);

};

#endif /* LambdaBCuts_hpp */
