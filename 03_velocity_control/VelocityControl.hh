/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef GZ_GAZEBO_SYSTEMS_VELOCITYCONTROL_HH_
#define GZ_GAZEBO_SYSTEMS_VELOCITYCONTROL_HH_

#include <memory>
#include <optional>

#include <gz/sim/System.hh>

using namespace gz;
using namespace sim;
namespace velocity_plagin
{
  class VelocityControl
      : public System,
        public ISystemConfigure,
        public ISystemPreUpdate
  {
  public:
    void Configure(const Entity &_entity,
                   const std::shared_ptr<const sdf::Element> &_sdf,
                   EntityComponentManager &_ecm,
                   EventManager &_eventMgr) override;

  public:
    void PreUpdate(
        const gz::sim::UpdateInfo & /*_info*/,
        gz::sim::EntityComponentManager &_ecm) override;

  private:
    Model model;
  };
}

#endif
