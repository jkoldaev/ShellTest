//
//  main.cpp
//  Shell
//
//  Created by Sergey Koldaev on 07/04/15.
//  Copyright (c) 2015 Sergey Koldaev. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const char* tmpFileName = "/tmp/Shell.tmp";

static int isSpecialChar(char c){
    return !isdigit(c) && !isascii(c);
}

static bool removeDoubleSlashes(char lhs, char rhs) {
    return (lhs == rhs) && (lhs == '/');
}

string ssystem (const string command) {
    time_t current_time;
    time(&current_time);
    struct tm * date = localtime( & current_time );
    
    string outputPath;
    ostringstream instream;
    instream << tmpFileName << "." << date->tm_year << "." << date->tm_mon << "." << date->tm_mday << "." << date->tm_hour << "." << date->tm_min << "." << date->tm_sec;
    outputPath = instream.str();
    
    string scommand = command;
    scommand.resize(remove_if(scommand.begin(), scommand.end(), isSpecialChar) - scommand.begin());
    string::iterator new_end = unique(scommand.begin(), scommand.end(), removeDoubleSlashes);
    scommand.erase(new_end, scommand.end());
    
    cout << "Command:" << endl << scommand << endl;
    string cmd = scommand + " >> " + outputPath;
    system(cmd.c_str());
    ifstream file(outputPath, ios::in );
    string result;
    if (file) {
        while (!file.eof()) {
            result.push_back(file.get());
        }
        file.close();
    }
    remove(outputPath.c_str());

    result.resize(remove_if(result.begin(), result.end(), isSpecialChar) - result.begin());
    
    return result;
}


int main(int argc, const char * argv[]) {
    const string cmdsh = "/bin/sh -c";
    string cmdin;
    
    while (true){
        string cmdout;
        string result;
        
        cout << "Enter command: ";
        getline (cin, cmdin);
        cmdout = cmdsh + " " + cmdin;
        result = ssystem(cmdout);
        
        cout << "Result:" << endl << result;
    }
    
    
    return 0;
}
