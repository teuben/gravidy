#ifdef GPU
#include "include/gpu/Hermite4GPU.cuh"
#elif _MPI
#include "include/mpi/Hermite4MPI.hpp"
#elif MPIGPU
#include "include/mpigpu/Hermite4MPIGPU.cuh"
#elif TSYM
#include "include/cpu-tsym/Hermite4CPU.hpp"
#else // CPU
#include "include/cpu/Hermite4CPU.hpp"
#endif

/*
 * Main routing of the initialization and exeucutio of GraviDy
 *
 * The main objects based on the existing classes are created here
 * and passing to some methods to perform the interaction of them
 * to achieve an N-body system integration.
 */
int main(int argc, char *argv[]) {


    #if defined(_MPI) || defined(MPIGPU)
    int rank, nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    #endif

    // Parsing the command-line parameters
    OptionsParser op(argc,argv);
    if(!op.check_options()) return 1;

    // Initialization of the system
    NbodySystem ns(op);

    // Reading the input file, storing the information in a temporal structure
    #if defined(_MPI) || defined(MPIGPU)
    if (rank == 0)
    {
        ns.read_input_file();
    }
    ns.alloc_base_attributes(rank);
    #else
    ns.read_input_file();
    ns.alloc_base_attributes(0);
    #endif

    ns.copy_input_data();

    // Creating the object in charge of printing the program logs
    Logger logger(&ns);
    // Creating the object with some extra functionallity for N-body codes
    NbodyUtils nu(&ns,RADIUS_RATIO);

    // Inside this functions there is an special treatment for the main
    // process and the slaves

    // Creating an Hermite object depending on the compiling rules
    #ifdef GPU
    Hermite4GPU h4(&ns, &logger, &nu);
    #elif _MPI
    Hermite4MPI h4(&ns, &logger, &nu, rank, nprocs);
    #elif MPIGPU
    Hermite4MPIGPU h4(&ns, &logger, &nu, rank, nprocs);
    #elif TSYM
    Hermite4CPU h4(&ns, &logger, &nu);
    #else
    Hermite4CPU h4(&ns, &logger, &nu);
    #endif

    // Calling the integration process using the corresponding Hermite object
    h4.integration();

    #if defined(_MPI) || defined(MPIGPU)
    MPI_Finalize();
    #endif
    return 0;
}
