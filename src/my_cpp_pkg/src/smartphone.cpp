#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string>

class SmartphoneNode : public rclcpp::Node
{
public:
    SmartphoneNode() : Node("smartphone")
    {
        __subscriber = this->create_subscription<example_interfaces::msg::String>(
            "robot_news", 10, std::bind(&SmartphoneNode::callbackRobotNews, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "C++ Smartphone node has started!");
    }

private:
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr __subscriber;

    void callbackRobotNews(const example_interfaces::msg::String msg)
    {
        RCLCPP_INFO(this->get_logger(), msg.data.c_str());
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartphoneNode>(); // Cpp nodes are created as shared pointer
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}