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

#include <Modules/Legacy/Bundle/InsertFieldsIntoBundle.h>
#include <Interface/Modules/Bundle/InsertFieldsIntoBundleDialog.h>
#include <Core/Algorithms/Base/AlgorithmVariableNames.h>
#include <Dataflow/Network/ModuleStateInterface.h>  //TODO: extract into intermediate

using namespace SCIRun::Gui;
using namespace SCIRun::Dataflow::Networks;
using namespace SCIRun::Core::Algorithms;

InsertFieldsIntoBundleDialog::InsertFieldsIntoBundleDialog(const std::string& name, ModuleStateHandle state,
  QWidget* parent /* = 0 */)
  : ModuleDialogGeneric(state, parent)
{
  setupUi(this);
  setWindowTitle(QString::fromStdString(name));
  fixSize();
  WidgetStyleMixin::tableHeaderStyle(tableWidget);
}

void InsertFieldsIntoBundleDialog::updateFromPortChange(int numPorts, const std::string& portId, DynamicPortChange type)
{
  qDebug() << "updateFromPortChange" << portId.c_str() << type;
  if (type == INITIAL_PORT_CONSTRUCTION)
    return;

  static const std::string typeName = "Fields";
  const int lineEditColumn = 1;
  syncTableRowsWithDynamicPort(portId, typeName, tableWidget, lineEditColumn, type == USER_ADDED_PORT, {
                                 [&]()
                                 {
                                   auto check = new QTableWidgetItem();
                                   check->setCheckState(Qt::Checked);
                                   check->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
                                   return check;
                                 },
                                 [&](){ return new QTableWidgetItem("[unknown, populated upon execute]"); }
                               });
}
