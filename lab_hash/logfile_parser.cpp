/**
 * @file logfile_parser.cpp
 * Implementation of the LogfileParser class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "logfile_parser.h"
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

// std::string LogfileParser::getProductId(std::string url) const {
//     // Create a stringstream from the string
//     std::stringstream ss(url);

//     // Create a vector to store the split parts
//     std::vector<std::string> parts;

//     std::string part;
//     // Use getline with '/' as delimiter to split the string
//     while (std::getline(ss, part, '/')) {
//         if (!part.empty()) {
//             parts.push_back(part);
//         }
//     }

//     string product = parts.back();
//     return product;
// }


/**
 * Constructs a LogLine from a string (actual physical line in the
 * logfile).
 *
 * @param line The line in the file to extract info from.
 */
LogfileParser::LogLine::LogLine( const string & line ) {
    istringstream iss( line );
    iss >> customer;
    customer = customer.substr(1, customer.length()-3);
    iss >> url;
    string dte = "";
    string dline;
    do {
        iss >> dline;
        dte += dline;
    } while( iss );

    date = time(NULL);
    tm * tme = localtime( &date );
    strptime( dte.c_str(), "%c", tme );
    // force correct DST
    tme->tm_isdst = 1;
    date = mktime( tme );
}

/**
 * Constructs a new LogfileParser from the name of a log file.
 *
 * @param fname The name of the log file to open.
 */
LogfileParser::LogfileParser( const string & fname ) : whenVisitedTable( 256 ) {
    SCHashTable< string, bool > pageVisitedTable( 256 );
    ifstream infile( fname.c_str() );
    string line;
    while( infile.good() ) {
        getline( infile, line );

        // if the line length is 0, move on to the next loop iteration
        if( line.length() == 0 )
            continue;

        // otherwise parse the line and update the hash tables and vector
        LogLine ll( line );
        /**
         * @todo Finish implementing this function.
         *
         * Given the LogLine above, you should be able to update the member
         * variable hash table and any other hash tables necessary to solve
         * this problem. This should also build the uniqueURLs member
         * vector as well.
         */
        
        auto it =  std::find(uniqueURLs.begin(), uniqueURLs.end(), ll.url);
        if (it == uniqueURLs.end()) {
            uniqueURLs.push_back(ll.url);
        }

        // Create a stringstream from the string
        std::stringstream ss(ll.url);

        // Create a vector to store the split parts
        std::vector<std::string> parts;

        std::string part;
        // Use getline with '/' as delimiter to split the string
        while (std::getline(ss, part, '/')) {
            if (!part.empty()) {
                parts.push_back(part);
            }
        }

        string product = parts.back();

        string key = ll.customer + product;
        whenVisitedTable[key] = ll.date;
    }
    infile.close();
}

/**
 * Determines if a given customer has ever visited the given url.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A boolean value indicating whether the customer visited the url.
 */
bool LogfileParser::hasVisited( const string & customer, const string & url ) const {
    /**
     * @todo Implement this function.
     */
    // Create a stringstream from the string
    std::stringstream ss(url);

    // Create a vector to store the split parts
    std::vector<std::string> parts;

    std::string part;
    // Use getline with '/' as delimiter to split the string
    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }

    string prod = parts.back();

    // Construct the key using customer name and product ID
    string key = customer + prod;

    // Check if the key exists in the hash table
    time_t it = whenVisitedTable.find(key);
    return it != time_t();

}

/**
 * Determines *when* a customer last visited a given url. If the customer
 * has not visited the given url, the output of this function should be the
 * default time_t.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A time_t representing when the customer last visited the given
 *  url.
 */
time_t LogfileParser::dateVisited( const string & customer, const string & url ) const {
    /**
     * @todo Implement this function.
     */
    // Create a stringstream from the string
    std::stringstream ss(url);

    // Create a vector to store the split parts
    std::vector<std::string> parts;

    std::string part;
    // Use getline with '/' as delimiter to split the string
    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }

    string prod = parts.back();

    // Construct the key using customer name and product ID
    string key = customer + prod;

    // Check if the key exists in the hash table
    auto it = whenVisitedTable.find(key);
    return it;
}

/**
 * Gets all of the unique urls that have been visited.
 *
 * @return A vector of urls that were visited in the logfile. Note
 *  that **there should be no duplicates in this vector**.
 */
vector<string> LogfileParser::uniquePages() const {
    return uniqueURLs;
}


