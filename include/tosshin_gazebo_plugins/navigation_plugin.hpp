// Copyright (c) 2021 Alfi Maulana
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef TOSSHIN_GAZEBO_PLUGINS__NAVIGATION_PLUGIN_HPP_
#define TOSSHIN_GAZEBO_PLUGINS__NAVIGATION_PLUGIN_HPP_

#include <gazebo/common/Plugin.hh>
#include <rclcpp/rclcpp.hpp>
#include <tosshin_interfaces/msg/maneuver.hpp>
#include <tosshin_interfaces/msg/orientation.hpp>
#include <tosshin_interfaces/msg/position.hpp>
#include <tosshin_interfaces/srv/configure_maneuver.hpp>

#include <map>
#include <string>

namespace tosshin_gazebo_plugins
{
using Maneuver = tosshin_interfaces::msg::Maneuver;
using Orientation = tosshin_interfaces::msg::Orientation;
using Position = tosshin_interfaces::msg::Position;
using ConfigureManeuver = tosshin_interfaces::srv::ConfigureManeuver;

class NavigationPlugin : public gazebo::ModelPlugin
{
public:
  NavigationPlugin();

  void Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf);

private:
  void Update();

  Maneuver configure_maneuver(const Maneuver & maneuver);

  double initial_x_position;
  double initial_y_position;
  double initial_yaw_orientation;

  double forward;
  double left;
  double yaw;

  rclcpp::Node::SharedPtr node;

  rclcpp::Publisher<Position>::SharedPtr position_publisher;
  rclcpp::Publisher<Orientation>::SharedPtr orientation_publisher;

  rclcpp::Publisher<Maneuver>::SharedPtr maneuver_event_publisher;
  rclcpp::Subscription<Maneuver>::SharedPtr maneuver_input_subscription;

  rclcpp::Service<ConfigureManeuver>::SharedPtr configure_maneuver_service;

  gazebo::physics::ModelPtr model;
  gazebo::physics::WorldPtr world;

  gazebo::event::ConnectionPtr update_connection;
};

}  // namespace tosshin_gazebo_plugins

#endif  // TOSSHIN_GAZEBO_PLUGINS__NAVIGATION_PLUGIN_HPP_