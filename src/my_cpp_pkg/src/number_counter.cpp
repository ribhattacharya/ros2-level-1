#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include <string>

class NumberCounter : public rclcpp::Node
{
public:
    NumberCounter() : Node("number_counter")
    {
        __subscriber = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10, std::bind(&NumberCounter::callbackNumber, this, std::placeholders::_1));

        __publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        
        RCLCPP_INFO(this->get_logger(), "Number publisher node has started!");
    }

private:
    int __counter = 0;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr __publisher;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr __subscriber;

    void callbackNumber(const example_interfaces::msg::Int64 msg)
    {
        __counter++;
        RCLCPP_INFO(this->get_logger(), "Received %d, Count = %d", int(msg.data), __counter);

        auto countMsg = example_interfaces::msg::Int64();
        countMsg.data = __counter;
        __publisher->publish(countMsg);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>(); // Cpp nodes are created as shared pointer
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}