#include <iostream>
#include "tclhello.hpp"

#if defined(TCLHELLO_DEBUG)
#   include <iostream>
#   define DEBUGLOG(_x_) (std::cerr << "DEBUG: " << _x_ << "\n")
#else
#   define DEBUGLOG(_x_)
#endif

int TclHelloCmd::Command(int objc, Tcl_Obj * const objv[]) {
  DEBUGLOG("TclHelloCmd::Command *" << this);

  Tcl_Obj * result = Tcl_GetObjResult(tclInterp);

  Tcl_AppendToObj(result, "Hello,", -1);
  if (objc > 1) {
    for (int i = 1; i < objc; i++) {
      Tcl_AppendToObj(result, " ", -1);
      Tcl_AppendObjToObj(result, objv[i]);
    }
  } else {
     Tcl_AppendToObj(result, " World", -1);
  }
  Tcl_AppendToObj(result, "!", -1);

  return TCL_OK;
};

void TclHelloCmd::Cleanup() {
  DEBUGLOG("TclHelloCmd::Cleanup *" << this);
};
