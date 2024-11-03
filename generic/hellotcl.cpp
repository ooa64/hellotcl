#include "tclhello.hpp"

extern "C" {
  DLLEXPORT int Hellotcl_Init (Tcl_Interp *interp);
}

#ifdef TCLHELLO_CLEANUP
    static void Hellotcl_Done(void *);
#endif

TclHelloCmd * cmd = NULL;

int Hellotcl_Init (Tcl_Interp *interp) {

  if (!cmd) {
#ifdef USE_TCL_STUBS    
    if (Tcl_InitStubs(interp, STUB_VERSION, 0) == NULL) {
        return TCL_ERROR;
    }
#endif
    cmd = new TclHelloCmd(interp, "hello");
#ifdef TCLHELLO_CLEANUP
    Tcl_CreateExitHandler(Hellotcl_Done, NULL);
#endif
    Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
  }

  return TCL_OK;
}

#ifdef TCLHELLO_CLEANUP
static void Hellotcl_Done(void *) {
  if (cmd) {
    delete cmd;
    cmd = NULL;
  }
}
#endif