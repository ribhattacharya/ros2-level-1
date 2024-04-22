#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string>

class RobotNewsStationNode : public rclcpp::Node
{
public:
    RobotNewsStationNode() : Node("robot_news_station")
    {
        __publisher = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        __timer = this->create_wall_timer(std::chrono::milliseconds(500),
                                          std::bind(&RobotNewsStationNode::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "C++ Robot News Station node has started!");
    }

private:
    rclcpp::TimerBase::SharedPtr __timer;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr __publisher;

    void publishNews()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = "Hello from C++ Robot News Station publisher!";
        __publisher->publish(msg);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); // Cpp nodes are created as shared pointer
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}