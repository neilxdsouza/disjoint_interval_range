
// map::lower_bound/upper_bound
#include <iostream>
#include <map>
using namespace std;

int main ()
{
  std::map<int,int> mymap;
  std::map<int,int>::iterator itlow,itup;

  mymap[1]=11;
  //mymap['b']=40;
  mymap[2]=12;
  //mymap['d']=80;
  mymap[3]=13;
  mymap[7]=17;
  mymap[8]=18;

  itlow=mymap.lower_bound (4);  // itlow points to b
  itup=mymap.upper_bound (4);   // itup points to e (not d!)
  cout << "itlow: " << itlow->first << "," << itlow->second << endl;
  cout << "itup: " << itup->first << "," << itup->second << endl;


  itlow=mymap.lower_bound (3);  // itlow points to b
  itup=mymap.upper_bound (3);   // itup points to e (not d!)
  cout << "itlow: " << itlow->first << "," << itlow->second << endl;
  cout << "itup: " << itup->first << "," << itup->second << endl;
  
  ///std::map<char,int>::iterator it1 = mymap.begin();
  ///it1--;
  ///if (it1 != mymap.begin()) {
  ///        cout << " moved before begin" << endl;
  ///        //cout << it1->first << it1->second << endl;
  ///        if (it1 == mymap.end()) {
  ///      	  cout << "it's map.end()" << endl;
  ///        }
  ///} else {
  ///        cout << " still begin" << endl;
  ///}

  /////mymap.erase(itlow,itup);        // erases [itlow,itup)

  ///// print content:
  /////for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
  /////  std::cout << it->first << " => " << it->second << '\n';
  ///cout << itlow->first << endl;
  ///cout << itup->first << endl;

  return 0;
}
