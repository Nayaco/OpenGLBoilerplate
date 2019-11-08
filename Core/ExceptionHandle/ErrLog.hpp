#ifndef ERRLOG_HPP
#define ERRLOG_HPP

#include <iostream>
#include <fstream>
#include <string>
using std::ostream;
using std::cout;
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
    const ErrLog& error(string log) const {
        cout<<"\e[0;31m[ERROR]"<<log<<"\e[0m\n";
    }
    const ErrLog& error(ostream &out, string log) const {
        out<<"[ERROR]"<<log<<"\n";
        return *this;
    }
    const ErrLog& warning(string log) const {
        cout<<"\e[1;33m[WARNING]"<<log<<"\e[0m\n";
        return *this;
    }
    const ErrLog& warning(ostream &out, string log) const {
        out<<"[WARNING]"<<log<<"\n";
        return *this;
    }
#ifdef I_DEBUG
ErrLog& debuging(string log) {
    cout<<"\e[1;34m[DEBUG]"<<log<<"\e[0m\n";
    return *this;
}
ErrLog& debuging(ostream &out, string log) {
    out<<"[DEBUG]"<<log<<"\n";
    return *this;
    }
#endif
};

extern ErrLog logger;

#endif