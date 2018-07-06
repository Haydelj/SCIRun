/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2015 Scientific Computing and Imaging Institute,
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


#include <Core/Algorithms/Math/ResizeMatrixAlgo.h>
#include<Core/Datatypes/Matrix.h>
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Datatypes/MatrixTypeConversions.h>
#include <Core/Algorithms/Base/AlgorithmVariableNames.h>
#include <Core/Math/MiscMath.h>

using namespace Eigen;
using namespace SCIRun;
using namespace SCIRun::Core;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Algorithms;
using namespace SCIRun::Core::Algorithms::Math;
using namespace SCIRun::Core::Algorithms::Math::Parameters;

ALGORITHM_PARAMETER_DEF(Math, NoOfRows);
ALGORITHM_PARAMETER_DEF(Math, NoOfColumns);

ResizeMatrixAlgo::ResizeMatrixAlgo()
{
    //set parameter defaults for UI
    addParameter(Parameters::NoOfRows, 1);
    addParameter(Parameters::NoOfColumns, 1);

}

AlgorithmOutput ResizeMatrixAlgo::run(const AlgorithmInput& input) const{
    
    auto inputMatrix=input.get<Datatypes::Matrix>(Variables::InputMatrix);
    
    //pull parameter from UI
    
    int rows = get(Parameters::NoOfRows).toInt();
    int columns = get(Parameters::NoOfColumns).toInt();
    
    auto dense=castMatrix::toDense(inputMatrix);
    Map<MatrixXd> result(dense->data(),columns,rows);
    DenseMatrixHandle outputArray(new DenseMatrix(result.matrix()));
    outputArray->transposeInPlace();
    
    if(dense->rows()*dense->cols() != rows*columns)
    {
        warning("size you input and the size of you matrix dont match");

        double *resultMatrix=outputArray->data();
        for(int i=dense->rows()*dense->cols();i<rows*columns;i++)
        {
            resultMatrix[i]=0;
        }
    }

        AlgorithmOutput output;
        output[Variables::OutputMatrix]=outputArray;
        
        return output;
    
    
}
