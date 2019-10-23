/*
For more information, please see: http://software.sci.utah.edu

The MIT License

Copyright (c) 2015 Scientific Computing and Imaging Institute,
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

#ifndef Graphics_Widgets_ArrowWidget_H
#define Graphics_Widgets_ArrowWidget_H

#include <Core/Datatypes/Legacy/Field/FieldFwd.h>
#include <Core/GeometryPrimitives/GeomFwd.h>
#include <Graphics/Widgets/Widget.h>
#include <Graphics/Widgets/share.h>

namespace SCIRun {
  namespace Graphics {
    namespace Datatypes {
      enum ArrowWidgetSection { SPHERE, CYLINDER, CONE, DISK };

      class SCISHARE ArrowWidget : public CompositeWidget
      {
      public:
        ArrowWidget(const Core::GeometryIDGenerator &idGenerator,
                    const std::string &name, double scale,
                    const Core::Geometry::Point &pos,
                    const Core::Geometry::Vector &dir, int resolution,
                    bool show_as_vector, size_t widget_num, size_t widget_iter,
                    const Core::Geometry::BBox &bbox);

        bool isVector();

      private:
        bool isVector_;
        std::string widgetName(size_t i, size_t id, size_t iter);
      };

      using ArrowWidgetHandle = SharedPointer<ArrowWidget>;
    }
  }
}
#endif