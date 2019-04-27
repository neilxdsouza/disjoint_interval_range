
// map::lower_bound/upper_bound
#include <iostream>
#include <map>
using namespace std;

int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  //mymap['b']=40;
  mymap['c']=60;
  //mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('b');   // itup points to e (not d!)

  
  std::map<char,int>::iterator it1 = mymap.begin();
  it1--;
  if (it1 != mymap.begin()) {
	  cout << " moved before begin" << endl;
	  //cout << it1->first << it1->second << endl;
	  if (it1 == mymap.end()) {
		  cout << "it's map.end()" << endl;
	  }
  } else {
	  cout << " still begin" << endl;
  }

  //mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  //for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
  //  std::cout << it->first << " => " << it->second << '\n';
  cout << itlow->first << endl;
  cout << itup->first << endl;

  return 0;
}
