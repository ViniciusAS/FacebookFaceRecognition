
/* 
 * File:   csv_reader.h
 * Author: viniciusas
 *
 * Created on 7 de Dezembro de 2016, 14:41
 */

#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <functional>

namespace CsvHandler {
    using namespace std;
    
    bool readCsvFile(const string &filename, const char &separator, const int &nCols, function<void(string*)> callback){
        ifstream file( filename, ifstream::in );
        if (!file.good()){
            return false;
        }
        string line, *cols;
        while ( std::getline(file,line) ){

            if ( line.empty() ) continue;
            if ( line.at(0) == '#' ) continue;

            cols = new string[nCols];
            stringstream sline(line);
            
            for (int i = 0; i < nCols-1; i++){
                std::getline(sline, cols[i], separator);
            }
            std::getline(sline, cols[nCols-1]);
            
            callback(cols);
        }
        return true;
    }
    
    bool writeCsvFile(const string &filename, const char &separator, const size_t &nCols, const vector<string*> &lines){
        ofstream file( filename, ofstream::out );
        if (!file.good()){
            return false;
        }
        for (const string *line : lines) {
            for (size_t i = 0; i < nCols-1; i++){
                file << line[i] << separator;
            }
            file << line[nCols-1] << "\n";
        }
        return true;
    }
    
};

#endif /* CSV_READER_H */

