/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2020 Scientific Computing and Imaging Institute,
   University of Utah.

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


//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
// Cleaver - A MultiMaterial Tetrahedral Mesher
// -- Mesher Class
//
//  Author: Jonathan Bronson (bronson@sci.utah.edu)
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------

#ifndef NRRD2CLEAVER_H
#define NRRD2CLEAVER_H

#include <Cleaver/ScalarField.h>
#include <string>
#include <vector>


Cleaver::ScalarField* loadNRRDFile(const std::string &filename, bool verbose);
std::vector<Cleaver::ScalarField*> loadNRRDFiles(const std::vector<std::string> &filenames, bool verbose);
std::vector<Cleaver::ScalarField*> loadNRRDLabelMap(const std::string &filename, bool verbose);

#endif // NRRD2CLEAVER_H
