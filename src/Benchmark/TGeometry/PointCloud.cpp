// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <benchmark/benchmark.h>
#include <string>

#include "Open3D/Geometry/PointCloud.h"
#include "Open3D/IO/ClassIO/PointCloudIO.h"
#include "Open3D/TGeometry/PointCloud.h"

namespace open3d {

class TPointCloudFixture : public benchmark::Fixture {
public:
    void SetUp(const benchmark::State& state) {
        pcd_legacy_ = io::CreatePointCloudFromFile(std::string(TEST_DATA_DIR) +
                                                   "/fragment.pcd");
        pcd_ = tgeometry::PointCloud::FromLegacyPointCloud(
                *pcd_legacy_, Dtype::Float32, Device("CUDA:0"));
    }

    void TearDown(const benchmark::State& state) {}

public:
    std::shared_ptr<geometry::PointCloud> pcd_legacy_;
    tgeometry::PointCloud pcd_;
};

BENCHMARK_DEFINE_F(TPointCloudFixture, LegacyVoxelDownSample)
(benchmark::State& state) {
    for (auto _ : state) {
        pcd_legacy_->VoxelDownSample(0.01);
    }
}

BENCHMARK_DEFINE_F(TPointCloudFixture, VoxelDownSample)
(benchmark::State& state) {
    for (auto _ : state) {
        pcd_.VoxelDownSample(0.01);
    }
}

BENCHMARK_REGISTER_F(TPointCloudFixture, LegacyVoxelDownSample);

}  // namespace open3d
