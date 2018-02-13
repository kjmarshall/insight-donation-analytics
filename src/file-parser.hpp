#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

// System includes --------------------
#include <iostream>
#include <string>
#include <vector>

// Boost includes --------------------
#include <boost/tokenizer.hpp>

namespace DA { // begin DA

  /**
   *FileParser.
   */
  class FileParser {
  public: 	// public typedefs
    typedef std::vector<std::string> StringVectorType;

  private: 	// private typedefs
    
  public: 	//public member functions
    //constructor
    FileParser( std::ifstream& FIN )
      : fin_( FIN ), delimiter_( "|" )
      {
      }
    FileParser(const FileParser &c) = delete;
    FileParser& operator=(const FileParser &c) = delete;
    // ~FileParser();

    //parse line
    bool ParseLine( StringVectorType& tokens ) {
      std::string line2parse;

      std::getline( fin_, line2parse );
      if ( !fin_.eof( ) ) {
	tokens = StringTokenizer( line2parse );
	return true;
      }
      else {
	return false;
      }
    }
  private: 	//private member functions
    //string tokenizer
    StringVectorType StringTokenizer( std::string input ) {
      StringVectorType result;
      //boost::char_delimiters_separator<char> separator(false, delimiter_.c_str());
      //boost::tokenizer< boost::char_delimiters_separator< char > > tok(input,separator);
      typedef boost::tokenizer<boost::char_separator<char>> TokenizerType;
      boost::char_separator<char> sep{"|", "", boost::keep_empty_tokens};
      TokenizerType tok{input, sep};
      TokenizerType::iterator it;
      for (it = tok.begin(); it != tok.end(); ++it)
	result.push_back(*it);

      return result;
    }
    
  public: 	//public data members
    
  private: 	//private data members
    std::ifstream& fin_;
    const std::string delimiter_;
  }; // end of class FileParser

} // end DA

#endif // FILE_PARSER_HPP
