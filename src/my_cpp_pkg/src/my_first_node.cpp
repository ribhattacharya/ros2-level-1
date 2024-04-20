#include "rclcpp/rclcpp.hpp"
#include <string>

class MyNode : public rclcpp::Node
{
public:
    MyNode(std::string nodeName) : Node(nodeName)
    {
        RCLCPP_INFO(this->get_logger(), "CPP node created!");
        _timer = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&MyNode::timerCallback, this));
    }

private:
    int counter = 0;
    rclcpp::TimerBase::SharedPtr _timer;

    void timerCallback()
    {
        counter++;
        RCLCPP_INFO(this->get_logger(), "Hello from cpp node %d!", counter);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>("cpp_test"); // Cpp nodes are created as shared pointer
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}