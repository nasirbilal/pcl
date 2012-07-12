/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef PCL_MODELER_ABSTRACT_WORKER_H_
#define PCL_MODELER_ABSTRACT_WORKER_H_
#include <pcl/apps/modeler/qt.h>
#include <sensor_msgs/PointCloud2.h>

namespace pcl
{
  namespace modeler
  {
    class PolymeshItem;
    class ParameterDialog;

    class AbstractWorker : public QObject
    {
      Q_OBJECT

      public:
        typedef sensor_msgs::PointCloud2  PointCloud2;
        typedef PointCloud2::Ptr          PointCloud2Ptr;
        typedef PointCloud2::ConstPtr     PointCloud2ConstPtr;

        AbstractWorker(const std::vector<PolymeshItem*>& polymeshs, QWidget* parent=0);
        ~AbstractWorker(void);

        virtual int
        exec();

      public slots:
        void
        process();

        void
        postProcess();

      signals:
        void
        processed();

        void
        finished();

      protected:
        virtual std::string
        getName () const {return ("");}

        virtual void
        initParameters(PointCloud2Ptr cloud) = 0;

        virtual void
        setupParameters() = 0;

        virtual void
        processImpl(PolymeshItem* polymesh) const = 0;

        virtual void
        postProcessImpl(PolymeshItem* polymesh) const = 0;

      protected:
        std::vector<PolymeshItem*>  polymeshs_;
        ParameterDialog*          parameter_dialog_;
    };

  }
}

#endif // PCL_MODELER_ABSTRACT_WORKER_H_