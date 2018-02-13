#ifndef CAMPAIGN_CONTRIBUTION_HPP
#define CAMPAIGN_CONTRIBUTION_HPP

// System includes --------------------
#include <iostream>
#include <string>

namespace DA { // begin DA
  using namespace std;
/**
 *CampContrib.
 */
  class CampContrib {
  public: 	// public typedefs
    
  private: 	// private typedefs
    
  public: 	//public member functions
    CampContrib( ) { }
    CampContrib( vector< string >& info ) {
      SetCMTE_ID( info.at( 0 ) );
      SetAMNDT_IND( info.at( 1 )[0] );
      SetRPT_TP( info.at( 2 ) );
      SetTRANSACTION_PGI( info.at( 3) );
      SetIMAGE_NUM( info.at( 4 ) );
      SetTRANSACTION_TP( info.at( 5 ) );
      SetENTITY_TP( info.at( 6 ) );
      SetNAME( info.at( 7 ) );
      SetCITY( info.at( 8 ) );
      SetSTATE( info.at( 9 ) );
      SetZIP_CODE( info.at( 10 ).substr( 0, 5 ) );
      SetEMPLOYER( info.at( 11 ) );
      SetOCCUPATION( info.at( 12 ) );
      SetTRANSACTION_DT( info.at( 13 ) );
      SetTRANSACTION_AMT( stod(info.at( 14 ) ) );
      SetOTHER_ID( info.at( 15 ) );
      SetTRAN_ID( info.at( 16 ) );
      SetFILE_NUM( info.at( 17 ) );
      SetMEMO_CD( info.at( 18 )[0] );
      SetMEMO_TEXT( info.at( 19 ) );
      SetSUB_ID( info.at( 20 ) );
    }
    // CampContrib(const CampContrib &c);
    // ~CampContrib();
    
  private: 	//private member functions
    
  public: 	//public data members
    string GetCMTE_ID( ) const { return CMTE_ID_; }
    void SetCMTE_ID( string CMTE_ID ) { CMTE_ID_ = CMTE_ID; }
    
    char GetAMNDT_IND( ) const { return AMNDT_IND_; }
    void SetAMNDT_IND( char AMNDT_IND ) { AMNDT_IND_ = AMNDT_IND; }
    
    string GetRPT_TP( ) const { return RPT_TP_; }
    void SetRPT_TP( string RPT_TP ) { RPT_TP_ = RPT_TP; }
    
    string GetTRANSACTION_PGI( ) const { return TRANSACTION_PGI_; }
    void SetTRANSACTION_PGI( string TRANSACTION_PGI ) { TRANSACTION_PGI_ = TRANSACTION_PGI; }
    
    string GetTRANSACTION_TP( ) const { return TRANSACTION_TP_; }
    void SetTRANSACTION_TP( string TRANSACTION_TP ) { TRANSACTION_TP_ = TRANSACTION_TP; }
    
    string GetIMAGE_NUM( ) const { return IMAGE_NUM_; }
    void SetIMAGE_NUM( string IMAGE_NUM ) { IMAGE_NUM_ = IMAGE_NUM; }
    
    string GetENTITY_TP( ) const { return ENTITY_TP_; }
    void SetENTITY_TP( string ENTITY_TP ) { ENTITY_TP = ENTITY_TP; }
    
    string GetNAME( ) const { return NAME_; }
    void SetNAME( string NAME ) { NAME_ = NAME; }
    
    string GetCITY( ) const { return CITY_; }
    void SetCITY( string CITY ) { CITY_ = CITY; }
    
    string GetSTATE( ) const { return STATE_; }
    void SetSTATE( string STATE ) { STATE_ = STATE; }
    
    string GetZIP_CODE( ) const { return ZIP_CODE_; }
    void SetZIP_CODE( string ZIP_CODE ) { ZIP_CODE_ = ZIP_CODE; }
    
    string GetEMPLOYER( ) const { return EMPLOYER_; }
    void SetEMPLOYER( string EMPLOYER ) { EMPLOYER_ = EMPLOYER; }
    
