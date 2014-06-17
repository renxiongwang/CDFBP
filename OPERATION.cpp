/***************************************************************************/
/*               CDFBP: C++ Data Files Batch Processing                    */
/*                                                                         */
/*                  Renxiong Wang, wang0402@umd.edu                        */
/*                                                                         */
/*                       Department of Physics                             */
/*                                                                         */   
/*                University of Maryland, College Park                     */
/***************************************************************************/

#include <iostream>

#include <fstream>

#include <stdlib.h>

#include <sstream>

#include <dirent.h>

#include "OPERATION.h"

using namespace std;

/*Function READTILE: input the filename, get the title*/

void READTITLE(const char* filename)
{ 
  int column_number = 0;

  ifstream filein(filename);

  std::string s;

  std::string column_name[10];

  getline(filein,s);

  std::istringstream ss(s);

  cout << "Reading the titles ......" <<endl;

  cout << "The titles are: " << endl;

  while(ss>>column_name[column_number])
    { 
      cout<<"column" << column_number <<" "<< column_name[column_number] <<endl;
      
      column_number++;
    }
}

/*function CPOUT*/

void CPOUT(const char* filename, const char* outfilename, int* column, int copynum)
{
  int i = 0;

  int column_number = 0;

  ifstream filein(filename);

  ofstream fileout(outfilename);

  std::string s;

  std::string column_name[10];
 
  while(getline(filein,s))
    {
      std::istringstream ss(s);

      while(ss>>column_name[column_number])
	{
	  column_number++;
	}  

      while(i<copynum)
	{
	  fileout<<column_name[column[i]]<<' ';

	  i++;
	}

      fileout<<'\n';

      i = 0;

      column_number = 0;
    }

  fileout.close();
}

/*function GENOUT*/
void GENOUT(const char* filename, const char* outfilename,int* column, int copynum)
{ 
  int i = 0;

  int column_number = 0;

  ifstream filein(filename);

  ofstream fileout(outfilename);

  std::string s;

  std::string column_name[10];
  
  getline(filein,s);

  std::istringstream ss(s);

  while(ss>>column_name[column_number])
    {
      column_number++;
    }  
  while(i < copynum)
    {
      fileout << column_name[column[i]] << ' ';

      i++;
    }

  fileout << "result";

  fileout << '\n';

  i = 0;

  column_number = 0;
  
  while(getline(filein,s))
    {
      std::istringstream ss(s);

      while(ss>>column_name[column_number])
	{
	  column_number++;
	}  
      while(i<copynum)
	{
	  fileout << column_name[column[i]] << ' ';

	  i++;
	}

      fileout << atof(column_name[0].c_str()) + atof(column_name[1].c_str());

      fileout << '\n';

      i = 0;

      column_number = 0;
    }

  fileout.close();
}

/*PLOUT*/
void PLOUT(const char* filename, const char* outfilename,int* column, int copynum)
{ 
  char buffer[200];

  int i = 0;

  int column_number = 0;

  ifstream filein(filename);

  ofstream fileout(outfilename);
  
  std::string s;
  
  std::string column_name[10];
  
  getline(filein,s);
  
  std::istringstream ss(s);

  while(ss >> column_name[column_number])
    {
    }  
  
  while(getline(filein,s))
    {
      std::istringstream ss(s);
      while(ss >> column_name[column_number])
	{
	  column_number++;
	}  
      while(i < copynum)
	{
	  fileout << column_name[column[i]]<<' ';
	  i++;
	}

      fileout << atof(column_name[0].c_str())+atof(column_name[1].c_str());

      fileout << '\n';

      i = 0;

      column_number = 0;
    }

  fileout.close();

  std::string temp;

  ifstream gnu_basic("CDFBP_info/gnu_basic");

  ofstream gnu_info1("CDFBP_info/gnu_info");
  
  while(getline(gnu_basic,s))
    gnu_info1 << s <<"\n";

  gnu_info1.close();

  gnu_basic.close();
  
  sprintf(buffer, "set terminal postscript\nset output '%s.eps'\nplot '%s'",outfilename,outfilename);

  ofstream gnu_info2("CDFBP_info/gnu_info", ios::app);

  gnu_info2 << buffer << "\n" << endl;

  gnu_info2.close();
  
  system("gnuplot 'CDFBP_info/gnu_info'");

}

