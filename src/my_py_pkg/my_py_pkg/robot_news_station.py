#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import (
    String,
)  # need to add this dependency in package.xml too


class RobotNewsStationNode(Node):
    def __init__(self):
        super().__init__("robot_news_station")

        self.publisher = self.create_publisher(String, "robot_news", 10)
        self.timer = self.create_timer(1, self.publish_news)
        self.get_logger().info("Python Robot News Station node has started!")

    def publish_news(self):
        msg = String()
        msg.data = "Hello from Python Robot News Station publisher!"
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)  # initialize ROS
    node = RobotNewsStationNode()  # create node
    rclpy.spin(node)  # allows the node to run indefintely
    rclpy.shutdown()  # shutdown node


if __name__ == "__main__":
    main()
