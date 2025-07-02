# Migrating a ROS2 C++ Node to an RTMaps Component

This document and the corresponding code samples explain how to convert a C++ ROS2 publisher/subscriber node into equivalent RTMaps components using the
RTMaps C++ API.  
We use the example of a minimal publisher that emits a string periodically and a minimal subscriber that displays the string.

## 1. Migration Steps

### 1.1 Node/Class Definition

- Declare an RTMaps component class instead of a ROS2 node class. Your class inherits from `MAPSComponent`.
- Use RTMaps macros (`MAPS_BEGIN_INPUTS_DEFINITION`, etc.) to declare inputs, outputs, and properties.

### 1.2 Publisher/Output

- In ROS2: Use a publisher (`create_publisher`) for a topic.
- In RTMaps: Declare an output (`MAPS_OUTPUT`) to write messages. Note that outputs have a fixed size during a run, to avoid reallocations and maximize performance. This size needs to be hard-coded (like in the publisher example) or set before the first write to the output. Please refer to the RTMaps developer documentation for more information.

### 1.3 Subscriber/Input

- In ROS2: Use a subscriber (`create_subscription`) for a topic.
- In RTMaps: Declare an input (`MAPS_INPUT`) to receive messages.

### 1.4 Publisher Message Handling

- In ROS2: Create a `std_msgs::msg::String` message and publish it.
- In RTMaps: Prepare a plain `std::string`, then copy its buffer into the output buffer with `memcpy`.

### 1.5 Logic

- In ROS2: Use `topic_callback()` to call the logic for a subscriber, and a timer callback for a publisher.
- In RTMaps: The `Core()` method should call the logic. It is called in a spinning loop without wait between calls. As a consequence, the code in `Core()` is free to handle its timing. There are multiple ways to achieve this, including the following:
  - The most standard behavior is to run the logic when inputs receive data. This is done by calling the `Read()` method on an `InputReader`. This method is equivalent to the ROS `spin()` method. `Read()` will call your callback and provide the input data as argument. In the subscriber example, the callback is called `ProcessData()`.
  - You can also create a periodic component using the `Wait()` function and a period property.
  - Other blocking functions can also be used, such as network listening functions.

### 1.6 Logging

- In ROS2: Use `RCLCPP_INFO`.
- In RTMaps: Use RTMaps logging functions (`ReportInfo()`, `ReportWarning()`, `ReportError()`).

### 1.7 Initialization and Cleanup

- In ROS2: Node constructor initializes member variables.
- In RTMaps: Use `Birth()` for initialization and `Death()` for cleanup.

---

## 2. Key Differences

| Concept        | ROS2                    | RTMaps                    |
|----------------|-------------------------|---------------------------|
| Node/Component | `rclcpp::Node`          | `MAPSComponent`           |
| Publisher      | `create_publisher()`    | `MAPS_OUTPUT`             |
| Subscriber     | `create_subscription()` | `MAPS_INPUT`              |
| Message object | `std_msgs::msg::String` | `std::string`             |
| Initialization | Node constructor        | `Birth()`                 |
| Loop logic     | Callback, spin          | `Read()`, `ProcessData()` |
| Properties     | Manual variables/params | `MAPS_PROPERTY`           |

---

## 3. See examples

Examples are available in the current folder, see "minimal_publisher_cpp" and "minimal_subscriber_cpp". In order to build
the RTMaps package, call the following commands:

```console
mkdir build && cd build
export RTMAPS_SDKDIR=/opt/rtmaps
cmake ..
make -j4
```

---

## 4. References

- [ROS2 minimal example](https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)
- Input reader documentation: /opt/rtmaps/packages/rtmaps_input_reader/doc/README.html
- [Knowledge base](https://support.intempora.com/hc/en-us)

---