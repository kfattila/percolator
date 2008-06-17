/*******************************************************************************
 * Percolator unofficial version
 * Copyright (c) 2006-8 University of Washington. All rights reserved.
 * Written by Lukas K�ll (lukall@u.washington.edu) in the 
 * Department of Genome Science at the University of Washington. 
 *
 * $Id: Scores.h,v 1.41 2008/06/17 23:21:44 lukall Exp $
 *******************************************************************************/
#ifndef SCORES_H_
#define SCORES_H_
#include <vector>
#include <map>
using namespace std;
#include "DescriptionOfCorrect.h"
#include "PSMDescription.h"
class SetHandler;

class ScoreHolder{
public:
  double score; // ,q,pep;
  PSMDescription * pPSM;
//  const double * featVec;
  int label;
  ScoreHolder():score(0.0),pPSM(NULL),label(0){;}
  ScoreHolder(const double &s,const int &l, PSMDescription * psm = NULL):score(s),pPSM(psm),label(l){;}
  virtual ~ScoreHolder() {;}
  pair<double,bool> toPair() {return pair<double,bool>(score,label>0);}
};

inline bool operator>(const ScoreHolder &one, const ScoreHolder &other); 
inline bool operator<(const ScoreHolder &one, const ScoreHolder &other); 

class AlgIn;

class Scores
{
public:
	Scores();
	~Scores();
    void merge(vector<Scores>& sv);
	double calcScore(const double * features) const;
    vector<ScoreHolder>::iterator begin() {return scores.begin();}
    vector<ScoreHolder>::iterator end() {return scores.end();}    
	int calcScores(vector<double>& w, double fdr=0.0);
    void fillFeatures(SetHandler& norm,SetHandler& shuff);
    void createXvalSets(vector<Scores>& train,vector<Scores>& test, const unsigned int xval_fold);
    void recalculateDescriptionOfGood(const double fdr);
    void generatePositiveTrainingSet(AlgIn& data,const double fdr,const double cpos);
    void generateNegativeTrainingSet(AlgIn& data,const double cneg);
    void normalizeScores();
    int getInitDirection(const double fdr, vector<double>& direction, bool findDirection);
     ScoreHolder* getScoreHolder(const double *d);
    void calcPep();
    double estimatePi0();
    void printRoc(string & fn); 
    void fill(string & fn);
    inline unsigned int size() {return (pos+neg);} 
    inline unsigned int posSize() {return (pos);} 
    inline unsigned int posNowSize() {return (posNow);} 
    inline unsigned int negSize() {return (neg);} 
    static double pi0;
    double factor;
protected:
    vector<double> w_vec;
    int neg,pos,posNow;
    double q1,q3;
    vector<ScoreHolder> scores;
    map<const double *,ScoreHolder *> scoreMap; 
    DescriptionOfCorrect doc;
};

#endif /*SCORES_H_*/
