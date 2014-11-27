#ifndef DATADISTRIBUTION_H 
#define DATADISTRIBUTION_H

#include"Network.h"
#include"Combinations.h"
#include<map>

class DataDistribution{
	public:
	DataDistribution(Network& network, Matrix<int>& observations);
	void assignObservationsToNodes();
	void distributeObservations();
	private:
	int computeParentCombinations(std::vector<unsigned int> parents);
	void assignValueNames(Node& n);
	int getObservationColIndex(unsigned int sample, const Node& n);
	int getObservationRowIndex(unsigned int sample, const Node& n, const Matrix<int>& obsMatrix);
	void assignParentNames(Node& n);
	void countObservations(Matrix<int>& obsMatrix, const Node& n);
	Network& network_;	
	Matrix<int>& observations_;
	std::unordered_map<std::string,int>& observationsMap_;
	std::map<std::pair<int,int>, std::string>& observationsMapR_;
};

#endif