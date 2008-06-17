#ifndef FEATURENAMES_H_
#define FEATURENAMES_H_

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class FeatureNames
{
public:
  FeatureNames();
  virtual ~FeatureNames();
  size_t getNumFeatures() { return featureNames.size();}
  string getFeatureNames();
  
  
  void insertFeature(string& featureName) { featureNames.push_back(featureName);}
  
  int getFeatureNumber(const string& featureName)
     {return distance(find(featureNames.begin(),featureNames.end(),featureName),featureNames.begin());}
  void setSQTFeatures(int minCharge, int maxCharge, bool doEnzyme, bool calcPTMs, bool doManyHitsPerSpectrum,
                                 const string& aaAlphabet, bool calcIntraSetFeatures, bool calcDOC);
  // SQT Feature Number getters, will return -1 if not defined.
  int getMinCharge() { return minCharge; } 
  int getMaxCharge() { return maxCharge; }
  int getChargeFeatNum() { return chargeFeatNum; } 
  int getEnzFeatNum() { return enzFeatNum;}
  int getNumSPFeatNum() { return numSPFeatNum;}
  int getPtmFeatNum() { return ptmFeatNum;}
  int getRank1FeatNum() { return rank1FeatNum;}
  int getAaFeatNum() { return aaFeatNum;}
  int getIntraSetFeatNum() { return intraSetFeatNum;}
  int getDocFeatNum() { return docFeatNum;}
protected:
  vector<string> featureNames;
  int minCharge, maxCharge;
  int chargeFeatNum, enzFeatNum, numSPFeatNum, ptmFeatNum, rank1FeatNum, aaFeatNum, intraSetFeatNum, docFeatNum;
};

#endif /*FEATURENAMES_H_*/
