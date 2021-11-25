// Copyright (c) 2021 - for information on the respective copyright owner
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <tf2_msgs/msg/tf_message.hpp>

#include "test.hpp"

// Related:
//    - https://github.com/eProsima/Micro-XRCE-DDS-Client/issues/286
//    - https://github.com/eProsima/Micro-CDR/pull/69

TEST_F(HardwareTestOneTransport, Regression_microCDR_1) {
  auto promise = std::make_shared<std::promise<void>>();
  auto future = promise->get_future();

  auto subscription = node->create_subscription<tf2_msgs::msg::TFMessage>(
    "test_pub", 10,
    [&](tf2_msgs::msg::TFMessage::UniquePtr msg) {
      // Check here message contents
      EXPECT_EQ(msg->transforms.size(), 20U);
      for(size_t i = 0; i < msg->transforms.size(); i++){
        auto t = msg->transforms[i];

        EXPECT_EQ(0, t.header.frame_id.compare(std::string("frame_") + std::to_string(i)));
        EXPECT_EQ(i, static_cast<size_t>(t.header.stamp.sec));
        EXPECT_EQ(i, t.header.stamp.nanosec);

        EXPECT_EQ(0, t.child_frame_id.compare(std::string("child_") + std::to_string(i)));

        EXPECT_EQ(i, t.transform.translation.x);
        EXPECT_EQ(i, t.transform.translation.y);
        EXPECT_EQ(i, t.transform.translation.z);

        EXPECT_EQ(i, t.transform.rotation.x);
        EXPECT_EQ(i, t.transform.rotation.y);
        EXPECT_EQ(i, t.transform.rotation.z);
        EXPECT_EQ(i, t.transform.rotation.w);

      }
      promise->set_value();
    }
  );

  ASSERT_EQ(rclcpp::spin_until_future_complete(node, future.share(), default_spin_timeout), rclcpp::FutureReturnCode::SUCCESS);
}