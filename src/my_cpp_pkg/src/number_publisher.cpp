#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include <string>

class NumberPublisher : public rclcpp::Node
{
public:
    NumberPublisher() : Node("number_publisher")
    {
        __publisher = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        __timer = this->create_wall_timer(std::chrono::milliseconds(500),
                                          std::bind(&NumberPublisher::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "");
    }

private:
    rclcpp::TimerBase::SharedPtr __timer;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr __publisher;

    void publishNews()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = 42;
        __publisher->publish(msg);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>(); // Cpp nodes are created as shared pointer
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}