
#ifndef ADIOS_ADIOS_PROFILE_H
#define ADIOS_ADIOS_PROFILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <Configuration.h>
#include <stdint.h>
#include <strings.h>
#include <vector>

using namespace std;

namespace ADIOS_PROFILE
{

typedef enum
{
  TRACES,
  CKPOINT
}	OUTPUT_T;

static double start = 0.0;
static double *comp_times;
static double *trace_times;
static double *checkpoint_times;
static int *ckp_data_grp;
static int *trace_data_grp;
static int *ckp_data_total;
static int *trace_data_total;
static int ckp_index;
static int trace_index;

typedef enum TIME_ATTR{
  COMP,
  COMM,
  IO
}TIME_ATTR;

typedef struct info{
  double time;
  TIME_ATTR t_attr;
  int block;
  int step;
}TIME_INFO;

static double comp_start;
static double comp_end;
static double comm_start;
static double comm_end;
static double io_start;
static double io_end;
static double comp_total;
static double comm_total;
static double io_total;
static int block;
static int step;
static vector<TIME_INFO> times;
static int myrank;

#if (defined HAVE_ADIOS) && (defined IO_PROFILE)
void updateBlock(int block);
void updateStep(int step);
void profile_init(int rank);
void profile_final();
void comp_s();
void comp_e();
void comm_s();
void comm_e();
void io_s();
void io_e();

void profile_adios_size(Communicate* myComm, OUTPUT_T op, uint64_t adios_groupsize, uint64_t adios_totalsize);
void profile_adios_init(int nBlock);
void profile_adios_finalize(Communicate* myComm, int nBlock);
void profile_adios_start_comp(int block);
void profile_adios_start_trace(int block);
void profile_adios_start_checkpoint(int block);
void profile_adios_end_comp(int block);
void profile_adios_end_trace(int block);
void profile_adios_end_checkpoint(int block);
#else
inline void updateBlock(int block){}
inline void updateStep(int step){}
inline void profile_init(int rank){}
inline void profile_final(){}
inline void comp_s(){}
inline void comp_e(){}
inline void comm_s(){}
inline void comm_e(){}
inline void io_s(){}
inline void io_e(){}

inline void profile_adios_size(Communicate* myComm, OUTPUT_T op, uint64_t adios_groupsize, uint64_t adios_totalsize){}
inline void profile_adios_init(int nBlock){}
inline void profile_adios_finalize(Communicate* myComm, int nBlock){}
inline void profile_adios_start_comp(int block){}
inline void profile_adios_start_trace(int block){}
inline void profile_adios_start_checkpoint(int block){}
inline void profile_adios_end_comp(int block){}
inline void profile_adios_end_trace(int block){}
inline void profile_adios_end_checkpoint(int block){}
#endif
}

#endif
