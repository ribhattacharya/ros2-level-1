#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import (
    String,
)  # need to add this dependency in package.xml too


class SmartphoneNode(Node):
    def __init__(self):
        super().__init__("smartphone")

        self.subcriber = self.create_subscription(
            String, "robot_news", self.callback_robot_news, 10
        )
        self.get_logger().info("Python Smartphone node has started!")

    def callback_robot_news(self, msg: String):
        self.get_logger().info(msg.data)


def main(args=None):
    rclpy.init(args=args)  # initialize ROS
    node = SmartphoneNode()  # create node
    rclpy.spin(node)  # allows the node to run indefintely
    rclpy.shutdown()  # shutdown node


if __name__ == "__main__":
    main()
