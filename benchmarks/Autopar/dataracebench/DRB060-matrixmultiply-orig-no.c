/*
Copyright (c) 2017, Lawrence Livermore National Security, LLC.
Produced at the Lawrence Livermore National Laboratory
Written by Chunhua Liao, Pei-Hung Lin, Joshua Asplund,
Markus Schordan, and Ian Karlin
(email: liao6@llnl.gov, lin32@llnl.gov, asplund1@llnl.gov,
schordan1@llnl.gov, karlin1@llnl.gov)
LLNL-CODE-732144
All rights reserved.
This file is part of DataRaceBench. For details, see
https://github.com/LLNL/dataracebench. Please also see the LICENSE file
for our additional BSD notice.
Redistribution and use in source and binary forms, with
or without modification, are permitted provided that the following
conditions are met:
* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the disclaimer below.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the disclaimer (as noted below)
  in the documentation and/or other materials provided with the
  distribution.
* Neither the name of the LLNS/LLNL nor the names of its contributors
  may be used to endorse or promote products derived from this
  software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL
SECURITY, LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.
*/
/*
Classic i-k-j matrix multiplication
*/
#define N 100
#define M 100 
#define K 100
#include <omp.h> 
double a[100][100];
double b[100][100];
double c[100][100];

int init()
{
  int i;
  int j;
  int k;
  for (i = 0; i <= 99; i += 1) {
    for (k = 0; k <= 99; k += 1) {
      for (j = 0; j <= 99; j += 1) {
        c[i][j] = (i * j);
        a[i][k] = (i * j);
        b[k][j] = (i * j);
      }
    }
  }
  return 0;
}

int mmm()
{
  int i;
  int j;
  int k;
  
#pragma omp parallel for private (i,j,k)
  for (i = 0; i <= 99; i += 1) {
    for (k = 0; k <= 99; k += 1) {
      
#pragma omp parallel for private (j)
      for (j = 0; j <= 99; j += 1) {
        c[i][j] = c[i][j] + a[i][k] * b[k][j];
      }
    }
  }
  return 0;
}

int print()
{
  int i;
  int j;
  int k;
  for (i = 0; i <= 99; i += 1) {
    for (k = 0; k <= 99; k += 1) {
      for (j = 0; j <= 99; j += 1) {
        printf("%lf %lf %lf\n",c[i][j],a[i][k],b[k][j]);
      }
    }
  }
  return 0;
}

int main()
{
  init();
  mmm();
  print();
  return 0;
}