void COPY(const char* INDIRECTORY,const char* OUTDIRECTORY )
{
  std::string indir,outdir,namefor,name,nameout,out;

  indir = INDIRECTORY;

  outdir = OUTDIRECTORY;

  int i=0;

  int column[10];

  char tt[30];
  
  cout<<"Copy data from "<<INDIRECTORY<<" to "<<OUTDIRECTORY<<endl;
  
  ifstream ocinfo("CDFBP_info/column_info.txt");

  while(ocinfo>>column[i])
    {
      i++;
    }
  
  struct dirent* ent = NULL;

  DIR *pDir;

  pDir = opendir(INDIRECTORY);
  
  cout << "Open the directory:" << INDIRECTORY << "......" <<  endl;
  
  if(pDir == NULL)
    {
      cout<<"The indirectory doesn't exist!"<<endl;

      return;
    }
  
  cout<<"Open successfully!"<<endl;

  while(NULL!=(ent=readdir(pDir)))
    {
      if(ent->d_type == 8)
	namefor=ent->d_name;

        name = indir+"/"+namefor; 

        nameout=outdir+"/out"+namefor;

        cout<< "Copy " << name << " to " << nameout << "......" << endl;
       
        CPOUT(name.c_str(),nameout.c_str(),column,i);
    }
}

void GENERATE(const char* INDIRECTORY,const char* OUTDIRECTORY )
{
  std::string indir,outdir,namefor,name,nameout,out;

  indir = INDIRECTORY;

  outdir = OUTDIRECTORY;

  int i=0;

  int column[10];

  char tt[30];

  char result[30];

  int  selection;

  ifstream ocinfo("CDFBP_info/column_info.txt");

  while( ocinfo >> column[i])
    {
      i++;
    }
  
  struct dirent* ent = NULL;
  
  DIR *pDir;
  
  pDir = opendir(INDIRECTORY);

  if(pDir == NULL)
    {
      cout<<"The indirectory doesn't exist!"<<endl;
      
      return;
    }
  while(NULL!=(ent=readdir(pDir)))
    {
      if(ent->d_type == 8)
	namefor=ent->d_name;
      
      name = indir+"/"+namefor; 
      
      cout<< "Generate" << name << " to " << nameout << "......" << endl;

      GENOUT(name.c_str(),name.c_str(),column,i);
    }
}


void PLOT(const char* INDIRECTORY,const char* OUTDIRECTORY )
{ 
  std::string indir, outdir, namefor, name, nameout, out, x_label, y_label, title;

  indir = INDIRECTORY;

  outdir = OUTDIRECTORY;

  int i=0;

  int column[10];

  char tt[30];

  cout<<"Copy data from "<<INDIRECTORY<<" to "<<OUTDIRECTORY<<endl;

  ifstream x("CDFBP_info/xlabel");

  getline (x, x_label);

  x.close();

  const char* XLABEL = x_label.c_str();

  ifstream y("CDFBP_info/ylabel");

  getline (y, y_label);

  y.close();

  const char* YLABEL = y_label.c_str();  

  ifstream ftitle("CDFBP_info/title");

  getline (ftitle, title);

  ftitle.close();

  const char* TITLE = title.c_str(); 

  cout<<"The directory is  " << INDIRECTORY <<endl;
  
  ifstream ocinfo("/CDFBP_info/column_info.txt");

  while(ocinfo>>column[i])
    {
      i++;
    }
  
  struct dirent* ent = NULL;

  DIR *pDir;

  pDir = opendir(INDIRECTORY);

  if(pDir == NULL)
    {
      cout<<"The indirectory doesn't exist!"<<endl;

      return;
    }
  while(NULL!=(ent=readdir(pDir)))
    {
      if(ent->d_type == 8)
	namefor=ent->d_name;

        name = indir+"/"+namefor; 

        nameout=outdir+"/plot_"+namefor;

        PLOUT(name.c_str(), nameout.c_str(), column, i);
    }
}