    string GetOCCUPATION( ) const { return OCCUPATION_; }
    void SetOCCUPATION( string OCCUPATION ) { OCCUPATION_ = OCCUPATION; }
    
    string GetTRANSACTION_DT( ) const { return TRANSACTION_DT_; }
    void SetTRANSACTION_DT( string TRANSACTION_DT ) { TRANSACTION_DT_ = TRANSACTION_DT; }
    
    double GetTRANSACTION_AMT( ) const { return TRANSACTION_AMT_; }
    void SetTRANSACTION_AMT( double TRANSACTION_AMT ) { TRANSACTION_AMT_ = TRANSACTION_AMT; }
    
    string GetOTHER_ID( ) const { return OTHER_ID_; }
    void SetOTHER_ID( string OTHER_ID ) { OTHER_ID_ = OTHER_ID; }
    
    string GetTRAN_ID( ) const { return TRAN_ID_; }
    void SetTRAN_ID( string TRAN_ID ) { TRAN_ID_ = TRAN_ID; }
    
    string GetFILE_NUM( ) const { return FILE_NUM_; }
    void SetFILE_NUM( string FILE_NUM ) { FILE_NUM_ = FILE_NUM; }
    
    char GetMEMO_CD( ) const { return MEMO_CD_; }
    void SetMEMO_CD( char MEMO_CD ) { MEMO_CD_ = MEMO_CD; }
    
    string GetMEMO_TEXT( ) const { return MEMO_TEXT_; }
    void SetMEMO_TEXT( string MEMO_TEXT ) { MEMO_TEXT_ = MEMO_TEXT; }
    
    string GetSUB_ID( ) const { return SUB_ID_; }
    void SetSUB_ID( string SUB_ID ) { SUB_ID_ = SUB_ID; }
    
    void Print( ) {
      cout << setw( 20 ) << left << "CMTE_ID: "
	   << this->GetCMTE_ID( ) << endl;
      cout << setw( 20 ) << left << "NAME: "
	   << this->GetNAME( ) << endl;
      cout << setw( 20 ) << left << "ZIP_CODE: "
	   << this->GetZIP_CODE( ) << endl;
      cout << setw( 20 ) << left << "TRANSACTION_DT: "
	   << this->GetTRANSACTION_DT( ) << endl;
      cout << setw( 20 ) << left << "TRANSACTION_AMT: "
	   << this->GetTRANSACTION_AMT( ) << endl;
      cout << setw( 20 ) << left << "OTHER_ID: "
	   << this->GetOTHER_ID( ) << endl;
    }
  private: 	//private data members
    //in order of where they appear in the file...
    // 1
    string CMTE_ID_; // len = 9
    // 2
    char AMNDT_IND_; // len = 1
    // 3
    string RPT_TP_; // len = 3
    // 4
    string TRANSACTION_PGI_; // len = 5
    // 5
    string IMAGE_NUM_; // len = 11 || 18
    // 6
    string TRANSACTION_TP_; // len = 3
    // 7
    string ENTITY_TP_; // len =3
    // 8
    string NAME_; // len = 200
    // 9
    string CITY_; // len = 30
    // 10
    string STATE_; // len = 2
    // 11
    string ZIP_CODE_; // len = 9
    // 12
    string EMPLOYER_; // len = 38
    // 13
    string OCCUPATION_; // len = 38
    // 14
    string TRANSACTION_DT_; // len = DATA MMDDYYYY
    // 15
    double TRANSACTION_AMT_; // len = 14,2
    // 16
    string OTHER_ID_; // len = 9
    // 17
    string TRAN_ID_;
    // 18
    string FILE_NUM_;
    // 19
    char MEMO_CD_;
    // 20
    string MEMO_TEXT_;
    // 21
    string SUB_ID_;
  }; // end of class CampContrib
} // end DA
#endif // CAMPAIGN_CONTRIBUTION_HPP
