#include "makePlots.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv){

  TApplication *app = new TApplication("app",0,0);

  TChain *chain = new TChain("hits");
  TChain *chain2 = new TChain("impactPoints");
  TChain *chain3 = new TChain("rechit_var");
//========================
    bool Is_Data;
    
    int arg_tmp = -1;
    if(argc == 2){
        std::string tmp_str(argv[1]);
        if(tmp_str.length() > 1){
            cout << "wrong argument! EXIT!!" << endl;
            exit(-1);}
        arg_tmp = (int)argv[1][0] - int('0');
        
        if(arg_tmp == 0){
            Is_Data = 0;
            cout << "Run MC\n" << endl;}
        if(arg_tmp == 1){
            Is_Data = 1;
            cout << "Run Data\n" << endl;}  }
    else if(argc == 1){
        Is_Data = 1;
        cout << "Run Data\n" << endl;}
    else{
        cout << "wrong argument! EXIT!!" << endl;
        exit(-1);
    }
//=====================
  string filename;
  string inputfile="input.txt";
  ifstream infile(inputfile.c_str());
  while(true){
    
    infile >> filename;
    if(infile.eof()) break;
    if( filename.length() > 2){
      cout << "input file: " << filename << endl;
      chain->Add(filename.c_str());
      chain2->Add(filename.c_str());
      chain3->Add(filename.c_str());
    }
    else{
      cout << filename << " is not available, please check "
	   << inputfile << endl;}
  }
  infile.close();
//======================

  makePlots *M;
  M = new makePlots(chain,chain2,chain3,filename);
  M->Is_Data = Is_Data ;
  //M->Event_Display();
  //M->my_Loop();
  M->Loop();
  return(0);
}
