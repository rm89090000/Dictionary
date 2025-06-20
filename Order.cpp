/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA7
* Order.cpp
* Puts the dictionary in Order 
***/ 




#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){

       ifstream in;
       ofstream out;

      if(argc!=3){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

     in.open(argv[1]);
      if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }


out.open(argv[2]);
  if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   Dictionary A;
string line;
int line_count = 0;
 while(getline(in, line) )  {
      line_count++;
      A.setValue(line, line_count);

}


out<<A.to_string()<<endl;
out<<A.pre_string()<<endl;
in.close();
out.close();

return(EXIT_SUCCESS);


}
