#ifndef TCLHELLO_H
#define TCLHELLO_H

#include <tcl.h>
#include "tclcmd.hpp"

class TclHelloCmd : public TclCmd {
public:
  TclHelloCmd(Tcl_Interp * interp, const char * name): TclCmd(interp, name) {};
private:    
  virtual int Command(int objc, Tcl_Obj * const objv[]);
  virtual void Cleanup();
};

#endif