/***************************************************************************/
/*               CDFBP: C++ Data Files Batch Processing                    */
/*                                                                         */
/*                  Renxiong Wang, wang0402@umd.edu                        */
/*                                                                         */
/*                       Department of Physics                             */
/*                                                                         */
/*                University of Maryland, College Park                     */
/***************************************************************************/

#include<sstream>

#include<iostream>

#include<string>

#include<stdio.h>

#include<stdlib.h>

#include"OPERATION.h"

#include<fstream>

using namespace std;

int main()
{ 
  std::string indirectory; /*input directory*/

  std::string outdirectory;/*output directory*/
  
  int  OPERATION;     /*operation*/
  
  

  ifstream indir("CDFBP_info/indirectory");

  getline (indir, indirectory);

  indir.close();
  
  const char* INDIRECTORY = indirectory.c_str();

  cout<<"The directory is  " << INDIRECTORY <<endl;
  

  ifstream outdir("CDFBP_info/outdirectory");

  getline (outdir, outdirectory);

  outdir.close();  

  const char* OUTDIRECTORY = outdirectory.c_str();

  cout<<"The output directory is " <<OUTDIRECTORY<<endl;
  
 DEAL:

  cout << "Please select the operation you want to do"<<endl;

  cout << " 1.copy datas\n 2.generate datas\n 3.fit datas\n 4.plot datas\n 5.end\n"<<endl;

  cin  >> OPERATION;

  switch(OPERATION)

    {

    case 1: 
    
      cout << "******************Copy the datas********************" << endl;
      
      COPY(INDIRECTORY,OUTDIRECTORY);
      
      cout << "****************************************************" << endl;

      goto DEAL;

    case 2: 
      
      cout << "******************Generate the datas****************" << endl;
      
      GENERATE(INDIRECTORY,OUTDIRECTORY);
      
      goto DEAL;

      cout << "****************************************************" << endl;

    case 3: 
      
      cout << "******************Fit the datas*********************" << endl;

      PLOT(INDIRECTORY,OUTDIRECTORY);

      cout << "****************************************************" << endl;

      goto DEAL;

    case 4: 

      cout << "******************Plot the datas********************" << endl;

      PLOT(INDIRECTORY,OUTDIRECTORY);

      cout << "****************************************************" << endl;

      goto DEAL;

    case 5: 

      cout << "The program ends" << endl;

    }
  return 0;
}
