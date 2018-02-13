#ifndef CAMPAIGN_BOOK_HPP
#define CAMPAIGN_BOOK_HPP

// System includes --------------------
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype> //isdigit
#include <unordered_map>
#include <map>

// Boost includes --------------------
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/iterator_range.hpp>

// Own includes --------------------
#include "file-parser.hpp"
#include "campaign-contribution.hpp"

namespace DA { // begin DA
/**
 *CampaignBook.
 */
  class CampaignBook {
  public: 	// public typedefs
    typedef vector< CampContrib > VectorCCType;
    typedef unordered_map< string, VectorCCType > UMapSVCCType;
    typedef vector< string > DonorInfoType;
    
  private: 	// private typedefs
    
  public: 	//public member functions
    CampaignBook( double percentage, ifstream& FIN, ofstream& FOUT  )
      : percentage_( percentage ), FIN_( FIN ), FOUT_( FOUT )
      {
      }
    // CampaignBook(const CampaignBook &c);
    // ~CampaignBook();
    
    //main processing function
    void Process( ) {
      //create file parser
      FileParser fp( FIN_ );
      FileParser::StringVectorType tokens;
      while ( fp.ParseLine( tokens ) == true && tokens.size( ) != 0 ) {
	// std::cout << "Tokens Size: " << tokens.size( ) << std::endl;
	// for ( std::size_t i = 0; i < tokens.size( ); ++i ) {
	//   std::cout << tokens[i] << std::endl;
	// }
	this -> AddDonor( tokens );
      }
    }
  private: 	//private member functions
    //function to add a donor based on donor info
    void AddDonor( DonorInfoType& info ) {
      if ( info.size( ) != 21 ) {
	return;
      }
      //Check for valid donor info...
      // per instructions "Input File Considerations"
      if ( info.at(15) != "" ) {
	return;
      }
      else if ( info.at(13) == "" ||
		CheckSizeAndNumeric( info.at(13), 8 ) == false ) {
	return;
      }
      else if ( info.at(10) == "" ||
		CheckSizeAndNumeric( info.at(10).substr(0,5), 5 ) == false ) {
	return;
      }
      else if ( info.at(7) == "" ) {
	return;
      }
      else if ( info.at(0) == "" || info.at(14) == "" ) {
	return;
      }
      
      //make campaign contribution object
      CampContrib cc( info );
      
      //print
      //cc.Print( );

      //dont technically need this...
      //add to contributions vector
      // contribs_.push_back( cc );
      
      //add to contributions map
      // key is "NAME-ZIP_CODE" using first five digits of the zip code...
      string key = BuildKey( info );
      if ( repeat_donors_.find( key ) == repeat_donors_.end( ) ) {
	repeat_donors_.insert( make_pair( key, VectorCCType( ) ) );
	repeat_donors_[key].push_back( cc );
      }
      else {
	//we have a repeat donor...
	repeat_donors_[key].push_back( cc );
	VectorCCType agg_donors; //aggregate donors...
	for ( auto it = repeat_donors_.begin( );
	      it != repeat_donors_.end( ); ++it ) {
	  this -> CrossRefDonor( cc, it, agg_donors );
	}
	//now do output/statistics on aggregate donors
	// cout << "Aggregate Donor List Size: " << agg_donors.size( ) << endl;
	string output = ComputeOutput( agg_donors );
	// cout << output << endl;
	FOUT_ << output << endl;
      }
    }

    //compute statistics
    string ComputeOutput( VectorCCType& agg_donors ) {
      size_t NumDonors = agg_donors.size( );
      size_t tot_contrib = NumDonors;
      double tot_trans_amt = 0.0;
      vector< double > trans_amt_vec;
      for ( size_t i = 0; i < NumDonors; ++i ) {
	double trans_amt = agg_donors[i].GetTRANSACTION_AMT( );
	tot_trans_amt += trans_amt;
	trans_amt_vec.push_back( trans_amt );
      }
      // for ( size_t i = 0; i < trans_amt_vec.size( ); ++i ) {
      // 	cout << trans_amt_vec.at(i) << " ";
      // }
      // cout << endl;
      size_t n = NearestRank( trans_amt_vec );
      int percentile = round( trans_amt_vec.at( n ) );
      // cout << "n,per: " << n << ", " << percentile << endl;
      stringstream ss;
      ss << agg_donors[0].GetCMTE_ID( ) << "|"
	 << agg_donors[0].GetZIP_CODE( ) << "|"
	 << agg_donors[0].GetTRANSACTION_DT( ).substr(4) << "|"
	 << percentile << "|"
	 << tot_trans_amt << "|"
	 << tot_contrib;
      return ss.str( );
    }
    template< typename T >
    size_t NearestRank( vector< T >& vec ) {
      sort( vec.begin( ), vec.end( ) );
      //subtract 1 to adjust to zero indexed arrays
      size_t n = ceil( percentage_/100.0 * double(vec.size( )) ) - 1;
      return n;
    }

