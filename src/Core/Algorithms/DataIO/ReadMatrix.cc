/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <fstream>
#include <iostream>
#include <Core/Algorithms/DataIO/ReadMatrix.h>
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Datatypes/SparseRowMatrix.h>
#include <Core/Datatypes/MatrixIO.h>
#include <Core/Algorithms/DataIO/EigenMatrixFromScirunAsciiFormatConverter.h>
#include <Core/Algorithms/Base/AlgorithmPreconditions.h>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

using namespace SCIRun::Core::Algorithms;
using namespace SCIRun::Core::Algorithms::DataIO;
using namespace SCIRun::Core::Datatypes;

AlgorithmParameterName ReadMatrixAlgorithm::Filename("Filename");

namespace SCIRun {
  namespace Core {
    namespace Algorithms {
      namespace DataIO {

        class ReadMatrixAlgorithmPrivate
        {
        public:
          static boost::mutex fileCheckMutex_;
        };

        boost::mutex ReadMatrixAlgorithmPrivate::fileCheckMutex_;
      }}}}

ReadMatrixAlgorithm::Outputs ReadMatrixAlgorithm::run(const ReadMatrixAlgorithm::Parameters& filename) const
{
  {
    //BOOST FILESYSTEM BUG: it is not thread-safe. TODO: need to meld this locking code into the ENSURE_FILE_EXISTS macro.
    boost::lock_guard<boost::mutex> guard(ReadMatrixAlgorithmPrivate::fileCheckMutex_);
    ENSURE_FILE_EXISTS(filename);
  }

  if (boost::filesystem::extension(filename) == ".txt")
  {
    std::ifstream reader(filename.c_str());
    DenseMatrixHandle matrix(new DenseMatrix);
    reader >> *matrix;
    return matrix;
  }
  else if (boost::filesystem::extension(filename) == ".mat")
  {
    status("FOUND .mat file: assuming is SCIRUNv4 ASCII format.");
    internal::EigenMatrixFromScirunAsciiFormatConverter conv(this);
    return conv.make(filename);
  }
  THROW_ALGORITHM_INPUT_ERROR("Unknown matrix file format");
}
