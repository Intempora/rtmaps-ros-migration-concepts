/////////////////////////////////////////////////////////////////////////////////
//
//   Copyright 2018-2025 Intempora S.A.S.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
/////////////////////////////////////////////////////////////////////////////////

#include "rtmaps_minimal_publisher.h"

// Use the macros to declare the inputs
MAPS_BEGIN_INPUTS_DEFINITION(MAPS_ros_minimal_publisher)
//No input
MAPS_END_INPUTS_DEFINITION

// Use the macros to declare the outputs
MAPS_BEGIN_OUTPUTS_DEFINITION(MAPS_ros_minimal_publisher)
MAPS_OUTPUT("hello", MAPS::TextUTF8, NULL, NULL, 255)//Output as string with a capacity of 255 characters
MAPS_END_OUTPUTS_DEFINITION

// Use the macros to declare the properties
MAPS_BEGIN_PROPERTIES_DEFINITION(MAPS_ros_minimal_publisher)
MAPS_PROPERTY("period",200000,false,true)
MAPS_END_PROPERTIES_DEFINITION

// Use the macros to declare the actions
MAPS_BEGIN_ACTIONS_DEFINITION(MAPS_ros_minimal_publisher)
//No action
MAPS_END_ACTIONS_DEFINITION

MAPS_COMPONENT_DEFINITION(MAPS_ros_minimal_publisher, "ROS_Minimal_Publisher", "1.0.0", 128,
    MAPS::Threaded, MAPS::Threaded,
    0, // Nb of inputs. Leave -1 to use the number of declared input definitions
    1, // Nb of outputs. Leave -1 to use the number of declared output definitions
    1, // Nb of properties. Leave -1 to use the number of declared property definitions
    0) // Nb of actions. Leave -1 to use the number of declared action definitions

	  
void MAPS_ros_minimal_publisher::Birth()
{
    m_count = 0;
    m_lastTs = MAPS::CurrentTime();
}

void MAPS_ros_minimal_publisher::Core()
{
    MAPSTimestamp period = GetIntegerProperty("period");

    MAPS::OutputGuard<> outGuard{ this, Output(0) };

    std::string message = "Hello, world! " + std::to_string(m_count++);
    memcpy(outGuard.DataPointer(), message.c_str(), message.size());

    m_lastTs += period;
    Wait(m_lastTs);
}

void MAPS_ros_minimal_publisher::Death()
{

}