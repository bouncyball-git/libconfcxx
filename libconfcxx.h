#ifndef LIBCONFCXX_H
#define LIBCONFCXX_H

#include <string>
#include <map>

using namespace std;

class confc {
   private:
      map<string, string> cfg;
      int isErr = 0;
      string lastErr = "";

   public:
      int load(string file_name);
      int save(string file_name);
      void setval(string key, string value);
      string toString(string key);
      int toInt(string key);
      double toDouble(string key);
      void print();
      void remove(string key);
      int chkval(string key, string value);
      int geterr();
      string lasterr();
};

#endif
