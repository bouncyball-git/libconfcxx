#include <iostream>
#include "libconfcxx.h"

int main(int argc, char **argv)
{
    if(argc < 2) {
	    cout << "Error: config file not specified\nUsage: " << argv[0] << " initial.conf\n";
	    return 1;
    }

    confc cfg;
    string arg1 = argv[1];
    if(!cfg.load(arg1)) {
    	cout << "Error loading config file\n";
	    return 1;
    }

    cout << "\nTest 1: print initial config\n";
    cfg.print();
    
    cout << "\nTest 2: print only 'ip' and 'mac' key-value:\n";
    string val = cfg.toString("ip");
    if(!cfg.geterr()) cout << "ip = " << val << "\n";
    val = cfg.toString("mac");
    if(!cfg.geterr()) cout << "mac = " << val << "\n";;
    
        
    cout << "\nTest 3: remove key 'gateway' and print full config\n";
    cfg.remove("gateway");
    cfg.print();
    
    cout << "\nTest 4: check if key 'interface' exists\n";
    val = cfg.toString("interface");
    (cfg.geterr()) ? cout << "'interface' does not exist\n" : cout << "'interface' does exist. val = "<< val << "\n";
	
    cout << "\nTest 5: check if key 'mac' exists\n";
    val = cfg.toString("mac");
    (cfg.geterr()) ? cout << "'mac' does not exist\n" : cout << "'mac' does exist. val = " << val << "\n";

    cout << "\nTest 6: check if key 'mac' = 'f0:19:54:27:7d:ab'\n";
    int chk = cfg.chkval("mac", "f0:79:59:67:7d:ad");
    cout << (chk ? "true" : "false") << "\n";

    cout << "\nTest 7: check if key 'mac' = 'a3:b1:cd:d7:e9:f5'\n";
    chk = cfg.chkval("mac", "a3:b1:cd:d7:e9:f5");
    cout << (chk ? "true" : "false") << "\n";

    cout << "\nTest 8: add new key 'domain1' to the config\n";
    cfg.setval("domain1", "last.org");
    cfg.print();

    cout << "\nTest 9: update 'IP' value\n";
    cfg.setval("ip", "1.1.1.1");
    cfg.print();

    cout << "\nTest 10: print key 'number' as 'int'\n";
    int ival = cfg.toInt("number");
    (cfg.geterr()) ? cout << "Error: " << cfg.lasterr() << "\n" : cout << "'number' does exist. val = " << ival << "\n";

    cout << "\nTest 11: print key 'port1' as 'int'\n";
    ival = cfg.toInt("port1");
    (cfg.geterr()) ? cout << "Error: " << cfg.lasterr() << "\n" : cout << "'port1' does exist. val = " << ival << "\n";

    cout << "\nTest 12: print key 'timeusec' as 'double'\n";
    double dval = cfg.toDouble("timeusec");
    (cfg.geterr()) ? cout << "Error: " << cfg.lasterr() << "\n" : cout << "'timeusec' does exist. val = " << dval << "\n";

    cout << "\nTest 14: save modified config to 'modded.conf'\n";
    int ret = cfg.save("modded.conf");
    if(!ret) {
    	cout << "Error: could not write file\n";
	    return 1;
    } else if(ret == -1) {
        cout << "Error: file already exists\n";
        return 1;
    }
    cout << "Done!\n";
}
