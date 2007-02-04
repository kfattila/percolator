/*******************************************************************************
 * Percolator v 1.00
 * Copyright (c) 2006-7 University of Washington. All rights reserved.
 * Written by Lukas K�ll (lukall@u.washington.edu) in the 
 * Department of Genome Science at the University of Washington. 
 *
 * $Id: DataSet.h,v 1.35 2007/02/04 04:50:39 lukall Exp $
 *******************************************************************************/
#ifndef DATASET_H_
#define DATASET_H_
class Scores;
class Normalizer;
class IntraSetRelation;

class DataSet
{
 public:
	DataSet();
	virtual ~DataSet();
    static string getFeatureNames();
    static void setFeatureNames(string fn){DataSet::featureNames=fn;}
    void readGistData(ifstream & is, vector<unsigned int> ixs);
    void inline setLabel(int l) {label=l;}
    void computeIntraSetFeatures();
    void computeIntraSetFeatures(double *feat,string &pep,set<string> &prots);
    void computeAAFrequencies(const string& pep, double *feat);
    void read_sqt(const string fname,IntraSetRelation * intrarel,const string & wild="", bool match=false);
    void modify_sqt(const string & outFN, const double *w, Scores * pSc ,const string greet, bool dtaSelect);
    static inline int getNumFeatures() { return numFeatures; }
    static void setQuadraticFeatures(bool on)
      { calcQuadraticFeatures=on;}
    static void setTrypticFeatures(bool on)
      { calcTrypticFeatures=on;}
    static void setChymoTrypticFeatures(bool on)
      { chymoInsteadOfTryptic=on;}
    static void setAAFreqencies(bool on)
      { calcAAFrequencies=on;}
    static void setNumFeatures();
    static void inline setHitsPerSpectrum(int hits) {hitsPerSpectrum=hits;}
    static inline int rowIx(int row) { return row*numFeatures; }
    double * getFeature() {return feature;}
    const double * getFeatures(const int pos) const;
    int inline getSize() const {return n_examples;}
    int inline const getLabel() const {return label;}
    double * getNext(int& pos);
    bool getGistDataRow(int& pos,string & out);
    void print_10features();
    void print_features();
    void print(Scores& test, vector<pair<double,string> > & outList);
protected:
    void readFeatures(const string &in,double *feat,int match,set<string> & proteins, string & pep,bool getIntra);
    string modifyRec(const string record, const set<int>& theMs, const double *w, Scores * pSc, bool dtaSelect);
    static unsigned int cntEnz(const string& peptide);
    static double isTryptic(const char n,const char c);
    static double isChymoTryptic(const char n,const char c);
    static double isEnz(const char n,const char c) {return (chymoInsteadOfTryptic?
                                                     isChymoTryptic(n,c):
                                                     isTryptic(n,c));}
    vector<string> ids;
    static bool calcQuadraticFeatures;
    static bool calcTrypticFeatures;
    static bool calcAAFrequencies;
    static bool chymoInsteadOfTryptic;
    static bool calcIntraSetFeatures;
    static int numFeatures;
    static int numRealFeatures;
    static int hitsPerSpectrum;
    static string aaAlphabet;
    static string featureNames;
    const static int maxNumRealFeatures = 16 + 20;
    vector<set<string> > proteinIds;
    vector<string> pepSeq;
    int label;
    double *feature;
    int n_examples;
    string sqtFN;
    string pattern;
    bool doPattern;
    bool matchPattern;
    IntraSetRelation * intra;
};

#endif /*DATASET_H_*/
