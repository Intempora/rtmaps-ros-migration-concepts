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

#include "rtmaps_minimal_subscriber.h"

// Use the macros to declare the inputs
MAPS_BEGIN_INPUTS_DEFINITION(MAPS_ros_minimal_subscriber)
MAPS_INPUT("message", MAPS::FilterTextUTF8, MAPS::FifoReader)
MAPS_END_INPUTS_DEFINITION

// Use the macros to declare the outputs
MAPS_BEGIN_OUTPUTS_DEFINITION(MAPS_ros_minimal_subscriber)
//No output
MAPS_END_OUTPUTS_DEFINITION

// Use the macros to declare the properties
MAPS_BEGIN_PROPERTIES_DEFINITION(MAPS_ros_minimal_subscriber)
//No property
MAPS_END_PROPERTIES_DEFINITION

// Use the macros to declare the actions
MAPS_BEGIN_ACTIONS_DEFINITION(MAPS_ros_minimal_subscriber)
//No action
MAPS_END_ACTIONS_DEFINITION

MAPS_COMPONENT_DEFINITION(MAPS_ros_minimal_subscriber, "ROS_Minimal_Subscriber", "1.0.0", 128,
    MAPS::Threaded, MAPS::Threaded,
    1, // Nb of inputs. Leave -1 to use the number of declared input definitions
    0, // Nb of outputs. Leave -1 to use the number of declared output definitions
    0, // Nb of properties. Leave -1 to use the number of declared property definitions
    0) // Nb of actions. Leave -1 to use the number of declared action definitions

	  
void MAPS_ros_minimal_subscriber::Birth()
{
    m_inputReader = MAPS::MakeInputReader::Reactive(
        this,
        Input(0),
        &MAPS_ros_minimal_subscriber::ProcessData
    );
}

void MAPS_ros_minimal_subscriber::Core()
{
    m_inputReader->Read();
}

void MAPS_ros_minimal_subscriber::Death()
{
    m_inputReader.reset();
}

void MAPS_ros_minimal_subscriber::ProcessData(const MAPSTimestamp ts, const MAPS::InputElt<char> inElt)
{
    ReportInfo(inElt.DataPointer());
}