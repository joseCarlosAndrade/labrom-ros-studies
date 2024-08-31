#!/usr/bin/env python

from Wrapper import Wrapper, Subscriber, Publisher
from std_msgs.msg import String
import rospy

def my_callback(data):
    rospy.loginfo(data.data)

def main():
    wrapper = Wrapper()
    sub = Subscriber("first_sub", "msg", String, my_callback)
    pub = Publisher("first_pub", "msg", String, 10)

    wrapper.addSubscriber(sub)
    wrapper.addPublisher(pub)

    wrapper.initSubscriber("first_sub")
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        msg = String()
        msg.data = "heloo"
        wrapper.publishMessage("first_pub", msg)
        rate.sleep()

if __name__ == "__main__" :
    main()