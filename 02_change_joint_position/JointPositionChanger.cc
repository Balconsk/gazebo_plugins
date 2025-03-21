/*
 * Copyright (C) 2022 Open Source Robotics Foundation
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

#include <gz/math/Rand.hh>
#include <gz/sim/System.hh>
#include <gz/sim/components/Joint.hh>
#include <gz/sim/components/JointPositionReset.hh>
#include <gz/sim/components/Model.hh>
#include "gz/sim/components/JointPosition.hh"
#include <gz/sim/components/JointType.hh>
#include <gz/sim/components/ParentEntity.hh>
#include <gz/sim/components/Name.hh>
#include <gz/plugin/Register.hh>

using namespace gz;
using namespace sim;
namespace change_plugin
{
class JointPositionChanger : public System,
                                public ISystemConfigure,
                                public ISystemPreUpdate
{
  void Configure(const Entity &_entity,
                 const std::shared_ptr<const sdf::Element> &,
                 EntityComponentManager &, EventManager &) override
  {
    this->targetEntity = _entity;
  }

  void PreUpdate(const UpdateInfo &_info, EntityComponentManager &_ecm) override
  {
    auto joints = _ecm.EntitiesByComponents(
        components::ParentEntity(this->targetEntity), components::Joint());
    for (auto joint : joints)
    {
      auto jointType = _ecm.Component<components::JointType>(joint);
      auto jointName = _ecm.Component<components::Name>(joint);

      double pos = 0.0;
      if (jointName->Data() == "arm_shoulder_pan_joint")
      {
        auto joinPos = _ecm.Component<components::JointPosition>(joint);
        if (!joinPos)
        {
          _ecm.CreateComponent(joint,
              components::JointPosition());
        }
        if (joinPos){
          std::cout << "Position: "<<joinPos->Data()[0]<<std::endl;
          pos = joinPos->Data()[0]+ 0.02; 
        }
      }
      _ecm.SetComponentData<components::JointPositionReset>(joint, {pos});
    }
  }

 

  private: Entity targetEntity;

};
}  // namespace change_plugin

GZ_ADD_PLUGIN(change_plugin::JointPositionChanger,
                    gz::sim::System,
                    change_plugin::JointPositionChanger::ISystemConfigure,
                    change_plugin::JointPositionChanger::ISystemPreUpdate)
