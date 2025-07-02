################################################################################
##
##   Copyright 2018-2025 Intempora S.A.S.
##
##   Licensed under the Apache License, Version 2.0 (the "License");
##   you may not use this file except in compliance with the License.
##   You may obtain a copy of the License at
##
##       http:##www.apache.org/licenses/LICENSE-2.0
##
##   Unless required by applicable law or agreed to in writing, software
##   distributed under the License is distributed on an "AS IS" BASIS,
##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##   See the License for the specific language governing permissions and
##   limitations under the License.
##
################################################################################

import rtmaps.core as rt
import rtmaps.types
from rtmaps.base_component import BaseComponent  # base class

# Python class that will be called from RTMaps.
class rtmaps_python(BaseComponent):
    
    # Constructor has to call the BaseComponent parent class.
    def __init__(self):
        BaseComponent.__init__(self)  # call base class constructor

    # Dynamic is called frequently at design time:
    # - When loading the diagram
    # - When connecting or disconnecting a wire
    # Dynamic is not called when the diagram is running.
    # Here you create your inputs, outputs and properties.
    def Dynamic(self):
        # Define the output. The type is set to AUTO which means that the output will be typed automatically.
        # This function sets the buffer_size, the maximum string length. This is necessary because RTMaps buffers have a fixed size, for performance optimization.
        self.add_output("hello", rtmaps.types.AUTO, 25)
        
    # Birth() will be called once at diagram execution startup.
    def Birth(self):
        self.i = 0

    # Core() is called every time you have new inputs available or periodically, depending on your chosen reading policy.
    # The reading policy, as well as the period (if any), are set in RTMaps, in the component's properties.
    def Core(self):
        msg = rtmaps.types.Ioelt()
        msg.data = 'Hello World: %d' % self.i
        # Write the message to the "hello" output
        self.write("hello", msg)
        print('Publishing: "%s"' % msg.data)
        self.i = self.i + 1

    # Death() will be called once at diagram execution shutdown.
    def Death(self):
        pass