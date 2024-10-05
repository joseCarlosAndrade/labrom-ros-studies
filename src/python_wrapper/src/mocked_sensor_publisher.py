#!/usr/bin/env python

from Wrapper import Wrapper, Subscriber, Publisher
from std_msgs.msg import String
import rospy
import random

def main(): 
    wrapper = Wrapper()

    sensor_publisher = Publisher("sensor", "mocked_sensor_data", String)

    wrapper.addPublisher(sensor_publisher)
    # wrapper.switch_debug_on()

    rate = rospy.Rate(5)

    while not rospy.is_shutdown():
        try:
            msg = String()
            
            msg.data = str(random.randint(0, 1000))
            try:
                rospy.loginfo("Publishing data to sensor: " + str(msg.data))
            except Exception as err:
                rospy.logwarn(err)
            wrapper.publishMessage("sensor", msg)
            
            rate.sleep()
        except Exception as err :
            rospy.logwarn(err)
    return

if __name__ == "__main__":
    main()