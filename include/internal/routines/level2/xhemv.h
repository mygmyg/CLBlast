
// =================================================================================================
// This file is part of the CLBlast project. The project is licensed under Apache Version 2.0. This
// project loosely follows the Google C++ styleguide and uses a tab-size of two spaces and a max-
// width of 100 characters per line.
//
// Author(s):
//   Cedric Nugteren <www.cedricnugteren.nl>
//
// This file implements the Xhemv routine. It is based on the generalized matrix multiplication
// routine (Xgemv). The Xhemv class inherits from the templated class Xgemv, allowing it to call the
// "DoGemm" function directly. The "DoHemv" function first preprocesses the hermetian matrix by
// transforming it into a general matrix, and then calls the regular GEMV code.
//
// =================================================================================================

#ifndef CLBLAST_ROUTINES_XHEMV_H_
#define CLBLAST_ROUTINES_XHEMV_H_

#include "internal/routines/level2/xgemv.h"

namespace clblast {
// =================================================================================================

// See comment at top of file for a description of the class
template <typename T>
class Xhemv: public Xgemv<T> {
 public:

  // Members and methods from the base class
  using Routine<T>::db_;
  using Routine<T>::context_;
  using Routine<T>::GetProgramFromCache;
  using Routine<T>::TestMatrixA;
  using Routine<T>::RunKernel;
  using Routine<T>::ErrorIn;

  // Uses the regular Xgemv routine
  using Xgemv<T>::DoGemv;

  // Constructor
  Xhemv(Queue &queue, Event &event, const std::string &name = "HEMV");

  // Templated-precision implementation of the routine
  StatusCode DoHemv(const Layout layout, const Triangle triangle,
                    const size_t n,
                    const T alpha,
                    const Buffer<T> &a_buffer, const size_t a_offset, const size_t a_ld,
                    const Buffer<T> &x_buffer, const size_t x_offset, const size_t x_inc,
                    const T beta,
                    const Buffer<T> &y_buffer, const size_t y_offset, const size_t y_inc);
};

// =================================================================================================
} // namespace clblast

// CLBLAST_ROUTINES_XHEMV_H_
#endif
