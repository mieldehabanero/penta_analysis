//
//  KaonCuts.hpp
//  
//
//  Created by Ricardo Zamora on 6/5/18.
//

#ifndef KaonCuts_hpp
#define KaonCuts_hpp

#include "CandidateCuts.hpp"
#include "../Particles/KaonCandidate.hpp"
#include <stdio.h>

class KaonCuts: public CandidateCuts {
public:
	KaonCuts();
	int applyCuts(KaonCandidate *kaon);
	
private:
	//	std::function<int (KaonCandidate *)> cuts;
	int masa(KaonCandidate *kaon);
};

#endif /* KaonCuts_hpp */
