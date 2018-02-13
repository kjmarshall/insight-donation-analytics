// System includes --------------------
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// Own includes --------------------
#include "campaign-book.hpp"

using namespace DA; //stands for "[D]onation [A]nalytics"

//main function
int main( int argc, char *argv[ ] ) {
  //-------------------------------------------------------------------------
  //parse command line arguments
  std::string infile_data, infilep, outfile;
  if ( argc != 4 ) {
    std::cerr << "Ooops... Incorrect Usage" << std::endl
	      << "  Required Usage: ./<executable> <input-donor-file> <input-percentage-file> <output-file>" << std::endl;
    exit(1);
  }
  else {
    infile_data  = std::string( argv[1] );
    infilep  = std::string( argv[2] );
    outfile = std::string( argv[3] );
  }
  //-------------------------------------------------------------------------
  //create file input streams
  std::ifstream FIN_DONORS( infile_data, std::ifstream::in );
  std::ifstream FIN_PER( infilep, std::ifstream::in );
  if ( !FIN_DONORS ) {
    std::cerr << "Ooops... Could not open InputFile: " << infile_data << std::endl;
    exit(1);
  }
  if ( !FIN_PER ) {
    std::cerr << "Ooops... Could not open InputFile: " << infilep << std::endl;
    exit(1);
  }
  //create output file stream
  std::ofstream FOUT( outfile, std::ofstream::out );
  //-------------------------------------------------------------------------
  //get percentage
  double percentage;
  string line;
  int line_ctr = 0;
  for ( ; getline( FIN_PER, line );  ) {
    percentage = stod( line );
    line_ctr++;  //make sure there's just one line.
  }
  if ( line_ctr > 1 ) {
    std::cerr << "Ooops... Percentage file has more than 1 line: " << std::endl
	      << "  Required: 1 line with double value for percentage" << std::endl;
    exit( 1 );
  }
  //-------------------------------------------------------------------------
  //create campaign book and process
  CampaignBook cbook( percentage, FIN_DONORS, FOUT );

  cbook.Process( );
  //-------------------------------------------------------------------------
  //close files
  FIN_DONORS.close( );
  FIN_PER.close( );
  FOUT.close( );
  return 0;
}
