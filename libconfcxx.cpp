#include <iostream>
#include <fstream>
#include <sstream>
#include "libconfcxx.h"

template <char C>
istream& expect(istream& in) {
    if ((in >> ws).peek() == C) {
        in.ignore();
    }
    else {
        in.setstate(ios_base::failbit);
    }
    return in;
}

int confc::geterr() {
    if(isErr) {
        isErr = 0;
        return 1;
    }
    return 0;
}

string confc::lasterr() {
    return lastErr;
}

// update or add config element to config
void confc::setval(string key, string value)
{
    cfg[key] = value;
}

string confc::toString(string key)
{
    isErr = 0;
    if(cfg.find(key) != cfg.end()) return cfg[key];
    lastErr = "key not found: " + key;
    isErr = 1;
    return "";
}

int confc::toInt(string key)
{
    string val = toString(key);
    // leave error state unchanged
    if(isErr) return 0;
    return stoi(val);
}

double confc::toDouble(string key)
{
    string val = toString(key);
    // leave error state unchanged
    if(isErr) return 0;
    return stod(val);
}

// remove config element from chain
void confc::remove(string key)
{
    cfg.erase(key);
}

// load config from file
int confc::load(string file_name)
{
    string line, key, value;

    ifstream f(file_name);
    if(!f) return 0;

    int read_ok = 0;
    while(getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream in(line);
        if (!(in >> key >> expect<'='> >> value)) continue;
        setval(key, value);
        read_ok = 1;
    }
    f.close();
    return read_ok ? 1 : 0;
}

// save config to file
int confc::save(string file_name)
{
    ifstream f(file_name);
    if(!f)
    {
        ofstream f(file_name);
        if(!f) return 0;

        for (auto it = cfg.begin(); it != cfg.end(); ++it)
        {
            f << it->first << " = " << it->second << "\n";
        }
        f.close();
        return 1;
    }
    return -1;
}

// debug: print all elements of config
void confc::print()
{
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
        cout << it->first << " = " << it->second << '\n';
}

// check if key exists or value of existing key matches value
int confc::chkval(string key, string value)
{
    string val = toString(key);
    // if there is no such key
    if(geterr()) return -1;
    // if value matches
    if(val == value) return 1;
    // otherwise 
    return 0;
}
