#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <mpi.h>
#include <climits>

using namespace std;

int main(int argc, char** argv) {

if (argc != 2) {
cerr << "Usage: " << argv[0] << " <number of points>" << endl;
return EXIT_FAILURE;
}
MPI_Init(&argc, &argv);
int world_size, world_rank;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
const long long num_samples = atoi(argv[1]);
long long local_samples = num_samples / world_size;

srand(time(NULL) + world_rank);


auto start_time = chrono::high_resolution_clock::now();

long long local_count_inside = 0;

for (long long i = 0; i < local_samples; ++i) {
double x = static_cast<double>(rand()) / RAND_MAX;
double y = static_cast<double>(rand()) / RAND_MAX;

double distance = sqrt(x * x + y * y);

if (distance <= 1.0) {
local_count_inside++;
}
}

long long global_count_inside;

MPI_Reduce(&local_count_inside, &global_count_inside, 1, MPI_LONG_LONG, MPI_SUM, 0,
MPI_COMM_WORLD);

auto end_time = chrono::high_resolution_clock::now();

if (world_rank == 0) {
double pi_estimate = 4.0 * global_count_inside / num_samples;
cout << "Estimated value of Pi: " << fixed << setprecision(15) << pi_estimate << endl;
cout << "Library value of Pi: " << M_PI << endl;



auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
auto minutes = chrono::duration_cast<chrono::minutes>(duration);
auto seconds = chrono::duration_cast<chrono::seconds>(duration - minutes);
auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration - minutes - seconds);

cout << "Time taken: " << minutes.count() << " minutes::" << seconds.count() << " seconds::" <<
milliseconds.count() << " milliseconds" << endl;
}

MPI_Finalize();
return 0;
}
