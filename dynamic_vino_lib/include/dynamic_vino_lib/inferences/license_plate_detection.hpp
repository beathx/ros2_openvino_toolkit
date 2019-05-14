// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @brief A header file with declaration for LicensePlateDetection Class
 * @file license_plate_detection.hpp
 */
#ifndef DYNAMIC_VINO_LIB__INFERENCES__LICENSE_PLATE_DETECTION_HPP_
#define DYNAMIC_VINO_LIB__INFERENCES__LICENSE_PLATE_DETECTION_HPP_
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <vector>
#include <string>
#include "dynamic_vino_lib/models/license_plate_detection_model.hpp"
#include "dynamic_vino_lib/engines/engine.hpp"
#include "dynamic_vino_lib/inferences/base_inference.hpp"
#include "inference_engine.hpp"
#include "opencv2/opencv.hpp"
// namespace
namespace dynamic_vino_lib
{
/**
 * @class LicensePlateDetectionResult
 * @brief Class for storing and processing license plate detection result.
 */
class LicensePlateDetectionResult : public Result
{
public:
  friend class LicensePlateDetection;
  explicit LicensePlateDetectionResult(const cv::Rect & location);
  std::string getLicense() const
  {
    return license_;
  }

private:
  std::string license_ = "";
};
/**
 * @class LicensePlateDetection
 * @brief Class to load license plate detection model and perform detection.
 */
class LicensePlateDetection : public BaseInference
{
public:
  using Result = dynamic_vino_lib::LicensePlateDetectionResult;
  explicit LicensePlateDetection();
  ~LicensePlateDetection() override;
  /**
   * @brief Load the license plate detection model.
   */
  void loadNetwork(std::shared_ptr<Models::LicensePlateDetectionModel>);
  /**
   * @brief Enqueue a frame to this class.
   * The frame will be buffered but not infered yet.
   * @param[in] frame The frame to be enqueued.
   * @param[in] input_frame_loc The location of the enqueued frame with respect
   * to the frame generated by the input device.
   * @return Whether this operation is successful.
   */
  bool enqueue(const cv::Mat &, const cv::Rect &) override;
  /**
   * @brief Start inference for all buffered frames.
   * @return Whether this operation is successful.
   */
  bool submitRequest() override;
  /**
   * @brief This function will fetch the results of the previous inference and
   * stores the results in a result buffer array. All buffered frames will be
   * cleared.
   * @return Whether the Inference object fetches a result this time
   */
  bool fetchResults() override;
  /**
   * @brief Get the length of the buffer result array.
   * @return The length of the buffer result array.
   */
  const int getResultsLength() const override;
  /**
   * @brief Get the location of result with respect
   * to the frame generated by the input device.
   * @param[in] idx The index of the result.
   */
  const dynamic_vino_lib::Result * getLocationResult(int idx) const override;
  /**
   * @brief Show the observed detection result either through image window
     or ROS topic.
   */
  const void observeOutput(const std::shared_ptr<Outputs::BaseOutput> & output);
  /**
   * @brief Get the name of the Inference instance.
   * @return The name of the Inference instance.
   */
  const std::string getName() const override;
  const std::vector<cv::Rect> getFilteredROIs(
    const std::string filter_conditions) const override;

private:
  std::shared_ptr<Models::LicensePlateDetectionModel> valid_model_;
  std::vector<Result> results_;
  const std::vector<std::string> licenses_ = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "<Anhui>", "<Beijing>", "<Chongqing>", "<Fujian>",
    "<Gansu>", "<Guangdong>", "<Guangxi>", "<Guizhou>",
    "<Hainan>", "<Hebei>", "<Heilongjiang>", "<Henan>",
    "<HongKong>", "<Hubei>", "<Hunan>", "<InnerMongolia>",
    "<Jiangsu>", "<Jiangxi>", "<Jilin>", "<Liaoning>",
    "<Macau>", "<Ningxia>", "<Qinghai>", "<Shaanxi>",
    "<Shandong>", "<Shanghai>", "<Shanxi>", "<Sichuan>",
    "<Tianjin>", "<Tibet>", "<Xinjiang>", "<Yunnan>",
    "<Zhejiang>", "<police>",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
    "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
    "U", "V", "W", "X", "Y", "Z"
  };
};
}  // namespace dynamic_vino_lib
#endif  // DYNAMIC_VINO_LIB__INFERENCES__LICENSE_PLATE_DETECTION_HPP_
