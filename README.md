# ROS2 for beginners <!-- omit in toc -->
[Udemy course link](https://www.udemy.com/course/ros2-for-beginners/?couponCode=ST7MT41824)

NOTE: Build files are not uploaded to this repository. To run anything, go to `ros_ws` and type `colcon build`.


- [1. Environment setup](#1-environment-setup)
- [2. Create workspace](#2-create-workspace)
- [3. Create custom package](#3-create-custom-package)
  - [3.1. Python](#31-python)
  - [3.2. C++](#32-c)
  - [3.3. Build custom package](#33-build-custom-package)
- [4. Nodes](#4-nodes)
  - [4.1. Python](#41-python)
  - [4.2. C++](#42-c)

## 1. Environment setup
1. To automatically source ROS in a new terminal
        
        echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

2. To install colcon build tools and add it to source automatically
   
        sudo apt install python3-colcon-common-extensions
        echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc
    
## 2. Create workspace
        mkdir -p ros2_ws/src/
        cd ros2_ws/
        colcon build

        echo "source /home/rishabh/Documents/ros2_ws/install/setup.bash" >> ~/.bashrc

## 3. Create custom package
`rcl` (ROS2 Client Library) is the base ROS2 library. It is used by python, c++ to interact with ROS2 and use its features. Specialized versions are used by each programming language (`rclpy`, `rclcpp`, etc.)

### 3.1. Python

        cd ros2_ws/src/
        ros2 pkg create [PACKAGE_NAME] --build-type ament_python --dependencies rclpy

`rclpy` is what enables python to use ROS2 features.

### 3.2. C++

        cd ros2_ws/src/
        ros2 pkg create [PACKAGE_NAME] --build-type ament_cmake --dependencies rclcpp

`rclcpp` is what enables C++ to use ROS2 features.

### 3.3. Build custom package

        cd ros2_ws/
        colcon build    // to build all packages
        colcon build --packages-select [PACKAGE_NAME]   // specific packages

## 4. Nodes
### 4.1. Python
Create the node file inside `src/[PACKAGE_NAME]/[PACKAGE_NAME]` ([Sample python node](src/my_py_pkg/my_py_pkg/my_first_node.py)).

        chmod +x [YOUR_NODE_PATH]
        ./[YOUR_NODE_PATH]

But this is not scalable for larger projects. We can make this node an executable in our project and call it from `ros run`. Modify the following in the `src/[PACKAGE_NAME]/setup.py` [file](src/my_py_pkg/setup.py).

        ...
        ...
        entry_points={
            'console_scripts': [
                "py_node = [PACKAGE_NAME].[NODE_FILE_NAME]:main"
            ]
        }

Then after building the changes,

        colcon build

This will create the `py_node` file in `install/my_py_pkg/lib/my_py_pkg/`, which can be run from there.

        cd [PATH_TO_WORKSPACE]/install/my_py_pkg/lib/my_py_pkg/
        ./py_node

Another way (much simpler and intuitive) to run the node is

        ros2 run my_py_pkg py_node

NOTE: The name of the node file (python file - `my_first_node`), the name of the node (inside the python file - `py_test`) and the name of the executable - `py_node` can be 3 different names for the same thing.

### 4.2. C++
Create the node file in the `src/[PACKAGE_NAME]/src` directory. You migh also need to add the ros cpp include path in your editor settings. For VSCode, add this in the `c_cpp_properties.json` file under `includePath`


        "/opt/ros/humble/include/**"

Then make the following additions to the CMakeLists.txt file,

        add_executable(cpp_node src/my_first_node.cpp)
        ament_target_dependencies(cpp_node rclcpp)

        install(TARGETS cpp_node DESTINATION lib/${PROJECT_NAME})

Steps to execute the `cpp_node` are similar as in the section above. 