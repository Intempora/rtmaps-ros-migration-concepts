# Migrating a ROS2 Python Node to an RTMaps Component

This folder explains how to convert a Python ROS2 publisher/subscriber node into equivalent RTMaps components using the
RTMaps Python API and the Python Bridge RTMaps component.
We use the example of a minimal publisher that emits a string periodically and a minimal subscriber that displays the string.

## 1. Migration Steps

### 1.1 Node/Class Definition

- Declare a class inheriting from `BaseComponent` instead of the ROS2 `Node`.
- Declare your inputs, outputs, and properties, in the `Dynamic` method.

### 1.2 Publisher/Output

- In ROS2: Use a publisher (`create_publisher`) for a topic.
- In RTMaps: Declare an output (`self.add_output` in the `Dynamic` method) to write messages.

### 1.3 Subscriber/Input

- In ROS2: Use a subscriber (`create_subscription`) for a topic.
- In RTMaps: Declare an input (`self.add_input` in the Dynamic method) to receive messages.

### 1.4 Publisher Message Handling

- In ROS2: Create a `String` message and publish it.
- In RTMaps: Create an `Ioelt` ("input/output element") and write to its `data` field.

### 1.5 Logic

- In ROS2: Use `topic_callback()` to call the logic for a subscriber, and a timer callback for a publisher.
- In RTMaps: Call the logic from the `Core()` method. This method is called by RTMaps when inputs are available or periodically, depending on the Reading Policy set on the Python Bridge component.

### 1.6 Logging

- In ROS2: Use `self.get_logger().info()`.
- In RTMaps: `print` is redirected to the RTMaps console. You can also use `rt.report_warning`, `rt.report_error` to print text in yellow or red.

### 1.7 Initialization and Cleanup

- In ROS2: Node constructor initializes member variables.
- In RTMaps: Use `Birth()` for initialization and `Death()` for cleanup.

---

## 2. Key Differences

| Concept        | ROS2                    | RTMaps                |
|----------------|-------------------------|---------------------  |
| Node/Component | `Node`                  | `BaseComponent`       |
| Publisher      | `create_publisher()`    | `self.add_output()`   |
| Subscriber     | `create_subscription()` | `self.add_input()`    |
| Initialization | Node constructor        | `Birth()`             |
| Loop logic     | Callback, spin          | `Core()`              |
| Properties     | Manual variables/params | `self.add_property()` |

---

## 3. Running the code

Python code is run in RTMaps using the Python Bridge component as follows:

- Open RTMaps Studio.
- Register the rtmaps_python_bridge.pck package from the Explorer view in the bottom left.
- In the top left Registered Components view, open rtmaps_python_bridge.pck and drag and drop the Python Bridge component onto the diagram.
- Click the newly created component.
- In the Properties view, set the Python Filename to the Python file you want to run (the small button to the right of the property opens an explorer).
- In the Properties view, you can also change the Reading Policy. "Sampling" is a periodic execution. This is suitable for a generator like the simple publisher here. When components have inputs, it is recommended to use the other Reading Policies, that run the code when one or multiple inputs have received data.
- Add more components and connect them as needed. You can connect the publisher and the subscriber together.
- You can now run your application by clicking the run icon in the top toolbar. This icon looks like a remote control on/off button logo.

---

## 4. References

- [ROS2 minimal example](https://docs.ros.org/en/jazzy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Py-Publisher-And-Subscriber.html)
- [Video: How to use the Python Bridge](https://www.youtube.com/watch?v=puSqEpnDANs)
- Python Bridge documentation: /opt/rtmaps/packages/rtmaps_python_bridge/doc/rtmaps_python_bridge.pdf
- [Knowledge base](https://support.intempora.com/hc/en-us)

---