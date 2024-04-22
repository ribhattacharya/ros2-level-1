#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import (
    Int64,
)  # need to add this dependency in package.xml too


class NumberPublisher(Node):
    def __init__(self):
        super().__init__("number_publisher")

        self.publisher = self.create_publisher(Int64, "number", 10)
        self.timer = self.create_timer(0.5, self.publish_number)
        self.get_logger().info("Number publisher node has started!")

    def publish_number(self):
        msg = Int64()
        msg.data = 42
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)  # initialize ROS
    node = NumberPublisher()  # create node
    rclpy.spin(node)  # allows the node to run indefintely
    rclpy.shutdown()  # shutdown node


if __name__ == "__main__":
    main()
