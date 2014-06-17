/***************************************************************************/
/*               CDFBP: C++ Data Files Batch Processing                    */
/*                                                                         */
/*                  Renxiong Wang, wang0402@umd.edu                        */
/*                                                                         */
/*                       Department of Physics                             */
/*                                                                         */ 
/*                University of Maryland, College Park                     */
/***************************************************************************/
#ifndef _OPERATION_H
#define _OPERATION_H
typedef const char* string;
void COPY(string INDIRECTORY, string OUTDIRECTORY);
void GENERATE(string INDIRECTORY, string OUTDIRECTORY);
void PLOT(string INDIRECTORY, string OUTDIRECTORY);
#endif
