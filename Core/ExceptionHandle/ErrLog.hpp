#ifndef ERRLOG_HPP
#define ERRLOG_HPP

#include <iostream>
#include <fstream>
#include <string>

using std::ostream;
using std::cout;
using std::cerr;
using std::string;

#define LOGINFO     0
#define LOGERROR    1
#define LOGWARNING  2

class ErrLog {
public:
    ~ErrLog() {}
    const ErrLog& info(string log) const {
        cout<<"\e[1;37m[INFO]"<<log<<"\e[0m\n";
        return *this;
    }
    const ErrLog& info(ostream &out, string log) const {
        out<<"[INFO]"<<log<<"\n";
        return *this;
    }
    const ErrLog& error(string log, int line = -1, string trace = "") const {
        cerr<<"\e[0;31m[ERROR]"<<log<<"\e[0m\n";
        if(line > 0)
            cerr<<"\e[1;37m    Line "<<line<<" Tracing:"<<trace;
    }
    const ErrLog& error(ostream &out, string log, int line = -1, string trace = "") const {
        out<<"[ERROR]"<<log<<"\n";
        if(line > 0)
            out<<"    Line "<<line<<" Tracing:"<<trace;
        return *this;
    }
    const ErrLog& warning(string log, int line = -1, string trace = "") const {
        cerr<<"\e[1;33m[WARNING]"<<log<<"\e[0m\n";
        if(line > 0)
            cerr<<"\e[1;37m    Line "<<line<<" Tracing(warning):"<<trace;
        return *this;
    }
    const ErrLog& warning(ostream &out, string log, int line = -1, string trace = "") const {
        out<<"[WARNING]"<<log<<"\n";
        if(line > 0)
            out<<"    Line "<<line<<" Tracing(warning):"<<trace;
        return *this;
    }
#ifdef I_DEBUG
    ErrLog& debuging(string log, int line = -1, string trace = "") {
        cout<<"\e[1;34m[DEBUG]"<<log<<"\e[0m\n";
        if(line > 0)
            cout<<"\e[1;37m    Line "<<line<<" Tracing(debug):"<<trace;
        return *this;
    }
    ErrLog& debuging(ostream &out, string log, int line = -1, string trace = "") {
        out<<"[DEBUG]"<<log<<"\n";
        if(line > 0)
            out<<"\e    Line "<<line<<" Tracing(debug):"<<trace;
        return *this;
    }
#endif
};

extern ErrLog logger;

#endif