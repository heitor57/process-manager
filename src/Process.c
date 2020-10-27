#include "Process.h"
#include "List.h"
#include <stdbool.h>
bool equalsProcess(const Object o1,const Object o2){
  Process* p1 = (Process*)o1;
  Process* p2 = (Process*)o2;
  if(p1->id == p2->id){
    return true;
  }else{
    return false;
  }
}
