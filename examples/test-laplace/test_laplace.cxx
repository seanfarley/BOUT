/*
 * Laplacian inversion
 * 
 */

#include <bout.hxx>
#include <boutmain.hxx>
#include <invert_laplace.hxx>
#include <field_factory.hxx>

int physics_init(bool restarting) {
  FieldFactory f;
  
  Field3D input = f.create3D("(1-gauss(x-0.5,0.2))*gauss(y)*gauss(z)");
  Field2D a = f.create2D("gauss(x) * sin(y)");
  Field2D c = f.create2D("sin(x) * gauss(x-0.5) * gauss(y)");
  SAVE_ONCE3(input, a, c);

  Field3D flag0 = invert_laplace(input, 0);
  Field3D flag3 = invert_laplace(input, 3);
  SAVE_ONCE2(flag0, flag3);
  
  Field3D flag0a = invert_laplace(input, 0, &a);
  Field3D flag3a = invert_laplace(input, 3, &a);
  SAVE_ONCE2(flag0a, flag3a);
  
  Field3D flag0ac = invert_laplace(input, 0, &a, &c);
  Field3D flag3ac = invert_laplace(input, 3, &a, &c);
  SAVE_ONCE2(flag0ac, flag3ac);
  
  // Get the processor number for the output file name
  int MYPE;
  MPI_Comm_rank(BoutComm::get(), &MYPE);
  dump.write("%s/BOUT.dmp.%d.nc", "data", MYPE);
  
  output << "\nFinished running test. Triggering error to quit\n\n";
  
  return 1;
}

int physics_run(BoutReal t) {
  // Doesn't do anything
  return 1;
}
