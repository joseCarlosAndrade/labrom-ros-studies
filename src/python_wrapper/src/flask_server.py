#!/usr/bin/env python


import rospy
from std_msgs.msg import String
from flask import Flask, jsonify, request
from Wrapper import Wrapper, Subscriber, Publisher

from threading import Thread
import signal, sys

class FlaskServer:
    def __init__(self):
        self.ros_wrapper = Wrapper(node=None, node_name="flask_server")
        FlaskServer.app = Flask(__name__)

        self.app.add_url_rule('/publish', view_func=self.publish_callback, methods=["POST"])

        self.flask_thread = None

    
    def initialize_publishers(self, topic_name : str):
        rospy.loginfo("Initializing publishers in topic: " + topic_name )

        test_publisher = Publisher("pub", topic_name, String, 10)
        self.ros_wrapper.addPublisher(test_publisher)
        

    def run(self): 
        try:
            signal.signal(signal.SIGINT, self.signal_handler)
            rospy.loginfo("Starting flask on port 9000")
            flask_thread = Thread(target=lambda: self.app.run(host='0.0.0.0', port=9000))
            flask_thread.start()

        except Exception as err :
            rospy.logerr("Could not spawn flask thread: ", err)


    def signal_handler(self, sig, frame): # this part i got from gpt!
        """Handle shutdown signals for graceful exit."""
        rospy.loginfo("Shutting down gracefully...")

        rospy.signal_shutdown("Shutting down")
        if self.flask_thread and self.flask_thread.is_alive():
            self.stop_flask()
        sys.exit(0)

    def publish_callback(self):
        data =  request.json
        rospy.loginfo("request received")

        if "msg" in data:
            msg = data["msg"]
            rosmsg = String()
            rosmsg.data = msg


            self.ros_wrapper.publishMessage("pub", rosmsg)
            rospy.loginfo("msg published. msg: "+ msg)

            return jsonify({"status" : "msg done!"}), 200
        else:
            rospy.logerr("msg not published. bad request")
            return jsonify({"status" : "bad request :("}), 400



if __name__ == "__main__":

    flask_server = FlaskServer()

    flask_server.initialize_publishers(topic_name="flask_topic")

    flask_server.run()
