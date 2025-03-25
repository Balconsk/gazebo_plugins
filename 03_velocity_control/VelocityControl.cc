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

#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <unordered_map>

#include <gz/common/Profiler.hh>
#include <gz/math/Vector3.hh>
#include <gz/plugin/Register.hh>
#include <gz/transport/Node.hh>

#include "gz/sim/components/AngularVelocityCmd.hh"
#include "gz/sim/components/LinearVelocityCmd.hh"
#include "gz/sim/components/Model.hh"
#include "gz/sim/components/Name.hh"
#include "gz/sim/Model.hh"
#include "gz/sim/Util.hh"

#include "VelocityControl.hh"

using namespace gz;
using namespace gz::sim;

namespace velocity_plagin{
void VelocityControl::Configure(const Entity &_entity,
  const std::shared_ptr<const sdf::Element> &_sdf,
  EntityComponentManager &_ecm,
  EventManager &_eventMgr){
    this->model = Model(_entity);
  }

void VelocityControl::PreUpdate(const UpdateInfo &_info,
                                EntityComponentManager &_ecm)
{
  IGN_PROFILE("VelocityControl::PreUpdate");

  // Nothing left to do if paused.
  if (_info.paused)
    return;
  
  auto modelAngularVel =
      _ecm.Component<components::AngularVelocityCmd>(this->model.Entity());
  if (modelAngularVel == nullptr)
  {
    _ecm.CreateComponent(
        model.Entity(),
        components::AngularVelocityCmd({0,0,0}));
  }
  else
  {
    *modelAngularVel =
        components::AngularVelocityCmd({0,0,0.5});
  }

  // update linear velocity of model
  auto modelLinearVel =
      _ecm.Component<components::LinearVelocityCmd>(model.Entity());

  if (modelLinearVel == nullptr)
  {
    _ecm.CreateComponent(
        model.Entity(),
        components::LinearVelocityCmd({0,0,0}));
  }
  else
  {
    *modelLinearVel =
        components::LinearVelocityCmd({0,0,0.5});
  }
  // update link velocities
  auto linkAngularVelComp =
      _ecm.Component<components::AngularVelocityCmd>(this->model.Entity());
  if (!linkAngularVelComp)
  {
    _ecm.CreateComponent(this->model.Entity(),
                          components::AngularVelocityCmd({0,0,0}));
  }
  else
  {
    *linkAngularVelComp = components::AngularVelocityCmd({0,0,0.5});
  }

}


IGNITION_ADD_PLUGIN(velocity_plagin::VelocityControl,
                    System,
                    VelocityControl::ISystemConfigure,
                    VelocityControl::ISystemPreUpdate)

IGNITION_ADD_PLUGIN_ALIAS(VelocityControl,
                          "gz::sim::systems::VelocityControl")

// TODO(CH3): Deprecated, remove on version 8
IGNITION_ADD_PLUGIN_ALIAS(VelocityControl,
                          "ignition::gazebo::systems::VelocityControl")
}