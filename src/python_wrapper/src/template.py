#!/usr/bin/env python

from Wrapper import Wrapper, Subscriber, Publisher
from std_msgs.msg import String
import rospy

"""This is a template file to follow to create a simple publisher and subscriber with the ROS wrapper
"""
def my_callback(data):
    rospy.loginfo(data.data)

def main():
    # init wrapper (its possible to pass as arg an already made node, if wanted. If not, it will create a default node)
    # note: the node used in this wrapper is static, which means that wherever Wrapper is used, it will use the same node.
    # with that being said, theres no need to create multiple nodes accross the same application when using this wrapper, if wanted
    wrapper = Wrapper()

    # the wrapper provides Subscriber and Publisher, to simplify the creation and handling of those features
    # obs: the wrapper manages them by the name passed as arg, NOT BY THE TOPIC IT PUBLISHES/LISTENS!
    sub = Subscriber("first_sub", "msg", String, my_callback)
    pub = Publisher("first_pub", "msg", String, 10)

    # adding them to the wrapper
    wrapper.addSubscriber(sub)
    wrapper.addPublisher(pub)

    # since subscribers handles callbacks, you have to initialize them here (BY THE NAME WHEN CREATED, NOT TOPIC)
    # this is done to avoid executing the callback before the intended moment 
    wrapper.initSubscriber("first_sub")

    # default ros behavior
    rate = rospy.Rate(10)
    
    while not rospy.is_shutdown():
        msg = String()
        msg.data = "heloo"
    
        # method to actually publish a message there
        wrapper.publishMessage("first_pub", msg)
        rate.sleep()

if __name__ == "__main__" :
    main()