    //check date
    bool CheckSizeAndNumeric( const string& str, size_t size ) {
      if ( str.size( ) != size ) //check MMDDYYY format...
	return false;
      
      //check digits
      bool digit_flag = true;
      for ( auto str_ele : str ) {
	if ( isdigit( str_ele ) == false ) {
	  digit_flag = false;
	  break;
	}
      }
      
      return digit_flag;
    }
    string BuildKey( const CampContrib& cc ) {
      string key = cc.GetNAME( ) + "-" + cc.GetZIP_CODE( );
      return key;
    }
    //function to check if another donor is
    // 1) a repeat donor
    // 2) has the same CMTE_ID, ZIP, and YEAR
    struct IdentifyRepeat {
      string CMTE_ID_, ZIP_CODE_, TRANSACTION_DT_;
      IdentifyRepeat( string CMTE_ID, string ZIP_CODE, string TRANSACTION_DT )
	: CMTE_ID_( CMTE_ID ), ZIP_CODE_( ZIP_CODE ), TRANSACTION_DT_( TRANSACTION_DT )
	{
	}
      bool operator( )( CampContrib& donor ) {
	// cout << "IdenfityRepeat: " << endl
	//      << donor.GetCMTE_ID( ) << ", " << CMTE_ID_ << endl
	//      << donor.GetZIP_CODE( ) << ", " << ZIP_CODE_ << endl
	//      << donor.GetTRANSACTION_DT( ).substr(4) << ", " << TRANSACTION_DT_.substr(4) << endl;
	if ( donor.GetCMTE_ID( ) == CMTE_ID_ &&
	     donor.GetZIP_CODE( ) == ZIP_CODE_ &&
	     donor.GetTRANSACTION_DT( ).substr(4) == TRANSACTION_DT_.substr(4) ) {
	  return true;
	}
	else {
	  return false;
	}
      }
    };
    void CrossRefDonor( CampContrib& donor, UMapSVCCType::iterator test_donor,
			VectorCCType& agg_donors ) {
      string CMTE_ID = donor.GetCMTE_ID( );
      string ZIP_CODE = donor.GetZIP_CODE( );
      string TRANSACTION_DT = donor.GetTRANSACTION_DT( );
      // cout << "Repeat Donor: " << endl;
      // donor.Print( );
      //first see if test donor is a repeat donor
      if ( test_donor -> second.size( ) > 1 ) {
	// cout << "Test Donor Info: " << test_donor->first << ", " << test_donor -> second.size( ) << endl;
	auto begin_iter = boost::make_filter_iterator( IdentifyRepeat( CMTE_ID, ZIP_CODE, TRANSACTION_DT ), test_donor->second.begin( ), test_donor->second.end( ) );
	auto end_iter = boost::make_filter_iterator( IdentifyRepeat( CMTE_ID, ZIP_CODE, TRANSACTION_DT ), test_donor->second.end( ), test_donor->second.end( ) );
	auto range = boost::make_iterator_range( begin_iter, end_iter );
	for ( auto ele : range ) {
	  // cout << "CrossReferenced Donor: " << endl;
	  // ele.Print( );
	  agg_donors.push_back( ele );
	}
      }
    }    
  public: 	//public data members
    
  private: 	//private data members
    double percentage_;
    // VectorCCType contribs_; //dont technically need this
    UMapSVCCType repeat_donors_;
    ifstream& FIN_;
    ofstream& FOUT_;
  }; // end of class CampaignBook
} // end DA

#endif // CAMPAIGN_BOOK_HPP
