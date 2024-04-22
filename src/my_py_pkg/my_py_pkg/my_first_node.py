#!/usr/bin/env python3
import rclpy
from rclpy.node import Node


class MyNode(Node):
    def __init__(self):
        super().__init__("py_test")

        self.counter = 0
        self.get_logger().info("MyNode created.")
        self.create_timer(1, self.timer_callback)

    def timer_callback(self):
        self.counter += 1
        self.get_logger().info(f"Hello from MyNode: {self.counter}")


def main(args=None):
    rclpy.init(args=args)  # initialize ROS
    node = MyNode()  # create node
    rclpy.spin(node)  # allows the node to run indefintely
    rclpy.shutdown()  # shutdown node


if __name__ == "__main__":
    main()
